//=============================================================================
//
// �� [enemy_flower.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "mode_game.h"
#include "renderer.h"
#include "scene2d.h"
#include "enemy_flower.h"
#include "player.h"
#include "bullet.h"
#include "item_life.h"
#include "explosion_death.h"
#include "bullet_flower.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/flower.png")
#define SIZE (D3DXVECTOR3(100.0f,100.0f,0.0f))
#define LIFE (13)
#define SCORE (50000)
#define SPEED (D3DXVECTOR3(0.0f,5.0f,0.0f))
#define RATE_MOVE (0.03f)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyFlower::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyFlower::CEnemyFlower(int nPriority)
{
	m_nCounterAnime = 0;					//�A�j���J�E���^
	m_nPatternAnime = 0;					//�A�j���p�^�[��
	m_nBulletTime = 0;						//�e�̔��ˊԊu
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyFlower::~CEnemyFlower()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CEnemyFlower::TextureLoad(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE,						// �t�@�C���̖��O
		&m_pTexture);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CEnemyFlower::TextureUnload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CEnemyFlower * CEnemyFlower::Create(D3DXVECTOR3 Position)
{
	CEnemyFlower * pEnemyFlower;
	pEnemyFlower = new CEnemyFlower;
	pEnemyFlower->SetPosition(Position);
	pEnemyFlower->Init();
	return pEnemyFlower;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CEnemyFlower::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.250f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.250f * m_nPatternAnime + 0.250f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.250f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.250f * m_nPatternAnime + 0.250f, 1.0f);
	//�G�̏����������֐��Ăяo��
	CEnemy::Init();
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�̗͂̏����ݒ�
	SetLife(LIFE);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	//��Ԃ��ړ���
	SetState(STATE_MOVE);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CEnemyFlower::Uninit(void)
{
	//�G�̏I�������֐��Ăяo��
	CEnemy::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CEnemyFlower::Update(void)
{
	//�G�̍X�V�����֐��Ăяo��
	CEnemy::Update();
	//�U�������֐��Ăяo��
	if (GetState() != STATE_MOVE)
	{
		Attack();
	}
	//�������C�t��0�ɂȂ�����
	if (GetLife() <= 0)
	{
		//���S�����֐��Ăяo��
		Death();
	}
	//�A�j���[�V���������֐��Ăяo��
	Animation();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CEnemyFlower::Draw(void)
{
	//�G�̕`�揈���֐��Ăяo��
	CEnemy::Draw();
}

//=============================================================================
// �U�������֐�
//=============================================================================
void CEnemyFlower::Attack(void)
{
	//�v���C���[���擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		//�����v���C���[�̏�Ԃ����S��Ԃ���Ȃ��Ƃ�
		if (pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			//�e�𔭎˂���܂ł̎���
			if (m_nBulletTime >= 50)
			{
				if (m_nBulletTime % 20 == 0)
				{

				}
			}
		}
		//�e�𔭎˂���܂ł̎��Ԃ����Z����
		m_nBulletTime++;
	}
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CEnemyFlower::Death(void)
{
	//�v���C���[���擾����
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	if (pPlayer != NULL)
	{
		//�����G�t�F�N�g�̐���
		CExplosionDeath::Create(GetPosition());
		//�������̍Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
		//�v���C���[�̃X�R�A�����Z����
		pPlayer->AddScore(SCORE);
	}
	//�h���b�v�����֐��Ăяo��
	Drop();
	//�I�������֐��Ăяo��
	Uninit();
	return;
}

//=============================================================================
// �h���b�v�����֐�
//=============================================================================
void CEnemyFlower::Drop(void)
{
	//�̗͉񕜃A�C�e���𗎂Ƃ�
	CItemLife::Create(GetPosition());
}

//=============================================================================
// �A�j���[�V���������֐�
//=============================================================================
void CEnemyFlower::Animation(void)
{
	//�J�E���g�C���N�������g
	m_nCounterAnime++;
	//�J�E���g��4�ȏ�ɂȂ����ꍇ
	if (m_nCounterAnime > 16)
	{
		//�J�E���g��0�ɂ���
		m_nCounterAnime = 0;

		//�p�^�[���̃C���N�������g
		m_nPatternAnime++;
	}
	//�A�j���[�V�����̃J�E���g��i�߂�
	m_nCounterAnime++;
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.250f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.250f * m_nPatternAnime + 0.250f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.250f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.250f * m_nPatternAnime + 0.250f, 1.0f);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
}
