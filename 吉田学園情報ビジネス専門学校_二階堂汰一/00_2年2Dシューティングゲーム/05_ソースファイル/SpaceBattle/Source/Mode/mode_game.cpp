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
#include "mode_game.h"
#include "Player/player.h"
#include "Enemy/enemy_eye_normal.h"
#include "Enemy/enemy_eye_hard.h"
#include "Enemy/enemy_spider.h"
#include "Enemy/enemy_flower.h"
#include "Enemy/enemy_dragon.h"
#include "Enemy/enemy_bomb_head.h"
#include "Enemy/enemy_bomb_body.h"
#include "2DPolygon/wormhole.h"
#include "Background/background_manager.h"
#include "UI/ui_score.h"
#include "UI/ui_bomb.h"
#include "UI/ui_life.h"
#include "2DPolygon/flame.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MINIMUM_FLAME_COUNT (0)	//�t���[���̐��̍ŏ��l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CScoreUI * CGameMode::m_pScoreUI = NULL;				//�X�R�A��UI�ւ̃|�C���^
CBombUI * CGameMode::m_pBombUI = NULL;					//���e��UI�ւ̃|�C���^
CLifeUI * CGameMode::m_pLifeUI = NULL;					//�̗͂�UI�ւ̃|�C���^
CPlayer * CGameMode::m_pPlayer = NULL;					//�v���C���[�ւ̃|�C���^
CEnemyDragon * CGameMode::m_pDragon = NULL;				//�h���S���ւ̃|�C���^
CWarning * CGameMode::m_pWarning = NULL;				//�댯�n�тւ̃|�C���^
CBulletFireball * CGameMode::m_pBulletFireBall = NULL;	//�΋��̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameMode::CGameMode()
{
	m_nFlameCount = MINIMUM_FLAME_COUNT;	//�t���[����
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
	//�Q�[�����[�h�̃|�C���^��NULL�������ꍇ
	if (pGameMode == NULL)
	{
		//�Q�[�����[�h�̃������m��
		pGameMode = new CGameMode;
		//�Q�[�����[�h�̃|�C���^��NULL����Ȃ��ꍇ
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
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//BGM�̍Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);
	//�S�������������֐��Ăяo��
	InitCreateAll();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CGameMode::Uninit(void)
{
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CGameMode::Update(void)
{
	//�S�X�V���������֐��Ăяo��
	UpdateCreateAll();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CGameMode::Draw(void)
{
}

//=============================================================================
// �S�������������֐�
//=============================================================================
void CGameMode::InitCreateAll(void)
{
	//�t���[���̐���
	CFlame::Create(D3DXVECTOR3(200, SCREEN_HEIGHT / 2, 0.0f));
	CFlame::Create(D3DXVECTOR3(1720, SCREEN_HEIGHT / 2, 0.0f));
	//�w�i�Ǘ��̐���
	CBackgroundManager::Create();
	//�X�R�A��UI�̐���
	m_pScoreUI = CScoreUI::Create();
	//�̗͂�UI�̐���
	m_pLifeUI = CLifeUI::Create();
	//���e��UI�̐���
	m_pBombUI = CBombUI::Create();
	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(PLAYER_POS, PLAYER_SIZE);
}

//=============================================================================
// �S�X�V���������֐�
//=============================================================================
void CGameMode::UpdateCreateAll(void)
{
	//�t���[���J�E���g��i�߂�
	m_nFlameCount++;

	if (m_nFlameCount == 50)
	{
		CEnemyEyeNormal::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(730.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(960.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1190.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1420.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 350)
	{
		CEnemyEyeHard::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f));
		CEnemyEyeHard::Create(D3DXVECTOR3(1420.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(600.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(900.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1200.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 750)
	{
		CEnemySpider::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 950)
	{
		CEnemyBombHead::Create(D3DXVECTOR3(600.0f, 200.0f, 0.0f));
	}
	if (m_nFlameCount == 1050)
	{
		CEnemyEyeNormal::Create(D3DXVECTOR3(730.0f, 0.0f, 0.0f));
		CEnemyFlower::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1190.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 1350)
	{
		CEnemyFlower::Create(D3DXVECTOR3(600.0f, 0.0f, 0.0f));
		CEnemyFlower::Create(D3DXVECTOR3(1320.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 1850)
	{
		CEnemySpider::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 2000)
	{
		CEnemyBombHead::Create(D3DXVECTOR3(600.0f, 200.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(730.0f, 0.0f, 0.0f));
		CEnemyFlower::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1190.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 2300)
	{
		CEnemyEyeNormal::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(730.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(960.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1190.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1420.0f, 0.0f, 0.0f));
		CEnemyFlower::Create(D3DXVECTOR3(600.0f, 0.0f, 0.0f));
		CEnemyFlower::Create(D3DXVECTOR3(1320.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 2800)
	{
		CWormhole::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4,0.0f));
	}
	if (m_nFlameCount == 3400)
	{
		CEnemyBombHead::Create(D3DXVECTOR3(600.0f, 200.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(730.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(960.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1190.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1420.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 3900)
	{
		CEnemyEyeHard::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(730.0f, 0.0f, 0.0f));
		CEnemyFlower::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1190.0f, 0.0f, 0.0f));
		CEnemyEyeHard::Create(D3DXVECTOR3(1420.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 4300)
	{
		CEnemyEyeNormal::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(730.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(960.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1190.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1420.0f, 0.0f, 0.0f));
	}
}