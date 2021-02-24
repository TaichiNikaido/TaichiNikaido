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
#include "enemy_bomb_head.h"
#include "player.h"
#include "bullet_direction.h"
#include "bullet.h"
#include "explosion_death.h"
#include "item_bomb.h"
#include "enemy_bomb_body.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/bombhead.png")	//テクスチャ
#define SIZE (D3DXVECTOR3(100.0f,150.0f,0.0f))		//サイズ
#define MINIMUM_LIFE (0)							//体力の最小値
#define LIFE (12)									//体力
#define MOVE (D3DXVECTOR3(5.0f,0.0f,0.0f))			//移動量		
#define SCORE (10000)								//スコア
#define MINIMUM_RADIAN (0.0f)						//ラジアンの最小値
#define MINIMUM_ADD_RADIAN (0.1f);					//ラジアンの加算量
#define MINIMUM_CREATE_TIME (0)						//生成される間隔の時間最小値
#define CREATE_TIME (15)							//生成される間隔の時間
#define MINIMUM_CREATE_BODY_COUNT (0)				//生成した体の数の最小値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyBombHead::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyBombHead::CEnemyBombHead()
{
	memset(m_pBombBody, NULL, sizeof(m_pBombBody));		//爆弾敵の体のポインタ
	m_InitialPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//初期位置		
	m_nCreateTime = MINIMUM_CREATE_TIME;				//生成する時間	
	m_nCreateBodyCount = MINIMUM_CREATE_BODY_COUNT;		//生成した体の数		
	m_nBombLife = LIFE;									//全体の体力					
	m_fRadian = MINIMUM_RADIAN;							//ラジアン		
	m_fAddRadian = MINIMUM_ADD_RADIAN;					//ラジアンの加算量		
	m_bCreateBody = true;								//体を生成したか		
	m_bDeath = false;									//死んだか		
	m_bDeathAll = false;								//全て死んだか		
}															

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyBombHead::~CEnemyBombHead()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CEnemyBombHead::TextureLoad(void)
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
void CEnemyBombHead::TextureUnload(void)
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
CEnemyBombHead * CEnemyBombHead::Create(D3DXVECTOR3 Position)
{
	//爆弾敵の頭のポインタ
	CEnemyBombHead * pEnemyBombHead = NULL;
	//爆弾敵の頭のポインタがNULLの場合
	if (pEnemyBombHead == NULL)
	{
		//爆弾敵の頭のメモリ確保
		pEnemyBombHead = new CEnemyBombHead;
		//爆弾敵の頭のポインタがNULLじゃない場合
		if (pEnemyBombHead != NULL)
		{
			//位置を設定する
			pEnemyBombHead->SetPosition(Position);
			//初期位置を設定する
			pEnemyBombHead->m_InitialPosition = Position;
			//初期化処理関数呼び出し
			pEnemyBombHead->Init();
		}
	}
	//爆弾敵の頭のポインタを返す
	return pEnemyBombHead;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEnemyBombHead::Init(void)
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
void CEnemyBombHead::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CEnemyBombHead::Update(void)
{
	//もし体が生成されたら
	if (m_bCreateBody == true)
	{
		//生成数を加算るう
		m_nCreateTime++;
		//もし生成される時間になったら
		if (m_nCreateTime % CREATE_TIME == REMAINDER)
		{
			//体を生成する
			m_pBombBody[m_nCreateBodyCount] = CEnemyBombBody::Create(m_InitialPosition, this);
			//体の生成数を加算する
			m_nCreateBodyCount++;
			//もし体の生成数が最大数になったら
			if (m_nCreateBodyCount >= MAX_BOMB_BODY)
			{
				//体の生成をやめる
				m_bCreateBody = false;
			}
		}
	}
	//ラジアンを加算する
	m_fRadian += m_fAddRadian;
	//もし一周したら
	if (m_fRadian >= 360.0f)
	{
		//ラジアンを0にする
		m_fRadian = MINIMUM_RADIAN;
	}
	//移動量のセット
	SetMove(D3DXVECTOR3(GetMove().x, float(5 * sin(m_fRadian)), GetMove().z));
	//画面端についたら逆方向に
	if (GetPosition().x < FIELD_WIDTH_MIN + 10.0f)
	{
		//移動量を設定する
		SetMove(D3DXVECTOR3(GetMove().x * -1.0f, GetMove().y, GetMove().z));
		//ラジアンを反転させる
		m_fAddRadian = m_fAddRadian * -1.0f;
	}
	//画面端についたら逆方向に
	if (GetPosition().x > FIELD_WIDTH - 10.0f)
	{
		//移動量を設定する
		SetMove(D3DXVECTOR3(GetMove().x * -1.0f, GetMove().y, GetMove().z));
		//ラジアンを反転させる
		m_fAddRadian = m_fAddRadian * -1.0f;
	}
	//進行方向に向きを合わせる
	SetRotation(D3DXVECTOR3(GetRotation().x, GetRotation().y, atan2f((GetPosition().x + GetMove().x) - GetPosition().x, (GetPosition().y + GetMove().y) - GetPosition().y)));
	//敵の更新処理関数呼び出し
	CEnemy::Update();
	//もしライフが0になったら
	if (GetLife() <= MINIMUM_LIFE)
	{
		//もし死んでいなかったら
		if (m_bDeath == false)
		{
			//死亡処理関数呼び出し
			Death();
			return;
		}
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CEnemyBombHead::Draw(void)
{
	//敵の描画処理関数呼び出し
	CEnemy::Draw();
}
//=============================================================================
// 全体死亡処理関数
//=============================================================================
void CEnemyBombHead::DeathAll(void)
{
	//もし死んでなくかつ全部死んでなかったら
	if (m_bDeathAll == false && m_bDeath == false)
	{
		//全部殺す
		m_bDeathAll = true;
		//体の最大数分回す
		for (int nCount = 0; nCount < MAX_BOMB_BODY; nCount++)
		{
			//もし爆弾敵の体のポインタがNULLじゃない場合
			if (m_pBombBody[nCount] != NULL)
			{
				//爆発エフェクトの生成
				CExplosionDeath::Create(m_pBombBody[nCount]->GetPosition(), EXPLOSION_SIZE);
				//爆弾敵の体の終了処理関数呼び出し
				m_pBombBody[nCount]->Uninit();
			}
		}
		//終了処理関数呼び出し
		Uninit();
	}
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CEnemyBombHead::Death(void)
{
		//プレイヤーを取得する
		CPlayer * pPlayer = CGameMode::GetPlayer();
		//サウンドの取得
		CSound * pSound = CManager::GetSound();
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
			//爆弾アイテムの生成
			CItemBomb::Create(GetPosition());
			//プレイヤーのスコアを加算する
			pPlayer->AddScore(SCORE);
			//全体死亡処理関数呼び出し
			DeathAll();
			//殺す
			m_bDeath = true;
		}
}