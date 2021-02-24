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
#define TEXTURE ("Data/Texture/Enemy/flower.png")	//�e�N�X�`��
#define SIZE (D3DXVECTOR3(100.0f,100.0f,0.0f))		//�T�C�Y
#define MINIMUM_LIFE (0)							//�̗͂̍ŏ��l
#define LIFE (13)									//�̗�
#define SCORE (50000)								//�X�R�A
#define MOVE (D3DXVECTOR3(0.0f,5.0f,0.0f))			//�ړ���		
#define RETURN_MOVE (D3DXVECTOR3(0.0f,-10.0f,0.0f))	//�߂�ړ���
#define STOP (D3DXVECTOR3(GetMove().x,GetMove().y + (0.0f - GetMove().y)*RATE_MOVE,GetMove().z))	//��~�ʒu
#define STAY_TIME (500)								//�؍ݎ���
#define BULLET_MOVE (D3DXVECTOR3(cosf(D3DXToRadian(nCount * (360 / 20)))*3.5f, sinf(D3DXToRadian(nCount * (360 / 20)))*3.5f, 0.0f))	//�e�̈ړ���
#define RATE_MOVE (0.03f)							//�ړ���
#define INITIAL_STOP_POSITION (D3DXVECTOR3(0.0f, 0.0f, 0.0f))	//��~�ʒu�̍ŏ��l
#define MINIMUM_COUNTER_ANIME (0)					//�J�E���^�[�A�j���̍ŏ��l
#define MINIMUM_PATTERN_ANIME (0)					//�p�^�[���A�j���̍ŏ��l
#define MINIMUM_SHOT_TIME (0)						//���ˎ��Ԃ̍ŏ��l
#define MINIMUM_COLOR_COUNT (0)						//�F�̍ŏ��J�E���g
#define MINIMUM_STAY_TIME (0)						//�؍ݍŏ�����
#define ANIMATION_VALUE (0.250f)					//�A�j���[�V�����̒l
#define STOP_POSITION (float(rand() % (FIELD_HEIGHT / 8)))	//��~�ʒu
#define SHOT_TIME (50)								//��~����
#define SHOT_COOL_TIME (100)						//�e�̐F�̎���
#define INTERVAL_BULLET (20)						//�e�̊Ԋu
#define MINIMUM_ANIMATION (0)						//�A�j���[�V�����̍ŏ��l
#define MAX_ANIMATION (16)							//�A�j���[�V�����̍ő�l
#define SHOT_VALUE (20)								//���ˉ�

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyFlower::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyFlower::CEnemyFlower()
{
	m_StopPosition = INITIAL_STOP_POSITION;		//��~�ʒu
	m_nCounterAnime = MINIMUM_COUNTER_ANIME;	//�A�j���J�E���^
	m_nPatternAnime = MINIMUM_PATTERN_ANIME;	//�A�j���p�^�[��
	m_nShotTime = MINIMUM_SHOT_TIME;			//�e�𔭎˂���܂ł̎���
	m_nColorCount = MINIMUM_COLOR_COUNT;		//�F�J�E���g
	m_nStayTime = MINIMUM_STAY_TIME;			//�؍ݎ���
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
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
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
	//�����e�N�X�`����NULL����Ȃ��ꍇ
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`����NULL�ɂ���
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CEnemyFlower * CEnemyFlower::Create(D3DXVECTOR3 Position)
{
	//�Ԃ̓G�̃|�C���^
	CEnemyFlower * pEnemyFlower = NULL;
	//�����Ԃ̓G�̃|�C���^��NULL�̏ꍇ
	if (pEnemyFlower == NULL)
	{
		//�Ԃ̓G�̃������m��
		pEnemyFlower = new CEnemyFlower;
		//�����Ԃ̓G�̃|�C���^��NULL����Ȃ��ꍇ
		if (pEnemyFlower != NULL)
		{
			//�ʒu��ݒ肷��
			pEnemyFlower->SetPosition(Position);
			//�����������֐��Ăяo��
			pEnemyFlower->Init();
		}
	}
	//�Ԃ̓G�̃|�C���^��Ԃ�
	return pEnemyFlower;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CEnemyFlower::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
	//�G�̏����������֐��Ăяo��
	CEnemy::Init();
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�̗͂̏����ݒ�
	SetLife(LIFE);
	//�ړ��ʂ̏����ݒ�
	SetMove(MOVE);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	//��Ԃ��ړ���
	SetState(STATE_MOVE);
	//�G�̎~�܂�ʒu���w�肷��
	m_StopPosition.y = STOP_POSITION;
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
	//��Ԃ��ړ���Ԃ���Ȃ��Ƃ�
	if (GetState() != STATE_MOVE)
	{
		//�U�������֐��Ăяo��
		Attack();
	}
	//��~�����֐��Ăяo��
	Stop();
	//�؍ݏ����֐��Ăяo��
	Stay();
	//�A�j���[�V���������֐��Ăяo��
	Animation();
	//�������C�t��0�ɂȂ�����
	if (GetLife() <= MINIMUM_LIFE)
	{
		//���S�����֐��Ăяo��
		Death();
	}
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
	//�ʒu���擾
	D3DXVECTOR3 Position = GetPosition();
	//�����v���C���[��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�����v���C���[�̏�Ԃ����S��Ԃ���Ȃ��Ƃ�
		if (pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			//�e�𔭎˂���܂ł̎���
			if (m_nShotTime >= SHOT_TIME)
			{
				//�Ԋu���Ƃɔ��˂���
				if (m_nShotTime % INTERVAL_BULLET == REMAINDER)
				{
					//�F�J�E���g���ő�ȉ��̏ꍇ
					if (m_nColorCount < CBulletFlower::COLOR_NUMBER_MAX)
					{
						//���˒e������
						for (int nCount = 0; nCount < SHOT_VALUE; nCount++)
						{
							//�Ԓe�̐���
							CBulletFlower::Create(Position, BULLET_MOVE, (CBulletFlower::COLOR_NUMBER)m_nColorCount);
						}
					}
					//�F�̃J�E���g�����Z
					m_nColorCount++;
				}
				//�F�J�E���g���ő吔���z�����̏ꍇ
				if (m_nColorCount > CBulletFlower::COLOR_NUMBER_MAX)
				{
					//�����e�̔��ˎ��Ԃ��N�[���^�C�����z������
					if (m_nShotTime % SHOT_COOL_TIME == REMAINDER)
					{
						//�F�̃J�E���g��0�ɂ���
						m_nColorCount = MINIMUM_COLOR_COUNT;
					}
				}
			}
		}
		//�e�𔭎˂���܂ł̎��Ԃ����Z����
		m_nShotTime++;
	}
}

//=============================================================================
// ��~�����֐�
//=============================================================================
void CEnemyFlower::Stop(void)
{
	//�ʒu���擾
	D3DXVECTOR3 Position = GetPosition();
	//���݂̈ʒu����~�ʒu���l���ゾ�����ꍇ
	if (Position.y >= m_StopPosition.y)
	{
		//�ړ��ʂ�ݒ肷��
		SetMove(STOP);
		//��Ԃ𖳂ɂ���
		SetState(STATE_NONE);
	}
}

//=============================================================================
// �؍ݏ����֐�
//=============================================================================
void CEnemyFlower::Stay(void)
{
	//�؍ݎ��Ԃ����Z����
	m_nStayTime++;
	//�����w��̑؍ݎ��Ԃ��߂�����
	if (m_nStayTime == STAY_TIME)
	{
		//��Ԃ��ړ��ɂ���
		SetState(STATE_MOVE);
		//�ړ��ʂ�ݒ肷��
		SetMove(RETURN_MOVE);
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
	//�v���C���[��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�����G�t�F�N�g�̐���
		CExplosionDeath::Create(GetPosition(), EXPLOSION_SIZE);
		//�����T�E���h��NULL����Ȃ��ꍇ
		if (pSound != NULL)
		{
			//�������̍Đ�
			pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
		}
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
	//�J�E���g��16�ȏ�ɂȂ����ꍇ
	if (m_nCounterAnime > MAX_ANIMATION)
	{
		//�J�E���g��0�ɂ���
		m_nCounterAnime = MINIMUM_ANIMATION;
		//�p�^�[���̃C���N�������g
		m_nPatternAnime++;
	}
	//�A�j���[�V�����̃J�E���g��i�߂�
	m_nCounterAnime++;
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
}
