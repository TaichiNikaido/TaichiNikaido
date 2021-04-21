//=============================================================================
//
// �h���S�� [enemy_dragon.cpp]
// Author : �ѐ�ї���
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Mode/mode_game.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/scene2d.h"
#include "Base/sound.h"
#include "enemy_dragon.h"
#include "Bullet/bullet_fireball.h"
#include "Player/player.h"
#include "Effect/explosion_dragon.h"
#include "2DPolygon/gameclear_logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/dragon.png")				//�e�N�X�`��
#define SIZE (D3DXVECTOR3(600.0f,600.0f,0.0f))					//�T�C�Y
#define INITIAL_TARGET_DISTANCE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//�ڕW�܂ł̋���
#define MINIMUM_LIFE (0)										//�̗͂̍ŏ��l
#define LIFE (450)												//�̗�
#define MINIMUM_SCALE (0.1f)									//�ŏ��̊g��l
#define MAX_SCALE (1.0f)										//�ő�̊g��l
#define ADD_SCALE (0.01f)										//���Z����g���
#define SCORE (100000)											//�X�R�A
#define INITIAL_PATTERN_ANIME (0)								//�p�^�[���A�j���̏����l
#define MAX_PATTERN_ANIME (4)									//�p�^�[���A�j���̍ő�l
#define INITIAL_COUNTER_ANIME (0)								//�J�E���^�[�A�j���̏����l
#define MAX_COUNTER_ANIME (24)									//�J�E���^�[�A�j���̍ő�l
#define MINIMUM_BULLET_TIME (0)									//�e�̔��ˍŏ�����
#define MINIMUM_CHARGE_TIME (0)									//�`���[�W�̍ŏ�����
#define SHOT_TIME (400)											//�e�𔭎˂���܂ł̎���
#define ANIMATION_VALUE (0.1666f)								//�A�j���[�V�����̒l
#define RANDSEED_VALUE (500)									//�V�[�h�l
#define MOVE_SPEED (2.5f)										//�ړ���
#define RANDMOVE_MAX_X (600.0f)									//�����_���ő�ړ���
#define RANDMOVE_MIN_X (200.0f)									//�����_���ŏ��ړ���
#define RANDMOVE_MAX_Y (300)									//�����_���ő�ړ���

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
	m_TargetPosition = INITIAL_TARGET_DISTANCE;			//�ڕW�܂ł̋���
	m_bCharge = false;								//�`���[�W���Ă邩
	m_bDeath = false;								//���S�������ǂ���
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
	//�����h���S���̃|�C���^��NULL�̏ꍇ
	if (pEnemyDragon == NULL)
	{
		//�h���S���̃������m��
		pEnemyDragon = new CEnemyDragon;
		//�����h���S���̃|�C���^��NULL����Ȃ��ꍇ
		if (pEnemyDragon != NULL)
		{
			//�����������֐��Ăяo��
			pEnemyDragon->Init();
			//�ʒu�ݒ�֐��Ăяo��
			pEnemyDragon->SetPosition(Position);
		}
	}
	//�h���S���̃|�C���^��Ԃ�
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
	SetScale(MINIMUM_SCALE);
	//�̗͂̏����ݒ�
	SetLife(LIFE);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	//�����T�E���h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (pSound != NULL)
	{
		//BGM�̍Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_BGM_DRAGON);
	}
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
	//�Փ˃T�C�Y�̏����ݒ�
	SetCollisionSize(D3DXVECTOR3(SIZE.x - 200.0f,SIZE.y - 200.0f,SIZE.z) * fScale);
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
			SetMove(INITIAL_D3DXVECTOR3);
		}
		else
		{
			//�����X�P�[�����ő�l�ȏ�ɂȂ�����
			if (GetScale() >= MAX_SCALE)
			{
				//�ڕW�����ɋ߂Â�����ڕW���Đݒ肷��
				if (Position.x >= m_TargetPosition.x - PlayerSize.x / 2 &&
					Position.x < m_TargetPosition.x + PlayerSize.x / 2 &&
					Position.y >= m_TargetPosition.y - PlayerSize.y / 2 &&
					Position.y < m_TargetPosition.y + PlayerSize.y / 2)
				{
					//�����_���V�[�h�l
					int nRandSeed = rand() % (FIELD_WIDTH - RANDSEED_VALUE) + (FIELD_WIDTH_MIN + RANDSEED_VALUE);
					srand((unsigned int)nRandSeed);
					m_TargetPosition.x = (float)(rand() % (FIELD_WIDTH - RANDSEED_VALUE) + (FIELD_WIDTH_MIN + RANDSEED_VALUE));//�ڕW�����̌���
					m_TargetPosition.y = (float)(rand() % RANDMOVE_MAX_Y);
				}
				else
				{
					m_TargetDistance = D3DXVECTOR3(m_TargetPosition.x - Position.x, m_TargetPosition.y - Position.y, 0.0f);//�ڕW�܂ł̋������Z�o
					SetRotation(D3DXVECTOR3(Position.x, atan2f(m_TargetDistance.y, m_TargetDistance.x), Position.z));
					SetMove(D3DXVECTOR3(cosf(GetRotation().y)*MOVE_SPEED, sinf(GetRotation().y)*MOVE_SPEED, 0.0f));
				}
				if (Position.x > FIELD_WIDTH - RANDMOVE_MIN_X)
				{
					//�����_���V�[�h�l
					int nRandSeed = rand() % (FIELD_WIDTH - RANDSEED_VALUE) + (FIELD_WIDTH_MIN + RANDSEED_VALUE);
					srand((unsigned int)nRandSeed);
					m_TargetPosition.x = (float)(rand() % (FIELD_WIDTH - RANDSEED_VALUE) + (FIELD_WIDTH_MIN + RANDSEED_VALUE));//�ڕW�����̌���
					m_TargetPosition.y = (float)(rand() % RANDMOVE_MAX_Y);
					m_TargetPosition.x += -RANDMOVE_MAX_X;
				}
				if (Position.x < FIELD_WIDTH_MIN + RANDMOVE_MIN_X)
				{
					//�����_���V�[�h�l
					int nRandSeed = rand() % (FIELD_WIDTH - RANDSEED_VALUE) + (FIELD_WIDTH_MIN + RANDSEED_VALUE);
					srand((unsigned int)nRandSeed);
					m_TargetPosition.x = (float)(rand() % (FIELD_WIDTH - RANDSEED_VALUE) + (FIELD_WIDTH_MIN + RANDSEED_VALUE));//�ڕW�����̌���
					m_TargetPosition.y = (float)(rand() % RANDMOVE_MAX_Y);
					m_TargetPosition.x += RANDMOVE_MIN_X;
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
				CGameMode::SetFireBall(CBulletFireball::Create(D3DXVECTOR3(Position.x, Position.y + Size.y / 2, 0.0f)));
			}
		}
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
	//�΋����擾����
	CBulletFireball * pBulletFireBall = CGameMode::GetBulletFireBall();
	//�����v���C���[�̃|�C���^��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̃X�R�A�����Z����
 		pPlayer->AddScore(SCORE);
	}
	//���S��Ԃɂ���
	m_bDeath = true;
	//�Q�[���N���A���S�̐���
	CGameClearLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	//�h���S���̔�������
	CExplosionDragon::Create();
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
	if (m_nCounterAnime > MAX_COUNTER_ANIME)
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