//=============================================================================
//
// ���e�̓G�̓��� [enemy_bomb_body.cpp]
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
#include "enemy_bomb_head.h"
#include "player.h"
#include "bullet_direction.h"
#include "bullet.h"
#include "explosion_death.h"
#include "item_bomb.h"
#include "enemy_bomb_body.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/bombhead.png")	//�e�N�X�`��
#define SIZE (D3DXVECTOR3(100.0f,150.0f,0.0f))		//�T�C�Y
#define MINIMUM_LIFE (0)							//�̗͂̍ŏ��l
#define LIFE (12)									//�̗�
#define MOVE (D3DXVECTOR3(5.0f,0.0f,0.0f))			//�ړ���		
#define SCORE (10000)								//�X�R�A
#define MINIMUM_RADIAN (0.0f)						//���W�A���̍ŏ��l
#define MINIMUM_ADD_RADIAN (0.1f);					//���W�A���̉��Z��
#define MINIMUM_CREATE_TIME (0)						//���������Ԋu�̎��ԍŏ��l
#define CREATE_TIME (15)							//���������Ԋu�̎���
#define MINIMUM_CREATE_BODY_COUNT (0)				//���������̂̐��̍ŏ��l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyBombHead::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyBombHead::CEnemyBombHead()
{
	memset(m_pBombBody, NULL, sizeof(m_pBombBody));		//���e�G�̑̂̃|�C���^
	m_InitialPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����ʒu		
	m_nCreateTime = MINIMUM_CREATE_TIME;				//�������鎞��	
	m_nCreateBodyCount = MINIMUM_CREATE_BODY_COUNT;		//���������̂̐�		
	m_nBombLife = LIFE;									//�S�̗̂̑�					
	m_fRadian = MINIMUM_RADIAN;							//���W�A��		
	m_fAddRadian = MINIMUM_ADD_RADIAN;					//���W�A���̉��Z��		
	m_bCreateBody = true;								//�̂𐶐�������		
	m_bDeath = false;									//���񂾂�		
	m_bDeathAll = false;								//�S�Ď��񂾂�		
}															

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyBombHead::~CEnemyBombHead()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CEnemyBombHead::TextureLoad(void)
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
void CEnemyBombHead::TextureUnload(void)
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
CEnemyBombHead * CEnemyBombHead::Create(D3DXVECTOR3 Position)
{
	//���e�G�̓��̃|�C���^
	CEnemyBombHead * pEnemyBombHead = NULL;
	//���e�G�̓��̃|�C���^��NULL�̏ꍇ
	if (pEnemyBombHead == NULL)
	{
		//���e�G�̓��̃������m��
		pEnemyBombHead = new CEnemyBombHead;
		//���e�G�̓��̃|�C���^��NULL����Ȃ��ꍇ
		if (pEnemyBombHead != NULL)
		{
			//�ʒu��ݒ肷��
			pEnemyBombHead->SetPosition(Position);
			//�����ʒu��ݒ肷��
			pEnemyBombHead->m_InitialPosition = Position;
			//�����������֐��Ăяo��
			pEnemyBombHead->Init();
		}
	}
	//���e�G�̓��̃|�C���^��Ԃ�
	return pEnemyBombHead;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CEnemyBombHead::Init(void)
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
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CEnemyBombHead::Uninit(void)
{
	//�G�̏I�������֐��Ăяo��
	CEnemy::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CEnemyBombHead::Update(void)
{
	//�����̂��������ꂽ��
	if (m_bCreateBody == true)
	{
		//�����������Z�邤
		m_nCreateTime++;
		//������������鎞�ԂɂȂ�����
		if (m_nCreateTime % CREATE_TIME == REMAINDER)
		{
			//�̂𐶐�����
			m_pBombBody[m_nCreateBodyCount] = CEnemyBombBody::Create(m_InitialPosition, this);
			//�̂̐����������Z����
			m_nCreateBodyCount++;
			//�����̂̐��������ő吔�ɂȂ�����
			if (m_nCreateBodyCount >= MAX_BOMB_BODY)
			{
				//�̂̐�������߂�
				m_bCreateBody = false;
			}
		}
	}
	//���W�A�������Z����
	m_fRadian += m_fAddRadian;
	//�������������
	if (m_fRadian >= 360.0f)
	{
		//���W�A����0�ɂ���
		m_fRadian = MINIMUM_RADIAN;
	}
	//�ړ��ʂ̃Z�b�g
	SetMove(D3DXVECTOR3(GetMove().x, float(5 * sin(m_fRadian)), GetMove().z));
	//��ʒ[�ɂ�����t������
	if (GetPosition().x < FIELD_WIDTH_MIN + 10.0f)
	{
		//�ړ��ʂ�ݒ肷��
		SetMove(D3DXVECTOR3(GetMove().x * -1.0f, GetMove().y, GetMove().z));
		//���W�A���𔽓]������
		m_fAddRadian = m_fAddRadian * -1.0f;
	}
	//��ʒ[�ɂ�����t������
	if (GetPosition().x > FIELD_WIDTH - 10.0f)
	{
		//�ړ��ʂ�ݒ肷��
		SetMove(D3DXVECTOR3(GetMove().x * -1.0f, GetMove().y, GetMove().z));
		//���W�A���𔽓]������
		m_fAddRadian = m_fAddRadian * -1.0f;
	}
	//�i�s�����Ɍ��������킹��
	SetRotation(D3DXVECTOR3(GetRotation().x, GetRotation().y, atan2f((GetPosition().x + GetMove().x) - GetPosition().x, (GetPosition().y + GetMove().y) - GetPosition().y)));
	//�G�̍X�V�����֐��Ăяo��
	CEnemy::Update();
	//�������C�t��0�ɂȂ�����
	if (GetLife() <= MINIMUM_LIFE)
	{
		//��������ł��Ȃ�������
		if (m_bDeath == false)
		{
			//���S�����֐��Ăяo��
			Death();
			return;
		}
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CEnemyBombHead::Draw(void)
{
	//�G�̕`�揈���֐��Ăяo��
	CEnemy::Draw();
}
//=============================================================================
// �S�̎��S�����֐�
//=============================================================================
void CEnemyBombHead::DeathAll(void)
{
	//��������łȂ����S������łȂ�������
	if (m_bDeathAll == false && m_bDeath == false)
	{
		//�S���E��
		m_bDeathAll = true;
		//�̂̍ő吔����
		for (int nCount = 0; nCount < MAX_BOMB_BODY; nCount++)
		{
			//�������e�G�̑̂̃|�C���^��NULL����Ȃ��ꍇ
			if (m_pBombBody[nCount] != NULL)
			{
				//�����G�t�F�N�g�̐���
				CExplosionDeath::Create(m_pBombBody[nCount]->GetPosition(), EXPLOSION_SIZE);
				//���e�G�̑̂̏I�������֐��Ăяo��
				m_pBombBody[nCount]->Uninit();
			}
		}
		//�I�������֐��Ăяo��
		Uninit();
	}
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CEnemyBombHead::Death(void)
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
			//���e�A�C�e���̐���
			CItemBomb::Create(GetPosition());
			//�v���C���[�̃X�R�A�����Z����
			pPlayer->AddScore(SCORE);
			//�S�̎��S�����֐��Ăяo��
			DeathAll();
			//�E��
			m_bDeath = true;
		}
}