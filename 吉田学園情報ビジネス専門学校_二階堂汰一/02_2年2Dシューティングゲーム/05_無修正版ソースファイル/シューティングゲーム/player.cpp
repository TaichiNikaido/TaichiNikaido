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
#include "main.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "input.h"
#include "keyboard.h"
#include "joystick.h"
#include "scene.h"
#include "scene2d.h"
#include "player.h"
#include "sound.h"
#include "own.h"
#include "ownui.h"
#include "Bomb.h"
#include "explosion.h"
#include "bombui.h"
#include "fade.h"
#include "score.h"
#include "player.h"
#include "title.h"
#include <stdio.h>
#include <stdlib.h>

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^
int CPlayer::m_nScore = 0;						//�X�R�A
char CPlayer::m_aPlayerName[MAX_NAME] = {};		//���O
int CPlayer::m_nNameCount = 0;					//���O�̕�����
bool CPlayer::m_bDeath = false;					//���񂾂��ǂ���

//=============================================================================
// �R���X�g���N�^(�����o�ϐ��̏�����(�S��0��))
//=============================================================================
CPlayer::CPlayer(int nPriority):CScene2d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�ʒu
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���_���W
		m_col[nCount] = D3DCOLOR_RGBA(0, 0, 0, 255);	//���_�J���[	
	}
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //����
	m_fLength = 0.0f;		//�|���S���̑Ίp���̒���
	m_fAngle = 0.0f;		//�|���S���̊p�x
	m_fScale = 0.0f;		//�g��
	m_fAddScale = 0.0f;		//�g����Z�l
	m_nOwn = 0;				//���@�̐�
	m_nLevel = 0;			//�v���C���[���x��
	m_nCountBullet = 0;		//�e�̃J�E���g
	m_nBomb = 0;			//�������Ă锚�e�̐�
	m_fWidth = 0.0f;		//��
	m_fHeight = 0.0f;		//����
	m_fSpeed = 0.0f;		//����
	m_bShot = false;		//���˂��Ă邩�ǂ���
	m_bInvincible = false;	//���G���ǂ���
	m_bHit = false;			//HIT�������ǂ���
	m_nInvincibleCount = 0;	//���G���ԃJ�E���g
	m_nCount = 0;			//�J�E���g
	m_nContinue = 0;		//�R���e�B�j���[��
	m_nDeath = 0;			//���S��
	m_nUseBomb = 0;			//�g�p�����{���̐�
	m_nDeathCount = 0;		//���S����
	memset(m_aInputData, NULL, sizeof(m_aInputData));	//���͏��
	m_bDeath = false;		//���S�������ǂ���
	m_pBullet = NULL;		//�e�ւ̃|�C���^
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// �e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CPlayer::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PLAYER,								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h�֐�
//=============================================================================
void CPlayer::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �����֐�
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,int nOwn)
{
	CPlayer * pPlayer;
	pPlayer = new CPlayer;
	pPlayer->Init(pos, SizeHeight, SizeWidth, nOwn);
	return pPlayer;
}

