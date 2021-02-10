//=============================================================================
//
// �ڋ�(�n�[�h) [enemy_eye_hard.cpp]
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
#include "enemy_eye_hard.h"
#include "bullet_homing.h"
#include "player.h"
#include "bullet.h"
#include "explosion_death.h"
#include "bullet_homing.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/eye_hard.png")					//�e�N�X�`��
#define SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))						//�T�C�Y
#define MOVE (D3DXVECTOR3(0.0f,5.0f,0.0f))							//�ړ���
#define RETURN_MOVE (D3DXVECTOR3(0.0f,-10.0f,0.0f))					//�߂鎞�̈ړ���
#define INITIAL_STOP_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))			//��~����ʒu�̏����l
#define STOP_POSITION (float(rand() % (FIELD_HEIGHT / 2) + 100))	//��~����ʒu
#define MINIMUM_SHOT_TIME (0)										//�e�����܂ł̍ŏ�����
#define SHOT_TIME (100)												//���܂ł̎���
#define MINIMUM_STAY_TIME (0)										//�؍݂���ŏ�����
#define STAY_TIME (500)												//�؍ݎ���
#define MINIMUM_TARGET_ANGLE (0.0f)									//�ڕW�̊p�x�̍ŏ��l
#define RATE_MOVE (0.03f)											//�ړ���
#define STOP (D3DXVECTOR3(GetMove().x,GetMove().y + (0.0f - GetMove().y) * RATE_MOVE,GetMove().z))	//��~�ʒu
#define MINIMUM_LIFE (0)											//�̗͂̍ŏ��l
#define LIFE (3)													//�̗�
#define SCORE (10000)												//�X�R�A								
#define BULLET_SPEED (7.0f)											//�e�̑��x

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyEyeHard::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyEyeHard::CEnemyEyeHard()
{
	m_StopPosition = INITIAL_STOP_POSITION;		//��~�ʒu
	m_fTargetAngle = MINIMUM_TARGET_ANGLE;		//�ڕW�܂ł̊p�x
	m_nShotTime = MINIMUM_SHOT_TIME;			//�e�𔭎˂���܂ł̎���
	m_nStayTime = MINIMUM_STAY_TIME;			//�؍ݎ���
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyEyeHard::~CEnemyEyeHard()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CEnemyEyeHard::TextureLoad(void)
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
void CEnemyEyeHard::TextureUnload(void)
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
CEnemyEyeHard * CEnemyEyeHard::Create(D3DXVECTOR3 Position)
{
	//�ڋʂ̓G(�n�[�h)�̃|�C���^
	CEnemyEyeHard * pEnemyEyeHard = NULL;
	//�����ڋʂ̃|�C���^��NULL�̏ꍇ
	if (pEnemyEyeHard == NULL)
	{
		//�ڋʂ̓G(�n�[�h)�̃������m��
		pEnemyEyeHard = new CEnemyEyeHard;
	}
	//�����ڋʂ̃|�C���^��NULL����Ȃ��ꍇ
	if (pEnemyEyeHard != NULL)
	{
		//�����������֐��Ăяo��
		pEnemyEyeHard->Init();
		//�ʒu��ݒ肷��
		pEnemyEyeHard->SetPosition(Position);
	}
	return pEnemyEyeHard;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CEnemyEyeHard::Init(void)
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
void CEnemyEyeHard::Uninit(void)
{
	//�G�̏I�������֐��Ăяo��
	CEnemy::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CEnemyEyeHard::Update(void)
{
	//�G�̍X�V�����֐��Ăяo��
	CEnemy::Update();
	//���߂鏈���֐��Ăяo��
	Gaze();
	//��Ԃ��ړ���Ԃ���Ȃ��Ƃ�
	if (GetState() != STATE_MOVE)
	{
		//�U�������֐��Ăяo��
		Attack();
	}
	//��~�����֐��Ăяo��
	Stop();
	//��~�����֐��Ăяo��
	Stay();
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
void CEnemyEyeHard::Draw(void)
{
	//�G�̕`�揈���֐��Ăяo��
	CEnemy::Draw();
}

//=============================================================================
// �U�������֐�
//=============================================================================
void CEnemyEyeHard::Attack(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�����v���C���[�̃|�C���^��NULL����Ȃ�������
	if (pPlayer != NULL)
	{
		//�����v���C���[�̏�Ԃ����S��ԈȊO�̎�
		if (pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			//�e�𔭎˂��鎞�ԂɂȂ�����
			if (m_nShotTime % SHOT_TIME == REMAINDER)
			{
				//�z�[�~���O�e�̐���
				CBulletHoming::Create(Position);
			}
			//�e�̃J�E���g�����Z
			m_nShotTime++;
		}
	}
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CEnemyEyeHard::Death(void)
{
	//�v���C���[���擾����
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�v���C���[��NULL����Ȃ��ꍇ
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
void CEnemyEyeHard::Gaze(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�v���C���[���擾����
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�v���C���[��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�ڕW�̈ʒu���擾����
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//������Ԃ������͈ړ���Ԃ�������
		if (GetState() == STATE_NONE || GetState() == STATE_MOVE)
		{
			//�v���C���[�܂ł̋������v�Z
			D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(PlayerPosition.x - Position.x, PlayerPosition.y - Position.y, 0.0f);
			//�v���C���̕��Ɍ������p�x���v�Z
			m_fTargetAngle = atan2f(m_TargetDistance.y, m_TargetDistance.x);
			//������ݒ肷��
			SetRotation(D3DXVECTOR3(0.0f, 0.0f, -m_fTargetAngle));
		}
	}
}

//=============================================================================
// ��~�����֐�
//=============================================================================
void CEnemyEyeHard::Stop(void)
{
	//�ʒu���擾����
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
void CEnemyEyeHard::Stay(void)
{
	//�؍ݎ��Ԃ����Z����
	m_nStayTime++;
	//�����w��̑؍ݎ��Ԃ��߂�����
	if (m_nStayTime >= STAY_TIME)
	{
		//��Ԃ��ړ���
		SetState(STATE_MOVE);
		//�ړ��ʂ�ݒ肷��
		SetMove(RETURN_MOVE);
	}
}
