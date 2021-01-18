//=============================================================================
//
// ���͏��� [input.h]
// Author : ��K������
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
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