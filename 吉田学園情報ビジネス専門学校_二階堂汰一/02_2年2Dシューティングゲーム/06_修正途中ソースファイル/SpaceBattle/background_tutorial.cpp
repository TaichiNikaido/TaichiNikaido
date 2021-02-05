//=============================================================================
//
// チュートリアル背景 [background_tutorial.cpp]
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
#include "background_tutorial.h"
#include "joystick.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define KEYBOARD_GUID_TEXTURE ("Data/Texture/Background/background_keyboard_guid.png")
#define JOYSTICK_GUID_TEXTURE ("Data/Texture/Background/background_joystick_guid.png")
#define SIZE (D3DXVECTOR3(1920.0f,1080.0f,0.0f))
#define FLAME (0)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBackgroundTutorial::m_apTexture[TEXTURE_MAX] = {};	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBackgroundTutorial::CBackgroundTutorial(int nPriority) : CBackground(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBackgroundTutorial::~CBackgroundTutorial()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBackgroundTutorial::TextureLoad(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		KEYBOARD_GUID_TEXTURE,					// ファイルの名前
		&m_apTexture[TEXTURE_KEYBOARD_GUID]);	// 読み込むメモリー
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		JOYSTICK_GUID_TEXTURE,					// ファイルの名前
		&m_apTexture[TEXTURE_JOYSTICK_GUID]);	// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CBackgroundTutorial::TextureUnload(void)
{
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CBackgroundTutorial * CBackgroundTutorial::Create(D3DXVECTOR3 Position)
{
	CBackgroundTutorial * pBackgroundTutorial;
	pBackgroundTutorial = new CBackgroundTutorial;
	pBackgroundTutorial->Init();
	pBackgroundTutorial->SetPosition(Position);
	return pBackgroundTutorial;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBackgroundTutorial::Init(void)
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
	//もしジョイスティックがNULLだったら
	if (CJoystick::GetDevice() == NULL)
	{
		//テクスチャの割り当て
		BindTexture(m_apTexture[TEXTURE_KEYBOARD_GUID]);
	}
	else
	{
		//テクスチャの割り当て
		BindTexture(m_apTexture[TEXTURE_JOYSTICK_GUID]);
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CBackgroundTutorial::Uninit(void)
{
	//背景の終了処理
	CBackground::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBackgroundTutorial::Update(void)
{
	//背景の更新処理
	CBackground::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CBackgroundTutorial::Draw(void)
{
	//背景の描画処理
	CBackground::Draw();
}