//=============================================================================
// �������֐�(�����o�ϐ��̏����ݒ�)
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,int nOwn)
{
	CScene2d::Init(pos, SizeWidth, SizeHeight);

	//�I�u�W�F�^�C�v���v���C���[�ɂ���
	SetObjType(CScene::OBJTYPE_PLAYER);
	//�v���C���[�̈ʒu��ݒ肷��
	m_pos = pos;
	//�ʒu��ݒ肷��
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���_���W
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);	//���_�J���[
	}
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //����
	m_fLength = 0.0f;			//�|���S���̑Ίp���̒���
	m_fAngle = 0.0f;			//�|���S���̊p�x
	m_fScale = 0.0f;			//�g��
	m_fAddScale = 0.0f;			//�g����Z�l
	m_nOwn = nOwn;				//���@�̐�
	m_nLevel = 1;				//�v���C���[���x��
	m_nCountBullet = 0;			//�e�̃J�E���g
	m_nBomb = 3;				//���e�̏�����
	m_bShot = false;			//���˂��Ă邩�ǂ���
	m_bInvincible = true;		//���G���ǂ���
	m_fWidth = SizeWidth;		//�v���C���[�̕�
	m_fHeight = SizeHeight;		//�v���C���[�̍���
	m_fSpeed = PLAYER_SPEED;	//�v���C���[�̑��x
	m_nCount = 0;				//�J�E���g
	m_nDeath = 0;				//���S��
	m_nContinue = 0;			//�R���e�B�j���[��
	m_nDeathCount = 0;			//���S����
	m_nUseBomb = 0;				//�g�p�����{���̐�
	m_bDeath = false;			//���񂾂��ǂ���
	m_bHit = false;				//HIT�������ǂ���
	memset(m_aInputData, NULL, sizeof(m_aInputData));	//���͏��
	//�������v���C���[�h�Ȃ�
	if (CTitle::GetbReplay() == true)
	{
		//���͏���ǂݍ���
		InputLoad();
	}
	// ���_���W��ݒ�
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	//�e�N�X�`���̃Z�b�g
	SetTex(
		(m_nLevel - 1) * 0.33333f,
		0.0f,
		(m_nLevel - 1) * 0.33333f + 0.33333f,
		1.0f);
	SetVertexPosition(m_vpos);	//���_���W�̐ݒ�
	BindTexture(m_pTexture);	//�e�N�X�`���̊��蓖��
	//�{����UI�擾
	CBombUI * pBombUI = CGame::GetBombUI();
	//�{���̏����ݒ�
	pBombUI->AddBombUI(3);
	//�Z�[�u�֐��Ăяo��
	Save();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CPlayer::Update(void)
{
	CScene2d::Update();
	//�ʒu�̎擾
	m_pos = GetPosition();
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//�W���C�X�e�B�b�N�̎擾
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
	DIJOYSTATE js;
	//�W���C�X�e�B�b�N�̐U���擾
	LPDIRECTINPUTEFFECT pDIEffect = CInputJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//�������@�������Ă���
	if (m_bDeath == false)
	{
		//�v���C���[���ړ����Ă��Ȃ��Ƃ�
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//���͏����֐��Ăяo��
		Input();
		//�U�������֐�
		Attack();
		//�ړ��\�͈͐��䏈���֐��Ăяo��
		MovableRange();
	}
	//�����v���C���[�����G�̎�
	if (m_bInvincible == true)
	{
		//���G�����֐��Ăяo��
		Invincible();
	}
	//�������@�����񂾂Ƃ�
	if (m_bDeath == true)
	{
		//���S�����֐��Ăяo��
		Death();
	}
	//�ʒu�X�V
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	// ���_���W��ݒ�
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	//�������v���C���[�h����Ȃ��Ƃ�
	if (CTitle::GetbReplay() == false)
	{
		//�����h���S�������S������
		if (CDragon::GetDeath() == true)
		{
			CPlayer::Save();
			CPlayer::InputSave();
			CDragon::SetDeath(false);
			CManager::StartFade(CManager::MODE_RESULT);
		}
	}
	//�e�N�X�`���̐ݒ�
	SetTex(
		(m_nLevel - 1) * 0.33333f,
		0.0f,
		(m_nLevel - 1) * 0.33333f + 0.33333f,
		1.0f);
	//�F�̃Z�b�g
	SetColor(m_col);
	//���_���̃Z�b�g
	SetVertexPosition(m_vpos);
	//�ʒu�̏��̃Z�b�g
	SetPosition(m_pos);
}

//=============================================================================
// �`��֐�
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// HIT�֐�
//=============================================================================
void CPlayer::Hit(void)
{
	//�̗͂̌��Z
	SubOwn(PLAYER_SUB_OWN);
	//HIT��Ԃ�true�ɂ���
	m_bHit = true;
}

//=============================================================================
// ���@���Z�֐�
//=============================================================================
void CPlayer::AddOwn(int nValue)
{
	//���@��UI�̎擾
	COwnUI * pOwnUI = CGame::GetOwnUI();						
	if (m_nOwn < MAX_OWN)
	{
		//���@�̉��Z����
		m_nOwn += nValue;
		//�v���C���[�̎��@��UI�����Z
		pOwnUI->AddOwnUI(PLAYER_ADD_OWN);
	}
}

