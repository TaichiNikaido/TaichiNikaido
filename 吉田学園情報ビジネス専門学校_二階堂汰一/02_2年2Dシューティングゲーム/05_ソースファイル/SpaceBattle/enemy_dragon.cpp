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
#define INITIAL_TARGET_DISTANCE (D3DXVECTOR3(0.0f,0.0f,0.0f))
#define LIFE (300)
#define SCALE (0.1f)
#define ADD_SCALE (0.01f)
#define SCORE (100000)
#define INITIAL_PATTERN_ANIME (0)
#define INITIAL_COUNTER_ANIME (0)
#define MINIMUM_LIFE (0)
#define MINIMUM_BULLET_TIME (0)
#define MINIMUM_CHARGE_TIME (0)
#define MAX_SCALE (1.0f)
#define MAX_ANIME_COUNT (24)
#define MAX_PATTERN_ANIME (4)
#define SHOT_TIME (400)
#define ANIMATION_VALUE (0.1666f)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyDragon::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyDragon::CEnemyDragon()
{
	m_nPatternAnime = INITIAL_PATTERN_ANIME;		//�p�^�[���A�j��
	m_nCounterAnime = INITIAL_COUNTER_ANIME;		//�J�E���^�[�A�j��
	m_nBulletTime = MINIMUM_BULLET_TIME;			//�e�̔��˂܂ł̎���
	m_TargetDistance = INITIAL_TARGET_DISTANCE;		//�ڕW�܂ł̋���
	m_bCharge = false;								//�`���[�W���Ă邩
	m_pBulletFireBall = NULL;						//�΋�
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
void CEnemyDragon::TextureUnload(void)
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
CEnemyDragon * CEnemyDragon::Create(D3DXVECTOR3 Position)
{
	//�h���S���̃|�C���^
	CEnemyDragon * pEnemyDragon = NULL;
	//�����h���S���̃|�C���^��NULL��������
	if (pEnemyDragon == NULL)
	{
		//�h���S���̃������m��
		pEnemyDragon = new CEnemyDragon;
	}
	//�����������֐��Ăяo��
	pEnemyDragon->Init();
	//�ʒu�ݒ�֐��Ăяo��
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
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
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
	//�G�̍X�V�����֐��Ăяo��
	CEnemy::Update();
	//�g�k�����֐��Ăяo��
	Scale();
	//AI�����֐��Ăяo��
	AI();
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
	if (fScale <= MAX_SCALE)
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
// AI�����֐�
//=============================================================================
void CEnemyDragon::AI(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�v���C���[���擾����
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�����v���C���[�̃|�C���^��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̈ʒu���擾����
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//�v���C���[�̃T�C�Y���擾����
		D3DXVECTOR3 PlayerSize = GetSize();
		//�����`���[�W������������
		if (m_bCharge == true)
		{
			//�ړ��ʂ�ݒ肷��
			SetMove(INITIAL_MOVE);
		}
		else
		{
			//�����X�P�[�����ő�l�ȏ�ɂȂ�����
			if (GetScale() >= MAX_SCALE)
			{
				//�ڕW�����ɋ߂Â�����ڕW���Đݒ肷��
				if (Position.x >= PlayerPosition.x - PlayerSize.x / 2 &&
					Position.x < PlayerPosition.x + PlayerSize.x / 2 &&
					Position.y >= PlayerPosition.y - PlayerSize.y / 2 &&
					Position.y < PlayerPosition.y + PlayerSize.y / 2)
				{
					//�����_���V�[�h�l
					int nRandSeed = rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500);
					srand((unsigned int)nRandSeed);
					PlayerPosition.x = (float)(rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500));//�ڕW�����̌���
					PlayerPosition.y = (float)(rand() % 300 + 200);
				}
				else
				{
					m_TargetDistance = D3DXVECTOR3(PlayerPosition.x - Position.x, PlayerPosition.y - Position.y, 0.0f);//�ڕW�܂ł̋������Z�o
					SetRotation(D3DXVECTOR3(Position.x, atan2f(m_TargetDistance.y, m_TargetDistance.x), Position.z));
					SetMove(D3DXVECTOR3(cosf(Position.y)*2.5f, sinf(Position.y)*2.5f, 0.0f));
				}
				if (Position.x > FIELD_WIDTH - 200)
				{
					//�����_���V�[�h�l
					int nRandSeed = rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500);
					srand((unsigned int)nRandSeed);
					PlayerPosition.x = (float)(rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500));//�ڕW�����̌���
					PlayerPosition.y = (float)(rand() % 300 + 200);
					PlayerPosition.x += -600.0f;
				}
				if (Position.x < FIELD_WIDTH_MIN + 200)
				{
					//�����_���V�[�h�l
					int nRandSeed = rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500);
					srand((unsigned int)nRandSeed);
					PlayerPosition.x = (float)(rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500));//�ڕW�����̌���
					PlayerPosition.y = (float)(rand() % 300 + 200);
					PlayerPosition.x += 200.0f;
				}
			}
		}
	}
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
			//�������˂܂ł̎���
			if (m_nBulletTime % SHOT_TIME == REMAINDER)
			{
				//�΋��̔���
				m_pBulletFireBall = CBulletFireball::Create(D3DXVECTOR3(Position.x, Position.y + Size.y / 2, 0.0f));
			}
		}
	}
	//�����`���[�W������������
	if (m_bCharge == true)
	{
		//�`���[�W���I��点��
		m_bCharge = false;
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
	//�����v���C���[�̃|�C���^��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̃X�R�A�����Z����
 		pPlayer->AddScore(SCORE);
		//�v���C���[�̏��������֐��Ăяo��
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
	//�A�j���J�E���g���ő�ɂȂ����ꍇ
	if (m_nCounterAnime > MAX_ANIME_COUNT)
	{
		//�J�E���g��0�ɂ���
		m_nCounterAnime = INITIAL_COUNTER_ANIME;
		//�p�^�[���̃C���N�������g
		m_nPatternAnime++;
		//�����p�^�[���A�j����4�ɂȂ�����
		if (m_nPatternAnime > MAX_PATTERN_ANIME)
		{
			//�p�^�[���A�j��������������
			m_nPatternAnime = INITIAL_PATTERN_ANIME;
		}
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
