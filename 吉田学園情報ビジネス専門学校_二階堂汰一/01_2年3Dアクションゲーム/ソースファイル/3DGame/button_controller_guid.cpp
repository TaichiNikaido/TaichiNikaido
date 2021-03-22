//=============================================================================
//
// ゲームに戻るボタン [button_quit_game.cpp]
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
#include "renderer.h"
#include "sound.h"
#include "button_controller_guid.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/Button/Button_Ranking.png")		//テクスチャのパス

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CControllerGuidButton::m_pTexture;	//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CControllerGuidButton::CControllerGuidButton()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CControllerGuidButton::~CControllerGuidButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CControllerGuidButton::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_PASS,					// ファイルの名前
		&m_pTexture);					// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CControllerGuidButton::TextureUnload(void)
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
// 生成処理関数呼び出し
//=============================================================================
CControllerGuidButton * CControllerGuidButton::Create(D3DXVECTOR3 Position)
{
	//操作説明ボタンのポインタ
	CControllerGuidButton * pControllerGuidButton = NULL;
	//操作説明ボタンポインタがNULLの場合
	if (pControllerGuidButton == NULL)
	{
		//操作説明ボタンのメモリ確保
		pControllerGuidButton = new CControllerGuidButton;
		//操作説明ボタンのポインタがNULLではない場合
		if (pControllerGuidButton != NULL)
		{
			//操作説明ボタンの位置設定
			pControllerGuidButton->SetPosition(Position);
			//操作説明ボタンの初期化処理関数呼び出し
			pControllerGuidButton->Init();
		}
	}
	//操作説明ボタンのポインタを返す
	return pControllerGuidButton;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CControllerGuidButton::Init(void)
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
void CControllerGuidButton::Uninit(void)
{
	//ボタンの終了処理関数呼び出し
	CButton::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CControllerGuidButton::Update(void)
{
	//ボタンの更新処理関数呼び出し
	CButton::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CControllerGuidButton::Draw(void)
{
	//ボタンの描画処理関数呼び出し
	CButton::Draw();
}

//=============================================================================
// プレス処理関数
//=============================================================================
void CControllerGuidButton::Press(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//もしサウンドのポインタがNULLじゃない場合
	if (pSound != NULL)
	{
		//決定音の再生
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);
	}
}