//=============================================================================
// ���@���Z�֐�
//=============================================================================
void CPlayer::SubOwn(int nValue)
{
	//�W���C�X�e�B�b�N�̐U���擾
	LPDIRECTINPUTEFFECT pDIEffect = CInputJoystick::GetEffect();
	//�X�R�A�擾
	CScore * pScore = CGame::GetScore();
	//���@��UI�擾
	COwnUI * pOwnUI = CGame::GetOwnUI();
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();

	//�������@�����G����Ȃ��Ƃ�
	if (m_bDeath == false)
	{
		if (m_bInvincible == false)
		{
			//�J���[�̎w��
			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
			{
				m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			//�����̔���
			CExplosion::Create(m_pos, PLAYER_EXPLOSION_SIZE, PLAYER_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
			//�������̐���
			pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
			//���@�̌��Z����
			m_nOwn -= nValue;
			//���S�������Z
			m_nDeath++;
			//���@UI�̌��Z
			pOwnUI->SubOwnUI(PLAYER_SUB_OWN);
			if (pDIEffect != NULL)
			{
				//�W���C�X�e�B�b�N�̐U���J�n
				pDIEffect->Start(1, 0);
			}
			//���S��Ԃɂ���
			m_bDeath = true;
		}
		//�v���C���[�̎��@����PLAYER_MIN_OWN�ȉ��ɂȂ����Ƃ�(�v���C���[�����񂾂Ƃ�)
		if (m_nOwn <= PLAYER_MIN_OWN)
		{
			//���@�̉��Z����
			m_nOwn = PLAYER_INIT_OWN;
			//���@UI�̉��Z����
			pOwnUI->AddOwnUI(PLAYER_INIT_OWN);
			//�X�R�A�̉��Z�֐��Ăяo��
			pScore->AddScore(1);
			//�X�R�A�̌��Z
			pScore->SubScore(1000);
			//���U���g�������Z
			m_nContinue++;
			//���S��Ԃɂ���
			m_bDeath = true;
		}
	}
}

//=============================================================================
// ���x�����Z�֐�
//=============================================================================
void CPlayer::AddLevel(int nValue)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_LVUP);
	//�����̒l�����Z
	m_nLevel += nValue;
}

//=============================================================================
// ���e���Z�֐�
//=============================================================================
void CPlayer::AddBomb(int nValue)
{
	//�{����UI�擾
	CBombUI * pBombUI = CGame::GetBombUI();
	//�����̒l�����Z
	if (m_nBomb <= 5)
	{
		m_nBomb += nValue;
		pBombUI->AddBombUI(PLAYER_ADD_BOMB);
	}
}

//=============================================================================
// ���e���Z�֐�
//=============================================================================
void CPlayer::SubBomb(int nValue)
{
	//�X�R�A�擾
	CScore * pScore = CGame::GetScore();
	//�{����UI�擾
	CBombUI * pBombUI = CGame::GetBombUI();
	//�����̒l�����Z
	m_nBomb -= nValue;
	//�{���̎g�p�񐔂����Z
	m_nUseBomb++;
	//�X�R�A�̌��Z
	pScore->SubScore(1000);
	//�{����UI�Z�b�g
	pBombUI->SubBombUI(PLAYER_SUB_BOMB);
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CPlayer::Input(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//�W���C�X�e�B�b�N�̎擾
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
	DIJOYSTATE js;
	//�W���C�X�e�B�b�N�̐U���擾
	LPDIRECTINPUTEFFECT pDIEffect = CInputJoystick::GetEffect();

	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	if (CTitle::GetbReplay() == false)
	{
		//�v���C���[�̍��ړ�
		if (pInputKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
		{
			m_move.x = cosf(D3DX_PI)*m_fSpeed;
			m_aInputData[CGame::GetbInputSaveCount()][INPUT_LEFT] = 1;
		}

		//�v���C���[�̉E�ړ�
		if (pInputKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
		{
			m_move.x = cosf(D3DX_PI)*-m_fSpeed;
			m_aInputData[CGame::GetbInputSaveCount()][INPUT_RIGHT] = 1;
		}

		//�v���C���[�̏�ړ�
		if (pInputKeyboard->GetKeyboardPress(DIK_W) || lpDIDevice != NULL &&js.lY == -1000)
		{
			m_move.y = cosf(D3DX_PI)*m_fSpeed;
			m_aInputData[CGame::GetbInputSaveCount()][INPUT_UP] = 1;
		}

		//�v���C���[�̉��ړ�
		if (pInputKeyboard->GetKeyboardPress(DIK_S) || lpDIDevice != NULL &&js.lY == 1000)
		{
			m_move.y = cosf(D3DX_PI)*-m_fSpeed;
			m_aInputData[CGame::GetbInputSaveCount()][INPUT_DOWN] = 1;
		}

		//�v���C���[�̔��e����
		if (pInputKeyboard->GetKeyboardTrigger(DIK_B) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_B))
		{
			//�������e��1�ȏ㎝���Ă�����
			if (m_nBomb >= PLAYER_BOMB_COST)
			{
				//���e�̐���
				m_pBomb = CBomb::Create(D3DXVECTOR3(m_pos.x, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BOMB_SIZE, BOMB_SIZE, PLAYER_BOMB_LIFE, PLAYER_BOMB_DAMAGE);
				//�������e���̌��Z
				SubBomb(PLAYER_SUB_BOMB);
			}
			m_aInputData[CGame::GetbInputSaveCount()][INPUT_BOMB] = 1;
		}

		//�v���C���[�̃r�[��
		if (pInputKeyboard->GetKeyboardPress(DIK_Q))
		{
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x + PLAYER_SIZE / 5, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BEAM_SIZE, BEAM_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NONE, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
		}

		//�v���C���[�̒e����
		if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) || lpDIDevice != NULL &&pInputJoystick->GetJoystickPress(JS_A))
		{
			//�ˌ���Ԃ�true�ɂ���
			m_bShot = true;
			m_aInputData[CGame::GetbInputSaveCount()][INPUT_SHOT] = 1;
		}
		else
		{
			//�ˌ���Ԃ�false�ɂ���
			m_bShot = false;
			//�e�̃J�E���g��
			m_nCountBullet = 9;
			//pDIEffect->Stop();
		}
	}
	else
	{
		if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_UP] == '1')
		{
			m_move.y = cosf(D3DX_PI)*m_fSpeed;
		}
		if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_DOWN] == '1')
		{
			m_move.y = cosf(D3DX_PI)*-m_fSpeed;
		}
		if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_LEFT] == '1')
		{
			m_move.x = cosf(D3DX_PI)*m_fSpeed;
		}
		if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_RIGHT] == '1')
		{
			m_move.x = cosf(D3DX_PI)*-m_fSpeed;
		}
		if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_SHOT] == '1')
		{
			//�ˌ���Ԃ�true�ɂ���
			m_bShot = true;
		}
		else
		{
			//�ˌ���Ԃ�false�ɂ���
			m_bShot = false;
			//�e�̃J�E���g��
			m_nCountBullet = 9;
		}
		if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_BOMB] == '1')
		{
			//�������e��1�ȏ㎝���Ă�����
			if (m_nBomb >= PLAYER_BOMB_COST)
			{
				//���e�̐���
				m_pBomb = CBomb::Create(D3DXVECTOR3(m_pos.x, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BOMB_SIZE, BOMB_SIZE, PLAYER_BOMB_LIFE, PLAYER_BOMB_DAMAGE);
				//�������e���̌��Z
				SubBomb(PLAYER_SUB_BOMB);
			}
		}
	}
}

