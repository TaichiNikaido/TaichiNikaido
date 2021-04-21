//=============================================================================
//
// �}�l�[�W���[ [manager.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Mode/mode_title.h"
#include "Mode/mode_name.h"
#include "Mode/mode_tutorial.h"
#include "Mode/mode_game.h"
#include "Mode/mode_result.h"
#include "Mode/mode_ranking.h"
#include "scene.h"
#include "scene2d.h"
#include "sound.h"
#include "input.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "Input/mouse.h"
#include "fade.h"
#include "Character/player.h"
#include "Character/enemy_dragon.h"
#include "Weapon/weapon_sword.h"
#include "Weapon/weapon_shield.h"
#include "Polygon3d/floor.h"
#include "Polygon2d/title_logo.h"
#include "Polygon2d/letter.h"
#include "Button/button_any.h"
#include "Button/button_start.h"
#include "Button/button_tutorial.h"
#include "Button/button_ranking.h"
#include "Button/button_exit.h"
#include "Button/button_quit_game.h"
#include "Button/button_controller_guid.h"
#include "Button/button_back_to_title.h"
#include "skybox.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CRenderer * CManager::m_pRenderer = nullptr;			//�����_���[�̃|�C���^
CSound * CManager::m_pSound = nullptr;					//�T�E���h�̃|�C���^
CKeyboard * CManager::m_pKeyboard = nullptr;			//�L�[�{�[�h�̃|�C���^
CMouse * CManager::m_pMouse = nullptr;					//�}�E�X�̃|�C���^
CJoystick * CManager::m_pJoystick = nullptr;			//�}�l�[�W���[�̃|�C���^
CTutorialMode * CManager::m_pTutorialMode = nullptr;	//�`���[�g���A�����[�h�̃|�C���^
CGameMode * CManager::m_pGameMode = nullptr;			//�Q�[�����[�h�̃|�C���^
CResultMode * CManager::m_pResultMode = nullptr;		//���U���g���[�h�̃|�C���^
CRankingMode * CManager::m_pRankingMode = nullptr;		//�����L���O���[�h�̃|�C���^
CFade * CManager::m_pFade = nullptr;					//�t�F�[�h�ւ̃|�C���^
CManager::MODE  CManager::m_Mode = MODE_NONE;			//���[�h
bool CManager::m_bUseFade = false;						//�t�F�[�h�̎g�p���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow)
{
	//���������_���[�̃|�C���^��nullptr�̏ꍇ
	if (m_pRenderer == nullptr)
	{
		//�����_���[�̃��������m��
		m_pRenderer = new  CRenderer;
		//���������_���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_pRenderer != nullptr)
		{
			//�����_���[�̏����������֐��Ăяo��
			m_pRenderer->Init(hWnd, TRUE);
		}
	}
	//�����t�F�[�h�̃|�C���^��nullptr�̏ꍇ
	if (m_pFade == nullptr)
	{
		//�t�F�[�h�̐��������֐��Ăяo��
		m_pFade = CFade::Create(m_Mode);
	}
	//�����T�E���h�̃|�C���^��nullptr�̏ꍇ
	if (m_pSound == nullptr)
	{
		//�T�E���h�̃������m��
		m_pSound = new CSound;
		//�����T�E���h�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_pSound != nullptr)
		{
			//�T�E���h�̏����������֐��Ăяo��
			m_pSound->Init(hWnd);
		}
	}
	//�����L�[�{�[�h�̃|�C���^��nullptr�̏ꍇ
	if (m_pKeyboard == nullptr)
	{
		//�L�[�{�[�h�̃������m��
		m_pKeyboard = new CKeyboard;
		//�����L�[�{�[�h�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_pKeyboard != nullptr)
		{
			//�L�[�{�[�h�̏����������֐��Ăяo��
			m_pKeyboard->Init(hInsitance, hWnd);
		}
	}
	//�����W���C�X�e�B�b�N�̃|�C���^��nullptr�̏ꍇ
	if (m_pJoystick == nullptr)
	{
		//�W���C�X�e�B�b�N�̃������m��
		m_pJoystick = new CJoystick;
		//�����W���C�X�e�B�b�N�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_pJoystick != nullptr)
		{
			//�W���C�X�e�B�b�N�̏����������֐��Ăяo��
			m_pJoystick->Init(hInsitance, hWnd);
		}
	}
	//�����}�E�X�̃|�C���^��nullptr�̏ꍇ
	if (m_pMouse == nullptr)
	{
		//�}�E�X�̃������m��
		m_pMouse = new CMouse;
		//�����}�E�X�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_pMouse != NULL)
		{
			//�}�E�X�̏����������֐��Ăяo��
			m_pMouse->Init(hInsitance, hWnd);
		}
	}
	//�S�ǂݍ��݊֐��Ăяo��
	LoadAll();
	//���[�h�̐ݒ�
	SetMode(MODE_GAME);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CManager::Uninit(void)
{
	//�V�[���̑S�j�������֐��Ăяo��
	CScene::ReleaseAll();
	//�����T�E���h�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pSound != nullptr)
	{
		//�T�E���h�̒�~
		m_pSound->StopSound();
	}
	//�S�j���֐��Ăяo��
	DeleteAll();
	//�S�ǂݍ��ݔj���֐��Ăяo��
	UnloadAll();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CManager::Update(void)
{
	//���������_���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pRenderer != nullptr)
	{
		//�����_���[�̍X�V�����֐��Ăяo��
		m_pRenderer->Update();
	}
	//�����L�[�{�[�h�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pKeyboard != nullptr)
	{
		//�L�[�{�[�h�̍X�V�����֐��Ăяo��
		m_pKeyboard->Update();
	}
	//�����W���C�X�e�B�b�N�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pJoystick != nullptr)
	{
		//�W���C�X�e�B�b�N�̍X�V�����֐��Ăяo��
		m_pJoystick->Update();
	}
	//�����}�E�X�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pMouse != nullptr)
	{
		//�}�E�X�̍X�V�����֐��Ăяo��
		m_pMouse->Update();
	}
	//�����t�F�[�h���ꂽ��
	if (m_bUseFade == true)
	{
		//�����t�F�[�h�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_pFade != nullptr)
		{
			//�t�F�[�h�̍X�V�����֐��Ăяo��
			m_pFade->Update();
		}
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CManager::Draw(void)
{
	//�����_���[�̕`�揈���֐��Ăяo��
	m_pRenderer->Draw();
}

//=============================================================================
// �t�F�[�h�J�n�����֐�
//=============================================================================
void CManager::StartFade(MODE mode)
{
	//���[�h��ݒ肷��
	m_Mode = mode;
	//�t�F�[�h������
	m_bUseFade = true;
}

//=============================================================================
// �t�F�[�h��~�����֐�
//=============================================================================
void CManager::StopFade(void)
{
	//�t�F�[�h����߂�
	m_bUseFade = false;
}

//=============================================================================
// ���[�h�ݒ�֐�
//=============================================================================
void CManager::SetMode(MODE Mode)
{
	//�V�[���̑S�j�������֐��Ăяo��
	CScene::ReleaseAll();
	//���[�h��ݒ肷��
	m_Mode = Mode;
	//�e���[�h�̏���
	switch (m_Mode)
	{
	case MODE_TITLE:
		//�^�C�g�����[�h�̐��������֐��Ăяo��
		CTitleMode::Create();
		break;
	case MODE_NAME:
		//���O���̓��[�h�̐��������֐��Ăяo��
		CNameMode::Create();
		break;
	case MODE_TUTORIAL:
		//�`���[�g���A�����[�h�̐��������֐��Ăяo��
		m_pTutorialMode = CTutorialMode::Create();
		break;
	case MODE_GAME:
		//�Q�[�����[�h�̐��������֐��Ăяo��
		m_pGameMode = CGameMode::Create();
		break;
	case MODE_RESULT:
		//���U���g���[�h�̐��������֐��Ăяo��
		m_pResultMode = CResultMode::Create();
		break;
	case MODE_RANKING:
		//�����L���O���[�h�̐��������֐��Ăяo��
		m_pRankingMode = CRankingMode::Create();
	default:
		break;
	}
}

//=============================================================================
// �S�ǂݍ��ݏ����֐�
//=============================================================================
void CManager::LoadAll(void)
{
	//�v���C���[�̃��f���ǂݍ���
	CPlayer::ModelLoad();
	//���̃��f���ǂݍ���
	CSword::ModelLoad();
	//���̃��f���ǂݍ���
	CShield::ModelLoad();
	//�h���S�����f���ǂݍ���
	CDragon::ModelLoad();
	//�n�ʂ̃e�N�X�`���ǂݍ���
	CFloor::TextureLoad();
	//���炩�̃{�^���̃e�N�X�`���ǂݍ���
	CAnyButton::TextureLoad();
	//�X�^�[�g�{�^���̃e�N�X�`���ǂݍ���
	CStartButton::TextureLoad();
	//�`���[�g���A���{�^���̃e�N�X�`���ǂݍ���
	CTutorialButton::TextureLoad();
	//�����L���O�{�^���̃e�N�X�`���ǂݍ���
	CRankingButton::TextureLoad();
	//�I���{�^���̃e�N�X�`���ǂݍ���
	CExitButton::TextureLoad();
	//�Q�[���ɖ߂�{�^���̃e�N�X�`���ǂݍ���
	CQuitGameButton::TextureLoad();
	//��������{�^���̃e�N�X�`���ǂݍ���
	CControllerGuidButton::TextureLoad();
	//�^�C�g���ɖ߂�{�^���̃e�N�X�`���ǂݍ���
	CBackToTitleButton::TextureLoad();
	//�^�C�g�����S�̃e�N�X�`���ǂݍ���
	CTitleLogo::TextureLoad();
	//�����̃e�N�X�`���ǂݍ���
	CLetter::TextureLoad();
	//�X�J�C�{�b�N�X�̃e�N�X�`���ǂݍ���
	CSkyBox::TextureLoad();
}

//=============================================================================
// �S�ǂݍ��ݔj�������֐�
//=============================================================================
void CManager::UnloadAll(void)
{
	//�v���C���[�̃��f���j��
	CPlayer::ModelUnload();
	//���̃��f���j��
	CSword::ModelUnload();
	//���̃��f���j��
	CShield::ModelUnload();
	//�h���S�����f���j��
	CDragon::ModelUnload();
	//�n�ʂ̃e�N�X�`���j��
	CFloor::TextureUnload();
	//���炩�̃{�^���̃e�N�X�`���j��
	CAnyButton::TextureUnload();
	//�X�^�[�g�{�^���̃e�N�X�`���j��
	CStartButton::TextureUnload();
	//�`���[�g���A���{�^���̃e�N�X�`���j��
	CTutorialButton::TextureUnload();
	//�����L���O�{�^���̃e�N�X�`���j��
	CRankingButton::TextureUnload();
	//�I���{�^���̃e�N�X�`���j��
	CExitButton::TextureUnload();
	//�Q�[���ɖ߂�{�^���̃e�N�X�`���j��
	CQuitGameButton::TextureUnload();
	//��������{�^���̃e�N�X�`���j��
	CControllerGuidButton::TextureUnload();
	//�^�C�g���ɖ߂�{�^���̃e�N�X�`���j��
	CBackToTitleButton::TextureUnload();
	//�^�C�g�����S�̃e�N�X�`���j��
	CTitleLogo::TextureUnload();
	//�����̃e�N�X�`���j��
	CLetter::TextureUnload();
	//�X�J�C�{�b�N�X�̃e�N�X�`���j��
	CSkyBox::TextureUnload();
}

//=============================================================================
// �S�j�������֐�
//=============================================================================
void CManager::DeleteAll(void)
{
	//�����}�E�X�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pMouse != nullptr)
	{
		//�}�E�X�̏I�������֐��Ăяo��
		m_pMouse->Uninit();
		//�}�E�X�̃������j��
		delete m_pMouse;
		//�}�E�X�̃|�C���^��nullptr�ɂ���
		m_pMouse = nullptr;
	}
	//�����W���C�X�e�B�b�N�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pJoystick != nullptr)
	{
		//�W���C�X�e�B�b�N�̏I�������֐��Ăяo��
		m_pJoystick->Uninit();
		//�W���C�X�e�B�b�N�̃������j��
		delete m_pJoystick;
		//�W���C�X�e�B�b�N�̃|�C���^��nullptr�ɂ���
		m_pJoystick = nullptr;
	}
	//�����L�[�{�[�h�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pKeyboard != nullptr)
	{
		//�L�[�{�[�h�̏I�������֐��Ăяo��
		m_pKeyboard->Uninit();
		//�L�[�{�[�h�̃������j��
		delete m_pKeyboard;
		//�L�[�{�[�h�̃|�C���^��nullptr�ɂ���
		m_pKeyboard = nullptr;
	}
	//�����T�E���h�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pSound != nullptr)
	{
		//�T�E���h�̏I�������֐��Ăяo��
		m_pSound->Uninit();
		//�T�E���h�̃������j��
		delete m_pSound;
		//�T�E���h�̃|�C���^��nullptr�ɂ���
		m_pSound = nullptr;
	}
	//���������_���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pRenderer != nullptr)
	{
		//�����_���[�̏I�������֐��Ăяo��
		m_pRenderer->Uninit();
		//�����_���[�̃������j��
		delete m_pRenderer;
		//�����_���[�̃|�C���^��nullptr�ɂ���
		m_pRenderer = nullptr;
	}
	//�����t�F�[�h�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pFade != nullptr)
	{
		//�t�F�[�h�̏I�������֐��Ăяo��
		m_pFade->Uninit();
		//�t�F�[�h�̃������j��
		delete m_pFade;
		//�t�F�[�h�̃|�C���^��nullptr�ɂ���
		m_pFade = nullptr;
	}
}