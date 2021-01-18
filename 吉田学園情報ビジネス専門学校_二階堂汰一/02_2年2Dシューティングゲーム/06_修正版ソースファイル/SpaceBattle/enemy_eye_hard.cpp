//=============================================================================
//
// 目玉(ハード) [enemy_eye_hard.cpp]
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
#include "mode_game.h"
#include "renderer.h"
#include "scene2d.h"
#include "enemy_eye_hard.h"
#include "bullet_homing.h"
#include "player.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/eye_hard.png")
#define SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))
#define LIFE (3)
#define SCORE (10000)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyEyeHard::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyEyeHard::CEnemyEyeHard(int nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyEyeHard::~CEnemyEyeHard()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CEnemyEyeHard::TextureLoad(void)
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
void CEnemyEyeHard::TextureUnload(void)
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
CEnemyEyeHard * CEnemyEyeHard::Create(D3DXVECTOR3 Position)
{
	CEnemyEyeHard * pEnemyEyeHard;
	pEnemyEyeHard = new CEnemyEyeHard;
	pEnemyEyeHard->Init();
	pEnemyEyeHard->SetPosition(Position);
	return pEnemyEyeHard;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEnemyEyeHard::Init(void)
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
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CEnemyEyeHard::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CEnemyEyeHard::Update(void)
{
	//敵の更新処理関数呼び出し
	CEnemy::Update();
	//もしライフが0になったら
	if (GetLife() <= 0)
	{
		//死亡処理関数呼び出し
		Death();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CEnemyEyeHard::Draw(void)
{
	//敵の描画処理関数呼び出し
	CEnemy::Draw();
}

//=============================================================================
// 攻撃処理関数
//=============================================================================
void CEnemyEyeHard::Attack(void)
{
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CEnemyEyeHard::Death(void)
{
	//プレイヤーを取得する
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		//プレイヤーのスコアを加算する
		pPlayer->AddScore(SCORE);
	}
	//終了処理関数呼び出し
	Uninit();
	return;
}
