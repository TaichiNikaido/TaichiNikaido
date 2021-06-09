//=============================================================================
//
// 丸影 [round_shadow.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Mode/mode_game.h"
#include "Base/renderer.h"
#include "Base/polygon3d.h"
#include "round_shadow.h"
#include "Character/player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/shadow.png")			//テクスチャ
#define ROTATION (D3DXVECTOR3(D3DXToRadian(-90.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)))	//回転

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CRoundShadow::m_pTexture = nullptr;		//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CRoundShadow::CRoundShadow(int nPriority) : CPolygon3d(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CRoundShadow::~CRoundShadow()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CRoundShadow::TextureLoad(void)
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
void CRoundShadow::TextureUnload(void)
{
	//もしテクスチャがnullptrじゃない場合
	if (m_pTexture != nullptr)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャをnullptrにする
		m_pTexture = nullptr;
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CRoundShadow * CRoundShadow::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size, D3DXCOLOR Color)
{
	//丸影のポインタ
	CRoundShadow * pRoundShadow = nullptr;
	//もし丸影のポインタがnullptrの場合
	if (pRoundShadow == nullptr)
	{
		//丸影のメモリ確保
		pRoundShadow = new CRoundShadow;
		//もし丸影がnullptrではない場合
		if (pRoundShadow != nullptr)
		{
			//丸影の位置を設定
			pRoundShadow->SetPosition(Position);
			//丸影のサイズを設定
			pRoundShadow->SetSize(Size);
			//丸影の色を設定
			pRoundShadow->SetColor(Color);
			//丸影の初期化処理関数呼び出し
			pRoundShadow->Init();
		}
	}
	//丸影のポインタを返す
	return pRoundShadow;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CRoundShadow::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//回転を設定する
	SetRotation(ROTATION);
	//ポリゴン3Dの初期化処理関数呼び出し
	CPolygon3d::Init();
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CRoundShadow::Uninit(void)
{
	//ポリゴン3Dの終了処理関数呼び出し
	CPolygon3d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CRoundShadow::Update(void)
{
	//ポリゴン3Dの更新処理関数呼び出し
	CPolygon3d::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CRoundShadow::Draw(void)
{
	//ポリゴン3Dの描画処理関数呼び出し
	CPolygon3d::Draw();
}