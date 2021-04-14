//=============================================================================
//
// �w� [enemy_spider.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/sound.h"
#include "Mode/mode_game.h"
#include "Base/renderer.h"
#include "Base/scene2d.h"
#include "enemy_spider.h"
#include "Player/player.h"
#include "Bullet/bullet.h"
#include "Bullet/bullet_n-way.h"
#include "Item/item_levelup.h"
#include "Effect/explosion_death.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/spider.png")				//�e�N�X�`��
#define MOVE (D3DXVECTOR3(0.0f,5.0f,0.0f))						//�ړ���
#define RATE_MOVE (0.03f)										//�ړ���
#define SIZE (D3DXVECTOR3(150.0f,150.0f,0.0f))					//�T�C�Y
#define MINIMUM_LIFE (0)										//�̗͂̍ŏ��l
#define LIFE (12)												//�̗�
#define RETURN_SPEED (D3DXVECTOR3(0.0f,-10.0f,0.0f))			//�߂�ړ���
#define STOP_MOVE (D3DXVECTOR3(GetMove().x,GetMove().y + (0.0f - GetMove().y)*RATE_MOVE,GetMove().z))	//��~
#define STAY_TIME (500)											//�؍ݎ���
#define BULLET_SPEED (D3DXVECTOR3(cosf(D3DXToRadian(nCount * (360 / 30) + 40.0f))*5.5f, sinf(D3DXToRadian(nCount * (360 / 30) + 40.0f))*5.5f, 0.0f))	//�e�̈ړ���
#define SHOT_TIME (50)											//���ˎ���
#define SHOT_INTERVAL (20)										//���ˊԊu
#define SCORE (100000)											//�X�R�A
#define INITIAL_STOP_POSITION (D3DXVECTOR3(0.0f, 0.0f, 0.0f))	//��~�ʒu�̍ŏ��l
#define INITIAL_SHOT_TIME (0)									//���ˍŏ�����
#define MINIMUM_COUNTER_ANIME (0)								//�A�j���[�V�����ŏ��J�E���^
#define MINIMUM_PATTERN_ANIME (0)								//�A�j���[�V�����ŏ��p�^�[��
#define MINIMUM_STAY_TIME (0)									//�؍ݍŏ�����
#define STOP_POSITION (float(rand() % (FIELD_HEIGHT / 6) + 100))//��~�ʒu
#define ANIMATION_VALUE (0.500f)								//�A�j���[�V�����̒l
#define MAX_COUNTER_ANIMATION (16)								//�A�j���[�V�����ő�J�E���^
#define MAX_BULLET (9)											//�e�̍ő吔

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemySpider::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemySpider::CEnemySpider()
{
	m_StopPosition = INITIAL_STOP_POSITION;			//��~����ʒu
	m_nShotTime = INITIAL_SHOT_TIME;				//�e�̃J�E���^
	m_nCounterAnime = MINIMUM_COUNTER_ANIME;		//�A�j���J�E���^
	m_nPatternAnime = MINIMUM_PATTERN_ANIME;		//�p�^�[���A�j��
	m_nStayTime = MINIMUM_STAY_TIME;				//�؍ݎ���
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemySpider::~CEnemySpider()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CEnemySpider::TextureLoad(void)
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
void CEnemySpider::TextureUnload(void)
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
CEnemySpider * CEnemySpider::Create(D3DXVECTOR3 Position)
{
	//�w偂̓G�̃|�C���^
	CEnemySpider * pEnemySpider = NULL;
	//�w偂̓G�̃|�C���^��NULL�̏ꍇ
	if (pEnemySpider == NULL)
	{
		//�w偂̓G�̃������m��
		pEnemySpider = new CEnemySpider;
		//�w偂̓G�̃|�C���^��NULL����Ȃ��ꍇ
		if (pEnemySpider != NULL)
		{
			//�ʒu��ݒ肷��
			pEnemySpider->SetPosition(Position);
			//�����������֐��Ăяo��
			pEnemySpider->Init();
		}
	}
	//�w偂̓G�̃|�C���^��Ԃ�
	return pEnemySpider;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CEnemySpider::Init(void)
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
	//��~�ꏊ�̏����ݒ�
	m_StopPosition.y = STOP_POSITION;
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CEnemySpider::Uninit(void)
{
	//�G�̏I�������֐��Ăяo��
	CEnemy::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CEnemySpider::Update(void)
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
	//�������C�t��0�ɂȂ�����
	if (GetLife() <= MINIMUM_LIFE)
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
void CEnemySpider::Draw(void)
{
	//�G�̕`�揈���֐��Ăяo��
	CEnemy::Draw();
}

//=============================================================================
// �U�������֐�
//=============================================================================
void CEnemySpider::Attack(void)
{
	//�v���C���[���擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�ʒu���擾
	D3DXVECTOR3 Position = GetPosition();
	//�T�C�Y���擾
	D3DXVECTOR3 Size = GetSize();
	//�����v���C���[��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�����v���C���[�̏�Ԃ����S��ԈȊO�̎�
		if (pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			//���e�𔭎˂���܂ł̎���
			if (m_nShotTime >= SHOT_TIME)
			{
				//���ˊԊu
				if (m_nShotTime % SHOT_INTERVAL == REMAINDER)
				{
					//���˂���e�̍ő吔��
					for (int nCount = 0; nCount < MAX_BULLET; nCount++)
					{
						//n_way�e�̐���
						CBulletN_Way::Create(D3DXVECTOR3(Position.x, Position.y + Size.y / 4, 0.0f), BULLET_SPEED);
					}
				}
			}
			//�e�̃J�E���g�����Z
			m_nShotTime++;
		}
	}
}

//=============================================================================
// ��~�����֐�
//=============================================================================
void CEnemySpider::Stop(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//���݂̈ʒu����~�ʒu���l���ゾ�����ꍇ
	if (Position.y >= m_StopPosition.y)
	{
		//�ړ��ʂ�ݒ肷��
		SetMove(STOP_MOVE);
		//��Ԃ𖳂ɂ���
		SetState(STATE_NONE);
	}
}

//=============================================================================
// �؍ݏ����֐�
//=============================================================================
void CEnemySpider::Stay(void)
{
	//�؍ݎ��Ԃ����Z����
	m_nStayTime++;
	//�����w��̑؍ݎ��Ԃ��߂�����
	if (m_nStayTime >= STAY_TIME)
	{
		//��Ԃ��ړ���
		SetState(STATE_MOVE);
		//�ړ��ʂ�ݒ肷��
		SetMove(RETURN_SPEED);
	}
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CEnemySpider::Death(void)
{
	//�v���C���[���擾����
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
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
void CEnemySpider::Drop(void)
{
	//�A�C�e���𗎂Ƃ�
	CItemLevelUP::Create(GetPosition());
}

//=============================================================================
// �A�j���[�V���������֐�
//=============================================================================
void CEnemySpider::Animation(void)
{
	//�J�E���g�C���N�������g
	m_nCounterAnime++;
	//�J�E���g��16�ȏ�ɂȂ����ꍇ
	if (m_nCounterAnime > MAX_COUNTER_ANIMATION)
	{
		//�J�E���g��0�ɂ���
		m_nCounterAnime = MINIMUM_COUNTER_ANIME;
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
