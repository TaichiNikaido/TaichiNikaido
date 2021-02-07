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
#include "enemy_bomb_head.h"
#include "enemy_bomb_body.h"
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
CEnemyDragon * CGameMode::m_pDragon = NULL;	//�h���S���ւ̃|�C���^
CWarning * CGameMode::m_pWarning = NULL;	//�댯�n�тւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameMode::CGameMode()
{
	m_nFlameCount = 0;	//�t���[����
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
	if (m_nFlameCount == 50)
	{
		for (int nCount = 0; nCount < 4; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 1.5f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 350)
	{
		for (int nCount = 0; nCount < 5; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 1.5f + 150.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 750)
	{
		CEnemySpider::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 950)
	{
		CEnemyBombHead::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}
	if (m_nFlameCount == 1050)
	{
		for (int nCount = 0; nCount < 2; nCount++)
		{
			CEnemyEyeHard::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 1.5f + 100.0f + 400.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 1350)
	{
		for (int nCount = 0; nCount < 4; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 1550)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 1900)
	{
		for (int nCount = 0; nCount < 3; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 700.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
		CEnemyFlower::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 2.0f + FIELD_WIDTH / 2, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 2200)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
		CEnemyFlower::Create(D3DXVECTOR3(FIELD_WIDTH_MIN* 2.0f + 700, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 2500)
	{
		CEnemySpider::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 2700)
	{
		CEnemyBombHead::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}
	if (m_nFlameCount == 2900)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 3200)
	{
		for (int nCount = 0; nCount < 3; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN* 2.0f + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
		CEnemyFlower::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 2.0f + FIELD_WIDTH / 4, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 3450)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 3700)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
		for (int nCount = 0; nCount < 2; nCount++)
		{
			CEnemyEyeHard::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 1.5f + 100.0f + 400.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 4200)
	{
		CWormhole::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, FIELD_HEIGHT / 4, 0.0f));
	}
	if (m_nFlameCount == 4600)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 4800)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 5000)
	{
		CEnemyBombHead::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}
	if (m_nFlameCount % 10 == 0 && m_nFlameCount > 5008 && m_nFlameCount < 5100)
	{
	}
	if (m_nFlameCount == 5200)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 5500)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 6000)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	//�t���[���J�E���g��i�߂�
	m_nFlameCount++;
}