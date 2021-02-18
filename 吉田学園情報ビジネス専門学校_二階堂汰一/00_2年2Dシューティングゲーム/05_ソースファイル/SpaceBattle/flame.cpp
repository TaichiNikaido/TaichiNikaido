//=============================================================================
//
// 警告 [warning.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mode_game.h"
#include "flame.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/flame.png")
#define SIZE (D3DXVECTOR3(400.0f,1080.0f,0.0f))

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CFlame::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CFlame::CFlame(int nPriority) : CScene2d(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CFlame::~CFlame()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CFlame::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE,									// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CFlame::TextureUnload(void)
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
CFlame * CFlame::Create(D3DXVECTOR3 Position)
{
	//フレームのポインタ
	CFlame * pFlame = NULL;
	//もしフレームのポインタがNULLの場合
	if (pFlame == NULL)
	{
		//フレームのメモリ確保
		pFlame = new CFlame;
	}
	//もしフレームのポインタがNULLじゃない場合
	if (pFlame != NULL)
	{
		//初期化処理関数呼び出し
		pFlame->Init();
		//位置を設定する
		pFlame->SetPosition(Position);
	}
	//フレームのポインタを返す
	return pFlame;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CFlame::Init()
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//2Dシーン初期化処理関数呼び出し
	CScene2d::Init();
	//サイズの初期設定
	SetSize(SIZE);
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CFlame::Uninit()
{
	//2Dシーン終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CFlame::Update()
{
	//2Dシーン更新処理関数呼び出し
	CScene2d::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CFlame::Draw()
{
	//2Dシーン描画処理関数呼び出し
	CScene2d::Draw();
}
