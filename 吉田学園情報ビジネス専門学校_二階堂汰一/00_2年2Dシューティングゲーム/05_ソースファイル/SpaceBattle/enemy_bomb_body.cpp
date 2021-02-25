//=============================================================================
//
// 爆弾の敵の胴体 [enemy_bomb_body.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "mode_game.h"
#include "renderer.h"
#include "scene2d.h"
#include "enemy_bomb_body.h"
#include "enemy_bomb_head.h"
#include "player.h"
#include "bullet_direction.h"
#include "bullet.h"
#include "explosion_death.h"
#include "item.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/bombbody.png")	//テクスチャ
#define SIZE (D3DXVECTOR3(100.0f,150.0f,0.0f))		//サイズ7
#define MINIMUM_LIFE (0)							//体力の最小値
#define LIFE (12)									//体力
#define MOVE (D3DXVECTOR3(5.0f,0.0f,0.0f))			//移動量		
#define SCORE (10000)								//スコア
#define MINIMUM_RADIAN (0.0f)						//ラジアンの最小値
#define ADD_RADIAN (0.1f)							//ラジアンの加算量

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyBombBody::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyBombBody::CEnemyBombBody(int nPriority) : CEnemy(nPriority)
{
	m_pBombHead = NULL;				//爆弾の敵の頭のポインタ
	m_fRadian = MINIMUM_RADIAN;		//ラジアン
	m_fAddRadian = ADD_RADIAN;		//ラジアンの加算量
	m_bDeath = false;				//死んだかどうか
}							

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyBombBody::~CEnemyBombBody()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CEnemyBombBody::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE,						// ファイルの名前
		&m_pTexture);					// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CEnemyBombBody::TextureUnload(void)
{
	//もしテクスチャがNULLじゃない場合
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャをNULLにする
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CEnemyBombBody * CEnemyBombBody::Create(D3DXVECTOR3 Position, CEnemyBombHead * pHead)
{
	//爆弾敵の体のポインタ
	CEnemyBombBody * pEnemyBombBody = NULL;
	//もし爆弾敵の体のポインタがNULLの場合
	if (pEnemyBombBody == NULL)
	{
		//爆弾敵の体のメモリ確保
		pEnemyBombBody = new CEnemyBombBody;
		//もし爆弾敵の体のポインタがNULLじゃない場合
		if (pEnemyBombBody != NULL)
		{
			//位置を設定す
			pEnemyBombBody->SetPosition(Position);
			//爆弾敵の頭のポインタ
			pEnemyBombBody->m_pBombHead = pHead;
			//初期化処理関数呼び出し
			pEnemyBombBody->Init();
		}
	}
	//爆弾敵の体のポインタを返す
	return pEnemyBombBody;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEnemyBombBody::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//敵の初期化処理関数呼び出し
	CEnemy::Init();
	//サイズの初期設定
	SetSize(SIZE);
	//体力の初期設定
	SetLife(LIFE);
	//移動量の初期設定
	SetMove(MOVE);
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	//状態を移動中
	SetState(STATE_MOVE);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CEnemyBombBody::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CEnemyBombBody::Update(void)
{
	//ラジアンを加算する
	m_fRadian += m_fAddRadian;
	//もし一周したtら
	if (m_fRadian >= 360.0f)
	{
		//ラジアンを0にする
		m_fRadian = MINIMUM_RADIAN;
	}
	//移動量の設定
	SetMove(D3DXVECTOR3(GetMove().x,float(5 * sin(m_fRadian)),GetMove().z));
	//画面端についたら逆方向に
	if (GetPosition().x < FIELD_WIDTH_MIN + 10.0f)
	{
		//移動量の設定
		SetMove(D3DXVECTOR3(GetMove().x * -1.0f, GetMove().y, GetMove().z));
		//ラジアンを反転させる
		m_fAddRadian = m_fAddRadian * -1.0f;
	}
	if (GetPosition().x > FIELD_WIDTH - 10.0f)
	{
		//移動量の設定
		SetMove(D3DXVECTOR3(GetMove().x * -1.0f, GetMove().y, GetMove().z));
		//ラジアンを反転させる
		m_fAddRadian = m_fAddRadian * -1.0f;
	}
	//進行方向に向きを合わせる
	SetRotation(D3DXVECTOR3(GetRotation().x, GetRotation().y,atan2f((GetPosition().x + GetMove().x) - GetPosition().x, (GetPosition().y + GetMove().y) - GetPosition().y)));
	//敵の更新処理関数呼び出し
	CEnemy::Update();
	//もしライフが0になったら
	if (GetLife() <= MINIMUM_LIFE)
	{
		//死亡処理関数呼び出し
		Death();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CEnemyBombBody::Draw(void)
{
	//敵の描画処理関数呼び出し
	CEnemy::Draw();
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CEnemyBombBody::Death(void)
{
	//もし死んでいなかったら
	if (m_bDeath == false)
	{
		//プレイヤーを取得する
		CPlayer * pPlayer = CGameMode::GetPlayer();
		//サウンドの取得
		CSound * pSound = CManager::GetSound();
		//もしプレイヤーのポインタがNULLじゃない場合
		if (pPlayer != NULL)
		{
			//爆発エフェクトの生成
			CExplosionDeath::Create(GetPosition(), EXPLOSION_SIZE);
			//もしサウンドがNULLじゃない場合
			if (pSound != NULL)
			{
				//爆発音の再生
				pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
			}
			//プレイヤーのスコアを加算する
			pPlayer->AddScore(SCORE);
			//全部殺す
			m_pBombHead->DeathAll();
			//死亡状態にする
			m_bDeath = true;
		}
	}
}