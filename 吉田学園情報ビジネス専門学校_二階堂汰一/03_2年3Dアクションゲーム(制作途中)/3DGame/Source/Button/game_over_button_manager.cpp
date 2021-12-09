//=============================================================================
//
// �Q�[���I�[�o�[�{�^���}�l�[�W���[ [game_over_button_manager.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/sound.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "game_over_button_manager.h"
#include "button_retry.h"
#include "button_back_to_title.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RETRY_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 790.0f, 0.0f))				//�X�^�[�g�{�^���̈ʒu
#define BACK_TO_TITLE_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 890.0f, 0.0f))		//�^�C�g���ɖ߂�{�^���̈ʒu
#define INPUT_INTERVAL (10)																//���͊Ԋu

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameOverButtonManager::CGameOverButtonManager(int nPriority) : CScene(nPriority)
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//�{�^���̃|�C���^
	m_nButton = BUTTON_NONE;						//�{�^��
	m_nInputCount = 0;								//���͊Ԋu
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameOverButtonManager::~CGameOverButtonManager()
{
}

//=============================================================================
// ���������֐��Ăяo��
//=============================================================================
CGameOverButtonManager * CGameOverButtonManager::Create(void)
{
	//�Q�[���I�[�o�[�{�^���}�l�[�W���[�̃|�C���^
	CGameOverButtonManager * pGameOverButtonManager = nullptr;
	//�Q�[���I�[�o�[�{�^���}�l�[�W���[��nullptr�̏ꍇ
	if (pGameOverButtonManager == nullptr)
	{
		//�Q�[���I�[�o�[�{�^���}�l�[�W���[�̃������m��
		pGameOverButtonManager = new CGameOverButtonManager;
		//�Q�[���I�[�o�[�{�^���}�l�[�W���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pGameOverButtonManager != nullptr)
		{
			//�Q�[���I�[�o�[�{�^���}�l�[�W���[�̏����������֐��Ăяo��
			pGameOverButtonManager->Init();
		}
	}
	//�Q�[���I�[�o�[�{�^���}�l�[�W���[�̃|�C���^��Ԃ�
	return pGameOverButtonManager;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CGameOverButtonManager::Init(void)
{
	//�����S�������֐��Ăяo��
	InitCreateAll();
	//�{�^���̏����ݒ�
	m_nButton = BUTTON_RETRY;
	//�{�^���̏����I�������֐��Ăяo��
	m_apButton[m_nButton]->ChangeTranslucent(true);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CGameOverButtonManager::Uninit(void)
{
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CGameOverButtonManager::Update(void)
{
	//�I�������֐��Ăяo��
	Select();
	//���͏����֐��Ăяo��
	Input();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CGameOverButtonManager::Draw(void)
{
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CGameOverButtonManager::Input(void)
{
	//�L�[�{�[�h�̎擾
	CKeyboard * pKeyboard = CManager::GetKeyboard();
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
	//����L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetKeyboardTrigger(DIK_UP))
	{
		//���݂̃{�^�������Z����
		m_nButton--;
		//�{�^���̑I�������Đ������֐��Ăяo��
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//����{�^������X�e�B�b�N�����͂��ꂽ�ꍇ
	if (lpDIDevice != NULL &&js.rgdwPOV[0] == 0 || lpDIDevice != NULL &&js.lY == -1000)
	{
		//���͊Ԋu�����Z����
		m_nInputCount++;
		if (m_nInputCount % INPUT_INTERVAL == 0)
		{
			//���݂̃{�^�������Z����
			m_nButton--;
			//�{�^���̑I�������Đ������֐��Ăяo��
			m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
		}
	}
	//�����L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetKeyboardTrigger(DIK_DOWN))
	{
		//���݂̃{�^�������Z����
		m_nButton++;
		//�{�^���̑I�������Đ������֐��Ăяo��
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//�����{�^�������X�e�B�b�N�����͂��ꂽ�ꍇ
	if (lpDIDevice != NULL &&js.rgdwPOV[0] == 18000 || lpDIDevice != NULL &&js.lY == 1000)
	{
		//���͊Ԋu�����Z����
		m_nInputCount++;
		if (m_nInputCount % INPUT_INTERVAL == 0)
		{
			//���݂̃{�^�������Z����
			m_nButton++;
			//�{�^���̑I�������Đ������֐��Ăяo��
			m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
		}
	}
	//����ENTER�L�[���̓W���C�X�e�B�b�N��A�{�^���������ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pJoystick->GetJoystickTrigger(JS_A))
	{
		//�{�^���̃v���X�����֐��Ăяo��
		m_apButton[m_nButton]->Press();
	}
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CGameOverButtonManager::Select(void)
{
	//�������݂̃{�^�������g���C�{�^����艺��������
	if (m_nButton < BUTTON_RETRY)
	{
		//���݂̃{�^�����^�C�g���ɖ߂�{�^���ɂ���
		m_nButton = BUTTON_BACK_TO_TITLE;
	}
	//�������݂̃{�^�����^�C�g���ɖ߂�{�^�����z������
	if (m_nButton > BUTTON_BACK_TO_TITLE)
	{
		//���݂̃{�^�������g���C�{�^���ɂ���
		m_nButton = BUTTON_RETRY;
	}
	//�{�^���̍ő吔����
	for (int nCount = BUTTON_RETRY; nCount < BUTTON_MAX; nCount++)
	{
		//�{�^���̑I������ĂȂ����̐F�ύX�����֐��Ăяo��
		m_apButton[nCount]->ChangeTranslucent(false);
	}
	//�{�^���̑I�����F�ύX�����֐��Ăяo��
	m_apButton[m_nButton]->ChangeTranslucent(true);
}

//=============================================================================
// �L�����Z�������Đ������֐�
//=============================================================================
void CGameOverButtonManager::CancelSound(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�����T�E���h�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (pSound != nullptr)
	{
		//�L�����Z�����̍Đ�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_CANCEL);
	}
}

//=============================================================================
// �������������֐�
//=============================================================================
void CGameOverButtonManager::InitCreateAll(void)
{
	//�X�^�[�g�{�^���̐���
	m_apButton[BUTTON_RETRY] = CRetryButton::Create(RETRY_BUTTON_POSITION);
	//�^�C�g���{�^���̐���
	m_apButton[BUTTON_BACK_TO_TITLE] = CBackToTitleButton::Create(BACK_TO_TITLE_BUTTON_POSITION);
}