//=============================================================================
//
// 下層背景 [background_under_layer.cpp]
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
#include "background.h"
#include "background_under_layer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Background/background_under_layer.png")
#define SIZE (D3DXVECTOR3(1120.0f,1080.0f,0.0f))
#define FLAME (3)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBackgroundUnderLayer::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBackgroundUnderLayer::CBackgroundUnderLayer()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBackgroundUnderLayer::~CBackgroundUnderLayer()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBackgroundUnderLayer::TextureLoad(void)
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
void CBackgroundUnderLayer::TextureUnload(void)
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
CBackgroundUnderLayer * CBackgroundUnderLayer::Create(D3DXVECTOR3 Position)
{
	//下層背景のポインタ
	CBackgroundUnderLayer * pBackgroundUnderLayer = NULL;
	//もし下層背景のポインタがNULLの場合
	if (pBackgroundUnderLayer == NULL)
	{
		//下層背景のメモリ確保
		pBackgroundUnderLayer = new CBackgroundUnderLayer;
	}
	//もし下層背景のポインタがNULLじゃない場合
	if (pBackgroundUnderLayer == NULL)
	{
		//初期化処理関数呼び出し
		pBackgroundUnderLayer->Init();
		//位置を設定する
		pBackgroundUnderLayer->SetPosition(Position);
	}
	return pBackgroundUnderLayer;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBackgroundUnderLayer::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//背景の初期化処理
	CBackground::Init();
	//サイズの初期設定
	SetSize(SIZE);
	//フレームの初期設定
	SetFlame(FLAME);
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CBackgroundUnderLayer::Uninit(void)
{
	//背景の終了処理
	CBackground::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBackgroundUnderLayer::Update(void)
{
	//背景の更新処理
	CBackground::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CBackgroundUnderLayer::Draw(void)
{
	//背景の描画処理
	CBackground::Draw();
}
