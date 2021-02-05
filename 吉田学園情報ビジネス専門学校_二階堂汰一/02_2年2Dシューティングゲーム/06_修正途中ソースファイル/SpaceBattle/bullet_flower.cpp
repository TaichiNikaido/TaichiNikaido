//=============================================================================
//
// 花弾 [bullet_flower.cpp]
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
#include "renderer.h"
#include "scene2d.h"
#include "mode_game.h"
#include "bullet_flower.h"
#include "bullet.h"
#include "player.h"
#include "bullet_flower.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/bullet_flower.png")
#define SIZE (D3DXVECTOR3(40.0f,40.0f,0.0f))
#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define LIFE (1500)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletFlower::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBulletFlower::CBulletFlower(int nPriority) : CBulletEnemy(nPriority)
{
	m_ColorNumber = COLOR_NUMBER_NONE;	//色の番号
	m_nTime = 0;						//時間
}

//=============================================================================
// デストラクタ
//=============================================================================
CBulletFlower::~CBulletFlower()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBulletFlower::TextureLoad(void)
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
void CBulletFlower::TextureUnload(void)
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
CBulletFlower * CBulletFlower::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed, COLOR_NUMBER nColor)
{
	CBulletFlower * pBulletFlower;
	pBulletFlower = new CBulletFlower;
	pBulletFlower->SetPosition(Position);
	pBulletFlower->SetMove(Speed);
	pBulletFlower->m_ColorNumber = nColor;
	pBulletFlower->Init();
	return pBulletFlower;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBulletFlower::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_ColorNumber * 0.1428f, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_ColorNumber * 0.1428f + 0.1428f, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_ColorNumber * 0.1428f, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_ColorNumber * 0.1428f + 0.1428f, 1.0f);
	//敵の弾の初期化処理関数呼び出し
	CBulletEnemy::Init();
	//サイズの設定
	SetSize(SIZE);
	//色の初期設定
	SetColor(COLOR);
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
void CBulletFlower::Uninit(void)
{
	//敵の弾の終了処理関数呼び出し
	CBulletEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBulletFlower::Update(void)
{
	CBulletEnemy::Update();
	//移動処理関数呼び出し
	Move();
	//色選択処理関数呼び出し
	ColorSelect();
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
void CBulletFlower::Draw(void)
{
	//敵の描画処理関数呼び出し
	CBulletEnemy::Draw();
}

//=============================================================================
// 移動処理関数
//=============================================================================
void CBulletFlower::Move(void)
{
	//位置を取得
	D3DXVECTOR3 Position = GetPosition();
	//向きを取得
	D3DXVECTOR3 Rotaion = GetRotation();
	//移動量を取得
	D3DXVECTOR3 Move = GetMove();
	//プレイヤーを取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		if (m_nTime == 80)
		{
			//プレイヤーの位置を取得
			D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
			//プレイヤーまでの距離を求める
			D3DXVECTOR3 TargetDistance = D3DXVECTOR3(PlayerPosition.x - Position.x, PlayerPosition.y - Position.y, 0.0f);
			Rotaion.y = float(atan2(TargetDistance.y, TargetDistance.x));
			Move = D3DXVECTOR3(cosf(Rotaion.y) * 5.5f, sinf(Rotaion.y) * 5.5f, 0.0f);
		}
		//タイムを進める
		m_nTime++;
	}
	//進行方向に向きを合わせる
	Rotaion.z = atan2f((Position.x + Move.x) - Position.x, (Position.y + Move.y) - Position.y);
	//向きを合わせる
	SetRotation(Rotaion);
	//移動量を設定
	SetMove(Move);
}

//=============================================================================
// 色選択処理関数
//=============================================================================
void CBulletFlower::ColorSelect(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_ColorNumber * 0.1428f, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_ColorNumber * 0.1428f + 0.1428f, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_ColorNumber * 0.1428f, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_ColorNumber * 0.1428f + 0.1428f, 1.0f);
	//テクスチャの設定
	SetTexture(aTexture);
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CBulletFlower::Death(void)
{
	//終了処理関数呼び出し
	Uninit();
	return;
}