//=============================================================================
// �U�������֐�
//=============================================================================
void CPlayer::Attack(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//�W���C�X�e�B�b�N�̎擾
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
	DIJOYSTATE js;
	//�W���C�X�e�B�b�N�̐U���擾
	LPDIRECTINPUTEFFECT pDIEffect = CInputJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//�����e�������Ă���Ƃ�
	if (m_bShot == true)
	{
		//�e�̃J�E���g��i�߂�
		m_nCountBullet++;
	}
	//�e�̔��ˊ��o����
	if (m_nCountBullet % 10 == 0)
	{
		//�v���C���[�̃��x���ɂ��e�̐���
		switch (m_nLevel)
		{
		case 1:
			//�e�̐���
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
			break;
		case 2:
			//�e�̐���
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x + PLAYER_SIZE / 5, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x - PLAYER_SIZE / 5, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
			break;
		case 3:
			//�e�̐���
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x + PLAYER_SIZE / 5, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x - PLAYER_SIZE / 5, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(cosf(D3DXToRadian(-10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(-10.0f + 90.0f)) * -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK * 2);
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(cosf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK * 2);
			break;
		default:
			break;
		}
		//�V���b�g���̐���
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

		if (pDIEffect != NULL)
		{
			//�W���C�X�e�B�b�N�̐U������
			pDIEffect->Start(1, 0);
		}
	}
}

//=============================================================================
// �ړ��\�͈͐��䏈���֐�
//=============================================================================
void CPlayer::MovableRange(void)
{
	//�����v���C���[�����ʊO�ɍs������
	if (m_pos.y - PLAYER_SIZE / 2 < 0)
	{
		m_pos.y = PLAYER_SIZE / 2;
	}

	//�����v���C���[������ʊO�ɍs������
	if (m_pos.y + PLAYER_SIZE > FIELD_HEIGHT)
	{
		m_pos.y = FIELD_HEIGHT - PLAYER_SIZE;
	}

	//�����v���C���[������ʊO�ɍs������
	if (m_pos.x - PLAYER_SIZE / 2 < FIELD_WIDTH_MIN)
	{
		m_pos.x = PLAYER_SIZE / 2 + FIELD_WIDTH_MIN;
	}

	//�����v���C���[���E��ʊO�ɍs������
	if (m_pos.x + PLAYER_SIZE / 2 > FIELD_WIDTH)
	{
		m_pos.x = FIELD_WIDTH - PLAYER_SIZE / 2;
	}
}

//=============================================================================
// ���G�����֐�
//=============================================================================
void CPlayer::Invincible(void)
{
	//���G��
	if (m_nCount <= PLAYER_INVINCIBLE_TIME)
	{
		if (m_nCount % 5 == 0)
		{
			//���G���Ԃ̃J�E���g��i�߂�
			m_nInvincibleCount++;

			if (m_nInvincibleCount % 2 == 0)
			{
				//�������
				for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
				{
					m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 0);
				}
			}
			else
			{
				//�ʏ���
				for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
				{
					m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
			}
		}
	}
	else
	{
		//���G����߂�
		m_bInvincible = false;
		//�J�E���g��߂�
		m_nInvincibleCount = 0;
		//�J�E���g��߂�
		m_nCount = 0;
		//�ʏ��Ԃɖ߂�
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
	}
	//�J�E���g��i�߂�
	m_nCount++;
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CPlayer::Death(void)
{
	if (m_bHit == true)
	{
		m_bHit = false;
	}
	for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
	{
		CScene * pScene = GetScene(4, nCountScene);
		if (pScene != NULL)
		{
			//�I�u�W�F�^�C�v�̎擾
			OBJTYPE objType;
			objType = pScene->GetObjType();
			//�V�[���I�u�W�F�N�g�̈ʒu���擾
			D3DXVECTOR3 Scene_pos;
			Scene_pos = pScene->GetPosition();
			//�����I�u�W�F�^�C�v���e�̏ꍇ
			if (objType == OBJTYPE_BULLET)
			{
				pScene->Uninit();
			}
		}
	}
	//�������
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 0);
	}
	//�����J�E���g�����S���Ԉȉ��̏ꍇ
	if (m_nDeathCount >= PLAYER_DEATH_TIME)
	{
		//���@�������ʒu�ɔz�u
		m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 180, 0.0f);
		//���S��ԉ���
		m_bDeath = false;
		//���G��Ԃɂ���
		m_bInvincible = true;
		//�J�E���g��0�ɖ߂�
		m_nDeathCount = 0;
	}
	//���S���Ԃ�i�߂�
	m_nDeathCount++;
}

