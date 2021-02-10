//=============================================================================
//
// �v���C���[ [player.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �x������
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "keyboard.h"
#include "joystick.h"
#include "scene2d.h"
#include "mode_game.h"
#include "ui_score.h"
#include "ui_bomb.h"
#include "ui_life.h"
#include "explosion_death.h"
#include "bullet_player.h"
#include "bullet_bomb.h"
#include "player.h"
#include "enemy_dragon.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Player/BattleShip.png")			//�e�N�X�`���p�X
#define SPEED (5.0f)											//�ړ����x
#define DEATH_TIME (100)										//���S����
#define INVINCIBLE_TIME (80)									//���G����
#define INVINCIBLE_COLOR_CHANGE (2)								//�F�ύX
#define INITIAL_BOMB (3)										//�����{����
#define INITIAL_LIFE (3)										//�������@��
#define MINIMUM_LIFE (0)											//�̗͂̍ŏ��l
#define MINIMUM_SPEED (0.0f)										//�ړ����x�̍ŏ��l
#define MINIMUM_BOMB (0)											//�{���̍ŏ��l
#define MINIMUM_SCORE (0)											//�X�R�A�̍ŏ��l
#define MINIMUM_DEATH_COUNT (0)									//���S���̍ŏ��l
#define MINIMUM_DEATH_TIME (0)										//���S���Ԃ̍ŏ��l
#define MINIMUM_INVINCIBLE_TIME (0)								//���G���Ԃ̍ŏ��l
#define MINIMUM_BULLET_INTERVAL (0)								//�e�̔��ˊԊu�̍ŏ��l
#define MINIMUM_CONTINUE_COUNT (0)									//�R���e�B�j���[�̍ŏ��l
#define BOMB_COST (1000)										//�{���g�p���̃X�R�A���Z�l
#define DEATH_COST (1000)										//���S���̃X�R�A���Z�l
#define DEATH_ADD_SCORE (1)										//���S���̃X�R�A���Z�n							
#define ANIMATION_VALUE (0.33333f)								//�A�j���[�V�����̒l
#define BULLET_INTERVAL (10)									//�e�̔��ˊԊu
#define INVICIBLE_TITME_REMAINDER (0)							//���G���Ԃ̗]��
#define BULLET_INTERVAL_REMAINDER (0)							//�e�̔��ˊԊu�̗]��
#define COLOR_TRANSPARENT (D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))	//�����F
#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))					//�F
#define BULLET_DAMAGE (0)										//�e�ւ̃_���[�W
#define LEVEL1_BULLETSPEED (D3DXVECTOR3(0.0f, -10.0f, 0.0f))	//���x��1�̒e�̑��x
#define LEVEL2_LEFTBULLETSPEED (D3DXVECTOR3(cosf(D3DXToRadian (-10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(-10.0f + 90.0f)) * -10.0f, 0.0f))	//���x��2�̒e�̑��x
#define LEVEL2_RIGHTBULLETSPEED (D3DXVECTOR3(cosf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, 0.0f))		//���x��3�̒e�̑��x

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^
char CPlayer::m_aPlayerName[MAX_NAME] = {};		//�v���C���[�l�[��
bool CPlayer::m_bReplay = false;				//���v���C�̐^�U

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene2d(nPriority)
{
	m_Move = INITIAL_MOVE;								//�ړ���
	m_nLife = MINIMUM_LIFE;								//�̗�
	m_nBomb = MINIMUM_BOMB;								//���e�̏�����
	m_nUseBomb = MINIMUM_BOMB;								//���e�̎g�p��
	m_nDeathCount = MINIMUM_DEATH_COUNT;					//���S��
	m_nContinue = MINIMUM_CONTINUE_COUNT;					//�R���e�B�j���[��
	m_nScore = MINIMUM_SCORE;								//�X�R�A
	m_nLevel = LEVEL_NONE;								//���x��
	m_nDeathTime = MINIMUM_DEATH_TIME;						//���S����
	m_nInvincibleTime = MINIMUM_INVINCIBLE_TIME;			//���G����
	m_nBulletInterval = MINIMUM_BULLET_INTERVAL;			//���ˊԊu
	m_fSpeed = MINIMUM_SPEED;								//����
	memset(m_aInputData, NULL, sizeof(m_aInputData));	//���͏��
	m_State = STATE_NONE;								//���
	m_Input = INPUT_NONE;								//���̓L�[���
	m_Attack = ATTACK_NONE;								//�U�����
}	

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CPlayer::TextureLoad(void)
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
void CPlayer::TextureUnload(void)
{
	// �e�N�X�`���̔j��
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
CPlayer * CPlayer::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size)
{
	//�v���C���[�̃|�C���^
	CPlayer * pPlayer = NULL;
	//�v���C���[��NULL�̏ꍇ
	if (pPlayer == NULL)
	{
		//�v���C���[�̃������m��
		pPlayer = new CPlayer;
	}
	//�v���C���[��NULL�ł͂Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̏����������֐��Ăяo��
		pPlayer->Init();
		//�v���C���[�̈ʒu��ݒ肷��
		pPlayer->SetPosition(Position);
		//�v���C���[�̃T�C�Y��ݒ肷��
		pPlayer->SetSize(Size);
	}
	return pPlayer;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel + ANIMATION_VALUE, 1.0f);
	//2D�V�[���Ǘ������������֐��Ăяo��
	CScene2d::Init();
	//�ړ����x�̏����ݒ�
	m_fSpeed = SPEED;
	//�̗͂̏����ݒ�
	m_nLife = INITIAL_LIFE;
	//�����ێ��{�����̏����ݒ�
	m_nBomb = INITIAL_BOMB;
	//���x���̏����ݒ�
	m_nLevel = LEVEL_1;
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	//�������v���C���^�̂Ƃ�
	if (m_bReplay == true)
	{
		//���͏��ǂݍ���
		InputDataLoad();
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPlayer::Uninit(void)
{
	//2D�V�[���Ǘ��I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPlayer::Update(void)
{
	//�X�R�A��UI���擾
	CScoreUI * pScoreUI = CGameMode::GetScoreUI();
	//���e��UI���擾
	CBombUI * pBombUI = CGameMode::GetBombUI();
	//�̗͂�UI���擾
	CLifeUI * pLifeUI = CGameMode::GetLifeUI();
	//�h���S���̎擾
	CEnemyDragon * pEnemyDragon = CGameMode::GetDragon();
	//2D�V�[���Ǘ��X�V�����֐��Ăяo��
	CScene2d::Update();
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel + ANIMATION_VALUE, 1.0f);
	//�ʒu���擾
	D3DXVECTOR3 Position = GetPosition();
	//�������v���C��Ԃ��U�̂Ƃ�
	if (m_bReplay == false)
	{
		//���͏����֐��Ăяo��
		Input();
	}
	//�������v���C��Ԃ��^�Ŏ���ł��Ȃ��Ƃ�
	else
	{
		//���v���C�֐��Ăяo��
		Replay();
	}
	//������Ԃ����G��Ԃ̎�
	if (m_State == STATE_INVINCIBLE)
	{
		//���G�����֐��Ăяo��
		Invincible();
	}
	//�ړ��\�͈͏����֐��Ăяo��
	Position = MovableRange();
	//�ʒu�X�V
	Position += m_Move;
	//�ʒu�̐ݒ�
	SetPosition(Position);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�X�R�A��UI���X�V����
	pScoreUI->SetScore(m_nScore);
	//���e��UI���X�V����
	pBombUI->SetBomb(m_nBomb);
	//�̗͂�UI���X�V����
	pLifeUI->SetLife(m_nLife);
	//�^�C���J�E���g�����֐��Ăяo��
	TimeCount();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPlayer::Draw(void)
{
	//2D�V�[���Ǘ��`�揈���֐��Ăяo��
	CScene2d::Draw();
}

//=============================================================================
// �̗͉��Z�����֐�
//=============================================================================
void CPlayer::AddLife(void)
{
	//�̗͂��ő�l�ɒB���Ă��Ȃ��Ƃ�
	if (m_nLife < PLAYER_MAX_LIFE)
	{
		//�̗͂����Z����
		m_nLife++;
	}
}

//=============================================================================
// �̗͌��Z�����֐�
//=============================================================================
void CPlayer::SubLife(int nValue)
{
	//������Ԃ����G�����S����Ȃ��Ƃ�
	if (m_State != STATE_INVINCIBLE && m_State != STATE_DEATH)
	{
		//�̗͂����Z����
		m_nLife -= nValue;
		//���S�����֐��Ăяo��
		Death();
		//�����̗͂�0�ɂȂ�����
		if (m_nLife <= MINIMUM_LIFE)
		{
			//�R���e�B�j���[�������Z����
			m_nContinue++;
			//���C�t�������ݒ肷��
			m_nLife = INITIAL_LIFE;
		}
	}
}

//=============================================================================
// ���x���A�b�v�����֐�
//=============================================================================
void CPlayer::LevelUp(void)
{
	//�������x��������ɒB���Ă��Ȃ��Ƃ�
	if (m_nLevel <= LEVEL_3)
	{
		//���x�������Z����
		m_nLevel++;
	}
}

//=============================================================================
// ���e���Z�����֐�
//=============================================================================
void CPlayer::AddBomb(void)
{
	//�����������e�����ő�ʂ���Ȃ�������
	if (m_nBomb <= PLAYER_MAX_BOMB)
	{
		//�������e�������Z����
		m_nBomb++;
	}
}

//=============================================================================
// ���e���Z�����֐�
//=============================================================================
void CPlayer::SubBomb(void)
{
	//���e�̏�������1���炷
	m_nBomb--;
	//���e�̎g�p�������Z����
	m_nUseBomb++;
	//�X�R�A�����Y����
	SubScore(BOMB_COST);
}

//=============================================================================
// �X�R�A���Z�����֐�
//=============================================================================
void CPlayer::AddScore(int nValue)
{
	//�X�R�A�����Z����
	m_nScore += nValue;
}

//=============================================================================
// �X�R�A���Z�����֐�
//=============================================================================
void CPlayer::SubScore(int nValue)
{
	//�X�R�A��0��艺�̏ꍇ
	if (m_nScore < MINIMUM_SCORE)
	{
		//�X�R�A�����Z����
		m_nScore -= nValue;
	}
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CPlayer::Input(void)
{
	//�L�[�{�[�h�̎擾
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//�W���C�X�e�B�b�N�̐U���擾
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//�Q�[�����[�h�̎擾
	CGameMode * pGameMode = CManager::GetGameMode();
	//�v���C���[���ړ����Ă��Ȃ��Ƃ�
	m_Move = INITIAL_MOVE;
	//��ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_W) || lpDIDevice != NULL &&js.lY == -1000)
	{
		//���̓L�[������ɂ���
		m_Input = INPUT_UP;
		//���͏���ۑ��ɂ���
		m_aInputData[pGameMode->GetFlameCount()][INPUT_UP] = 1;
		//�ړ������֐��Ăяo��
		Move();
	}
	//���ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_S) || lpDIDevice != NULL &&js.lY == 1000)
	{
		//���̓L�[�������ɂ���
		m_Input = INPUT_DOWN;
		//���͏���ۑ�����
		m_aInputData[pGameMode->GetFlameCount()][INPUT_DOWN] = 1;
		//�ړ������֐��Ăяo��
		Move();
	}
	//���ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
	{
		//���̓L�[�������ɂ���
		m_Input = INPUT_LEFT;
		//���͏���ۑ�����
		m_aInputData[pGameMode->GetFlameCount()][INPUT_LEFT] = 1;
		//�ړ������֐��Ăяo��
		Move();
	}
	//�E�ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
	{
		//���̓L�[�����E�ɂ���
		m_Input = INPUT_RIGHT;
		//���͏���ۑ�����
		m_aInputData[pGameMode->GetFlameCount()][INPUT_RIGHT] = 1;
		//�ړ������֐��Ăяo��
		Move();
	}
	//�e���˃L�[���͏���
	if (pKeyboard->GetKeyboardPress(DIK_SPACE) || lpDIDevice != NULL &&lpDIDevice != NULL && pJoystick->GetJoystickPress(JS_A))
	{
		//���ˊԊu�̃J�E���g��i�߂�
		m_nBulletInterval++;
		//���͏���ۑ�����
		m_aInputData[pGameMode->GetFlameCount()][INPUT_SHOT] = 1;
		//�U������e���˂ɂ���
		m_Attack = ATTACK_SHOT;
		//�U�������֐��Ăяo��
		Attack();
	}
	//���e���˃L�[���͏���
	if (pKeyboard->GetKeyboardTrigger(DIK_B) || lpDIDevice != NULL &&pJoystick->GetJoystickTrigger(JS_B))
	{
		//���͏���ۑ�����
		m_aInputData[pGameMode->GetFlameCount()][INPUT_BOMB] = 1;
		//�U�����𔚒e���˂ɂ���
		m_Attack = ATTACK_BOMB;
		//�U�������֐��Ăяo��
		Attack();
	}
}

//=============================================================================
// �ړ������֐�
//=============================================================================
void CPlayer::Move(void)
{
	//�������S��Ԃ���Ȃ��Ƃ�
	if (m_State != STATE_DEATH)
	{
		switch (m_Input)
		{
			//�������͏�񂪏�̎�
		case INPUT_UP:
			//Y���̏�����Ɉړ��ʂ����Z
			m_Move.y = cosf(D3DX_PI) * m_fSpeed;
			break;
			//�������͏�񂪉��̎�
		case INPUT_DOWN:
			//Y���̉������Ɉړ��ʂ����Z
			m_Move.y = cosf(D3DX_PI) * -m_fSpeed;
			break;
			//�������͏�񂪍��̎�
		case INPUT_LEFT:
			//X���̍������Ɉړ��ʂ����Z
			m_Move.x = cosf(D3DX_PI) * m_fSpeed;
			break;
			//�������͏�񂪉E�̎�
		case INPUT_RIGHT:
			//X���̉E�����Ɉړ��ʂ����Z
			m_Move.x = cosf(D3DX_PI) * -m_fSpeed;
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// �U�������֐�
//=============================================================================
void CPlayer::Attack(void)
{
	//�ړ��ʂ��擾
	D3DXVECTOR3 Position = GetPosition();
	//�T�C�Y������
	D3DXVECTOR3 Size = GetSize();
	//�������S��Ԃ���Ȃ��Ƃ�
	if (m_State != STATE_DEATH)
	{
		switch (m_Attack)
		{
			//�U����񂪃V���b�g�̎�
		case ATTACK_SHOT:
			//�e�̔��ˊ��o����
			if (m_nBulletInterval % BULLET_INTERVAL == BULLET_INTERVAL_REMAINDER)
			{
				switch (m_nLevel)
				{
					//���x��1�̎�
				case LEVEL_1:
					//�e�̐���
					CBulletPlayer::Create(D3DXVECTOR3(Position.x, Position.y - Size.y / 2, Position.z), LEVEL1_BULLETSPEED);
					break;		
					//���x��2�̎�
				case LEVEL_2:	
					//�e�̐���	
					CBulletPlayer::Create(D3DXVECTOR3(Position.x + Size.x / 5, Position.y - Size.y / 2, Position.z), LEVEL1_BULLETSPEED);
					CBulletPlayer::Create(D3DXVECTOR3(Position.x - Size.x / 5, Position.y - Size.y / 2, Position.z), LEVEL1_BULLETSPEED);
					break;	
					//���x��3�̎�
				case LEVEL_3:	
					//�e�̐���
					CBulletPlayer::Create(D3DXVECTOR3(Position.x + Size.x / 5, Position.y - Size.y / 2, Position.z), LEVEL1_BULLETSPEED);
					CBulletPlayer::Create(D3DXVECTOR3(Position.x - Size.x / 5, Position.y - Size.y / 2, Position.z), LEVEL1_BULLETSPEED);
					CBulletPlayer::Create(D3DXVECTOR3(Position.x, Position.y - Size.y / 2, 0.0f), LEVEL2_LEFTBULLETSPEED);
					CBulletPlayer::Create(D3DXVECTOR3(Position.x, Position.y - Size.y / 2, 0.0f), LEVEL2_RIGHTBULLETSPEED);
					break;
				default:
					break;
				}
			}
			break;
			//�U����񂪃{���̎�
		case ATTACK_BOMB:
			//�������e�̏�������1�ȏ�̂Ƃ�
			if (m_nBomb > MINIMUM_BOMB)
			{
				//���e�̐���
				CBulletBomb::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y - GetSize().y / 2, 0.0f), BOMB_SPEED);
				//���e���Z�֐��Ăяo��
				SubBomb();
			}
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CPlayer::Death(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//���S��Ԃɂ���
	m_State = STATE_DEATH;
	//�����G�t�F�N�g�̐���
	CExplosionDeath::Create(GetPosition());
	//�������̍Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
	//�X�R�A�����Z����
	SubScore(DEATH_COST);
	//�X�R�A�����Z����
	AddScore(DEATH_ADD_SCORE);
	//���S�������Z����
	m_nDeathCount++;
	//�F�𓧖��ɂ���
	D3DXCOLOR Color = COLOR_TRANSPARENT;
	//�S�Ă̒e������
	DeleteAllBullet();
	//�F�̐ݒ�
	SetColor(Color);
}

//=============================================================================
// ���G�����֐�
//=============================================================================
void CPlayer::Invincible(void)
{
	//�F��؂�ւ���
	if (m_nInvincibleTime % INVINCIBLE_COLOR_CHANGE == INVICIBLE_TITME_REMAINDER)
	{
		//���_������
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			//�����ɂ���
			D3DXCOLOR Color = COLOR_TRANSPARENT;
			//�F�̐ݒ�
			SetColor(Color);
		}
	}
	else
	{
		//���_������
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			//�ʏ�E�ɂ���
			D3DXCOLOR Color = COLOR;
			//�F�̐ݒ�
			SetColor(Color);
		}
	}
}

//=============================================================================
// ���X�|�[�������֐�
//=============================================================================
void CPlayer::Respawn(void)
{
	//���@�������ʒu�ɔz�u
	SetPosition(PLAYER_POS);
	//���G��Ԃɂ���
	m_State = STATE_INVINCIBLE;
}

//=============================================================================
// �ړ��\�͈͏����֐�
//=============================================================================
D3DXVECTOR3 CPlayer::MovableRange()
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�T�C�Y���擾����
	D3DXVECTOR3 Size = GetSize();
	//�����v���C���[�����ʊO�ɍs������
	if (Position.y - Size.y / 2 < FIELD_HEIGHT_MIN)
	{
		//�ʒu����ʊO�Ɉړ����Ȃ��悤�ɐ��䂷��
		Position.y = Size.y / 2;
	}
	//�����v���C���[������ʊO�ɍs������
	if (Position.y + Size.y > FIELD_HEIGHT)
	{
		//�ʒu����ʊO�Ɉړ����Ȃ��悤�ɐ��䂷��
		Position.y = FIELD_HEIGHT - Size.y;
	}
	//�����v���C���[������ʊO�ɍs������
	if (Position.x - Size.y / 2 < FIELD_WIDTH_MIN)
	{
		//�ʒu����ʊO�Ɉړ����Ȃ��悤�ɐ��䂷��
		Position.x = Size.y / 2 + FIELD_WIDTH_MIN;
	}
	//�����v���C���[���E��ʊO�ɍs������
	if (Position.x + Size.y / 2 > FIELD_WIDTH)
	{
		//�ʒu����ʊO�Ɉړ����Ȃ��悤�ɐ��䂷��
		Position.x = FIELD_WIDTH - Size.y / 2;
	}
	return Position;
}

//=============================================================================
// ���v���C�����֐�
//=============================================================================
void CPlayer::Replay(void)
{
	//�Q�[�����[�h�̎擾
	CGameMode * pGameMode = CManager::GetGameMode();
	//�v���C���[���ړ����Ă��Ȃ��Ƃ�
	m_Move = INITIAL_MOVE;
	//��L�[�̓��͏�񂪂���Ƃ�
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_UP] == '1')
	{
		//���̓L�[������ɂ���
		m_Input = INPUT_UP;
		//�ړ������֐��Ăяo��
		Move();
	}
	//���L�[�̓��͏�񂪂���Ƃ�
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_DOWN] == '1')
	{
		//���̓L�[�������ɂ���
		m_Input = INPUT_DOWN;
		//�ړ������֐��Ăяo��
		Move();
	}
	//���L�[�̓��͏�񂪂���Ƃ�
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_LEFT] == '1')
	{
		//���̓L�[�������ɂ���
		m_Input = INPUT_LEFT;
		//�ړ������֐��Ăяo��
		Move();
	}
	//�E�L�[�̓��͏�񂪂���Ƃ�
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_RIGHT] == '1')
	{
		//���̓L�[�����E�ɂ���
		m_Input = INPUT_RIGHT;
		//�ړ������֐��Ăяo��
		Move();
	}
	//�ˌ��L�[�̓��͏�񂪂���Ƃ�
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_SHOT] == '1')
	{
		//���ˊԊu�̃J�E���g��i�߂�
		m_nBulletInterval++;
		//�U������e���˂ɂ���
		m_Attack = ATTACK_SHOT;
		//�U�������֐��Ăяo��
		Attack();
	}
	//���e���˃L�[�̓��͏�񂪂���Ƃ�
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_BOMB] == '1')
	{
		//�U�����𔚒e���˂ɂ���
		m_Attack = ATTACK_BOMB;
		//�U�������֐��Ăяo��
		Attack();
	}
}

