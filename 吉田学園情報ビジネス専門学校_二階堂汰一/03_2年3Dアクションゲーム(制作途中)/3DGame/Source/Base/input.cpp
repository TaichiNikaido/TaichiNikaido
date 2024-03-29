//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECTINPUT8	CInput::m_pDinput = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CInput::CInput()
{
	m_pDevice = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDinput, nullptr)))
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CInput::Uninit(void)
{
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
	if (m_pDinput != nullptr)
	{
		m_pDinput->Release();
		m_pDinput = nullptr;
	}
}
