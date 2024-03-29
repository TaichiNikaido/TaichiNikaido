//=============================================================================
//
// タイトルに戻るボタン [button_back_to_title.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/sound.h"
#include "Mode/mode_game.h"
#include "button_back_to_title.h"
#include "Player/player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/Button/Button_ReturnTitle.png")		//テクスチャのパス

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBackToTitleButton::m_pTexture;	//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBackToTitleButton::CBackToTitleButton()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBackToTitleButton::~CBackToTitleButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBackToTitleButton::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,	//デバイスへのポインタ
		TEXTURE_PASS,					//ファイルの名前
		&m_pTexture);					//読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CBackToTitleButton::TextureUnload(void)
{
	//もしテクスチャのポインタがnullptrではない場合
	if (m_pTexture != nullptr)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャをnullptrにする
		m_pTexture = nullptr;
	}
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CBackToTitleButton * CBackToTitleButton::Create(D3DXVECTOR3 Position)
{
	//タイトルに戻るボタンのポインタ
	CBackToTitleButton * pBackToTitleButton = nullptr;
	//タイトルに戻るボタンポインタがnullptrの場合
	if (pBackToTitleButton == nullptr)
	{
		//タイトルに戻るボタンのメモリ確保
		pBackToTitleButton = new CBackToTitleButton;
		//タイトルに戻るボタンのポインタがnullptrではない場合
		if (pBackToTitleButton != nullptr)
		{
			//タイトルに戻るボタンの位置設定
			pBackToTitleButton->SetPosition(Position);
			//タイトルに戻るボタンの初期化処理関数呼び出し
			pBackToTitleButton->Init();
		}
	}
	//タイトルに戻るボタンのポインタを返す
	return pBackToTitleButton;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBackToTitleButton::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//ボタンの初期化処理関数呼び出し
	CButton::Init();
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CBackToTitleButton::Uninit(void)
{
	//ボタンの終了処理関数呼び出し
	CButton::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBackToTitleButton::Update(void)
{
	//ボタンの更新処理関数呼び出し
	CButton::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CBackToTitleButton::Draw(void)
{
	//ボタンの描画処理関数呼び出し
	CButton::Draw();
}

//=============================================================================
// プレス処理関数
//=============================================================================
void CBackToTitleButton::Press(void)
{
	//もしプレイヤーがリプレイ状態の場合
	if (CPlayer::GetReplay() == true)
	{
		//プレイヤーのリプレイ状態を止める
		CPlayer::SetbReplay(false);
	}
	//タイトルモードに遷移する
	CManager::StartFade(CManager::MODE_TITLE);
}