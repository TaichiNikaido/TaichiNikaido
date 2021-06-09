//=============================================================================
//
// �|�[�Y�{�^���}�l�[�W���[ [pause_button_manager.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Mode/mode_tutorial.h"
#include "Mode/mode_game.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "pause_button_manager.h"
#include "button_back_to_title.h"
#include "button_controller_guid.h"
#include "button_quit_game.h"
#include "button_exit.h"
#include "polygon2d/pause_bg.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define QUIT_GAME_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 740.0f, 0.0f))				//�Q�[���ɖ߂�{�^���̈ʒu
#define CONTROLLER_GUIDE_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 820.0f, 0.0f))		//��������{�^���̈ʒu
#define BACK_TO_TITLE_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 900.0f, 0.0f))			//�^�C�g���ɖ߂�{�^���̈ʒu
#define EXIT_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 980.0f, 0.0f))					//�I���{�^���̈ʒu
#define INPUT_INTERVAL (10)																	//���͊Ԋu

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPauseButtonManager::CPauseButtonManager(int nPriority) : CScene(nPriority)
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//�{�^���̃|�C���^
	m_nButton = BUTTON_NONE;						//�{�^��
	m_nInputCount = 0;								//���͊Ԋu
	m_pPouseBG = nullptr;							//�|�[�Y�w�i�̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPauseButtonManager::~CPauseButtonManager()
{
}

