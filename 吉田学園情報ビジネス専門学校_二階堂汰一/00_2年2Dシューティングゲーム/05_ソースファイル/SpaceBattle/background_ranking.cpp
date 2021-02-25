//=============================================================================
//
// ランキング背景 [background_ranking.cpp]
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
#include "background_ranking.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Background/background_ranking.png")	//テクスチャ
#define SIZE (D3DXVECTOR3(1920.0f,1080.0f,0.0f))					//サイズ
#define FLAME (0)													//フレーム

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBackgroundRanking::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBackgroundRanking::CBackgroundRanking()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBackgroundRanking::~CBackgroundRanking()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBackgroundRanking::TextureLoad(void)
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
void CBackgroundRanking::TextureUnload(void)
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
CBackgroundRanking * CBackgroundRanking::Create(D3DXVECTOR3 Position)
{
	//ランキング背景のポインタ
	CBackgroundRanking * pbackgeroundRanking = NULL;
	//もしランキング背景がNULLの場合
	if (pbackgeroundRanking == NULL)
	{
		//ランキング背景のメモリを確保する
		pbackgeroundRanking = new CBackgroundRanking;
		//もしランキング背景がNULLじゃない場合
		if (pbackgeroundRanking != NULL)
		{
			//初期化処理関数呼び出し
			pbackgeroundRanking->Init();
			//位置を設定する
			pbackgeroundRanking->SetPosition(Position);
		}
	}
	//ランキング背景を返す
	return pbackgeroundRanking;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBackgroundRanking::Init(void)
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
void CBackgroundRanking::Uninit(void)
{
	//背景の終了処理
	CBackground::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBackgroundRanking::Update(void)
{
	//背景の更新処理
	CBackground::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CBackgroundRanking::Draw(void)
{
	//背景の描画処理
	CBackground::Draw();
}
