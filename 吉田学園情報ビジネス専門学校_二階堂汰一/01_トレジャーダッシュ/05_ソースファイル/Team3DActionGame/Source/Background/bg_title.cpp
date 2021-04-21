//=============================================================================
//
// タイトル背景 [bg_title.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "Base/main.h"
#include "Base/manager.h"
#include "Mode/mode_game.h"
#include "Base/renderer.h"
#include "Base/scene2d.h"
#include "bg_title.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/TitleBG.png")										//テクスチャ
#define SIZE (D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))							//サイズ
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))				//位置
#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))										//色
#define FLAME (0)																	//フレーム

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTitleBG::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CTitleBG::CTitleBG()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitleBG::~CTitleBG()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CTitleBG::TextureLoad(void)
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
void CTitleBG::TextureUnload(void)
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
CTitleBG * CTitleBG::Create(void)
{
	//タイトル背景のポインタ
	CTitleBG * pTitleBG = NULL;
	//もしタイトル背景のポインタがNULLの場合
	if (pTitleBG == NULL)
	{
		//タイトル背景のメモリ確保
		pTitleBG = new CTitleBG;
		//もしタイトル背景がNULLじゃない場合
		if (pTitleBG != NULL)
		{
			//初期化処理関数呼び出し
			pTitleBG->Init();
			//位置を設定する
			pTitleBG->SetPosition(POSITION);
			//サイズを設定する
			pTitleBG->SetSize(SIZE);
			//色を設定する
			pTitleBG->SetColor(COLOR);
		}
	}
	//タイトル背景のポインタを返す
	return pTitleBG;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CTitleBG::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//シーン2Dの初期化処理関数呼び出し
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
void CTitleBG::Uninit(void)
{
	//シーン2Dの終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CTitleBG::Update(void)
{
	//シーン2Dの更新処理関数呼び出し
	CScene2d::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CTitleBG::Draw(void)
{
	//シーン2Dの描画処理関数呼び出し
	CScene2d::Draw();
}
