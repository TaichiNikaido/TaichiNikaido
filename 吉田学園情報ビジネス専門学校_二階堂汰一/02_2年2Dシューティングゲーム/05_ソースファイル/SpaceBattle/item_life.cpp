//=============================================================================
//
// 体力付与アイテム [item_life.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "mode_game.h"
#include "player.h"
#include "item_life.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Item/Life.png")	//テクスチャ

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CItemLife::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CItemLife::CItemLife()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CItemLife::~CItemLife()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CItemLife::TextureLoad(void)
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
void CItemLife::TextureUnload(void)
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
CItemLife * CItemLife::Create(D3DXVECTOR3 Position)
{
	//体力付与アイテムのポインタ
	CItemLife * pItemLife = NULL;
	//もし体力付与アイテムのポインタがNULLの場合
	if (pItemLife == NULL)
	{
		//体力付与アイテムのメモリ確保
		pItemLife = new CItemLife;
	}
	//もし体力付与アイテムのポインタがNULLじゃない場合
	if (pItemLife != NULL)
	{
		//位置を設定する
		pItemLife->SetPosition(Position);
		//初期化処理関数呼び出し
		pItemLife->Init();
	}
	//体力付与アイテムのポインタを返す
	return pItemLife;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CItemLife::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//アイテムの初期化処理関数呼び出し
	CItem::Init();
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CItemLife::Uninit(void)
{
	//アイテムの終了処理関数呼び出し
	CItem::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CItemLife::Update(void)
{
	//アイテムの更新処理関数呼び出し
	CItem::Update();
	//もし衝突判定が真のとき
	if (GetbCollision() == true)
	{
		//効果を与える処理関数呼び出し
		Give();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CItemLife::Draw(void)
{
	//アイテムの描画処理関数呼び出し
	CItem::Draw();
}

//=============================================================================
// 効果を与える処理関数
//=============================================================================
void CItemLife::Give(void)
{
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		//体力加算処理関数呼び出し
		pPlayer->AddLife();
	}
	//終了処理関数呼び出し
	Uninit();
	return;
}
