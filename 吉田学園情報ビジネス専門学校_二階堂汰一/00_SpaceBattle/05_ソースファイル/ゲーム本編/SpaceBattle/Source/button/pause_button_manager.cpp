//=============================================================================
//
// �|�[�Y�{�^���}�l�[�W���[ [pose_button_manager.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Mode/mode_game.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "pause_button_manager.h"
#include "button_back_to_title.h"
#include "button_quit_game.h"
#include "button/button_exit.h"
#include "background/background_pause.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define START_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 740.0f, 0.0f))			//�X�^�[�g�{�^���̈ʒu
#define BACK_TO_TITLE_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 840.0f, 0.0f))	//�^�C�g���֖߂�{�^���̈ʒu
#define EXIT_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 940.0f, 0.0f))			//�I���{�^���̈ʒu
#define INPUT_INTERVAL (10)															//���͊Ԋu

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPoseButtonManager::CPoseButtonManager(int nPriority) : CScene(nPriority)
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//�{�^���̃|�C���^
	m_nButton = BUTTON_NONE;						//�{�^��
	m_nInputCount = 0;								//���͊Ԋu
	m_pPauseBG = nullptr;							//�|�[�Y�w�i�̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPoseButtonManager::~CPoseButtonManager()
{
}

//=============================================================================
// ���������֐��Ăяo��
//=============================================================================
CPoseButtonManager * CPoseButtonManager::Create(void)
{
	//�|�[�Y�{�^���}�l�[�W���[�̃|�C���^
	CPoseButtonManager * pPoseButtonManager = nullptr;
	//�|�[�Y�{�^���}�l�[�W���[�|�C���^��nullptr�̏ꍇ
	if (pPoseButtonManager == nullptr)
	{
		//�|�[�Y�{�^���}�l�[�W���[�̃������m��
		pPoseButtonManager = new CPoseButtonManager;
		//�|�[�Y�{�^���}�l�[�W���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pPoseButtonManager != nullptr)
		{
			//�|�[�Y�{�^���}�l�[�W���[�̏����������֐��Ăяo��
			pPoseButtonManager->Init();
		}
	}
	//�|�[�Y�{�^���}�l�[�W���[�̃|�C���^��Ԃ�
	return pPoseButtonManager;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPoseButtonManager::Init(void)
{
	//�Q�[�����[�h�̎擾
	CGameMode * pGameMode = CManager::GetGameMode();
	//�����S�������֐��Ăяo��
	InitCreateAll();
	//�{�^���̏����ݒ�
	m_nButton = BUTTON_QUIT_GAME;
	//�{�^���̏����I�������֐��Ăяo��
	m_apButton[m_nButton]->SelectColor();
	//�|�[�Y��Ԃɂ���
	SetbPause(true);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPoseButtonManager::Uninit(void)
{
	//�|�[�Y��Ԃ��~�߂�
	SetbPause(false);
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPoseButtonManager::Update(void)
{
	//�I�������֐��Ăяo��
	Select();
	//���͏����֐��Ăяo��
	Input();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPoseButtonManager::Draw(void)
{
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CPoseButtonManager::Input(void)
{
	//�Q�[�����[�h�̎擾
	CGameMode * pGameMode = CManager::GetGameMode();
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
		}
	}
	//�����L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetKeyboardTrigger(DIK_DOWN))
	{
		//���݂̃{�^�������Z����
		m_nButton++;
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
		}
	}
	//����ENTER�L�[���̓W���C�X�e�B�b�N��A�{�^���������ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pJoystick->GetJoystickTrigger(JS_A))
	{
		//�{�^���̃v���X�����֐��Ăяo��
		m_apButton[m_nButton]->Press();
		//�����|�[�Y�w�i�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_pPauseBG != nullptr)
		{
			//�|�[�Y�w�i�̏I�������֐��Ăяo��
			m_pPauseBG->Uninit();
		}
		//�{�^���̑�������
		for (int nCount = BUTTON_QUIT_GAME; nCount < BUTTON_MAX; nCount++)
		{
			//�e�{�^���̏I�������֐��Ăяo��
			m_apButton[nCount]->Uninit();
		}
		//�I�������֐��Ăяo��
		Uninit();
		return;
	}
	if (lpDIDevice != NULL &&js.lY == 0)
	{
		m_nInputCount = 0;
	}
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPoseButtonManager::Select(void)
{
	//�������݂̃{�^�����I���{�^����艺��������
	if (m_nButton < BUTTON_QUIT_GAME)
	{
		//���݂̃{�^�����^�C�g���ɖ߂�{�^���ɂ���
		m_nButton = BUTTON_EXIT;
	}
	//�������݂̃{�^�����I���{�^�����z������
	if (m_nButton > BUTTON_EXIT)
	{
		//���݂̃{�^�����Q�[���ɖ߂�{�^���ɂ���
		m_nButton = BUTTON_QUIT_GAME;
	}
	//�{�^���̍ő吔����
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
	{
		//�{�^���̑I������ĂȂ����̐F�ύX�����֐��Ăяo��
		m_apButton[nCount]->NotSelectColor();
	}
	//�{�^���̑I�����F�ύX�����֐��Ăяo��
	m_apButton[m_nButton]->SelectColor();
}

//=============================================================================
// �������������֐�
//=============================================================================
void CPoseButtonManager::InitCreateAll(void)
{
	//�Q�[���ɖ߂�{�^���̐���
	m_apButton[BUTTON_QUIT_GAME] = CQuitGameButton::Create(START_BUTTON_POSITION);
	//�^�C�g���{�^���̐���
	m_apButton[BUTTON_BACK_TO_TITLE] = CBackToTitleButton::Create(BACK_TO_TITLE_BUTTON_POSITION);
	//�I���{�^���̐���
	m_apButton[BUTTON_EXIT] = CExitButton::Create(EXIT_BUTTON_POSITION, CExitButton::TEXTURE_JAPANESE);
	//�|�[�Y�w�i�̐���
	m_pPauseBG = CBackgroundPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
}