//=============================================================================
//
// �^�C�g���{�^���}�l�[�W���[ [title_button_manager.cpp]
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
#include "title_button_manager.h"
#include "button_start.h"
#include "button_tutorial.h"
#include "button_ranking.h"
#include "button_exit.h"
#include "button_any.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define START_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 740.0f, 0.0f))		//�X�^�[�g�{�^���̈ʒu
#define TUTORIAL_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 820.0f, 0.0f))	//�`���[�g���A���{�^���̈ʒu
#define RANKING_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 900.0f, 0.0f))	//�����L���O�{�^���̈ʒu
#define EXIT_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 980.0f, 0.0f))		//�I���{�^���̈ʒu
#define INPUT_INTERVAL (10)														//���͊Ԋu

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitleButtonManager::CTitleButtonManager(int nPriority) : CScene(nPriority)
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//�{�^���̃|�C���^
	m_nButton = BUTTON_NONE;						//�{�^��
	m_nInputCount = 0;								//���͊Ԋu
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitleButtonManager::~CTitleButtonManager()
{
}

//=============================================================================
// ���������֐��Ăяo��
//=============================================================================
CTitleButtonManager * CTitleButtonManager::Create(void)
{
	//�^�C�g���{�^���}�l�[�W���[�̃|�C���^
	CTitleButtonManager * pTitleButtonManager = nullptr;
	//�^�C�g���{�^���}�l�[�W���[�|�C���^��nullptr�̏ꍇ
	if (pTitleButtonManager == nullptr)
	{
		//�^�C�g���{�^���}�l�[�W���[�̃������m��
		pTitleButtonManager = new CTitleButtonManager;
		//�^�C�g���{�^���}�l�[�W���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pTitleButtonManager != nullptr)
		{
			//�^�C�g���{�^���}�l�[�W���[�̏����������֐��Ăяo��
			pTitleButtonManager->Init();
		}
	}
	//�^�C�g���{�^���}�l�[�W���[�̃|�C���^��Ԃ�
	return pTitleButtonManager;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CTitleButtonManager::Init(void)
{
	//�����S�������֐��Ăяo��
	InitCreateAll();
	//�{�^���̏����ݒ�
	m_nButton = BUTTON_START;
	//�{�^���̏����I�������֐��Ăяo��
	m_apButton[m_nButton]->SelectColor();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CTitleButtonManager::Uninit(void)
{
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CTitleButtonManager::Update(void)
{
	//�I�������֐��Ăяo��
	Select();
	//���͏����֐��Ăяo��
	Input();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CTitleButtonManager::Draw(void)
{
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CTitleButtonManager::Input(void)
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
	}
	//����ESCAPE�L�[���̓W���C�X�e�B�b�N��B�{�^���������ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_ESCAPE) || pJoystick->GetJoystickTrigger(JS_B))
	{
		//�L�����Z�������Đ������֐��Ăяo��
		CancelSound();
		//���炩�̃{�^�����������֐��Ăяo��
		CAnyButton::Create();
		//�{�^���̍ő吔����
		for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
		{
			//�e�{�^���̏I�������֐��Ăяo��
			m_apButton[nCount]->Uninit();
		}
		//�I�������֐��Ăяo��
		Uninit();
		return;
	}
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CTitleButtonManager::Select(void)
{
	//�������݂̃{�^�����X�^�[�g�{�^����艺��������
	if (m_nButton < BUTTON_START)
	{
		//���݂̃{�^�����I���{�^���ɂ���
		m_nButton = BUTTON_EXIT;
	}
	//�������݂̃{�^�����I���{�^�����z������
	if (m_nButton > BUTTON_EXIT)
	{
		//���݂̃{�^�����X�^�[�g�{�^���ɂ���
		m_nButton = BUTTON_START;
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
// �L�����Z�������Đ������֐�
//=============================================================================
void CTitleButtonManager::CancelSound(void)
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
void CTitleButtonManager::InitCreateAll(void)
{
	//�X�^�[�g�{�^���̐���
	m_apButton[BUTTON_START] = CStartButton::Create(START_BUTTON_POSITION);
	//�`���[�g���A���{�^���̐���
	m_apButton[BUTTON_TUTORIAL] = CTutorialButton::Create(TUTORIAL_BUTTON_POSITION);
	//�����L���O�{�^���̐���
	m_apButton[BUTTON_RANKING] = CRankingButton::Create(RANKING_BUTTON_POSITION);
	//�I���{�^���̐���
	m_apButton[BUTTON_EXIT] = CExitButton::Create(EXIT_BUTTON_POSITION,CExitButton::TEXTURE_ENGLISH);
}