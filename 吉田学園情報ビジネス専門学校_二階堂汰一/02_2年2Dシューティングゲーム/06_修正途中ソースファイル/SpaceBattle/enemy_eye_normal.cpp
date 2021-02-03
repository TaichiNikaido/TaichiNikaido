//=============================================================================
//
// �ڋ�(�m�[�}��) [enemy_eye_normal.cpp]
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
#include "enemy_eye_normal.h"
#include "player.h"
#include "bullet_direction.h"
#include "bullet.h"
#include "explosion_death.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/eye_normal.png")
#define SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))
#define LIFE (3)
#define SPEED (D3DXVECTOR3(0.0f,5.0f,0.0f))
#define SCORE (10000)
#define BULLET_SPEED (7.0f)
#define RATE_MOVE (0.03f)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyEyeNormal::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyEyeNormal::CEnemyEyeNormal(int nPriority)
{
	m_nShotCount = 0;		//���˂��鐔
	m_nCountBullet = 0;		//�e�̔��ˊԊu
	m_fAngleRot = 0.0f;		//����
	m_fBulletAngle = 0.0f;	//���˕���
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyEyeNormal::~CEnemyEyeNormal()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CEnemyEyeNormal::TextureLoad(void)
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
void CEnemyEyeNormal::TextureUnload(void)
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
CEnemyEyeNormal * CEnemyEyeNormal::Create(D3DXVECTOR3 Position)
{
	CEnemyEyeNormal * pEnemyEyeNormal;
	pEnemyEyeNormal = new CEnemyEyeNormal;
	pEnemyEyeNormal->SetPosition(Position);
	pEnemyEyeNormal->Init();
	return pEnemyEyeNormal;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CEnemyEyeNormal::Init(void)
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
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	//��Ԃ𖳂ɂ���
	SetState(STATE_NONE);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CEnemyEyeNormal::Uninit(void)
{
	//�G�̏I�������֐��Ăяo��
	CEnemy::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CEnemyEyeNormal::Update(void)
{
	//�G�̍X�V�����֐��Ăяo��
	CEnemy::Update();
	//���߂鏈���֐��Ăяo��
	Gaze();
	//�U�������֐��Ăяo��
	Attack();
	//�������C�t��0�ɂȂ�����
	if (GetLife() <= 0)
	{
		//���S�����֐��Ăяo��
		Death();
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CEnemyEyeNormal::Draw(void)
{
	//�G�̕`�揈���֐��Ăяo��
	CEnemy::Draw();
}

//=============================================================================
// �U�������֐�
//=============================================================================
void CEnemyEyeNormal::Attack(void)
{
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		//�ڕW�̈ʒu
		D3DXVECTOR3 TargetPosisiton = pPlayer->GetPosition();
		//�ʒu�̎擾
		D3DXVECTOR3 Position = GetPosition();
		//�ڕW�܂ł̋������v�Z
		D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(TargetPosisiton.x - GetPosition().x, TargetPosisiton.y - GetPosition().y, 0.0f);
		//�v���C���[������ł��Ȃ��Ƃ�
		if (pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			if (m_nShotCount < 4)
			{
				if (m_nShotCount <= 0)
				{
					//�������p�x���v�Z
					m_fBulletAngle = atan2f(m_TargetDistance.y, m_TargetDistance.x);
				}
				//�����e�̔���
				if (m_nCountBullet % 10 == 0)
				{
					//��Ԃ��U����Ԃɂ���
					SetState(STATE_ATTACK);
					//�����e�̐���
					CBulletDirection::Create(GetPosition(), D3DXVECTOR3(cosf(m_fBulletAngle) * BULLET_SPEED, sinf(m_fBulletAngle) * BULLET_SPEED, 0.0f));
					//���˂���e�̃J�E���g��i�߂�
					m_nShotCount++;
				}
			}
			else
			{
				//��Ԃ𖳂ɂ���
				SetState(STATE_NONE);
				//�e�N�[���^�C��
				if (m_nCountBullet % 150 == 0)
				{
					//���˂���e�̃J�E���g��0�ɂ���
					m_nShotCount = 0;
				}
			}
			//�e�̃J�E���g�����Z
			m_nCountBullet++;
		}
	}
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CEnemyEyeNormal::Death(void)
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
	//�I�������֐��Ăяo��
	Uninit();
	return;
}

//=============================================================================
// ���߂鏈���֐�
//=============================================================================
void CEnemyEyeNormal::Gaze(void)
{
	//�v���C���[���擾����
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		//�ڕW�̈ʒu
		D3DXVECTOR3 TargetPosition = pPlayer->GetPosition();
		//������Ԃ��U����Ԃ���Ȃ��Ƃ�
		if (GetState() != STATE_ATTACK)
		{
			//�ڕW�܂ł̋������v�Z
			D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(TargetPosition.x - GetPosition().x, TargetPosition.y - GetPosition().y, 0.0f);
			//�v���C���̕��Ɍ������p�x���v�Z
			m_fAngleRot = atan2f(m_TargetDistance.y, m_TargetDistance.x);
			//������ݒ肷��
			SetRotation(D3DXVECTOR3(0.0f, 0.0f, m_fAngleRot * -1.0f));
		}
	}
}
