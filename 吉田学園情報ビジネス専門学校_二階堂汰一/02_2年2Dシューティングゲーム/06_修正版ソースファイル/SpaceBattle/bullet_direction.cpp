//=============================================================================
//
// 方向弾 [bullet_direction.cpp]
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
#include "bullet_direction.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/bullet.png")
#define SIZE (D3DXVECTOR3(10.0f,10.0f,0.0f))
#define LIFE (300)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletDirection::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBulletDirection::CBulletDirection(int nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBulletDirection::~CBulletDirection()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBulletDirection::TextureLoad(void)
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
void CBulletDirection::TextureUnload(void)
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
CBulletDirection * CBulletDirection::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed)
{
	CBulletDirection * pBulletDirection;
	pBulletDirection = new CBulletDirection;
	pBulletDirection->Init();
	pBulletDirection->SetPosition(Position);
	pBulletDirection->SetMove(Speed);
	return pBulletDirection;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBulletDirection::Init(void)
{
	//敵の初期化処理関数呼び出し
	CBulletEnemy::Init();
	//サイズの初期設定
	SetSize(SIZE);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CBulletDirection::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CBulletEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBulletDirection::Update(void)
{
	//敵の更新処理関数呼び出し
	CBulletEnemy::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CBulletDirection::Draw(void)
{
	//敵の描画処理関数呼び出し
	CBulletEnemy::Draw();
}
