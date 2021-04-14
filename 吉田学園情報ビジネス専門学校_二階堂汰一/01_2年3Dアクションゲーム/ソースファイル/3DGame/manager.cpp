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
#include "mode_title.h"
#include "mode_name.h"
#include "mode_tutorial.h"
#include "mode_game.h"
#include "mode_result.h"
#include "mode_ranking.h"
#include "scene.h"
#include "scene2d.h"
#include "sound.h"
#include "input.h"
#include "keyboard.h"
#include "joystick.h"
#include "fade.h"
#include "player.h"
#include "weapon_sword.h"
#include "weapon_shield.h"
#include "enemy_dragon.h"
#include "floor.h"
#include "button_any.h"
#include "button_start.h"
#include "button_tutorial.h"
#include "button_ranking.h"
#include "button_exit.h"
#include "button_quit_game.h"
#include "button_controller_guid.h"
#include "button_back_to_title.h"
#include "title_logo.h"
#include "letter.h"
#include "skybox.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CRenderer * CManager::m_pRenderer = NULL;			//�����_���[�̃|�C���^
CSound * CManager::m_pSound = NULL;					//�T�E���h�̃|�C���^
CKeyboard * CManager::m_pKeyboard = NULL;			//�L�[�{�[�h�̃|�C���^
CJoystick * CManager::m_pJoystick = NULL;			//�}�l�[�W���[�̃|�C���^
CTutorialMode * CManager::m_pTutorialMode = NULL;	//�`���[�g���A�����[�h�̃|�C���^
CGameMode * CManager::m_pGameMode = NULL;			//�Q�[�����[�h�̃|�C���^
CResultMode * CManager::m_pResultMode = NULL;		//���U���g���[�h�̃|�C���^
CRankingMode * CManager::m_pRankingMode = NULL;		//�����L���O���[�h�̃|�C���^
CFade * CManager::m_pFade = NULL;					//�t�F�[�h�ւ̃|�C���^
CManager::MODE  CManager::m_Mode = MODE_NONE;		//���[�h
bool CManager::m_bUseFade = false;					//�t�F�[�h�̎g�p���

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
	//���������_���[�̃|�C���^��NULL�̏ꍇ
	if (m_pRenderer == NULL)
	{
		//�����_���[�̃��������m��
		m_pRenderer = new  CRenderer;
		//���������_���[�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (m_pRenderer != NULL)
		{
			//�����_���[�̏����������֐��Ăяo��
			m_pRenderer->Init(hWnd, TRUE);
		}
	}
	//�����t�F�[�h�̃|�C���^��NULL�̏ꍇ
	if (m_pFade == NULL)
	{
		//�t�F�[�h�̐��������֐��Ăяo��
		m_pFade = CFade::Create(m_Mode);
	}
	//�����T�E���h�̃|�C���^��NULL�̏ꍇ
	if (m_pSound == NULL)
	{
		//�T�E���h�̃������m��
		m_pSound = new CSound;
		//�����T�E���h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (m_pSound != NULL)
		{
			//�T�E���h�̏����������֐��Ăяo��
			m_pSound->Init(hWnd);
		}
	}
	//�����L�[�{�[�h�̃|�C���^��NULL�̏ꍇ
	if (m_pKeyboard == NULL)
	{
		//�L�[�{�[�h�̃������m��
		m_pKeyboard = new CKeyboard;
		//�����L�[�{�[�h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (m_pKeyboard != NULL)
		{
			//�L�[�{�[�h�̏����������֐��Ăяo��
			m_pKeyboard->Init(hInsitance, hWnd);
		}
	}
	//�����W���C�X�e�B�b�N�̃|�C���^��NULL�̏ꍇ
	if (m_pJoystick == NULL)
	{
		//�W���C�X�e�B�b�N�̃������m��
		m_pJoystick = new CJoystick;
		//�����W���C�X�e�B�b�N�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (m_pJoystick != NULL)
		{
			//�W���C�X�e�B�b�N�̏����������֐��Ăяo��
			m_pJoystick->Init(hInsitance, hWnd);
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
	//�����T�E���h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (m_pSound != NULL)
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
	//���������_���[�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (m_pRenderer != NULL)
	{
		//�����_���[�̍X�V�����֐��Ăяo��
		m_pRenderer->Update();
	}
	//�����L�[�{�[�h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (m_pKeyboard != NULL)
	{
		//�L�[�{�[�h�̍X�V�����֐��Ăяo��
		m_pKeyboard->Update();
	}
	//�����W���C�X�e�B�b�N�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (m_pJoystick != NULL)
	{
		//�W���C�X�e�B�b�N�̍X�V�����֐��Ăяo��
		m_pJoystick->Update();
	}
	//�����t�F�[�h���ꂽ��
	if (m_bUseFade == true)
	{
		//�����t�F�[�h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (m_pFade != NULL)
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
	CShadow::ModelLoad();
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
	CShadow::ModelUnload();
}

//=============================================================================
// �S�j�������֐�
//=============================================================================
void CManager::DeleteAll(void)
{
	//�����W���C�X�e�B�b�N�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (m_pJoystick != NULL)
	{
		//�W���C�X�e�B�b�N�̏I�������֐��Ăяo��
		m_pJoystick->Uninit();
		//�W���C�X�e�B�b�N�̃������j��
		delete m_pJoystick;
		//�W���C�X�e�B�b�N�̃|�C���^��NULL�ɂ���
		m_pJoystick = NULL;
	}
	//�����L�[�{�[�h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (m_pKeyboard != NULL)
	{
		//�L�[�{�[�h�̏I�������֐��Ăяo��
		m_pKeyboard->Uninit();
		//�L�[�{�[�h�̃������j��
		delete m_pKeyboard;
		//�L�[�{�[�h�̃|�C���^��NULL�ɂ���
		m_pKeyboard = NULL;
	}
	//�����T�E���h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (m_pSound != NULL)
	{
		//�T�E���h�̏I�������֐��Ăяo��
		m_pSound->Uninit();
		//�T�E���h�̃������j��
		delete m_pSound;
		//�T�E���h�̃|�C���^��NULL�ɂ���
		m_pSound = NULL;
	}
	//���������_���[�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (m_pRenderer != NULL)
	{
		//�����_���[�̏I�������֐��Ăяo��
		m_pRenderer->Uninit();
		//�����_���[�̃������j��
		delete m_pRenderer;
		//�����_���[�̃|�C���^��NULL�ɂ���
		m_pRenderer = NULL;
	}
	//�����t�F�[�h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (m_pFade != NULL)
	{
		//�t�F�[�h�̏I�������֐��Ăяo��
		m_pFade->Uninit();
		//�t�F�[�h�̃������j��
		delete m_pFade;
		//�t�F�[�h�̃|�C���^��NULL�ɂ���
		m_pFade = NULL;
	}
}