//=============================================================================
// �S�e�j�������֐�
//=============================================================================
void CPlayer::DeleteAllBullet(void)
{
	//�V�[���̑�������
	for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
	{
		//�V�[���̎擾
		CScene * pScene = GetScene(PRIORITY_BULLET, nCountScene);
		//�����V�[����NULL����Ȃ��ꍇ
		if (pScene != NULL)
		{
			//�e�̃|�C���^
			CBullet * pBullet = dynamic_cast<CBullet*> (pScene);
			//�e�̃|�C���^��NULL����Ȃ��ꍇ
			if (pBullet != NULL)
			{
				//�e�̃��C�t��0�ɂ���
				pBullet->SetLife(BULLET_DAMAGE);
			}
		}
	}
}

//=============================================================================
// �^�C���J�E���g�����֐�
//=============================================================================
void CPlayer::TimeCount(void)
{
	switch (m_State)
	{
		//��Ԃ����S��Ԃ̎�
	case STATE_DEATH:
		//���S���Ԃ����Z����
		m_nDeathTime++;
		//�e�S����
		DeleteAllBullet();
		//���G��ԂɈڍs����
		if (m_nDeathTime >= DEATH_TIME)
		{
			//���X�|�[�������֐��Ăяo��
			Respawn();
			//���S���Ԃ�����������
			m_nDeathTime = MINIMUM_DEATH_TIME;
		}
		break;
		//��Ԃ����G��Ԃ̎�
	case STATE_INVINCIBLE:
		//���G���Ԃ����Z����
		m_nInvincibleTime++;
		//�e�S����
		DeleteAllBullet();
		//����ԂɈڍs����
		if (m_nInvincibleTime >= INVINCIBLE_TIME)
		{
			//��Ԃ𖳂ɂ���
			m_State = STATE_NONE;
			//���G���Ԃ�����������
			m_nInvincibleTime = MINIMUM_INVINCIBLE_TIME;
		}
		break;
	default:
		//�F��ݒ肷��
		SetColor(COLOR);
		break;
	}
}

