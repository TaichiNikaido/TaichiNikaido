//=============================================================================
//
// 爆弾付与アイテム [item_bomb.cpp]
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
#include "item_bomb.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Item/Bomb.png")	//テクスチャ
#define SIZE (D3DXVECTOR3(30.0f,30.0f,0.0f))	//サイズ

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CItemBomb::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CItemBomb::CItemBomb()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CItemBomb::~CItemBomb()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CItemBomb::TextureLoad(void)
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
void CItemBomb::TextureUnload(void)
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
// コンストラクタ
//=============================================================================
CItemBomb * CItemBomb::Create(D3DXVECTOR3 Position)
{
	//爆弾付与アイテムのポインタ
	CItemBomb * pItemBomb = NULL;
	//爆弾付与アイテムのポインタがNULLの場合
	if (pItemBomb == NULL)
	{
		//爆弾付与アイテムのメモリ確保
		pItemBomb = new CItemBomb;
	}
	//爆弾付与アイテムのポインタがNULLじゃない場合
	if (pItemBomb != NULL)
	{
		//位置を設定する
		pItemBomb->SetPosition(Position);
		//初期化処理関数呼び出し
		pItemBomb->Init();
	}
	return pItemBomb;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CItemBomb::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//アイテムの初期化処理関数呼び出し
	CItem::Init();
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
void CItemBomb::Uninit(void)
{
	//アイテムの終了処理関数呼び出し
	CItem::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CItemBomb::Update(void)
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
void CItemBomb::Draw(void)
{
	//アイテムの描画処理関数呼び出し
	CItem::Draw();
}

//=============================================================================
// 効果を与える処理関数
//=============================================================================
void CItemBomb::Give(void)
{
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//プレイヤーがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//爆弾加算処理関数呼び出し
		pPlayer->AddBomb();
	}
	//終了処理関数呼び出し
	Uninit();
	return;
}
