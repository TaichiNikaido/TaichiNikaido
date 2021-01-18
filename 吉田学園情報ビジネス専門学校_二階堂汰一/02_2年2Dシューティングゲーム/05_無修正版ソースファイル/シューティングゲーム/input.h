//=============================================================================
//
// 入力処理 [input.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
	virtual void UninitInput(void);
	virtual void UpdateInput(void) = 0;
protected:
	LPDIRECTINPUTDEVICE8	m_pDevice;
	static LPDIRECTINPUT8	m_pDinput;
};
#endif