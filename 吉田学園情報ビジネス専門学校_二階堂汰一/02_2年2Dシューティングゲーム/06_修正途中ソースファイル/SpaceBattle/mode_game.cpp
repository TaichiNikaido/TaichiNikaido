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
#include "sound.h"
#include "mode_game.h"
#include "player.h"
#include "enemy_eye_normal.h"
#include "enemy_eye_hard.h"
#include "enemy_spider.h"
#include "enemy_flower.h"
#include "enemy_dragon.h"
#include "wormhole.h"
#include "background_manager.h"
#include "ui_score.h"
#include "ui_bomb.h"
#include "ui_life.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CScoreUI * CGameMode::m_pScoreUI = NULL;	//�X�R�A��UI�ւ̃|�C���^
CBombUI * CGameMode::m_pBombUI = NULL;		//���e��UI�ւ̃|�C���^
CLifeUI * CGameMode::m_pLifeUI = NULL;		//�̗͂�UI�ւ̃|�C���^
CPlayer * CGameMode::m_pPlayer = NULL;		//�v���C���[�ւ̃|�C���^
CEnemy * CGameMode::m_pEnemy = NULL;		//�G�ւ̃|�C���^
CEnemyDragon * CGameMode::m_pDragon = NULL;	//�h���S���ւ̃|�C���^
CWarning * CGameMode::m_pWarning = NULL;	//�댯�n�тւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameMode::CGameMode()
{
	m_nFlameCount = 0;	//�t���[����
	m_bReplay = false;	//���v���C�̐^�U
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
	CGameMode * pGameMode;
	pGameMode = new CGameMode;
	pGameMode->Init();
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
	//�S���������֐��Ăяo��
	CreateAll();
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
	//�t���[���J�E���g��i�߂�
	m_nFlameCount++;
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CGameMode::Draw(void)
{
}

//=============================================================================
// ���v���C�̐^�U�ݒ�֐�
//=============================================================================
void CGameMode::SetbReplay(bool bReplay)
{
	//���v���C�̐^�U��ݒ肷��
	m_bReplay = bReplay;
}

//=============================================================================
// �S���������֐�
//=============================================================================
void CGameMode::CreateAll(void)
{
	//�w�i�Ǘ��̐���
	CBackgroundManager::Create();
	//�X�R�A��UI�̐���
	m_pScoreUI = CScoreUI::Create();
	//�̗͂�UI�̐���
	m_pLifeUI = CLifeUI::Create();
	//���e��UI�̐���
	m_pBombUI = CBombUI::Create();
	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(PLAYER_POS,PLAYER_SIZE);

	//CEnemyEyeNormal::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0.0f));

	//CEnemyEyeHard::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	//CEnemySpider::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	CEnemyFlower::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	//CWormhole::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	//m_pDragon = CEnemyDragon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f));
}