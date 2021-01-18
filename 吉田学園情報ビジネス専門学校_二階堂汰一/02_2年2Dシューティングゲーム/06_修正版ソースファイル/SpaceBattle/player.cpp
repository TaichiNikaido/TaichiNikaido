//=============================================================================
//
// �v���C���[���� [player.cpp]
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
#include "mode_game.h"
#include "renderer.h"
#include "scene2d.h"
#include "keyboard.h"
#include "joystick.h"
#include "sound.h"
#include "player.h"
#include "bullet_player.h"
#include "bullet_bomb.h"
#include "ui_score.h"
#include "ui_bomb.h"
#include "ui_life.h"
#include "explosion_death.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Player/BattleShip.png")
#define DEATH_TIME (100)
#define INVINCIBLE_TIME (80)
#define INITIAL_BOMB (3)
#define INITIAL_LIFE (3)
#define BOMB_COST (1000)
#define DEATH_COST (1000)
#define LEVEL1_BULLETSPEED (D3DXVECTOR3(0.0f, -10.0f, 0.0f))
#define LEVEL2_LEFTBULLETSPEED (D3DXVECTOR3(cosf(D3DXToRadian (-10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(-10.0f + 90.0f)) * -10.0f, 0.0f))
#define LEVEL2_RIGHTBULLETSPEED (D3DXVECTOR3(cosf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, 0.0f))

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority)
{
	m_pBullet = NULL;									//�e�ւ̃|�C���^
	m_Move = D3DXVECTOR3(0.0f,0.0f,0.0f);				//�ړ���
	m_nLife = 0;										//�̗�
	m_nBomb = 0;										//���e�̏�����
	m_nUseBomb = 0;										//���e�̎g�p��
	m_nDeathCount = 0;									//���S��
	m_nContinue = 0;									//�R���e�B�j���[��
	m_nScore = 0;										//�X�R�A
	m_nLevel = LEVEL_NONE;								//���x��
	m_nDeathTime = 0;									//���S����
	m_nInvincibleTime = 0;								//���G����
	m_nBulletinterval = 0;								//���ˊԊu
	m_nCount = 0;										//�J�E���g
	m_fSpeed = 0.0f;									//����
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
void CPlayer::TextureUnload(void)
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
CPlayer * CPlayer::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size)
{
	CPlayer * pPlayer;
	pPlayer = new CPlayer;
	pPlayer->Init();
	pPlayer->SetPosition(Position);
	pPlayer->SetSize(Size);
	return pPlayer;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.33333f * m_nLevel, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.33333f * m_nLevel + 0.33333f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.33333f * m_nLevel, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.33333f * m_nLevel + 0.33333f, 1.0f);
	//2D�V�[���Ǘ������������֐��Ăяo��
	CScene2d::Init();
	//�I�u�W�F�^�C�v���v���C���[�ɂ���
	SetObjType(CScene::OBJTYPE_PLAYER);
	//�ړ����x�̏����ݒ�
	m_fSpeed = PLAYER_SPEED;
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
	//�Q�[�����[�h�̎擾
	CGameMode * pGameMode = CManager::GetGameMode();
	//�X�R�A��UI���擾
	CScoreUI * pScoreUI = CGameMode::GetScoreUI();
	//���e��UI���擾
	CBombUI * pBombUI = CGameMode::GetBombUI();
	//�̗͂�UI���擾
	CLifeUI * pLifeUI = CGameMode::GetLifeUI();
	//2D�V�[���Ǘ��X�V�����֐��Ăяo��
	CScene2d::Update();
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.33333f * m_nLevel, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.33333f * m_nLevel + 0.33333f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.33333f * m_nLevel, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.33333f * m_nLevel + 0.33333f, 1.0f);
	//�ʒu���擾
	D3DXVECTOR3 Position = GetPosition();
	//�������v���C��Ԃ��U�̂Ƃ�
	if (pGameMode->GetbReplay() == false)
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
	Position = MovableRange(Position);
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
	//�̗͂����Z����
	m_nLife -= nValue;
	//���S�����֐��Ăяo��
	Death();
	//�����̗͂�0�ɂȂ�����
	if (m_nLife <= 0)
	{
		//�R���e�B�j���[�������Z����
		m_nContinue++;
		//���C�t�������ݒ肷��
		m_nLife = INITIAL_LIFE;
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
	if (m_nScore < 0)
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
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
		m_nBulletinterval++;
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

	if (pKeyboard->GetKeyboardTrigger(DIK_Z))
	{
		Death();
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
		case INPUT_UP:
			m_Move.y = cosf(D3DX_PI) * m_fSpeed;
			break;
		case INPUT_DOWN:
			m_Move.y = cosf(D3DX_PI) * -m_fSpeed;
			break;
		case INPUT_LEFT:
			m_Move.x = cosf(D3DX_PI) * m_fSpeed;
			break;
		case INPUT_RIGHT:
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
	//�������S��Ԃ���Ȃ��Ƃ�
	if (m_State != STATE_DEATH)
	{
		switch (m_Attack)
		{
		case ATTACK_SHOT:
			//�e�̔��ˊ��o����
			if (m_nBulletinterval % 10 == 0)
			{
				switch (m_nLevel)
				{
				case LEVEL_1:
					//�e�̐���
					m_pBullet = CBulletPlayer::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y - GetSize().y / 2, GetPosition().z), LEVEL1_BULLETSPEED);
					break;
				case LEVEL_2:
					//�e�̐���
					m_pBullet = CBulletPlayer::Create(D3DXVECTOR3(GetPosition().x + GetSize().x / 5, GetPosition().y - GetSize().y / 2, GetPosition().z), LEVEL1_BULLETSPEED);
					m_pBullet = CBulletPlayer::Create(D3DXVECTOR3(GetPosition().x - GetSize().x / 5, GetPosition().y - GetSize().y / 2, GetPosition().z), LEVEL1_BULLETSPEED);
					break;
				case LEVEL_3:
					//�e�̐���
					m_pBullet = CBulletPlayer::Create(D3DXVECTOR3(GetPosition().x + GetSize().x / 5, GetPosition().y - GetSize().y / 2, GetPosition().z), LEVEL1_BULLETSPEED);
					m_pBullet = CBulletPlayer::Create(D3DXVECTOR3(GetPosition().x - GetSize().x / 5, GetPosition().y - GetSize().y / 2, GetPosition().z), LEVEL1_BULLETSPEED);
					m_pBullet = CBulletPlayer::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y - GetSize().y / 2, 0.0f), LEVEL2_LEFTBULLETSPEED);
					m_pBullet = CBulletPlayer::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y - GetSize().y / 2, 0.0f), LEVEL2_RIGHTBULLETSPEED);
					break;
				default:
					break;
				}
			}
			break;
		case ATTACK_BOMB:
			//�������e�̏�������1�ȏ�̂Ƃ�
			if (m_nBomb > 0)
			{
				//���e�̐���
				m_pBullet = CBulletBomb::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y - GetSize().y / 2, 0.0f), BOMB_SPEED);
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
	D3DXCOLOR Color;
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
	AddScore(1);
	//���S�������Z����
	m_nDeathCount++;
	//�F�𓧖��ɂ���
	Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	//�S�Ă̒e������
	//
	//�F�̐ݒ�
	SetColor(Color);
}

