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
#include "manager.h"
#include "mode_title.h"
#include "mode_name.h"
#include "mode_tutorial.h"
#include "mode_game.h"
#include "mode_result.h"
#include "mode_ranking.h"
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"
#include "keyboard.h"
#include "joystick.h"
#include "player.h"
#include "enemy_eye_normal.h"
#include "enemy_eye_hard.h"
#include "enemy_spider.h"
#include "enemy_flower.h"
#include "enemy_dragon.h"
#include "enemy_bomb_head.h"
#include "enemy_bomb_body.h"
#include "bullet_player.h"
#include "bullet_enemy.h"
#include "bullet_fireball.h"
#include "bullet_n-way.h"
#include "bullet_direction.h"
#include "bullet_homing.h"
#include "bullet_flower.h"
#include "bullet_bomb.h"
#include "item_bomb.h"
#include "item_life.h"
#include "item_levelup.h"
#include "ui_number_texture.h"
#include "ui_bomb_texture.h"
#include "ui_life_texture.h"
#include "background_under_layer.h"
#include "background_middle_layer.h"
#include "background_upper_layer.h"
#include "background_title.h"
#include "background_name.h"
#include "background_tutorial.h"
#include "background_result.h"
#include "background_ranking.h"
#include "fade.h"
#include "effect.h"
#include "button.h"
#include "name.h"
#include "explosion_bomb.h"
#include "explosion_death.h"
#include "explosion_fireball.h"
#include "wormhole.h"
#include "warning.h"
#include "text.h"
#include "flame.h"
#include "gameclear_logo.h"
#include "continue_logo.h"

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
CText * CManager::m_pText = NULL;				//�e�L�X�g�ւ̃|�C���^
CManager::MODE  CManager::m_Mode = MODE_NONE;	//���[�h
bool CManager::m_bUseFade = false;				//�t�F�[�h�̐^�U

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
	//�����_���[�̐���
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new  CRenderer;
	}
	//�����_���[�̏���������
	m_pRenderer->Init(hWnd, TRUE);
	if (m_pFade == NULL)
	{
		//�t�F�[�h�̐��������֐��Ăяo��
		m_pFade = CFade::Create(m_Mode);
	}
	//�T�E���h�̐���
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}
	//�T�E���h�̏�����
	m_pSound->Init(hWnd);
	//�L�[�{�[�h�̐���
	if (m_pKeyboard == NULL)
	{
		m_pKeyboard = new CKeyboard;
	}
	//�L�[�{�[�h�̏�����
	m_pKeyboard->Init(hInsitance, hWnd);
	//�W���C�X�e�B�b�N�̐���
	if (m_pJoystick == NULL)
	{
		m_pJoystick = new CJoystick;
	}
	//�W���C�X�e�B�b�N�̏�����
	m_pJoystick->Init(hInsitance, hWnd);
	//�e�L�X�g�̐���
	m_pText = CText::Create();
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
	//�`��̍X�V
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
	//�L�[�{�[�h�̍X�V
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}
	//�L�[�{�[�h�̍X�V
	if (m_pJoystick != NULL)
	{
		m_pJoystick->Update();
	}
	//�t�F�[�h�X�V
	if (m_bUseFade == true)
	{
		if (m_pFade != NULL)
		{
			m_pFade->Update();
		}
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CManager::Draw(void)
{
	//�����_���[�̕`��
	m_pRenderer->Draw();
}

//=============================================================================
// �t�F�[�h�J�n�����֐�
//=============================================================================
void CManager::StartFade(MODE mode)
{
	m_Mode = mode;
	m_bUseFade = true;
	CText::IsDrawText(false);
}

//=============================================================================
// �t�F�[�h��~�����֐�
//=============================================================================
void CManager::StopFade(void)
{
	CText::IsDrawText(true);
	m_bUseFade = false;
}

//=============================================================================
// ���[�h�ݒ�֐�
//=============================================================================
void CManager::SetMode(MODE Mode)
{
	CScene::ReleaseAll();
	//�T�E���h���~����
	m_pSound->StopSound();
	//���[�h��ݒ肷��
	m_Mode = Mode;
	switch (m_Mode)
	{
	case MODE_TITLE:
		CTitleMode::Create();
		break;
	case MODE_NAME:
		CNameMode::Create();
		break;
	case MODE_TUTORIAL:
		CTutorialMode::Create();
		break;
	case MODE_GAME:
		m_pGameMode = CGameMode::Create();
		break;
	case MODE_RESULT:
		m_pResultMode = CResultMode::Create();
		break;
	case MODE_RANKING:
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
	//�v���C���[�̃e�N�X�`���ǂݍ���
	CPlayer::TextureLoad();
	//�ڋ�(�m�[�}��)�̃e�N�X�`���ǂݍ���
	CEnemyEyeNormal::TextureLoad();
	//�ڋ�(�n�[�h)�̃e�N�X�`���ǂݍ���
	CEnemyEyeHard::TextureLoad();
	//�w偂̃e�N�X�`���ǂݍ���
	CEnemySpider::TextureLoad();
	//�Ԃ̃e�N�X�`���ǂݍ���
	CEnemyFlower::TextureLoad();
	//�h���S���̃e�N�X�`���ǂݍ���
	CEnemyDragon::TextureLoad();
	//���e�G�̓��e�N�X�`���ǂݍ���
	CEnemyBombHead::TextureLoad();
	//���e�G�̑̃e�N�X�`���ǂݍ���
	CEnemyBombBody::TextureLoad();
	//�v���C���[�̒e�̃e�N�X�`���ǂݍ���
	CBulletPlayer::TextureLoad();
	//�΋��̃e�N�X�`���ǂݍ���
	CBulletFireball::TextureLoad();
	//n-way�̃e�N�X�`���ǂݍ���
	CBulletN_Way::TextureLoad();
	//�����e�̃e�N�X�`���ǂݍ���
	CBulletDirection::TextureLoad();
	//�z�[�~���O�e�̃e�N�X�`��
	CBulletHoming::TextureLoad();
	//�Ԓe�̃e�N�X�`��
	CBulletFlower::TextureLoad();
	//���e�̃e�N�X�`���ǂݍ���
	CBulletBomb::TextureLoad();
	//���e�t�^�A�C�e���e�N�X�`���ǂݍ���
	CItemBomb::TextureLoad();
	//�̗͕t�^�A�C�e���e�N�X�`���ǂݍ���
	CItemLife::TextureLoad();
	//���x���A�b�v�A�C�e���e�N�X�`���ǂݍ���
	CItemLevelUP::TextureLoad();
	//UI�p�����e�N�X�`���ǂݍ���
	CUINumberTexture::TextureLoad();
	//UI�p���e�e�N�X�`���ǂݍ���
	CUIBombTexture::TextureLoad();
	//UI�p�̗̓e�N�X�`���ǂݍ���
	CUILifeTexture::TextureLoad();
	//���w�w�i�e�N�X�`���ǂݍ���
	CBackgroundUnderLayer::TextureLoad();
	//���w�w�i�e�N�X�`���ǂݍ���
	CBackgroundMiddleLayer::TextureLoad();
	//��w�w�i�e�N�X�`���ǂݍ���
	CBackgroundUpperLayer::TextureLoad();
	//�^�C�g���w�i�e�N�X�`���ǂݍ���
	CBackgroundTitle::TextureLoad();
	//���O���͔w�i�e�N�X�`���ǂݍ���
	CBackgroundName::TextureLoad();
	//�`���[�g���A���w�i�e�N�X�`���ǂݍ���
	CBackgroundTutorial::TextureLoad();
	//���U���g�w�i�e�N�X�`���ǂݍ���
	CBackgroundResult::TextureLoad();
	//�����L���O�w�i�e�N�X�`���ǂݍ���
	CBackgroundRanking::TextureLoad();
	//�G�t�F�N�g�e�N�X�`���ǂݍ���
	CEffect::TextureLoad();
	//�{�^���e�N�X�`���ǂݍ���
	CButton::TextureLoad();
	//���O�e�N�X�`���ǂݍ���
	CName::TextureLoad();
	//���e�����e�N�X�`���ǂݍ���
	CExplosionBomb::TextureLoad();
	//���S�������e�N�X�`���ǂݍ���
	CExplosionDeath::TextureLoad();
	//�΋������e�N�X�`���ǂݍ���
	CExplosionFireball::TextureLoad();
	//���[���z�[���e�N�X�`���ǂݍ���
	CWormhole::TextureLoad();
	//���[�j���O�e�N�X�`���ǂݍ���
	CWarning::TextureLoad();
	//�t���[���e�N�X�`���ǂݍ���
	CFlame::TextureLoad();
	//�Q�[���N���A���S�̃e�N�X�`���ǂݍ���
	CGameClearLogo::TextureLoad();
	//�R���e�B�j���[���S�̃e�N�X�`���ǂݍ���
	CContinueLogo::TextureLoad();
}

//=============================================================================
// �S�ǂݍ��ݔj�������֐�
//=============================================================================
void CManager::UnloadAll(void)
{
	//�v���C���[�̃e�N�X�`���j��
	CPlayer::TextureUnload();
	//�ڋ�(�m�[�}��)�̃e�N�X�`���j��
	CEnemyEyeNormal::TextureUnload();
	//�ڋ�(�n�[�h)�̃e�N�X�`���j��
	CEnemyEyeHard::TextureUnload();
	//�w偂̃e�N�X�`���j��
	CEnemySpider::TextureUnload();
	//�Ԃ̃e�N�X�`���j��
	CEnemyFlower::TextureUnload();
	//�h���S���̃e�N�X�`���j��
	CEnemyDragon::TextureUnload();
	//���e�G�̓��e�N�X�`���j��
	CEnemyBombHead::TextureUnload();
	//���e�G�̑̃e�N�X�`���ǂݍ���
	CEnemyBombBody::TextureUnload();
	//�v���C���[�̒e�̃e�N�X�`���j��
	CBulletPlayer::TextureUnload();
	//�΋��̃e�N�X�`���j��
	CBulletFireball::TextureUnload();
	//n-way�̃e�N�X�`���j��
	CBulletN_Way::TextureUnload();
	//�����e�̃e�N�X�`���j��
	CBulletDirection::TextureUnload();
	//�z�[�~���O�e�̃e�N�X�`���j��
	CBulletHoming::TextureUnload();
	//�Ԓe�̃e�N�X�`���j��
	CBulletFlower::TextureUnload();
	//���e�̃e�N�X�`��
	CBulletBomb::TextureUnload();
	//���e�t�^�A�C�e���e�N�X�`���j��
	CItemBomb::TextureUnload();
	//�̗͕t�^�A�C�e���e�N�X�`���j��
	CItemLife::TextureUnload();
	//���x���A�b�v�A�C�e���e�N�X�`���j��
	CItemLevelUP::TextureUnload();
	//UI�p�����e�N�X�`���j��
	CUINumberTexture::TextureUnload();
	//UI�p���e�e�N�X�`���j��
	CUIBombTexture::TextureUnload();
	//UI�p���C�t�e�N�X�`���j��
	CUILifeTexture::TextureUnload();
	//���w�w�i�e�N�X�`���j��
	CBackgroundUnderLayer::TextureUnload();
	//���w�w�i�e�N�X�`���j��
	CBackgroundMiddleLayer::TextureUnload();
	//��w�w�i�e�N�X�`���j��
	CBackgroundUpperLayer::TextureUnload();
	//�^�C�g���w�i�e�N�X�`���j��
	CBackgroundTitle::TextureUnload();
	//���O���͔w�i�e�N�X�`���j��
	CBackgroundName::TextureUnload();
	//�`���[�g���A���w�i�e�N�X�`���j��
	CBackgroundTutorial::TextureUnload();
	//���U���g�w�i�e�N�X�`���j��
	CBackgroundResult::TextureUnload();
	//�����L���O�w�i�e�N�X�`���j��
	CBackgroundRanking::TextureUnload();
	//�G�t�F�N�g�e�N�X�`���j��
	CEffect::TextureUnload();
	//�{�^���e�N�X�`���j��
	CButton::TextureUnload();
	//���O�e�N�X�`���j��
	CName::TextureUnload();
	//���e�����e�N�X�`���j��
	CExplosionBomb::TextureUnload();
	//���S�������e�N�X�`���j��
	CExplosionDeath::TextureUnload();
	//�΋������e�N�X�`���j��
	CExplosionFireball::TextureUnload();
	//���[���z�[���e�N�X�`���j��
	CWormhole::TextureUnload();
	//���[�j���O�e�N�X�`���j��
	CWarning::TextureUnload();
	//�t���[���e�N�X�`���j��
	CFlame::TextureUnload();
	//�Q�[���N���A���S�̃e�N�X�`���j��
	CGameClearLogo::TextureUnload();
	//�R���e�B�j���[���S�̃e�N�X�`���j��
	CContinueLogo::TextureUnload();
}

//=============================================================================
// �S�j�������֐�
//=============================================================================
void CManager::DeleteAll(void)
{
	//�W���C�X�e�B�b�N�̔j��
	if (m_pJoystick != NULL)
	{
		m_pJoystick->Uninit();
		delete m_pJoystick;
		m_pJoystick = NULL;
	}
	//�L�[�{�[�h�̔j��
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}
	//�T�E���h�̔j��
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	//�����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	//�t�F�[�h�̔j��
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}
}
