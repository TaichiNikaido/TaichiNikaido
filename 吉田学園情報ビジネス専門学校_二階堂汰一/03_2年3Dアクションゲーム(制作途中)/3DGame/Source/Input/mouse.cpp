//=============================================================================
//
// �}�E�X���� [mouse.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "mouse.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMouse::CMouse()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMouse::~CMouse()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	if (FAILED(m_pDinput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	m_pDevice->SetDataFormat(&c_dfDIMouse2);    //ϳ��p���ް��E̫�ϯĐݒ�
	m_pDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;    // ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j
	m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	m_pDevice->Acquire();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CMouse::Uninit(void)
{
	//���̓f�o�C�X�J��
	if (m_pDevice != NULL)
	{
		//�L�[�{�[�h�̃A�N�Z�X���J��
		m_pDevice->Unacquire();
		m_pDevice = NULL;
	}
	CInput::Uninit();
}

//=============================================================================
// �X�V�����֐�
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
// �}�E�X�{�^���̏�Ԏ擾
//=============================================================================
bool CMouse::GetMousePress(int Mouse)
{
	return (m_State.rgbButtons[Mouse] & 0x80) ? true : false;
}

//=============================================================================
// �}�E�X�����ꂽ����
//=============================================================================
bool CMouse::GetMouseTrigger(int nkey)
{
	//�O�̃t���[���ƍ��̃t���[�����Ⴄ�Ȃ�true;
	static bool prevState[sizeof(m_State.rgbButtons) / sizeof(m_State.rgbButtons[0])];
	bool current = GetMousePress(nkey);
	bool ret = current && !prevState[nkey];
	prevState[nkey] = current;
	return ret;
}

