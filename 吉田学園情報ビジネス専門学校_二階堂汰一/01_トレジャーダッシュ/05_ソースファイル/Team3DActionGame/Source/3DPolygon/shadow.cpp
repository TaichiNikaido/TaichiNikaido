//=============================================================================
//
// 影 [shadow.cpp]
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
#include "shadow.h"
#include "Character/player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/shadow.png")			//テクスチャ
#define SIZE (D3DXVECTOR3(150.0f,150.0f,0.0f))		//サイズ
#define FLAME (0)									//フレーム
#define COLOR (D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f))	//色
#define ROTATION (D3DXVECTOR3(D3DXToRadian(-90.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)))	//回転

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CShadow::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CShadow::CShadow(int nPriority) : CPolygon3d(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CShadow::~CShadow()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CShadow::TextureLoad(void)
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
void CShadow::TextureUnload(void)
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
CShadow * CShadow::Create(void)
{
	//影のポインタ
	CShadow * pShadow = NULL;
	//もし影のポインタがNULLの場合
	if (pShadow == NULL)
	{
		//影のメモリ確保
		pShadow = new CShadow;
		//もし影がNULLじゃない場合
		if (pShadow != NULL)
		{
			//初期化処理関数呼び出し
			pShadow->Init();
		}
	}
	//影のポインタを返す
	return pShadow;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CShadow::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしプレイヤーのポインタがNULLではない場合
	if (pPlayer != NULL)
	{
		//プレイヤーの位置を取得する
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPos();
		//位置を設定する
		SetPosition(D3DXVECTOR3(PlayerPosition.x, 10.0f, PlayerPosition.z));
	}
	//サイズを設定する
	SetSize(SIZE);
	//色を設定する
	SetColor(COLOR);
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
void CShadow::Uninit(void)
{
	//ポリゴン3Dの終了処理関数呼び出し
	CPolygon3d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CShadow::Update(void)
{
	//ポリゴン3Dの更新処理関数呼び出し
	CPolygon3d::Update();
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしプレイヤーのポインタがNULLではない場合
	if (pPlayer != NULL)
	{
		//プレイヤーの位置を取得する
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPos();
		//位置を設定する
		SetPosition(D3DXVECTOR3(PlayerPosition.x, 10.0f, PlayerPosition.z));
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CShadow::Draw(void)
{
	//ポリゴン3Dの描画処理関数呼び出し
	CPolygon3d::Draw();
}
