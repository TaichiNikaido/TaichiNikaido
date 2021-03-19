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
#include "enemy_skeleton.h"
#include "weapon_sword.h"
#include "weapon_shield.h"
#include "enemy_dragon.h"
#include "object_wood_house.h"
#include "object_stone_house.h"
#include "object_fountain.h"
#include "object_fence.h"
#include "object_corpse.h"
#include "gauge.h"
#include "floor.h"
#include "button.h"
#include "particle_texture_sparks.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CRenderer * CManager::m_pRenderer = NULL;		//�����_���[�ւ̃|�C���^
CSound * CManager::m_pSound = NULL;				//�T�E���h�ւ̃|�C���^
CKeyboard * CManager::m_pKeyboard = NULL;		//�L�[�{�[�h�ւ̃|�C���^
CJoystick * CManager::m_pJoystick = NULL;		//�}�l�[�W���[�ւ̃|�C���^
CGameMode * CManager::m_pGameMode = NULL;		//�Q�[�����[�h�ւ̃|�C���^
CResultMode * CManager::m_pResultMode = NULL;	//���U���g���[�h�ւ̃|�C���^
CRankingMode * CManager::m_pRankingMode = NULL;	//���U���g���[�h�ւ̃|�C���^
CFade * CManager::m_pFade = NULL;				//�t�F�[�h�ւ̃|�C���^
CManager::MODE  CManager::m_Mode = MODE_NONE;	//���[�h
bool CManager::m_bUseFade = false;				//�t�F�[�h���Ă邩

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
	}
	//�����_���[�̏����������֐��Ăяo��
	m_pRenderer->Init(hWnd, TRUE);
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
	}
	//�T�E���h�̏����������֐��Ăяo��
	m_pSound->Init(hWnd);
	//�����L�[�{�[�h�̃|�C���^��NULL�̏ꍇ
	if (m_pKeyboard == NULL)
	{
		//�L�[�{�[�h�̃������m��
		m_pKeyboard = new CKeyboard;
	}
	//�L�[�{�[�h�̏����������֐��Ăяo��
	m_pKeyboard->Init(hInsitance, hWnd);
	//�����W���C�X�e�B�b�N�̃|�C���^��NULL�̏ꍇ
	if (m_pJoystick == NULL)
	{
		//�W���C�X�e�B�b�N�̃������m��
		m_pJoystick = new CJoystick;
	}
	//�W���C�X�e�B�b�N�̏����������֐��Ăяo��
	m_pJoystick->Init(hInsitance, hWnd);
	//�S�ǂݍ��݊֐��Ăяo��
	LoadAll();
	//���[�h�̐ݒ�
	SetMode(MODE_TITLE);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CManager::Uninit(void)
{
	//�V�[���̑S�j�������֐��Ăяo��
	CScene::ReleaseAll();
	//�T�E���h�̒�~
	m_pSound->StopSound();
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
	//���������_���[�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pRenderer != NULL)
	{
		//�����_���[�̍X�V�����֐��Ăяo��
		m_pRenderer->Update();
	}
	//�����L�[�{�[�h�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pKeyboard != NULL)
	{
		//�L�[�{�[�h�̍X�V�����֐��Ăяo��
		m_pKeyboard->Update();
	}
	//�����W���C�X�e�B�b�N�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pJoystick != NULL)
	{
		//�W���C�X�e�B�b�N�̍X�V�����֐��Ăяo��
		m_pJoystick->Update();
	}
	//�����t�F�[�h���ꂽ��
	if (m_bUseFade == true)
	{
		//�����t�F�[�h�̃|�C���^��NULL����Ȃ��ꍇ
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
	//�T�E���h���~����
	m_pSound->StopSound();
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
		CTutorialMode::Create();
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
	//�X�P���g���̃��f���ǂݍ���
	CSkeleton::ModelLoad();
	//���̃��f���ǂݍ���
	CSword::ModelLoad();
	//���̃��f���ǂݍ���
	CShield::ModelLoad();
	//�h���S�����f���ǂݍ���
	//CDragon::ModelLoad();
	//�ؑ��̉ƃ��f���ǂݍ���
	CWoodHouse::ModelLoad();
	//�Α��̉ƃ��f���ǂݍ���
	CStoneHouse::ModelLoad();
	//�����̃��f���ǂݍ���
	CFountain::ModelLoad();
	//�t�F���X�̃��f���ǂݍ���
	CFence::ModelLoad();
	//�r�̃��f���ǂݍ���
	CCorpse::ModelLoad();
	//�Q�[�W�̃e�N�X�`���ǂݍ���
	CGauge::TextureLoad();
	//�n�ʂ̃e�N�X�`���ǂݍ���
	CFloor::TextureLoad();
	//�{�^���̃e�N�X�`���ǂݍ���
	CButton::TextureLoad();
	//�΂̕��̃e�N�X�`���ǂݍ���
	//CSparksTexture::TextureLoad();
}

//=============================================================================
// �S�ǂݍ��ݔj�������֐�
//=============================================================================
void CManager::UnloadAll(void)
{
	//�v���C���[�̃��f���j��
	CPlayer::ModelUnload();
	//�X�P���g���̃��f���j��
	CSkeleton::ModelUnload();
	//���̃��f���j��
	CSword::ModelUnload();
	//���̃��f���j��
	CShield::ModelUnload();
	//�h���S�����f���j��
	//CDragon::ModelUnload();
	//�ؑ��̉ƃ��f���j��
	CWoodHouse::ModelUnload();
	//�Α��̉ƃ��f���j��
	CStoneHouse::ModelUnload();
	//�����̃��f���j��
	CFountain::ModelUnload();
	//�t�F���X�̃��f���j��
	CFence::ModelUnload();
	//�r�̃��f���j��
	CCorpse::ModelUnload();
	//�Q�[�W�̃e�N�X�`���j��
	CGauge::TextureUnload();
	//�n�ʂ̃e�N�X�`���j��
	CFloor::TextureUnload();
	//�{�^���̃e�N�X�`���j��
	CButton::TextureUnload();
	//�΂̕��̃e�N�X�`���j��
	//CSparksTexture::TextureUnload();
}

//=============================================================================
// �S�j�������֐�
//=============================================================================
void CManager::DeleteAll(void)
{
	//�����W���C�X�e�B�b�N�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pJoystick != NULL)
	{
		//�W���C�X�e�B�b�N�̏I�������֐��Ăяo��
		m_pJoystick->Uninit();
		//�W���C�X�e�B�b�N�̃������j��
		delete m_pJoystick;
		//�W���C�X�e�B�b�N�̃|�C���^��NULL�ɂ���
		m_pJoystick = NULL;
	}
	//�����L�[�{�[�h�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pKeyboard != NULL)
	{
		//�L�[�{�[�h�̏I�������֐��Ăяo��
		m_pKeyboard->Uninit();
		//�L�[�{�[�h�̃������j��
		delete m_pKeyboard;
		//�L�[�{�[�h�̃|�C���^��NULL�ɂ���
		m_pKeyboard = NULL;
	}
	//�����T�E���h�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pSound != NULL)
	{
		//�T�E���h�̏I�������֐��Ăяo��
		m_pSound->Uninit();
		//�T�E���h�̃������j��
		delete m_pSound;
		//�T�E���h�̃|�C���^��NULL�ɂ���
		m_pSound = NULL;
	}
	//���������_���[�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pRenderer != NULL)
	{
		//�����_���[�̏I�������֐��Ăяo��
		m_pRenderer->Uninit();
		//�����_���[�̃������j��
		delete m_pRenderer;
		//�����_���[�̃|�C���^��NULL�ɂ���
		m_pRenderer = NULL;
	}
	//�����t�F�[�h�̃|�C���^��NULL����Ȃ��ꍇ
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
