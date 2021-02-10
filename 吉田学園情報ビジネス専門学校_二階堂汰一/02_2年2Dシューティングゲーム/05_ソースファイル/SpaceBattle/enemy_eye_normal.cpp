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
#define TEXTURE ("Data/Texture/Enemy/eye_normal.png")				//�e�N�X�`��
#define SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))						//�T�C�Y
#define MINIMUM_LIFE (0)											//�̗͂̍ŏ��l
#define LIFE (3)													//�̗�
#define MOVE (D3DXVECTOR3(0.0f,5.0f,0.0f))							//�ړ���
#define RETURN_MOVE (D3DXVECTOR3(0.0f,-10.0f,0.0f))					//�߂�ړ���
#define INITIAL_STOP_POSITION (D3DXVECTOR3(0.0f, 0.0f, 0.0f))		//��~�ʒu�̏����l
#define MAX_COUNT_SHOT (4)											//�ő唭�ː�						
#define MINIMUM_COUNT_SHOT (0)										//�ŏ����ː�
#define MINIMUM_COUNT_BULLET (0)									//�e�̍ŏ����ˊԊu			
#define SHOT_COUNT_BULLET (10)										//�e�̔��ˊԊu			
#define SHOT_COUNT_COOL_TIME_BULLET (150)							//�e���ˌ�̃N�[���^�C��
#define STOP (D3DXVECTOR3(GetMove().x,GetMove().y + (0.0f - GetMove().y)*RATE_MOVE,GetMove().z))	//��~�ʒu
#define SCORE (10000)												//�X�R�A
#define MINIMUM_STAY_TIME (0)										//�؍ݍŏ�����
#define STAY_TIME (500)												//�؍ݎ���
#define BULLET_SPEED (7.0f)											//�e�̑��x
#define RATE_MOVE (0.03f)											//�ړ���
#define MINIMUM_TARGET_ANGLE (0.0f)									//�ڕW�܂ł̍ŏ��p�x
#define MINIMUM_BULLET_ANGLE (0.0f)									//�e�̍ŏ��p�x
#define STOP_POSITION (float(rand() % (FIELD_HEIGHT / 2) + 100))	//��~�ʒu

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyEyeNormal::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyEyeNormal::CEnemyEyeNormal()
{
	m_StopPosition = INITIAL_STOP_POSITION;		//��~�ʒu
	m_nShotCount = MINIMUM_COUNT_SHOT;			//���˂��鐔
	m_nCountBullet = MINIMUM_COUNT_BULLET;		//�e�̔��ˊԊu
	m_nStayTime = MINIMUM_STAY_TIME;			//�؍ݎ���
	m_fTargetAngle = MINIMUM_TARGET_ANGLE;		//�ڕW�܂ł̊p�x
	m_fBulletAngle = MINIMUM_BULLET_ANGLE;		//���ˊp�x
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
void CEnemyEyeNormal::TextureUnload(void)
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
CEnemyEyeNormal * CEnemyEyeNormal::Create(D3DXVECTOR3 Position)
{
	//�ڋʂ̓G(�m�[�}��)�̃|�C���^
	CEnemyEyeNormal * pEnemyEyeNormal = NULL;
	//�ڋʂ̓G(�m�[�}��)�̃|�C���^��NULL�̏ꍇ
	if (pEnemyEyeNormal == NULL)
	{
		//�ڋʂ̓G(�m�[�}��)�̃������m��
		pEnemyEyeNormal = new CEnemyEyeNormal;
	}
	//�ڋʂ̓G(�m�[�}��)�̃|�C���^��NULL����Ȃ��ꍇ
	if (pEnemyEyeNormal != NULL)
	{
		//�ʒu���擾����
		pEnemyEyeNormal->SetPosition(Position);
		//�����������֐��Ăяo��
		pEnemyEyeNormal->Init();
	}
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
	//�ʒu�̎擾
	D3DXVECTOR3 Position = GetPosition();
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�v���C���[��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//�ڕW�܂ł̋������v�Z
		D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(PlayerPosition.x - Position.x, PlayerPosition.y - Position.y, 0.0f);
		//�v���C���[������ł��Ȃ��Ƃ�
		if (pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			//�������˂����e�̐���4�ȉ���������
			if (m_nShotCount < MAX_COUNT_SHOT)
			{
				if (m_nShotCount <= MINIMUM_COUNT_SHOT)
				{
					//�������p�x���v�Z
					m_fBulletAngle = atan2f(m_TargetDistance.y, m_TargetDistance.x);
				}
				//�����e�̔���
				if (m_nCountBullet % SHOT_COUNT_BULLET == REMAINDER)
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
				if (m_nCountBullet % SHOT_COUNT_COOL_TIME_BULLET == REMAINDER)
				{
					//���˂���e�̃J�E���g��0�ɂ���
					m_nShotCount = MINIMUM_COUNT_SHOT;
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
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�v���C���[���擾����
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�����v���C���[�̃|�C���^��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//������Ԃ��U����Ԃ���Ȃ��Ƃ�
		if (GetState() != STATE_ATTACK)
		{
			//�ڕW�܂ł̋������v�Z
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
void CEnemyEyeNormal::Stop(void)
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
void CEnemyEyeNormal::Stay(void)
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
