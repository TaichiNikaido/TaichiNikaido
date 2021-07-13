//=============================================================================
//
// 丸火 [round_fire.cpp]
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
#include "round_fire.h"
#include "Character/player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/round_fire.png")			//テクスチャ
#define SIZE (D3DXVECTOR3(50.0f,50.0f,50.0f))			//サイズ
#define ROTATION (D3DXVECTOR3(D3DXToRadian(-90.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)))	//回転

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CRoundFire::m_pTexture = nullptr;		//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CRoundFire::CRoundFire(int nPriority) : CPolygon3d(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CRoundFire::~CRoundFire()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CRoundFire::TextureLoad(void)
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
void CRoundFire::TextureUnload(void)
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
CRoundFire * CRoundFire::Create(D3DXVECTOR3 Position)
{
	//丸火のポインタ
	CRoundFire * pRoundFire = nullptr;
	//もし丸火のポインタがnullptrの場合
	if (pRoundFire == nullptr)
	{
		//丸火のメモリ確保
		pRoundFire = new CRoundFire;
		//もし丸火がnullptrではない場合
		if (pRoundFire != nullptr)
		{
			//丸火の位置を設定
			pRoundFire->SetPosition(Position);
			//丸火の初期化処理関数呼び出し
			pRoundFire->Init();
		}
	}
	//丸火のポインタを返す
	return pRoundFire;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CRoundFire::Init(void)
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
void CRoundFire::Uninit(void)
{
	//ポリゴン3Dの終了処理関数呼び出し
	CPolygon3d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CRoundFire::Update(void)
{
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//ポリゴン3Dの更新処理関数呼び出し
	CPolygon3d::Update();
	//もしプレイヤーのポインタがnullptrの場合
	if (pPlayer != nullptr)
	{
		//プレイヤーの位置を取得する
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//プレイヤーまでの距離を求める
		D3DXVECTOR3 Distance = D3DXVECTOR3(PlayerPosition.x - Position.x, PlayerPosition.y - Position.y, PlayerPosition.z - Position.z);
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CRoundFire::Draw(void)
{
	//ポリゴン3Dの描画処理関数呼び出し
	CPolygon3d::Draw();
}