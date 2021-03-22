//=============================================================================
//
// �Q�[�����[�h [mode_game.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "sound.h"
#include "mode_game.h"
#include "camera.h"
#include "light.h"
#include "pose_button_manager.h"
#include "floor.h"
#include "player.h"
#include "weapon_sword.h"
#include "weapon_shield.h"
#include "enemy_skeleton.h"
#include "enemy_dragon.h"
#include "village.h"
#include "sparks.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CCamera * CGameMode::m_pCamera = NULL;	//�J�����̃|�C���^
CPlayer * CGameMode::m_pPlayer = NULL;	//�v���C���[�̃|�C���^
CDragon * CGameMode::m_pDragon = NULL;	//�h���S���̃|�C���^
CVillage * CGameMode::m_pVillage = NULL;	//���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameMode::CGameMode()
{
	m_pLight = NULL;	//���C�g�̃|�C���^
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
	CGameMode * pGameMode = NULL;
	//�����Q�[�����[�h�̃|�C���^��NULL�������ꍇ
	if (pGameMode == NULL)
	{
		//�Q�[�����[�h�̃������m��
		pGameMode = new CGameMode;
		//�����Q�[�����[�h�̃|�C���^��NULL����Ȃ��ꍇ
		if (pGameMode != NULL)
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
	//�S�������������֐��Ăяo��
	InitCreateAll();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CGameMode::Uninit(void)
{
	//�����J�����̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pCamera != NULL)
	{
		//�J�����̏����������֐��Ăяo��
		m_pCamera->Uninit();
		//�J�����̃������j��
		delete m_pCamera;
		//�J�����̃|�C���^��NULL�ɂ���
		m_pCamera = NULL;
	}
	//�������C�g�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pLight != NULL)
	{
		//���C�g�̏����������֐��Ăяo��
		m_pLight->Uninit();
		//���C�g�̃������j��
		delete m_pLight;
		//���C�g�̃|�C���^��NULL�ɂ���
		m_pLight = NULL;
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CGameMode::Update(void)
{
	//�S�X�V���������֐��Ăяo��
	UpdateCreateAll();
	//�����J�����̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pCamera != NULL)
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
		//�|�[�Y�{�^���}�l�[�W���[�̐��������֐��Ăяo��
		CPoseButtonManager::Create();
	}
}

//=============================================================================
// �S�������������֐�
//=============================================================================
void CGameMode::InitCreateAll(void)
{
	////�������C�g�̃|�C���^��NULL�̏ꍇ
	//if (m_pLight == NULL)
	//{
	//	//���C�g�̃������m��
	//	m_pLight = new CLight;
	//}
	////�������C�g�̃|�C���^��NULL����Ȃ��ꍇ
	//if (m_pLight != NULL)
	//{
	//	//���C�g�̏����������֐��Ăяo��
	//	m_pLight->Init();
	//}
	////�����v���C���[�̃|�C���^��NULL�̏ꍇ
	//if (m_pPlayer == NULL)
	//{
	//	//�v���C���[�̐���
	//	m_pPlayer = CPlayer::Create();
	//}
	////�����J�����̃|�C���^��NULL�̏ꍇ
	//if (m_pCamera == NULL)
	//{
	//	//�J�����̃������m��
	//	m_pCamera = new CCamera;
	//}
	////�����J�����̃|�C���^��NULL����Ȃ��ꍇ
	//if (m_pCamera != NULL)
	//{
	//	//�J�����̏����������֐��Ăяo��
	//	m_pCamera->Init();
	//}



	//CFloor::Create();
	//CSkeleton::Create();
	//m_pDragon = CDragon::Create();
	//CSparks::Create();
	//CSword::Create();
	//CShield::Create();
	//m_pStage = CStage::Create();
	//CVillageLifeUI::Create();
	//CVillageIcon::Create();
}

//=============================================================================
// �S�X�V���������֐�
//=============================================================================
void CGameMode::UpdateCreateAll(void)
{
}