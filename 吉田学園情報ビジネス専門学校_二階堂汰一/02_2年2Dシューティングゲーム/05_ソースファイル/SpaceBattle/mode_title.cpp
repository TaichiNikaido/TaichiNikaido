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
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INPUT_TIME (5)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitleMode::CTitleMode()
{
	m_InputStick.Up.bTrigger = false;			//�X�e�B�b�N����ɓ|���Ă��邩�ǂ���
	m_InputStick.Down.bTrigger = false;			//�X�e�B�b�N�����ɓ|���Ă��邩�ǂ���
	m_InputStick.Up.nCount = 0;					//�X�e�B�b�N�̏���̗͂V��
	m_InputStick.Down.nCount = 0;				//�X�e�B�b�N�̉����̗͂V��
	m_nButtonPosition = 0;						//�I�𒆂̃{�^���̈ʒu
	memset(m_apButton,NULL,sizeof(m_apButton));	//�{�^���ւ̃|�C���^
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
	//���͏����֐��Ăяo��
	Input();
	//�{�^���ݒ菈���֐��Ăяo��
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
// �{�^���ݒ菈���֐�
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
// ���͏����֐�
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
	//�X�e�B�b�N�̏オ���͂��ꂽ�Ƃ�
	if (lpDIDevice != NULL &&js.lY == -1000)
	{
		//�X�e�B�b�N�̏���̗͂V�т����Z����
		m_InputStick.Up.nCount++;
	}
	//W�L�[�����͂��ꂽ�Ƃ�
	if (pKeyboard->GetKeyboardTrigger(DIK_W))
	{
		//�����{�^���̈ʒu���v���C�{�^�����ゾ������
		if (m_nButtonPosition > CButton::BUTTON_PLAY)
		{
			//�I�𒆂̃{�^���̈ʒu��������
			m_nButtonPosition--;
		}
	}
	//�X�e�B�b�N�̉������͂��ꂽ�Ƃ�
	if (lpDIDevice != NULL &&js.lY == 1000)
	{
		//�X�e�B�b�N�̉����̗͂V�т����Z����
		m_InputStick.Down.nCount++;
	}
	//S�L�[�����͂��ꂽ�Ƃ�
	if (pKeyboard->GetKeyboardTrigger(DIK_S))
	{
		//�����{�^���̈ʒu��EXIT�{�^�����ゾ������
		if (m_nButtonPosition < CButton::BUTTON_EXIT)
		{
			//�I�𒆂̃{�^���̈ʒu���グ��
			m_nButtonPosition++;
		}

	}
	//�X�e�B�b�N�̏���̗͂V�т��w��̎��ԂɂȂ�����
	if (m_InputStick.Up.nCount > INPUT_TIME)
	{
		//�X�e�B�b�N�̏���͂�^�ɂ���
		m_InputStick.Up.bTrigger = true;
		//���̗͂V�т�0�ɂ���
		m_InputStick.Up.nCount = 0;
	}
	//�X�e�B�b�N�̉����̗͂V�т��w��̎��ԂɂȂ�����
	if (m_InputStick.Down.nCount > INPUT_TIME)
	{
		//�X�e�B�b�N�̉����͂�^�ɂ���
		m_InputStick.Down.bTrigger = true;
		//���̗͂V�т�0�ɂ���
		m_InputStick.Down.nCount = 0;
	}
	//�����X�e�B�b�N�̏���͂��^�ɂȂ�����
	if (m_InputStick.Up.bTrigger == true)
	{
		//�����X�e�B�b�N�̏���͂��U�ɂ���
		m_InputStick.Up.bTrigger = false;
		//�����{�^���̈ʒu���v���C�{�^�����ゾ������
		if (m_nButtonPosition > CButton::BUTTON_PLAY)
		{
			//�I�𒆂̃{�^���̈ʒu��������
			m_nButtonPosition--;
		}
	}
	//�����X�e�B�b�N�̉����͂��^�ɂȂ�����
	if (m_InputStick.Down.bTrigger == true)
	{
		//�����X�e�B�b�N�̉����͂��U�ɂ���
		m_InputStick.Down.bTrigger = false;
		//�����{�^���̈ʒu��EXIT�{�^�����ゾ������
		if (m_nButtonPosition < CButton::BUTTON_EXIT)
		{
			//�I�𒆂̃{�^���̈ʒu���グ��
			m_nButtonPosition++;
		}
	}
	//�����L�[�{�[�h�̃G���^�[�L�[���̓W���C�X�e�B�b�N��A�{�^���������ꂽ��
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
	switch (m_nButtonPosition)
	{
	case CButton::BUTTON_PLAY:
		 //���O���̓��[�h�ɑJ��
		CManager::StartFade(CManager::MODE_NAME);
		break;
	case CButton::BUTTON_REPLAY:
		CPlayer::SetbReplay(true);
		//�Q�[�����[�h�ɑJ��
		CManager::StartFade(CManager::MODE_GAME);
		break;
	case CButton::BUTTON_EXIT:
		//�I������
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
		m_apButton[nCount] = CButton::Create(D3DXVECTOR3(float(SCREEN_WIDTH * 0.75), float(SCREEN_HEIGHT * 0.6 + 100.0f * nCount), 0.0f),(CButton::BUTTON)nCount);
	}
}
