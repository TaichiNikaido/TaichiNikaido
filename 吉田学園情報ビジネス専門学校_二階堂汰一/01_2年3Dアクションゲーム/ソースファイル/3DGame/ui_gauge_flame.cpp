//=============================================================================
//
// UIのゲージ [ui_gauge.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// 警告制御
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

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
#include "ui_gauge_flame.h"
#include "stage.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/UI/GaugeFlame.png")		//テクスチャのパス

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGaugeFlame::m_pTexture = NULL;	//テクスチャ

//=============================================================================
// コンストラクタ
//=============================================================================
CGaugeFlame::CGaugeFlame()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CGaugeFlame::~CGaugeFlame()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CGaugeFlame::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_PASS,					// ファイルの名前
		&m_pTexture);					// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CGaugeFlame::TextureUnload(void)
{
	// テクスチャの破棄
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
CGaugeFlame * CGaugeFlame::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size)
{
	//ゲージフレームのポインタ
	CGaugeFlame * pGaugeFlame = NULL;
	//ゲージフレームのポインタがNULLの場合
	if (pGaugeFlame == NULL)
	{
		//ゲージフレームのメモリ確保
		pGaugeFlame = new CGaugeFlame;
	}
	//ゲージフレームのポインタがNULLではない場合
	if (pGaugeFlame != NULL)
	{
		//位置を設定する
		pGaugeFlame->SetPosition(Position);
		//サイズを設定する
		pGaugeFlame->SetSize(Size);
		//ゲージフレームの初期化処理関数呼び出し
		pGaugeFlame->Init();
	}
	//ゲージフレームのポインタを返す
	return pGaugeFlame;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CGaugeFlame::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//2Dシーン管理初期化処理関数呼び出し
	CScene2d::Init();
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CGaugeFlame::Uninit(void)
{
	//2Dシーン管理終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CGaugeFlame::Update(void)
{
	//ステージの取得
	CStage * pStage = CGameMode::GetStage();
	//村全体のライフを取得する
	int nVillageLife = pStage->GetLife();
	//2Dシーン管理更新処理関数呼び出し
	CScene2d::Update();
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//テクスチャの設定
	SetTexture(aTexture);
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGaugeFlame::Draw(void)
{
	//2Dシーン管理描画処理関数呼び出し
	CScene2d::Draw();
}
