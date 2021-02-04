//=============================================================================
//
// 花 [enemy_flower.cpp]
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
#include "enemy_flower.h"
#include "player.h"
#include "bullet.h"
#include "item_life.h"
#include "explosion_death.h"
#include "bullet_flower.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/flower.png")
#define SIZE (D3DXVECTOR3(100.0f,100.0f,0.0f))
#define LIFE (13)
#define SCORE (50000)
#define SPEED (D3DXVECTOR3(0.0f,5.0f,0.0f))
#define RATE_MOVE (0.03f)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyFlower::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyFlower::CEnemyFlower(int nPriority)
{
	m_nCounterAnime = 0;					//アニメカウンタ
	m_nPatternAnime = 0;					//アニメパターン
	m_nBulletTime = 0;						//弾の発射間隔
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyFlower::~CEnemyFlower()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CEnemyFlower::TextureLoad(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
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
void CEnemyFlower::TextureUnload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CEnemyFlower * CEnemyFlower::Create(D3DXVECTOR3 Position)
{
	CEnemyFlower * pEnemyFlower;
	pEnemyFlower = new CEnemyFlower;
	pEnemyFlower->SetPosition(Position);
	pEnemyFlower->Init();
	return pEnemyFlower;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEnemyFlower::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.250f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.250f * m_nPatternAnime + 0.250f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.250f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.250f * m_nPatternAnime + 0.250f, 1.0f);
	//敵の初期化処理関数呼び出し
	CEnemy::Init();
	//サイズの初期設定
	SetSize(SIZE);
	//体力の初期設定
	SetLife(LIFE);
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
void CEnemyFlower::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CEnemyFlower::Update(void)
{
	//敵の更新処理関数呼び出し
	CEnemy::Update();
	//攻撃処理関数呼び出し
	if (GetState() != STATE_MOVE)
	{
		Attack();
	}
	//もしライフが0になったら
	if (GetLife() <= 0)
	{
		//死亡処理関数呼び出し
		Death();
	}
	//アニメーション処理関数呼び出し
	Animation();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CEnemyFlower::Draw(void)
{
	//敵の描画処理関数呼び出し
	CEnemy::Draw();
}

//=============================================================================
// 攻撃処理関数
//=============================================================================
void CEnemyFlower::Attack(void)
{
	//プレイヤーを取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		//もしプレイヤーの状態が死亡状態じゃないとき
		if (pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			//弾を発射するまでの時間
			if (m_nBulletTime >= 50)
			{
				if (m_nBulletTime % 20 == 0)
				{

				}
			}
		}
		//弾を発射するまでの時間を加算する
		m_nBulletTime++;
	}
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CEnemyFlower::Death(void)
{
	//プレイヤーを取得する
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	if (pPlayer != NULL)
	{
		//爆発エフェクトの生成
		CExplosionDeath::Create(GetPosition());
		//爆発音の再生
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
		//プレイヤーのスコアを加算する
		pPlayer->AddScore(SCORE);
	}
	//ドロップ処理関数呼び出し
	Drop();
	//終了処理関数呼び出し
	Uninit();
	return;
}

//=============================================================================
// ドロップ処理関数
//=============================================================================
void CEnemyFlower::Drop(void)
{
	//体力回復アイテムを落とす
	CItemLife::Create(GetPosition());
}

//=============================================================================
// アニメーション処理関数
//=============================================================================
void CEnemyFlower::Animation(void)
{
	//カウントインクリメント
	m_nCounterAnime++;
	//カウントが4以上になった場合
	if (m_nCounterAnime > 16)
	{
		//カウントを0にする
		m_nCounterAnime = 0;

		//パターンのインクリメント
		m_nPatternAnime++;
	}
	//アニメーションのカウントを進める
	m_nCounterAnime++;
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.250f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.250f * m_nPatternAnime + 0.250f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.250f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.250f * m_nPatternAnime + 0.250f, 1.0f);
	//テクスチャの設定
	SetTexture(aTexture);
}
