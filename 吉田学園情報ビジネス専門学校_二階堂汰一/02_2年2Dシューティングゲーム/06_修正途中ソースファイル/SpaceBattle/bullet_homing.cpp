//=============================================================================
//
// ホーミング弾 [bullet_horming.cpp]
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
#include "player.h"
#include "bullet_homing.h"
#include "bullet.h"
#include "effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/bullet.png")
#define SIZE (D3DXVECTOR3(10.0f,10.0f,0.0f))
#define COLOR (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define LIFE (150)
#define SPEED (5.0f)
#define EFFECT_LIFE (7)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletHoming::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBulletHoming::CBulletHoming(int nPriority) : CBulletEnemy(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBulletHoming::~CBulletHoming()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBulletHoming::TextureLoad(void)
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
void CBulletHoming::TextureUnload(void)
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
CBulletHoming * CBulletHoming::Create(D3DXVECTOR3 Position)
{
	CBulletHoming * pBulletHoming;
	pBulletHoming = new CBulletHoming;
	pBulletHoming->Init();
	pBulletHoming->SetPosition(Position);
	return pBulletHoming;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBulletHoming::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//敵の初期化処理関数呼び出し
	CBulletEnemy::Init();
	//サイズの初期設定
	SetSize(SIZE);
	//色の初期設定
	SetColor(COLOR);
	//体力の設定
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
void CBulletHoming::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CBulletEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBulletHoming::Update(void)
{
	//敵の更新処理関数呼び出し
	CBulletEnemy::Update();
	//追尾処理関数呼び出し
	Homing();
	//エフェクトの生成
	CEffect::Create(GetPosition(), GetSize(), GetColor(), EFFECT_LIFE);
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
void CBulletHoming::Draw(void)
{
	//敵の描画処理関数呼び出し
	CBulletEnemy::Draw();
}

//=============================================================================
// 追尾処理関数
//=============================================================================
void CBulletHoming::Homing(void)
{
	//プレイヤー取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		//目標の位置を取得
		D3DXVECTOR3 TargetPosition = pPlayer->GetPosition();
		//位置を取得
		D3DXVECTOR3 Position = GetPosition();
		//移動量を取得
		D3DXVECTOR3 Move = GetMove();
		//目標との距離
		float m_fDistance = float(sqrt((TargetPosition.x - Position.x) * (TargetPosition.x - Position.x) + (TargetPosition.y - Position.y) * (TargetPosition.y - Position.y)));
		if (m_fDistance)
		{
			Move.x = ((TargetPosition.x - GetPosition().x) / m_fDistance * SPEED);
			Move.y = ((TargetPosition.y - GetPosition().y) / m_fDistance * SPEED);
		}
		else
		{
			Move.x = 0;
			Move.y = SPEED;
		}
		//移動量を設定する
		SetMove(Move);
	}
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CBulletHoming::Death(void)
{
	//終了処理関数呼び出し
	Uninit();
	return;
}
