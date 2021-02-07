//=============================================================================
//
// �h���S�� [enemy_dragon.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "mode_game.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "sound.h"
#include "enemy_dragon.h"
#include "bullet_fireball.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/dragon.png")
#define SIZE (D3DXVECTOR3(600.0f,600.0f,0.0f))
#define LIFE (300)
#define SCALE (0.1f)
#define ADD_SCALE (0.01f)
#define SCORE (100000)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyDragon::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyDragon::CEnemyDragon(int nPriority) : CEnemy(nPriority)
{
	m_nPatternAnime = 0;	//�p�^�[���A�j��
	m_nCounterAnime = 0;	//�J�E���^�[�A�j��
	m_nBulletTime = 0;		//�e�̔��ˊԊu
	m_TargetDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bCharge = false;
	m_nChargeTime = 0;
	m_pBulletFireBall = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyDragon::~CEnemyDragon()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CEnemyDragon::TextureLoad(void)
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
void CEnemyDragon::TextureUnload(void)
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
CEnemyDragon * CEnemyDragon::Create(D3DXVECTOR3 Position)
{
	CEnemyDragon * pEnemyDragon;
	pEnemyDragon = new CEnemyDragon;
	pEnemyDragon->Init();
	pEnemyDragon->SetPosition(Position);
	return pEnemyDragon;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CEnemyDragon::Init(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.1666f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.1666f * m_nPatternAnime + 0.1666f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.1666f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.1666f * m_nPatternAnime + 0.1666f, 1.0f);
	//�G�̏����������֐��Ăяo��
	CEnemy::Init();
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�X�P�[���̏����ݒ�
	SetScale(SCALE);
	//�̗͂̏����ݒ�
	SetLife(LIFE);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	//BGM�̍Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_DRAGON);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CEnemyDragon::Uninit(void)
{
	//�G�̏I�������֐��Ăяo��
	CEnemy::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CEnemyDragon::Update(void)
{
	if (m_bCharge == true)
	{
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		if (GetScale() >= 1.0f)
		{
			//�ڕW�����ɋ߂Â�����ڕW���Đݒ肷��
			if (GetPosition().x >= m_TargetPos.x - 50 / 2 &&
				GetPosition().x < m_TargetPos.x + 50 / 2 &&
				GetPosition().y >= m_TargetPos.y - 50 / 2 &&
				GetPosition().y < m_TargetPos.y + 50 / 2)
			{
				//�����_���V�[�h�l
				int nRandSeed = rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500);
				srand((unsigned int)nRandSeed);
				m_TargetPos.x = (float)(rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500));//�ڕW�����̌���
				m_TargetPos.y = (float)(rand() % 300 + 200);
			}
			else
			{
				m_TargetDistance = D3DXVECTOR3(m_TargetPos.x - GetPosition().x, m_TargetPos.y - GetPosition().y, 0.0f);//�ڕW�܂ł̋������Z�o
				SetRotation(D3DXVECTOR3(GetRotation().x, atan2f(m_TargetDistance.y, m_TargetDistance.x), GetRotation().z));
				SetMove(D3DXVECTOR3(cosf(GetRotation().y)*2.5f, sinf(GetRotation().y)*2.5f, 0.0f));
			}
			if (GetPosition().x > FIELD_WIDTH - 200)
			{
				//�����_���V�[�h�l
				int nRandSeed = rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500);
				srand((unsigned int)nRandSeed);
				m_TargetPos.x = (float)(rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500));//�ڕW�����̌���
				m_TargetPos.y = (float)(rand() % 300 + 200);
				m_TargetPos.x += -600.0f;
			}
			if (GetPosition().x < FIELD_WIDTH_MIN + 200)
			{
				//�����_���V�[�h�l
				int nRandSeed = rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500);
				srand((unsigned int)nRandSeed);
				m_TargetPos.x = (float)(rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500));//�ڕW�����̌���
				m_TargetPos.y = (float)(rand() % 300 + 200);
				m_TargetPos.x += 200.0f;
			}
		}
	}
	//�G�̍X�V�����֐��Ăяo��
	CEnemy::Update();
	//�g�k�����֐��Ăяo��
	Scale();
	//�A�j���[�V���������֐��Ăяo��
	Animation();
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
void CEnemyDragon::Draw(void)
{
	//�G�̕`�揈���֐��Ăяo��
	CEnemy::Draw();
}

//=============================================================================
// �g�k�����֐�
//=============================================================================
void CEnemyDragon::Scale(void)
{
	//�g�嗦���擾����
	float fScale = GetScale();
	//�����g�嗦��1�{�ȉ��̏ꍇ
	if (fScale <= 1.0f)
	{
		//�g�傷��
		fScale += ADD_SCALE;
	}
	else
	{
		//�U�������֐��Ăяo��
		Attack();
	}
	//�g�k��ݒ�
	SetScale(fScale);
}

//=============================================================================
// �U�������֐�
//=============================================================================
void CEnemyDragon::Attack(void)
{
	//�ʒu���擾
	D3DXVECTOR3 Position = GetPosition();
	//�T�C�Y���擾
	D3DXVECTOR3 Size = GetSize();
	//�v���C���[���擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//�����v���C���[�̈ʒu�����̏ꍇ
		if (PlayerPosition.y >= Position.y)
		{
			if (m_nBulletTime % 400 == 0)
			{
				//�΋��̔���
				m_pBulletFireBall = CBulletFireball::Create(D3DXVECTOR3(Position.x, Position.y + Size.y / 2, 0.0f));
				m_bCharge = true;
			}
		}
	}
	if (m_bCharge == true)
	{
		if (m_nChargeTime >= 70)
		{
			m_bCharge = false;
			m_nChargeTime = 0;
		}
		m_nChargeTime++;
	}
	//�o���b�g�̔��ˊԊu��i�߂�
	m_nBulletTime++;
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CEnemyDragon::Death(void)
{
	//�v���C���[���擾����
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		//�v���C���[�̃X�R�A�����Z����
 		pPlayer->AddScore(SCORE);
		pPlayer->Clear();
	}
	//�I�������֐��Ăяo��
	Uninit();
	return;
}

//=============================================================================
// �A�j���[�V���������֐�
//=============================================================================
void CEnemyDragon::Animation(void)
{
	//�J�E���g�C���N�������g
	m_nCounterAnime++;
	//�J�E���g��4�ȏ�ɂȂ����ꍇ
	if (m_nCounterAnime > 24)
	{
		//�J�E���g��0�ɂ���
		m_nCounterAnime = 0;
		//�p�^�[���̃C���N�������g
		m_nPatternAnime++;
		//�����p�^�[���A�j����4�ɂȂ�����
		if (m_nPatternAnime > 4)
		{
			//�p�^�[���A�j��������������
			m_nPatternAnime = 0;
		}
	}
	//�A�j���[�V�����̃J�E���g��i�߂�
	m_nCounterAnime++;
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.1666f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.1666f * m_nPatternAnime + 0.1666f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.1666f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.1666f * m_nPatternAnime + 0.1666f, 1.0f);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
}
