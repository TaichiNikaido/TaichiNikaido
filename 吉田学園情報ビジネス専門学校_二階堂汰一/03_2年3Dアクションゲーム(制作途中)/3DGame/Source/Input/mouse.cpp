//=============================================================================
//
// マウス処理 [mouse.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "mouse.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CMouse::CMouse()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CMouse::~CMouse()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	if (FAILED(m_pDinput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	m_pDevice->SetDataFormat(&c_dfDIMouse2);    //ﾏｳｽ用のﾃﾞｰﾀ・ﾌｫｰﾏｯﾄ設定
	m_pDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;    // 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）
	m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	m_pDevice->Acquire();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CMouse::Uninit(void)
{
	//入力デバイス開放
	if (m_pDevice != NULL)
	{
		//キーボードのアクセス権開放
		m_pDevice->Unacquire();
		m_pDevice = NULL;
	}
	CInput::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CMouse::Update(void)
{
	for (int nCount = 0; nCount < 4; nCount++)
	{
		m_State.rgbButtons[nCount] = 0;
	}
	m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &m_State);

	m_pDevice->Acquire();
}

//=============================================================================
// マウスボタンの状態取得
//=============================================================================
bool CMouse::GetMousePress(int Mouse)
{
	return (m_State.rgbButtons[Mouse] & 0x80) ? true : false;
}

//=============================================================================
// マウス押された処理
//=============================================================================
bool CMouse::GetMouseTrigger(int nkey)
{
	//前のフレームと今のフレームが違うならtrue;
	static bool prevState[sizeof(m_State.rgbButtons) / sizeof(m_State.rgbButtons[0])];
	bool current = GetMousePress(nkey);
	bool ret = current && !prevState[nkey];
	prevState[nkey] = current;
	return ret;
}

