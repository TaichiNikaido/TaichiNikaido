//=============================================================================
//
// �Q�[�����[�h [mode_game.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/sound.h"
#include "Base/light.h"
#include "Base/camera.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "mode_game.h"
#include "Character/player.h"
#include "Character/enemy_dragon.h"
#include "Weapon/weapon_sword.h"
#include "Weapon/weapon_shield.h"
#include "UI/ui_life_gauge_dragon.h"
#include "Polygon3d/floor.h"
#include "Button/pause_button_manager.h"
#include "skybox.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CPlayer * CGameMode::m_pPlayer = nullptr;	//�v���C���[�̃|�C���^
CDragon * CGameMode::m_pDragon = nullptr;	//�h���S���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameMode::CGameMode()
{
	m_pPlayer = nullptr;	//�v���C���[�̃|�C���^
	m_pDragon = nullptr;	//�h���S���̃|�C���^
	m_pCamera = nullptr;	//�J�����̃|�C���^
	m_pLight = nullptr;		//���C�g�̃|�C���^
	m_bCreatePause = false;		//�|�[�Y���g�p���Ă邩
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameMode::~CGameMode()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CGameMode * CGameMode::Create()
{
	//�Q�[�����[�h�̃|�C���^
	CGameMode * pGameMode = nullptr;
	//�����Q�[�����[�h�̃|�C���^��nullptr�������ꍇ
	if (pGameMode == nullptr)
	{
		//�Q�[�����[�h�̃������m��
		pGameMode = new CGameMode;
		//�����Q�[�����[�h�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pGameMode != nullptr)
		{
			//�Q�[�����[�h�̏������֐��Ăяo��
			pGameMode->Init();
		}
	}
	//�Q�[�����[�h�̃|�C���^��Ԃ�
	return pGameMode;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CGameMode::Init(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�����T�E���h�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (pSound != nullptr)
	{
		//���O���͂�BGM��~ 
		pSound->StopSound(CSound::SOUND_LABEL_BGM_NAME);
	}
	//�������������֐��Ăяo��
	InitCreate();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CGameMode::Uninit(void)
{
	//�����J�����̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pCamera != nullptr)
	{
		//�J�����̏I�������֐��Ăяo��
		m_pCamera->Uninit();
		//�J�����̃������j��
		delete m_pCamera;
		//�J�����̃|�C���^��nullptr�ɂ���
		m_pCamera = nullptr;
	}
	//�������C�g�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pLight != nullptr)
	{
		//���C�g�̏I�������֐��Ăяo��
		m_pLight->Uninit();
		//���C�g�̃������j��
		delete m_pLight;
		//���C�g�̃|�C���^��nullptr�ɂ���
		m_pLight = nullptr;
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CGameMode::Update(void)
{
	//�X�V���������֐��Ăяo��
	UpdateCreate();
	//�����J�����̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pCamera != nullptr)
	{
		//�J������ݒ肷��
		m_pCamera->SetCamera();
		//�J�����̍X�V�����֐��Ăяo��
		m_pCamera->Update();
	}
	//���͏����֐��Ăяo��
	Input();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CGameMode::Draw(void)
{
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CGameMode::Input(void)
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
		//����ESCAPE�L�[���̓W���C�X�e�B�b�N�̃X�^�[�g�{�^���������ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_ESCAPE) || pJoystick->GetJoystickTrigger(JS_START))
	{
		//�����|�[�Y���g�p���Ă��Ȃ��ꍇ
		if (m_bCreatePause == false)
		{
			//�|�[�Y�{�^���}�l�[�W���[�̐��������֐��Ăяo��
			CPauseButtonManager::Create();
		}
	}
}

//=============================================================================
// �������������֐�
//=============================================================================
void CGameMode::InitCreate(void)
{
	//�S��{���������֐��Ăяo��
	BaseCreateAll();
	//�S�}�b�v�I�u�W�F�N�g���������֐��Ăяo��
	MapObjectCreateAll();
	//�S�L�����N�^�[���������֐��Ăяo��
	CharacterCreateAll();
}

//=============================================================================
// �X�V���������֐�
//=============================================================================
void CGameMode::UpdateCreate(void)
{
}

//=============================================================================
// �S��{���������֐�
//=============================================================================
void CGameMode::BaseCreateAll(void)
{
	//�������C�g�̃|�C���^��nullptr�̏ꍇ
	if (m_pLight == nullptr)
	{
		//���C�g�̃������m��
		m_pLight = new CLight;
		//�������C�g�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_pLight != nullptr)
		{
			//���C�g�̏����������֐��Ăяo��
			m_pLight->Init();
		}
	}
	//�����J�����̃|�C���^��nullptr�̏ꍇ
	if (m_pCamera == nullptr)
	{
		//�J�����̃������m��
		m_pCamera = new CCamera;
		//�����J�����̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_pCamera != nullptr)
		{
			//�J�����̏����������֐��Ăяo��
			m_pCamera->Init();
		}
	}
}

//=============================================================================
// �S�}�b�v�I�u�W�F�N�g���������֐�
//=============================================================================
void CGameMode::MapObjectCreateAll(void)
{
	//�X�J�C�{�b�N�X�̐���
	CSkyBox::Create();
	//���̐���
	//CFloor::Create();
}

//=============================================================================
// �S�L�����N�^�[���������֐�
//=============================================================================
void CGameMode::CharacterCreateAll(void)
{
	//�����v���C���[�̃|�C���^��nullptr�̏ꍇ
	if (m_pPlayer == nullptr)
	{
		//�v���C���[�̐���
		m_pPlayer = CPlayer::Create();
		//�����v���C���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_pPlayer != nullptr)
		{
			//���̐���
			CSword::Create();
			//���̐���
			CShield::Create();
			//�v���C���[�̗̑͂�UI����
			//CPlayerLifeUI::Create();
		}
	}
	//�����h���S���̃|�C���^��nullptr�̏ꍇ
	if (m_pDragon == nullptr)
	{
		//�h���S���̐���
		m_pDragon = CDragon::Create();
		//�����h���S���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_pDragon != nullptr)
		{
			//�h���S���̗̑͂�UI����
			CDragonLifeGaugeUI::Create();
		}
	}
}