//=============================================================================
// ���G�����֐�
//=============================================================================
void CPlayer::Invincible(void)
{
	if (m_nCount % 5 == 0)
	{
		if (m_nInvincibleTime % 2 == 0)
		{
			//�������
			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
			{
				D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				//�F�̐ݒ�
				SetColor(Color);
			}
		}
		else
		{
			//�ʏ���
			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
			{
				D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				//�F�̐ݒ�
				SetColor(Color);
			}
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
D3DXVECTOR3 CPlayer::MovableRange(D3DXVECTOR3 Position)
{
	//�����v���C���[�����ʊO�ɍs������
	if (Position.y - GetSize().y / 2 < 0)
	{
		Position.y = GetSize().y / 2;
	}
	//�����v���C���[������ʊO�ɍs������
	if (Position.y + GetSize().y > FIELD_HEIGHT)
	{
		Position.y = FIELD_HEIGHT - GetSize().y;
	}
	//�����v���C���[������ʊO�ɍs������
	if (Position.x - GetSize().y / 2 < FIELD_WIDTH_MIN)
	{
		Position.x = GetSize().y / 2 + FIELD_WIDTH_MIN;
	}
	//�����v���C���[���E��ʊO�ɍs������
	if (Position.x + GetSize().y / 2 > FIELD_WIDTH)
	{
		Position.x = FIELD_WIDTH - GetSize().y / 2;
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
	//��L�[�̓��͏�񂪂���Ƃ�
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_UP] == '1')
	{
		//�ړ��ʂ���
		m_Move.y = cosf(D3DX_PI)*m_fSpeed;
		//���̓L�[������ɂ���
		m_Input = INPUT_UP;
		//�ړ������֐��Ăяo��
		Move();
	}
	//���L�[�̓��͏�񂪂���Ƃ�
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_DOWN] == '1')
	{
		//�ړ��ʂ���
		m_Move.y = cosf(D3DX_PI)*-m_fSpeed;
		//���̓L�[�������ɂ���
		m_Input = INPUT_DOWN;
		//�ړ������֐��Ăяo��
		Move();
	}
	//���L�[�̓��͏�񂪂���Ƃ�
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_LEFT] == '1')
	{
		//�ړ��ʂ���
		m_Move.x = cosf(D3DX_PI)*m_fSpeed;
		//���̓L�[�������ɂ���
		m_Input = INPUT_LEFT;
		//�ړ������֐��Ăяo��
		Move();
	}
	//�E�L�[�̓��͏�񂪂���Ƃ�
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_RIGHT] == '1')
	{
		//�ړ��ʂ���
		m_Move.x = cosf(D3DX_PI)*-m_fSpeed;
		//���̓L�[�����E�ɂ���
		m_Input = INPUT_RIGHT;
		//�ړ������֐��Ăяo��
		Move();
	}
	//�ˌ��L�[�̓��͏�񂪂���Ƃ�
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_SHOT] == '1')
	{
		//���ˊԊu�̃J�E���g��i�߂�
		m_nBulletinterval++;
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
// �^�C���J�E���g�����֐�
//=============================================================================
void CPlayer::TimeCount(void)
{
	switch (m_State)
	{
	case STATE_DEATH:
		//���S���Ԃ����Z����
		m_nDeathTime++;
		//���G��ԂɈڍs����
		if (m_nDeathTime >= DEATH_TIME)
		{
			//���X�|�[�������֐��Ăяo��
			Respawn();
			//���S���Ԃ�����������
			m_nDeathTime = 0;
		}
		break;
	case STATE_INVINCIBLE:
		//���G���Ԃ����Z����
		m_nInvincibleTime++;
		//�J�E���g��i�߂�
		m_nCount++;
		//����ԂɈڍs����
		if (m_nInvincibleTime >= INVINCIBLE_TIME)
		{
			//��Ԃ𖳂ɂ���
			m_State = STATE_NONE;
			//���G���Ԃ�����������
			m_nInvincibleTime = 0;
			//�J�E���g������������
			m_nCount = 0;
		}
		break;
	default:
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	}
}

//=============================================================================
// �v���C���[���ۑ������֐�
//=============================================================================
void CPlayer::DataSave(void)
{
	FILE * pFile;

	pFile = fopen("data/TEXT/PlayerData.txt", "w"); //�t�@�C���̏�������

	if (pFile != NULL)
	{
		//���O���L�^
		//fprintf(pFile, "%s\n", &m_aPlayerName);
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
	FILE * pFile;
	//�Q�[�����[�h�̎擾
	CGameMode * pGameMode = CManager::GetGameMode();

	//�t�@�C���̏�������
	pFile = fopen("data/TEXT/InputData.txt", "w");

	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < pGameMode->GetFlameCount(); nCount++)
		{
		//	�v���C���[�̓��͏��̋L�^
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_UP]);
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_DOWN]);
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_LEFT]);
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_RIGHT]);
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_BOMB]);
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
	FILE *pFile;

	//�t�@�C���̓ǂݍ���
	pFile = fopen("data/TEXT/InputData.txt", "r");

	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < 15000; nCount++)
		{
			//���͏��ǂݍ���
			fscanf(pFile, "%s", &m_aInputData[nCount][0]);
		}
		//�t�@�C�������
		fclose(pFile);
	}
}