//=============================================================================
// �N���A�����֐�
//=============================================================================
void CPlayer::Clear(void)
{
	//�������v���C���[�h�ł͖����ꍇ
	if (m_bReplay == false)
	{
		//���͏��ۑ������֐��Ăяo��
		InputDataSave();
	}
	else
	{
		//���v���C���U�ɂ���
		m_bReplay = false;
	}
	//�f�[�^�ۑ������֐��Ăяo��
	DataSave();
	//���U���g�֑J��
	CManager::StartFade(CManager::MODE_RESULT);
}

//=============================================================================
// �f�[�^�ۑ������֐�
//=============================================================================
void CPlayer::DataSave(void)
{
	//�t�@�C���̃|�C���^
	FILE * pFile;
	//�t�@�C���̏�������
	pFile = fopen("data/Text/PlayerData.txt", "w");
	//�t�@�C����NULL�`�F�b�N
	if (pFile != NULL)
	{
		//���O���L�^
		fprintf(pFile, "%s\n", &m_aPlayerName);
		//���S�����L�^
		fprintf(pFile, "%d\n", m_nDeathCount);
		//�R���e�B�j���[�����L�^
		fprintf(pFile, "%d\n", m_nContinue);
		//�{���̎g�p�񐔂��L�^
		fprintf(pFile, "%d\n", m_nUseBomb);
		//�X�R�A���L�^
		fprintf(pFile, "%d\n", m_nScore);
		//�t�@�C�������
		fclose(pFile);
	}
}