//=============================================================================
// �X�R�A�擾�֐�
//=============================================================================
void CPlayer::SetPlayerScpre(int nValue)
{
	m_nScore = nValue;
}

//=============================================================================
// ���O�擾�֐�
//=============================================================================
void CPlayer::SetPlayerName(int nCount,char aName)
{
	m_aPlayerName[nCount] = aName;
}

//=============================================================================
// �Z�[�u�֐�
//=============================================================================
void CPlayer::Save(void)
{
	FILE *pFile;

	pFile = fopen("data/TEXT/PlayerData.txt", "w"); //�t�@�C���̏�������

	if (pFile != NULL)
	{
		//���O���L�^
		fprintf(pFile, "%s\n", &m_aPlayerName);
		//���S�����L�^
		fprintf(pFile, "%d\n", m_nDeath);
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
// ���͏��Z�[�u�֐�
//=============================================================================
void CPlayer::InputSave(void)
{
	FILE *pFile;

	pFile = fopen("data/TEXT/InputData.txt", "w"); //�t�@�C���̏�������

	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < CGame::GetbInputSaveCount(); nCount++)
		{
			//�v���C���[�̓��͏��̋L�^
			fprintf(pFile, "%d", m_aInputData[nCount][0]);
			fprintf(pFile, "%d", m_aInputData[nCount][1]);
			fprintf(pFile, "%d", m_aInputData[nCount][2]);
			fprintf(pFile, "%d", m_aInputData[nCount][3]);
			fprintf(pFile, "%d", m_aInputData[nCount][4]);
			fprintf(pFile, "%d\n", m_aInputData[nCount][5]);
		}

		//�t�@�C�������
		fclose(pFile);
	}
}

//=============================================================================
// ���͏��ǂݍ��݊֐�
//=============================================================================
void CPlayer::InputLoad(void)
{
	FILE *pFile;
	pFile = fopen("data/TEXT/InputData.txt", "r"); //�t�@�C���̓ǂݍ���
	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < 15000; nCount++)
		{
			//�v���C���[�̓��͏��ǂݍ���
			fscanf(pFile, "%s", &m_aInputData[nCount][0]);
		}
		fclose(pFile); //�t�@�C�������
	}
}
