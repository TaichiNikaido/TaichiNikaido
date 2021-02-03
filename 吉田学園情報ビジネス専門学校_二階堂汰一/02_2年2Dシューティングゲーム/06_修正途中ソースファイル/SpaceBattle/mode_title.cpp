//=============================================================================
//
// �^�C�g�����[�h [mode_title.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "mode_title.h"
#include "background_title.h"
#include "keyboard.h"
#include "joystick.h"
#include "button.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COUNT_TRIGGER_PAUSE (5)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitleMode::CTitleMode()
{
	m_IsTrigger.Down.bTrigger = false;//������Ă邩�ǂ���
	m_IsTrigger.Up.bTrigger = false;
	m_IsTrigger.Left.bTrigger = false;
	m_IsTrigger.Right.bTrigger = false;
	m_IsTrigger.Down.nCount = 0;//������Ă邩�ǂ���
	m_IsTrigger.Up.nCount = 0;
	m_IsTrigger.Left.nCount = 0;
	m_IsTrigger.Right.nCount = 0;
	m_nButtonPosition = 0;
	memset(m_apButton,NULL,sizeof(m_apButton));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitleMode::~CTitleMode()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CTitleMode * CTitleMode::Create()
{
	CTitleMode * pTitleMode;
	pTitleMode = new CTitleMode;
	pTitleMode->Init();
	return pTitleMode;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CTitleMode::Init(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//BGM�̍Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
	//�S���������֐��Ăяo��
	CreateAll();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CTitleMode::Uninit(void)
{
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CTitleMode::Update(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	Input();
	
	SetButtonUI();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CTitleMode::Draw(void)
{
	for (int nCount = 0; nCount < CButton::BUTTON_MAX; nCount++)
	{
		m_apButton[nCount]->Draw();
	}
}

//=============================================================================
// �����֐�
//=============================================================================
void CTitleMode::SetButtonUI(void)
{
	for (int nCount = 0; nCount < CButton::BUTTON_MAX; nCount++)
	{
		m_apButton[nCount]->SelectButton(false);
	}

	m_apButton[m_nButtonPosition]->SelectButton(true);
}

//=============================================================================
// ���͊֐�
//=============================================================================
void CTitleMode::Input(void)
{
	//�L�[�{�[�h�̎擾
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//�W���C�X�e�B�b�N�̐U���擾
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	if (lpDIDevice != NULL &&js.lY == -1000 || pKeyboard->GetKeyboardPress(DIK_W))//��
	{
		m_IsTrigger.Up.nCount++;
	}
	if (lpDIDevice != NULL &&js.lY == 1000 || pKeyboard->GetKeyboardPress(DIK_S))//��
	{
		m_IsTrigger.Down.nCount++;
	}

	if (m_IsTrigger.Up.nCount > COUNT_TRIGGER_PAUSE)
	{
		m_IsTrigger.Up.bTrigger = true;
		m_IsTrigger.Up.nCount = COUNT_TRIGGER_PAUSE - 5;
	}
	if (m_IsTrigger.Down.nCount > COUNT_TRIGGER_PAUSE)
	{
		m_IsTrigger.Down.bTrigger = true;
		m_IsTrigger.Down.nCount = COUNT_TRIGGER_PAUSE - 5;
	}
	if (m_IsTrigger.Down.bTrigger == true)
	{
		m_IsTrigger.Down.bTrigger = false;
		if (m_nButtonPosition < 2)
		{
			m_nButtonPosition++;
		}
	}
	if (m_IsTrigger.Up.bTrigger == true)
	{
		m_IsTrigger.Up.bTrigger = false;
		if (m_nButtonPosition > 0)
		{
			m_nButtonPosition--;
		}
	}

	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pJoystick->GetJoystickTrigger(JS_A))
	{
		//�I�������֐��Ăяo��
		Select();
	}
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CTitleMode::Select(void)
{
	//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_ENTER);
	switch (m_nButtonPosition)
	{
	case CButton::BUTTON_PLAY://�X�^�[�g
		 //���O���͂Ɉړ�
		 //pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
		CManager::StartFade(CManager::MODE_NAME);
		//pSound->StopSound();
		break;
	case CButton::BUTTON_REPLAY://���v���C�{�^��
		//pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
		//pSound->StopSound();
		//m_bReplay = true;
		//���O���͂Ɉړ�
		CManager::StartFade(CManager::MODE_GAME);
		break;
	case CButton::BUTTON_EXIT://�I��
		//pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
		exit(0);
		return;
		break;
	default:
		break;
	}
}

//=============================================================================
// �S���������֐�
//=============================================================================
void CTitleMode::CreateAll(void)
{
	//�^�C�g���w�i����
	CBackgroundTitle::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	//�v���C�{�^���̐���
	for (int nCount = 0; nCount < CButton::BUTTON_MAX; nCount++)
	{
		m_apButton[nCount] = CButton::Create(D3DXVECTOR3(600.0f, 300.0f + 100.0f * nCount, 0.0f),(CButton::BUTTON)nCount);
	}
}
