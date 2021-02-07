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
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "mode_game.h"
#include "renderer.h"
#include "scene2d.h"
#include "enemy_spider.h"
#include "player.h"
#include "bullet.h"
#include "bullet_n-way.h"
#include "item_levelup.h"
#include "explosion_death.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/spider.png")
#define SPEED (D3DXVECTOR3(0.0f,5.0f,0.0f))
#define RATE_MOVE (0.03f)
#define SIZE (D3DXVECTOR3(150.0f,150.0f,0.0f))
#define LIFE (12)
#define RETURN_SPEED (D3DXVECTOR3(0.0f,-10.0f,0.0f))
#define RETURN_SPEED ((D3DXVECTOR3(0.0f,-7.0f,0.0f)))
#define STOP (D3DXVECTOR3(GetMove().x,GetMove().y + (0.0f - GetMove().y)*RATE_MOVE,GetMove().z))
#define STAY_TIME (500)
#define SHOT_SPEED (D3DXVECTOR3(cosf(D3DXToRadian(nCnt * (360 / 30) + 40.0f))*5.5f, sinf(D3DXToRadian(nCnt * (360 / 30) + 40.0f))*5.5f, 0.0f))
#define SHOT_TIME (50)
#define SHOT_INTERVAL (20)
#define SCORE (100000)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemySpider::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemySpider::CEnemySpider(int nPriority) : CEnemy(nPriority)
{
	m_StopPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCountBullet = 0;		//�e�̃J�E���^
	m_nCounterAnime = 0;	//�A�j���J�E���^
	m_nPatternAnime = 0;	//�p�^�[���A�j��
	m_nStayTime = 0;
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
void CEnemySpider::TextureUnload(void)
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
CEnemySpider * CEnemySpider::Create(D3DXVECTOR3 Position)
{
	CEnemySpider * pEnemySpider;
	pEnemySpider = new CEnemySpider;
	pEnemySpider->SetPosition(Position);
	pEnemySpider->Init();
	return pEnemySpider;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CEnemySpider::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.500f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.500f * m_nPatternAnime + 0.500f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.500f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.500f * m_nPatternAnime + 0.500f, 1.0f);
	//�G�̏����������֐��Ăяo��
	CEnemy::Init();
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�̗͂̏����ݒ�
	SetLife(LIFE);
	//�ړ��ʂ̏����ݒ�
	SetMove(SPEED);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	//��Ԃ��ړ���
	SetState(STATE_MOVE);
	m_StopPosition.y = float(rand() % (FIELD_HEIGHT / 6) + 100);
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
	Stay();
	//�������C�t��0�ɂȂ�����
	if (GetLife() <= 0)
	{
		//���S�����֐��Ăяo��
		Death();
	}
	//�A�j���[�V���������֐��Ăяo��
	Animation();
	//�ړ������֐��Ăяo��
	Move();
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
// �ړ��ʐݒ菈���֐�
//=============================================================================
void CEnemySpider::Move(void)
{

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
	if (pPlayer != NULL)
	{
		//�����v���C���[�̏�Ԃ����S��ԈȊO�̎�
		if (pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			//���e�𔭎˂���܂ł̎���
			if (m_nCountBullet >= SHOT_TIME)
			{
				//���ˊԊu
				if (m_nCountBullet % SHOT_INTERVAL == 0)
				{
					//���˂���e��
					for (int nCnt = 0; nCnt < 9; nCnt++)
					{
						//n_way�e�̐���
						CBulletN_Way::Create(D3DXVECTOR3(Position.x, Position.y + Size.y / 4, 0.0f), SHOT_SPEED);
					}
				}
			}
			//�e�̃J�E���g�����Z
			m_nCountBullet++;
		}
	}
}

//=============================================================================
// ��~�����֐�
//=============================================================================
void CEnemySpider::Stop(void)
{
	D3DXVECTOR3 Position = GetPosition();

	if (Position.y >= m_StopPosition.y)
	{
		SetMove(STOP);
		SetState(STATE_NONE);
	}
}

void CEnemySpider::Stay(void)
{
	m_nStayTime++;
	if (m_nStayTime == STAY_TIME)
	{
		//��Ԃ��ړ���
		SetState(STATE_MOVE);
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
	aTexture[0] = D3DXVECTOR2(0.500f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.500f * m_nPatternAnime + 0.500f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.500f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.500f * m_nPatternAnime + 0.500f, 1.0f);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
}