//=============================================================================
// ���������֐��Ăяo��
//=============================================================================
CPauseButtonManager * CPauseButtonManager::Create(void)
{
	//�|�[�Y�{�^���}�l�[�W���[�̃|�C���^
	CPauseButtonManager * pPoseButtonManager = nullptr;
	//�|�[�Y�{�^���}�l�[�W���[�|�C���^��nullptr�̏ꍇ
	if (pPoseButtonManager == nullptr)
	{
		//�|�[�Y�{�^���}�l�[�W���[�̃������m��
		pPoseButtonManager = new CPauseButtonManager;
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
HRESULT CPauseButtonManager::Init(void)
{
	//�`���[�g���A�����[�h�̎擾
	CTutorialMode * pTutorialMode = CManager::GetTutorialMode();
	//�Q�[�����[�h�̎擾
	CGameMode * pGameMode = CManager::GetGameMode();
	//�����S�������֐��Ăяo��
	InitCreateAll();
	//�{�^���̏����ݒ�
	m_nButton = BUTTON_QUIT_GAME;
	//�{�^���̏����I�������֐��Ăяo��
	m_apButton[m_nButton]->SelectColor();
	//�����`���[�g���A�����[�h�̃|�C���^��nullptr����Ȃ��ꍇ
	if (pTutorialMode != nullptr)
	{
		//�|�[�Y�g�p��Ԃɂ���
		pTutorialMode->SetbCreatePause(true);
	}
	//�����Q�[�����[�h�̃|�C���^��nullptr����Ȃ��ꍇ
	if (pGameMode != nullptr)
	{
		//�|�[�Y�g�p��Ԃɂ���
		pGameMode->SetbCreatePause(true);
	}
	//�����|�[�Y�w�i�̃|�C���^��nullptr�̏ꍇ
	if (m_pPouseBG == nullptr)
	{
		//�|�[�Y�w�i�̐���
		m_pPouseBG = CPauseBG::Create();
	}
	//�|�[�Y�̎g�p��Ԃ�ݒ肷��
	SetbPause(true);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPauseButtonManager::Uninit(void)
{
	//�`���[�g���A�����[�h�̎擾
	CTutorialMode * pTutorialMode = CManager::GetTutorialMode();
	//�Q�[�����[�h�̎擾
	CGameMode * pGameMode = CManager::GetGameMode();
	//�����`���[�g���A�����[�h�̃|�C���^��nullptr����Ȃ��ꍇ
	if (pTutorialMode != nullptr)
	{
		//�|�[�Y��������Ԃɂ���
		pTutorialMode->SetbCreatePause(false);
	}
	//�����Q�[�����[�h�̃|�C���^��nullptr����Ȃ��ꍇ
	if (pGameMode != nullptr)
	{
		//�|�[�Y��������Ԃɂ���
		pGameMode->SetbCreatePause(false);
	}
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPauseButtonManager::Update(void)
{
	//�I�������֐��Ăяo��
	Select();
	//���͏����֐��Ăяo��
	Input();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPauseButtonManager::Draw(void)
{
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CPauseButtonManager::Input(void)
{
	//�`���[�g���A�����[�h�̎擾
	CTutorialMode * pTutorialMode = CManager::GetTutorialMode();
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
	//�L�[�{�[�h�̍X�V�����֐��Ăяo��
	pKeyboard->Update();
	//�W���C�X�e�B�b�N�̍X�V�����֐��Ăяo��
	pJoystick->Update();
	//�E�B���h�E���A�N�e�B�u�̏ꍇ
	if (CManager::GetIsActiveWindow() == true)
	{
		//�}�E�X�J�[�\���̈ʒu����ʂ̒��S�ɐݒ肷��
		SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	//����L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetKeyboardTrigger(DIK_UP))
	{
		//���݂̃{�^�������Z����
		m_nButton--;
		//�{�^���̑I�������Đ������֐��Ăяo��
		m_apButton[m_nButton]->SelectSound();
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
			m_apButton[m_nButton]->SelectSound();
		}
	}
	//�����L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetKeyboardTrigger(DIK_DOWN))
	{
		//���݂̃{�^�������Z����
		m_nButton++;
		//�{�^���̑I�������Đ������֐��Ăяo��
		m_apButton[m_nButton]->SelectSound();
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
			m_apButton[m_nButton]->SelectSound();
		}
	}
	//����ENTER�L�[���̓W���C�X�e�B�b�N��A�{�^���������ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pJoystick->GetJoystickTrigger(JS_A))
	{
		//�{�^���̃v���X�����֐��Ăяo��
		m_apButton[m_nButton]->Press();
		//�����|�[�Y�w�i�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_pPouseBG != nullptr)
		{
			//�|�[�Y�w�i�̏I�������֐��Ăяo��
			m_pPouseBG->Uninit();
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
	//����ESCAPE�L�[���̓W���C�X�e�B�b�N��START�{�^���������ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_ESCAPE) || pJoystick->GetJoystickTrigger(JS_START))
	{
		//�����|�[�Y�w�i�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_pPouseBG != nullptr)
		{
			//�|�[�Y�w�i�̏I�������֐��Ăяo��
			m_pPouseBG->Uninit();
		}
		//�{�^���̑�������
		for (int nCount = BUTTON_QUIT_GAME; nCount < BUTTON_MAX; nCount++)
		{
			//�e�{�^���̏I�������֐��Ăяo��
			m_apButton[nCount]->Uninit();
		}
		//�|�[�Y�𖢎g�p��Ԃɂ���
		SetbPause(false);
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
void CPauseButtonManager::Select(void)
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
void CPauseButtonManager::InitCreateAll(void)
{
	//�Q�[���ɖ߂�{�^���̐���
	m_apButton[BUTTON_QUIT_GAME] = CQuitGameButton::Create(QUIT_GAME_BUTTON_POSITION);
	//��������{�^���̐���
	m_apButton[BUTTON_CONTROLLER_GUIDE] = CControllerGuidButton::Create(CONTROLLER_GUIDE_BUTTON_POSITION);
	//�^�C�g���{�^���̐���
	m_apButton[BUTTON_BACK_TO_TITLE] = CBackToTitleButton::Create(BACK_TO_TITLE_BUTTON_POSITION);
	//�I���{�^���̐���
	m_apButton[BUTTON_EXIT] = CExitButton::Create(EXIT_BUTTON_POSITION, CExitButton::TEXTURE_JAPANESE);
}