//=============================================================================
// ���͏��ۑ������֐�
//=============================================================================
void CPlayer::InputDataSave(void)
{
	//�t�@�C���̃|�C���^
	FILE * pFile;
	//�Q�[�����[�h�̎擾
	CGameMode * pGameMode = CManager::GetGameMode();
	//�t�@�C���̏�������
	pFile = fopen("data/Text/InputData.txt", "w");
	//�t�@�C����NULL�`�F�b�N
	if (pFile != NULL)
	{
		//�Q�[���̃t���[����������
		for (int nCount = 0; nCount < pGameMode->GetFlameCount(); nCount++)
		{
			//������̓��͏���ۑ�����
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_UP]);
			//�������̓��͏���ۑ�����
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_DOWN]);
			//�������̓��͏���ۑ�����
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_LEFT]);
			//�E�����̓��͏���ۑ�����
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_RIGHT]);
			//���e���˂̓��͏���ۑ�����
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_BOMB]);
			//�e���˂̓��͏���ۑ�����
			fprintf(pFile, "%d\n", m_aInputData[nCount][INPUT_SHOT]);
		}
		//�t�@�C�������
		fclose(pFile);
	}
}

//=============================================================================
// ���͏��ǂݍ��ݏ����֐�
//=============================================================================
void CPlayer::InputDataLoad(void)
{
	//�t�@�C���̃|�C���^
	FILE *pFile;
	//�t�@�C���̓ǂݍ���
	pFile = fopen("data/TEXT/InputData.txt", "r");
	//�t�@�C����NULL�`�F�b�N
	if (pFile != NULL)
	{
		//�t���[���̍ő�l����
		for (int nCount = 0; nCount < MAX_FLAME; nCount++)
		{
			//���͏��ǂݍ���
			fscanf(pFile, "%s", &m_aInputData[nCount][INPUT_UP]);
		}
		//�t�@�C�������
		fclose(pFile);
	}
}
//=============================================================================
// ���O�擾�֐�
//=============================================================================
void CPlayer::SetPlayerName(int nCount, char aName)
{
	//���O���擾����
	m_aPlayerName[nCount] = aName;
}