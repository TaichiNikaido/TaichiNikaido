//=============================================================================
//
// 上層背景 [background_upper_layer.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "background_upper_layer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Background/background_upper_layer.png")	//テクスチャ
#define SIZE (D3DXVECTOR3(1120.0f,1080.0f,0.0f))						//サイズ
#define FLAME (5)														//フレーム
#define MOVE_VALUE (0.003f)												//移動量

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBackgroundUpperLayer::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBackgroundUpperLayer::CBackgroundUpperLayer()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBackgroundUpperLayer::~CBackgroundUpperLayer()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBackgroundUpperLayer::TextureLoad(void)
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
void CBackgroundUpperLayer::TextureUnload(void)
{
	//もしテクスチャがNULLではない場合
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
CBackgroundUpperLayer * CBackgroundUpperLayer::Create(D3DXVECTOR3 Position)
{
	//上層背景のポインタ
	CBackgroundUpperLayer * pBackgroundUpperLayer = NULL;
	//もし上層背景のポインタがNULLの場合
	if (pBackgroundUpperLayer == NULL)
	{
		//もし上層背景のメモリを確保
		pBackgroundUpperLayer = new CBackgroundUpperLayer;
		//もし上層背景のポインタがNULLではない場合
		if (pBackgroundUpperLayer != NULL)
		{
			//初期化処理関数呼び出し
			pBackgroundUpperLayer->Init();
			//位置を設定する
			pBackgroundUpperLayer->SetPosition(Position);
		}
	}
	//上層背景のポインタを返す
	return pBackgroundUpperLayer;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBackgroundUpperLayer::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//背景の初期化処理関数呼び出し
	CBackground::Init();
	//サイズの初期設定
	SetSize(SIZE);
	//フレームの初期設定
	SetFlame(FLAME);
	//移動量を設定
	SetMove(MOVE_VALUE);
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CBackgroundUpperLayer::Uninit(void)
{
	//背景の終了処理関数呼び出し
	CBackground::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBackgroundUpperLayer::Update(void)
{
	//背景の更新処理関数呼び出し
	CBackground::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CBackgroundUpperLayer::Draw(void)
{
	//背景の描画処理関数呼び出し
	CBackground::Draw();
}
