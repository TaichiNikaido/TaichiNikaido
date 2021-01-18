//=============================================================================
//
// キーボード処理 [keyboard.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_KEY_MAX 256

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CInputKeyboard :public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
	void UninitInput(void);
	void UpdateInput(void);
	bool GetKeyboardPress(int nKey);
	bool GetKeyboardTrigger(int nKey);
	bool GetKeyboardRelease(int nKey);
private:
	BYTE m_aKeyState[NUM_KEY_MAX];		  //キーボードの入力情報ワーク
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX]; //キーボードのトリガー情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX]; //キーボードのリリース情報
};
#endif