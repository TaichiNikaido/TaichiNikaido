//=============================================================================
//
// ドラゴンゲージの枠 [gaugeflame_dragon.cpp]
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
#include "gaugeflame_dragon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture")
#define SCRIPT_PASS ("Data/Script")

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGaugeFlameDragon::m_pTexture = NULL;	//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CGaugeFlameDragon::CGaugeFlameDragon()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CGaugeFlameDragon::~CGaugeFlameDragon()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CGaugeFlameDragon::TextureLoad(void)
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
void CGaugeFlameDragon::TextureUnload(void)
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
CGaugeFlameDragon * CGaugeFlameDragon::Create(void)
{
	//ドラゴンゲージの枠のポインタ
	CGaugeFlameDragon * pGaugeFlameDragon = NULL;
	//ドラゴンゲージの枠がNULLの場合
	if (pGaugeFlameDragon == NULL)
	{
		//ドラゴンゲージの枠のメモリ確保
		pGaugeFlameDragon = new CGaugeFlameDragon;
		//ドラゴンゲージの枠がNULLではない場合
		if (pGaugeFlameDragon != NULL)
		{
			//ドラゴンゲージの枠の初期化処理関数呼び出し
			pGaugeFlameDragon->Init();
		}
	}
	//ドラゴンゲージの枠のポインタを返す
	return pGaugeFlameDragon;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CGaugeFlameDragon::Init(void)
{
	//スクリプトパスの設定
	SetScriptPass(SCRIPT_PASS);
	//ゲージフレームの初期化処理関数呼び出し
	CGaugeFlame::Init();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CGaugeFlameDragon::Uninit(void)
{
	//ゲージフレームの終了処理関数呼び出し
	CGaugeFlame::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CGaugeFlameDragon::Update(void)
{
	//ゲージフレームの更新処理関数呼び出し
	CGaugeFlame::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGaugeFlameDragon::Draw(void)
{
	//ゲージフレームの描画処理関数呼び出し
	CGaugeFlame::Draw();
}