////=============================================================================
////
//// �v���C���[���� [player.cpp]
//// Author : ��K������
////
////=============================================================================
//#define _CRT_SECURE_NO_WARNINGS
////*****************************************************************************
//// �w�b�_�t�@�C���̃C���N���[�h
////*****************************************************************************
//#include "main.h"
//#include "manager.h"
//#include "game.h"
//#include "renderer.h"
//#include "input.h"
//#include "keyboard.h"
//#include "joystick.h"
//#include "scene.h"
//#include "scene2d.h"
//#include "player.h"
//#include "sound.h"
//#include "own.h"
//#include "ownui.h"
//#include "Bomb.h"
//#include "explosion.h"
//#include "bombui.h"
//#include "fade.h"
//#include "score.h"
//#include "player.h"
//#include "title.h"
//#include <stdio.h>
//#include <stdlib.h>
//
//LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
//int CPlayer::m_nScore = 0;
//char CPlayer::m_aPlayerName[MAX_NAME] = {};
//int CPlayer::m_nNameCount = 0;
//bool CPlayer::m_bDeath = false;
//
////=============================================================================
//// �R���X�g���N�^(�����o�ϐ��̏�����(�S��0��))
////=============================================================================
//CPlayer::CPlayer(int nPriority) :CScene2d(nPriority)
//{
//	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //�ʒu
//	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�ʒu
//	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//	{
//		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���_���W
//		m_col[nCount] = D3DCOLOR_RGBA(0, 0, 0, 255);
//	}
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //����
//	m_fLength = 0.0f;		//�|���S���̑Ίp���̒���
//	m_fAngle = 0.0f;		//�|���S���̊p�x
//	m_fScale = 0.0f;		// �g��
//	m_fAddScale = 0.0f;		// �g����Z�l
//	m_nOwn = 0;				//���@�̐�
//	m_nLevel = 0;			//�v���C���[���x��
//	m_nCountBullet = 0;		//�e�̃J�E���g
//	m_nBomb = 0;			//�������Ă锚�e�̐�
//	m_fWidth = 0.0f;		//��
//	m_fHeight = 0.0f;		//����
//	m_fSpeed = 0.0f;		//����
//	m_bShot = false;		//���˂��Ă邩�ǂ���
//	m_bInvincible = false;	//���G���ǂ���
//	m_bHit = false;			//HIT�������ǂ���
//	m_nInvincibleCount = 0;
//	m_nCount = 0;			//�J�E���g
//	m_nContinue = 0;			//�R���e�B�j���[��
//	m_nDeath = 0;			//���S��
//	m_nUseBomb = 0;			//�g�p�����{���̐�
//	m_nDeathCount = 0;		//���S����
//	memset(m_aInputData, NULL, sizeof(m_aInputData));
//	m_bDeath = false;
//	//m_nInputSaveCount = 0;
//	//m_nInputLoadCount = 0;
//	m_pBullet = NULL;
//}
//
////=============================================================================
////�f�X�g���N�^
////=============================================================================
//CPlayer::~CPlayer()
//{
//}
//
////=============================================================================
//// �e�N�X�`�����[�h�֐�
////=============================================================================
//HRESULT CPlayer::TextureLoad(void)
//{
//	CRenderer *pRenderer = CManager::GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	// �e�N�X�`���̐���
//	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
//		TEXTURE_PLAYER,								// �t�@�C���̖��O
//		&m_pTexture);								// �ǂݍ��ރ������[
//	return S_OK;
//}
//
////=============================================================================
//// �e�N�X�`���A�����[�h�֐�
////=============================================================================
//void CPlayer::TextureUnload(void)
//{
//	// �e�N�X�`���̔j��
//	if (m_pTexture != NULL)
//	{
//		m_pTexture->Release();
//		m_pTexture = NULL;
//	}
//}
//
////=============================================================================
//// �����֐�
////=============================================================================
//CPlayer * CPlayer::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, int nOwn)
//{
//	CPlayer * pPlayer;
//	pPlayer = new CPlayer;
//	pPlayer->Init(pos, SizeHeight, SizeWidth, nOwn);
//	return pPlayer;
//}
//
////=============================================================================
//// �������֐�(�����o�ϐ��̏����ݒ�)
////=============================================================================
//HRESULT CPlayer::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, int nOwn)
//{
//	CScene2d::Init(pos, SizeWidth, SizeHeight);
//
//	//�����_���[�̎擾
//	//CRenderer *pRenderer = CManager::GetRenderer();
//	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	//�I�u�W�F�^�C�v���v���C���[�ɂ���
//	SetObjType(CScene::OBJTYPE_PLAYER);
//
//	m_Position = pos;	//�v���C���[�̈ʒu
//	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�ʒu
//	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//	{
//		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���_���W
//		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
//	}
//
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //����
//	m_fLength = 0.0f;			//�|���S���̑Ίp���̒���
//	m_fAngle = 0.0f;			//�|���S���̊p�x
//	m_fScale = 0.0f;			// �g��
//	m_fAddScale = 0.0f;			// �g����Z�l
//	m_nOwn = nOwn;				//���@�̐�
//	m_nLevel = 1;				//�v���C���[���x��
//	m_nCountBullet = 0;			//�e�̃J�E���g
//	m_nBomb = 3;				//���e�̏�����
//	m_bShot = false;			//���˂��Ă邩�ǂ���
//	m_bInvincible = true;
//	m_fWidth = SizeWidth;		//�v���C���[�̕�
//	m_fHeight = SizeHeight;		//�v���C���[�̍���
//	m_fSpeed = PLAYER_SPEED;	//�v���C���[�̑��x
//	m_nCount = 0;				//�J�E���g
//	m_nDeath = 0;				//���S��
//	m_nContinue = 0;			//�R���e�B�j���[��
//	m_nDeathCount = 0;			//���S����
//	m_nUseBomb = 0;				//�g�p�����{���̐�
//	m_bDeath = false;			//���񂾂��ǂ���
//	m_bHit = false;				//HIT�������ǂ���
//	memset(m_aInputData, NULL, sizeof(m_aInputData));
//	//m_nInputSaveCount = 0;
//	//m_nInputLoadCount = 5;
//
//	if (CTitle::GetbReplay() == true)
//	{
//		InputLoad();
//	}
//
//	// ���_���W��ݒ�
//	m_vpos[0] = D3DXVECTOR3(m_Position.x + (-m_fWidth / 2), m_Position.y + (-m_fHeight / 2), 0.0f);
//	m_vpos[1] = D3DXVECTOR3(m_Position.x + (m_fWidth / 2), m_Position.y + (-m_fHeight / 2), 0.0f);
//	m_vpos[2] = D3DXVECTOR3(m_Position.x + (-m_fWidth / 2), m_Position.y + (m_fHeight / 2), 0.0f);
//	m_vpos[3] = D3DXVECTOR3(m_Position.x + (m_fWidth / 2), m_Position.y + (m_fHeight / 2), 0.0f);
//
//	//�e�N�X�`���̃Z�b�g
//	SetTex(
//		(m_nLevel - 1) * 0.33333f,
//		0.0f,
//		(m_nLevel - 1) * 0.33333f + 0.33333f,
//		1.0f);
//	SetVertexPosition(m_vpos);	//���_���W�̐ݒ�
//	BindTexture(m_pTexture);	//�e�N�X�`���̊��蓖��
//
//								//�{����UI�擾
//	CBombUI * pBombUI = CGame::GetBombUI();
//
//	pBombUI->AddBombUI(3);
//	Save();
//	return S_OK;
//}
//
////=============================================================================
//// �I���֐�
////=============================================================================
//void CPlayer::Uninit(void)
//{
//	CScene2d::Uninit();
//}
//
////=============================================================================
//// �X�V�֐�
////=============================================================================
//void CPlayer::Update(void)
//{
//	CScene2d::Update();
//	//�ʒu�̎擾
//	m_Position = GetPosition();
//	//�T�E���h�̎擾
//	CSound * pSound = CManager::GetSound();
//	//�L�[�{�[�h�̎擾
//	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
//	//�W���C�X�e�B�b�N�̎擾
//	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
//	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
//	DIJOYSTATE js;
//	//�W���C�X�e�B�b�N�̐U���擾
//	LPDIRECTINPUTEFFECT pDIEffect = CInputJoystick::GetEffect();
//
//	if (lpDIDevice != NULL)
//	{
//		lpDIDevice->Poll();
//		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
//	}
//
//	//�������@�������Ă���
//	if (m_bDeath == false)
//	{
//		//�v���C���[���ړ����Ă��Ȃ��Ƃ�
//		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		if (CTitle::GetbReplay() == false)
//		{
//			//�v���C���[�̍��ړ�
//			if (pInputKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
//			{
//				m_move.x = cosf(D3DX_PI)*m_fSpeed;
//				m_aInputData[CGame::GetbInputSaveCount()][INPUT_LEFT] = 1;
//			}
//
//			//�v���C���[�̉E�ړ�
//			if (pInputKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
//			{
//				m_move.x = cosf(D3DX_PI)*-m_fSpeed;
//				m_aInputData[CGame::GetbInputSaveCount()][INPUT_RIGHT] = 1;
//			}
//
//			//�v���C���[�̏�ړ�
//			if (pInputKeyboard->GetKeyboardPress(DIK_W) || lpDIDevice != NULL &&js.lY == -1000)
//			{
//				m_move.y = cosf(D3DX_PI)*m_fSpeed;
//				m_aInputData[CGame::GetbInputSaveCount()][INPUT_UP] = 1;
//			}
//
//			//�v���C���[�̉��ړ�
//			if (pInputKeyboard->GetKeyboardPress(DIK_S) || lpDIDevice != NULL &&js.lY == 1000)
//			{
//				m_move.y = cosf(D3DX_PI)*-m_fSpeed;
//				m_aInputData[CGame::GetbInputSaveCount()][INPUT_DOWN] = 1;
//			}
//
//			//�v���C���[�̔��e����
//			if (pInputKeyboard->GetKeyboardTrigger(DIK_B) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_B))
//			{
//				//�������e��1�ȏ㎝���Ă�����
//				if (m_nBomb >= PLAYER_BOMB_COST)
//				{
//					//���e�̐���
//					m_pBomb = CBomb::Create(D3DXVECTOR3(m_Position.x, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BOMB_SIZE, BOMB_SIZE, PLAYER_BOMB_LIFE, PLAYER_BOMB_DAMAGE);
//					//�������e���̌��Z
//					SubBomb(PLAYER_SUB_BOMB);
//				}
//				m_aInputData[CGame::GetbInputSaveCount()][INPUT_BOMB] = 1;
//			}
//
//			//�v���C���[�̃r�[��
//			if (pInputKeyboard->GetKeyboardPress(DIK_Q))
//			{
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x + PLAYER_SIZE / 5, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BEAM_SIZE, BEAM_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NONE, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
//			}
//
//			//�v���C���[�̒e����
//			if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) || lpDIDevice != NULL &&pInputJoystick->GetJoystickPress(JS_A))
//			{
//				//�ˌ���Ԃ�true�ɂ���
//				m_bShot = true;
//				m_aInputData[CGame::GetbInputSaveCount()][INPUT_SHOT] = 1;
//			}
//			else
//			{
//				//�ˌ���Ԃ�false�ɂ���
//				m_bShot = false;
//				//�e�̃J�E���g��
//				m_nCountBullet = 9;
//				//pDIEffect->Stop();
//			}
//		}
//		else
//		{
//			if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_UP] == '1')
//			{
//				m_move.y = cosf(D3DX_PI)*m_fSpeed;
//			}
//			if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_DOWN] == '1')
//			{
//				m_move.y = cosf(D3DX_PI)*-m_fSpeed;
//			}
//			if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_LEFT] == '1')
//			{
//				m_move.x = cosf(D3DX_PI)*m_fSpeed;
//			}
//			if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_RIGHT] == '1')
//			{
//				m_move.x = cosf(D3DX_PI)*-m_fSpeed;
//			}
//			if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_SHOT] == '1')
//			{
//				//�ˌ���Ԃ�true�ɂ���
//				m_bShot = true;
//			}
//			else
//			{
//				//�ˌ���Ԃ�false�ɂ���
//				m_bShot = false;
//				//�e�̃J�E���g��
//				m_nCountBullet = 9;
//				//pDIEffect->Stop();
//			}
//			if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_BOMB] == '1')
//			{
//				//�������e��1�ȏ㎝���Ă�����
//				if (m_nBomb >= PLAYER_BOMB_COST)
//				{
//					//���e�̐���
//					m_pBomb = CBomb::Create(D3DXVECTOR3(m_Position.x, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BOMB_SIZE, BOMB_SIZE, PLAYER_BOMB_LIFE, PLAYER_BOMB_DAMAGE);
//					//�������e���̌��Z
//					SubBomb(PLAYER_SUB_BOMB);
//				}
//			}
//		}
//
//		//�����e�������Ă���Ƃ�
//		if (m_bShot == true)
//		{
//
//			//�e�̃J�E���g��i�߂�
//			m_nCountBullet++;
//		}
//
//		//�e�̔��ˊ��o����
//		if (m_nCountBullet % 10 == 0)
//		{
//			//�v���C���[�̃��x���ɂ��e�̐���
//			switch (m_nLevel)
//			{
//			case 1:
//				//�e�̐���
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
//				break;
//			case 2:
//				//�e�̐���
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x + PLAYER_SIZE / 5, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x - PLAYER_SIZE / 5, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
//				break;
//			case 3:
//				//�e�̐���
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x + PLAYER_SIZE / 5, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x - PLAYER_SIZE / 5, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(cosf(D3DXToRadian(-10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(-10.0f + 90.0f)) * -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK * 2);
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(cosf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK * 2);
//				break;
//			default:
//				break;
//			}
//			//�V���b�g���̐���
//			pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
//
//			if (pDIEffect != NULL)
//			{
//				//�W���C�X�e�B�b�N�̐U������
//				pDIEffect->Start(1, 0);
//			}
//		}
//
//		//�����v���C���[�����ʊO�ɍs������
//		if (m_Position.y - PLAYER_SIZE / 2 < 0)
//		{
//			m_Position.y = PLAYER_SIZE / 2;
//		}
//
//		//�����v���C���[������ʊO�ɍs������
//		if (m_Position.y + PLAYER_SIZE > FIELD_HEIGHT)
//		{
//			m_Position.y = FIELD_HEIGHT - PLAYER_SIZE;
//		}
//
//		//�����v���C���[������ʊO�ɍs������
//		if (m_Position.x - PLAYER_SIZE / 2 < FIELD_WIDTH_MIN)
//		{
//			m_Position.x = PLAYER_SIZE / 2 + FIELD_WIDTH_MIN;
//		}
//
//		//�����v���C���[���E��ʊO�ɍs������
//		if (m_Position.x + PLAYER_SIZE / 2 > FIELD_WIDTH)
//		{
//			m_Position.x = FIELD_WIDTH - PLAYER_SIZE / 2;
//		}
//	}
//	//�����v���C���[�����G�̎�
//	if (m_bInvincible == true)
//	{
//		//���G��
//		if (m_nCount <= PLAYER_INVINCIBLE_TIME)
//		{
//			if (m_nCount % 5 == 0)
//			{
//				//���G���Ԃ̃J�E���g��i�߂�
//				m_nInvincibleCount++;
//
//				if (m_nInvincibleCount % 2 == 0)
//				{
//					//�������
//					for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//					{
//						m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 0);
//					}
//				}
//				else
//				{
//					//�ʏ���
//					for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//					{
//						m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
//					}
//				}
//			}
//		}
//		else
//		{
//			//���G����߂�
//			m_bInvincible = false;
//			//�J�E���g��߂�
//			m_nInvincibleCount = 0;
//			//�J�E���g��߂�
//			m_nCount = 0;
//			//�ʏ��Ԃɖ߂�
//			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//			{
//				m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
//			}
//		}
//		//�J�E���g��i�߂�
//		m_nCount++;
//	}
//
//	//�������@�����񂾂Ƃ�
//	if (m_bDeath == true)
//	{
//		if (m_bHit == true)
//		{
//			m_bHit = false;
//		}
//		for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
//		{
//			CScene * pScene = GetScene(4, nCountScene);
//			if (pScene != NULL)
//			{
//				//�I�u�W�F�^�C�v�̎擾
//				OBJTYPE objType;
//				objType = pScene->GetObjType();
//				//�V�[���I�u�W�F�N�g�̈ʒu���擾
//				D3DXVECTOR3 Scene_pos;
//				Scene_pos = pScene->GetPosition();
//				//�����I�u�W�F�^�C�v���e�̏ꍇ
//				if (objType == OBJTYPE_BULLET)
//				{
//					pScene->Uninit();
//				}
//			}
//		}
//		//�������
//		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//		{
//			m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 0);
//		}
//		//�����J�E���g�����S���Ԉȉ��̏ꍇ
//		if (m_nDeathCount >= PLAYER_DEATH_TIME)
//		{
//			//���@�������ʒu�ɔz�u
//			m_Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 180, 0.0f);
//			//���S��ԉ���
//			m_bDeath = false;
//			//���G��Ԃɂ���
//			m_bInvincible = true;
//			//�J�E���g��0�ɖ߂�
//			m_nDeathCount = 0;
//		}
//		//���S���Ԃ�i�߂�
//		m_nDeathCount++;
//	}
//
//	//�ʒu�X�V
//	m_Position.x += m_move.x;
//	m_Position.y += m_move.y;
//
//	// ���_���W��ݒ�
//	m_vpos[0] = D3DXVECTOR3(m_Position.x + (-m_fWidth / 2), m_Position.y + (-m_fHeight / 2), 0.0f);
//	m_vpos[1] = D3DXVECTOR3(m_Position.x + (m_fWidth / 2), m_Position.y + (-m_fHeight / 2), 0.0f);
//	m_vpos[2] = D3DXVECTOR3(m_Position.x + (-m_fWidth / 2), m_Position.y + (m_fHeight / 2), 0.0f);
//	m_vpos[3] = D3DXVECTOR3(m_Position.x + (m_fWidth / 2), m_Position.y + (m_fHeight / 2), 0.0f);
//
//	//m_nInputSaveCount++;
//	//m_nInputLoadCount++;
//
//	if (CTitle::GetbReplay() == false)
//	{
//		if (CDragon::GetDeath() == true)
//		{
//			CPlayer::Save();
//			CPlayer::InputSave();
//			CDragon::SetDeath(false);
//			CManager::StartFade(CManager::MODE_RESULT);
//		}
//	}
//
//	SetTex(
//		(m_nLevel - 1) * 0.33333f,
//		0.0f,
//		(m_nLevel - 1) * 0.33333f + 0.33333f,
//		1.0f);
//	//�F�̃Z�b�g
//	SetColor(m_col);
//	//���_���̃Z�b�g
//	SetVertexPosition(m_vpos);
//	//�ʒu�̏��̃Z�b�g
//	SetPosition(m_Position);
//}
//
////=============================================================================
//// �`��֐�
////=============================================================================
//void CPlayer::Draw(void)
//{
//	CScene2d::Draw();
//}
//
////=============================================================================
//// HIT�֐�
////=============================================================================
//void CPlayer::Hit(void)
//{
//	//�̗͂̌��Z
//	SubOwn(PLAYER_SUB_OWN);
//	//HIT��Ԃ�true�ɂ���
//	m_bHit = true;
//}
//
////=============================================================================
//// ���@���Z�֐�
////=============================================================================
//void CPlayer::AddOwn(int nValue)
//{
//	//���@��UI�̎擾
//	COwnUI * pOwnUI = CGame::GetOwnUI();
//	if (m_nOwn < MAX_OWN)
//	{
//		//���@�̉��Z����
//		m_nOwn += nValue;
//		//�v���C���[�̎��@��UI�����Z
//		pOwnUI->AddOwnUI(PLAYER_ADD_OWN);
//	}
//}
//
////=============================================================================
//// ���@���Z�֐�
////=============================================================================
//void CPlayer::SubOwn(int nValue)
//{
//	//�W���C�X�e�B�b�N�̐U���擾
//	LPDIRECTINPUTEFFECT pDIEffect = CInputJoystick::GetEffect();
//	//�X�R�A�擾
//	CScore * pScore = CGame::GetScore();
//	//���@��UI�擾
//	COwnUI * pOwnUI = CGame::GetOwnUI();
//	//�T�E���h�̎擾
//	CSound * pSound = CManager::GetSound();
//
//	//�������@�����G����Ȃ��Ƃ�
//	if (m_bDeath == false)
//	{
//		if (m_bInvincible == false)
//		{
//			//�J���[�̎w��
//			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//			{
//				m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
//			}
//			//�����̔���
//			CExplosion::Create(m_Position, PLAYER_EXPLOSION_SIZE, PLAYER_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
//			//�������̐���
//			pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
//			//���@�̌��Z����
//			m_nOwn -= nValue;
//			//���S�������Z
//			m_nDeath++;
//			//���@UI�̌��Z
//			pOwnUI->SubOwnUI(PLAYER_SUB_OWN);
//			if (pDIEffect != NULL)
//			{
//				//�W���C�X�e�B�b�N�̐U���J�n
//				pDIEffect->Start(1, 0);
//			}
//			//���S��Ԃɂ���
//			m_bDeath = true;
//		}
//
//		//�v���C���[�̎��@����PLAYER_MIN_OWN�ȉ��ɂȂ����Ƃ�(�v���C���[�����񂾂Ƃ�)
//		if (m_nOwn <= PLAYER_MIN_OWN)
//		{
//			//���@�̉��Z����
//			m_nOwn = PLAYER_INIT_OWN;
//			//���@UI�̉��Z����
//			pOwnUI->AddOwnUI(PLAYER_INIT_OWN);
//			//�X�R�A�̉��Z�֐��Ăяo��
//			pScore->AddScore(1);
//			//�X�R�A�̌��Z
//			pScore->SubScore(1000);
//			//���U���g�������Z
//			m_nContinue++;
//			//���S��Ԃɂ���
//			m_bDeath = true;
//			//���[�h���U���g��
//			//CManager::StartFade(CManager::MODE_RESULT);
//		}
//	}
//}
//
////=============================================================================
//// ���x�����Z�֐�
////=============================================================================
//void CPlayer::AddLevel(int nValue)
//{
//	//�T�E���h�̎擾
//	CSound * pSound = CManager::GetSound();
//	pSound->PlaySound(CSound::SOUND_LABEL_LVUP);
//	//�����̒l�����Z
//	m_nLevel += nValue;
//}
//
////=============================================================================
//// ���e���Z�֐�
////=============================================================================
//void CPlayer::AddBomb(int nValue)
//{
//	//�{����UI�擾
//	CBombUI * pBombUI = CGame::GetBombUI();
//	//�����̒l�����Z
//	m_nBomb += nValue;
//	pBombUI->AddBombUI(PLAYER_ADD_BOMB);
//}
//
////=============================================================================
//// ���e���Z�֐�
////=============================================================================
//void CPlayer::SubBomb(int nValue)
//{
//	//�X�R�A�擾
//	CScore * pScore = CGame::GetScore();
//	//�{����UI�擾
//	CBombUI * pBombUI = CGame::GetBombUI();
//	//�����̒l�����Z
//	m_nBomb -= nValue;
//	//�{���̎g�p�񐔂����Z
//	m_nUseBomb++;
//	//�X�R�A�̌��Z
//	pScore->SubScore(1000);
//	//�{����UI�Z�b�g
//	pBombUI->SubBombUI(PLAYER_SUB_BOMB);
//}
//
////=============================================================================
//// �X�R�A�擾�֐�
////=============================================================================
//void CPlayer::SetPlayerScpre(int nValue)
//{
//	m_nScore = nValue;
//}
//
////=============================================================================
//// ���O�擾�֐�
////=============================================================================
//void CPlayer::SetPlayerName(int nCount, char aName)
//{
//	m_aPlayerName[nCount] = aName;
//	/*m_nNameCount++;*/
//}
//
////=============================================================================
//// �Z�[�u�֐�
////=============================================================================
//void CPlayer::Save(void)
//{
//	FILE *pFile;
//
//	pFile = fopen("data/TEXT/PlayerData.txt", "w"); //�t�@�C���̏�������
//
//	if (pFile != NULL)
//	{
//		//���O���L�^
//		fprintf(pFile, "%s\n", &m_aPlayerName);
//		//���S�����L�^
//		fprintf(pFile, "%d\n", m_nDeath);
//		//�R���e�B�j���[�����L�^
//		fprintf(pFile, "%d\n", m_nContinue);
//		//�{���̎g�p�񐔂��L�^
//		fprintf(pFile, "%d\n", m_nUseBomb);
//		//�X�R�A���L�^
//		fprintf(pFile, "%d\n", m_nScore);
//
//		//for (int nCount = 0; nCount < CGame::GetbInputSaveCount(); nCount++)
//		//{
//		//	//�v���C���[�̓��͏��̋L�^
//		//	fprintf(pFile, "%d", m_aInputData[nCount][0]);
//		//	fprintf(pFile, "%d", m_aInputData[nCount][1]);
//		//	fprintf(pFile, "%d", m_aInputData[nCount][2]);
//		//	fprintf(pFile, "%d", m_aInputData[nCount][3]);
//		//	fprintf(pFile, "%d", m_aInputData[nCount][4]);
//		//	fprintf(pFile, "%d\n", m_aInputData[nCount][5]);
//		//}
//
//		//�t�@�C�������
//		fclose(pFile);
//	}
//}
//
//void CPlayer::InputSave(void)
//{
//	FILE *pFile;
//
//	pFile = fopen("data/TEXT/InputData.txt", "w"); //�t�@�C���̏�������
//
//	if (pFile != NULL)
//	{
//		for (int nCount = 0; nCount < CGame::GetbInputSaveCount(); nCount++)
//		{
//			//�v���C���[�̓��͏��̋L�^
//			fprintf(pFile, "%d", m_aInputData[nCount][0]);
//			fprintf(pFile, "%d", m_aInputData[nCount][1]);
//			fprintf(pFile, "%d", m_aInputData[nCount][2]);
//			fprintf(pFile, "%d", m_aInputData[nCount][3]);
//			fprintf(pFile, "%d", m_aInputData[nCount][4]);
//			fprintf(pFile, "%d\n", m_aInputData[nCount][5]);
//		}
//
//		//�t�@�C�������
//		fclose(pFile);
//	}
//}
//
//void CPlayer::InputLoad(void)
//{
//	FILE *pFile;
//
//	pFile = fopen("data/TEXT/InputData.txt", "r"); //�t�@�C���̓ǂݍ���
//
//	if (pFile != NULL)
//	{
//		for (int nCount = 0; nCount < 15000; nCount++)
//		{
//			//�v���C���[�̓��͏��ǂݍ���
//			fscanf(pFile, "%s", &m_aInputData[nCount][0]);
//		}
//
//		fclose(pFile); //�t�@�C�������
//	}
//}
