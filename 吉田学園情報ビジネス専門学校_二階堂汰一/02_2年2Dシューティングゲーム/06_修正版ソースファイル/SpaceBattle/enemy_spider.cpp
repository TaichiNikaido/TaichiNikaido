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
#include "mode_game.h"
#include "renderer.h"
#include "scene2d.h"
#include "enemy_spider.h"
#include "player.h"
#include "bullet.h"
#include "bullet_n-way.h"
#include "item_levelup.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/spider.png")
#define SPEED (D3DXVECTOR3(0.0f,5.0f,0.0f))
#define RATE_MOVE (0.03f)
#define SIZE (D3DXVECTOR3(150.0f,150.0f,0.0f))
#define LIFE (12)
#define SHOT_SPEED (D3DXVECTOR3(cosf(D3DXToRadian(nCnt * (360 / 30) + 40.0f))*5.5f, sinf(D3DXToRadian(nCnt * (360 / 30) + 40.0f))*5.5f, 0.0f))
#define SHOT_TIME (50)
#define SHOT_INTERVAL (20)
#define TARGET_POINT (float(rand() % (FIELD_HEIGHT / 6) + 100))
#define STAY_TIME (500)
#define RETURN_SPEED ((D3DXVECTOR3(0.0f,-7.0f,0.0f)))
#define SCORE (100000)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemySpider::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemySpider::CEnemySpider(int nPriority)
{
	m_nCountBullet = 0;	//�e�̃J�E���^
	m_nStayTime = 0;	//�ҋ@����
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
	pEnemySpider->Init();
	pEnemySpider->SetPosition(Position);
	return pEnemySpider;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CEnemySpider::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�G�̏����������֐��Ăяo��
	CEnemy::Init();
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�̗͂̏����ݒ�
	SetLife(LIFE);
	//�ҋ@���Ԃ̐ݒ�
	m_nStayTime = STAY_TIME;
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
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
	//�������C�t��0�ɂȂ�����
	if (GetLife() <= 0)
	{
		//���S�����֐��Ăяo��
		Death();
	}
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
	//�ʒu���擾
	D3DXVECTOR3 m_Move = GetMove();
	//�J�E���g
	int nCount = 0;
	//�����ڕW�̈ʒu�ɒB���Ă��Ȃ�������
	if (GetPosition().y <= TARGET_POINT)
	{
		//�ړ��ʂ�ݒ肷��
		SetMove(SPEED);
	}
	else
	{
		//�����ҋ@���Ԃ��z������
		if (nCount >= m_nStayTime)
		{
			//�ړ��ʂ�ݒ肷��
			SetMove(RETURN_SPEED);
		}
		else
		{
			//����
			m_Move.y += (0.0f - m_Move.y) * RATE_MOVE;
			//�U�������֐��Ăяo��
			Attack();
		}
	}
	//�J�E���g��i�߂�
	nCount++;
}

//=============================================================================
// �U�������֐�
//=============================================================================
void CEnemySpider::Attack(void)
{
	//�v���C���[���擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//���e�𔭎˂���܂ł̎���
	if (m_nCountBullet >= SHOT_TIME)
	{
		//�v���C���[������łȂ��Ƃ�
		//if (CPlayer::GetbDeath() == false)
		//{
			//���ˊԊu
			if (m_nCountBullet % SHOT_INTERVAL == 0)
			{
				//���˂���e��
				for (int nCnt = 0; nCnt < 9; nCnt++)
				{
					//�v���C���[������ł��Ȃ��Ƃ�
					if (pPlayer->GetState() != CPlayer::STATE_DEATH)
					{
						CBulletN_Way::Create(GetPosition(), SHOT_SPEED);
					}
				}
			}
		//}
	}
	//�e�̃J�E���g�����Z
	m_nCountBullet++;
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CEnemySpider::Death(void)
{
	//�v���C���[���擾����
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
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
