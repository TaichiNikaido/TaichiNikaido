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
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/sound.h"
#include "Base/camera.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "Mode/mode_game.h"
#include "player.h"
#include "enemy_dragon.h"
#include "Weapon/weapon_sword.h"
#include "Weapon/weapon_shield.h"
#include "Polygon3d/shadow.h"
#include "Polygon3d/round_shadow.h"
#include "Polygon2d/game_over_logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PASS ("Data/Script/Player/PlayerModel.txt")		//���f���X�N���v�g�̃p�X
#define SCRIPT_PASS ("Data/Script/Player/PlayerData.txt")		//�v���C���[�f�[�^�̃X�N���v�g�̃p�X
#define MINIMUM_LIFE (0)										//�̗͂̍ŏ��l
#define MINIMUM_ATTACK (0)										//�U���͂̍ŏ��l
#define MINIMUM_ATTACK_COMBO (0)								//�U���R���{���̍ŏ��l
#define MINIMUM_COOL_TIME (0)									//�N�[���^�C��
#define MINIMUM_SPEED (0.0f)									//��������
#define MINIMUM_WALK_SPEED (0.0f)								//�������s���x
#define MINIMUM_DASH_SPEED (0.0f)								//�����_�b�V�����x
#define MINIMUM_ADD_DIRECTION_VALUE (D3DXToRadian(0.75f))		//�����̉��Z�l�̏����l
#define MINIMUM_CAMERA_DISTANCE (0.0f)							//�J�����Ƃ̋���
#define ATTACK1_COOL_TIME (1)									//�U��(1)�̃N�[���^�C��
#define ATTACK2_COOL_TIME (2)									//�U��(2)�̃N�[���^�C��
#define ATTACK3_COOL_TIME (3)									//�U��(3)�̃N�[���^�C��
#define BURNING_MINIMUM_TIME (0)								//�R�Ď��Ԃ̍ŏ��l
#define BURNING_SUB_LIFE (1)									//�R�Ď��̗̑͌��Z��
#define ROUND_SHADOW_SIZE (D3DXVECTOR3(50.0f,50.0f,50.0f))		//�ۉe�̃T�C�Y
#define ROUND_SHADOW_COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))		//�ۉe�̐F

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODEL_DATA CPlayer::m_aPlayerModelData[MAX_PARTS] = {};	//���f�����

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer()
{
	m_DirectionDest = INITIAL_D3DXVECTOR3;				//�ړI�̌���
	m_Move = INITIAL_D3DXVECTOR3;						//�ړ���
	m_nMaxLife = MINIMUM_LIFE;							//�ő�̗�
	m_nLife = MINIMUM_LIFE;								//�̗�
	m_nAttack = MINIMUM_ATTACK;							//�U����
	m_nAttackCombo = MINIMUM_ATTACK_COMBO;				//�U���R���{
	m_nCoolTime = MINIMUM_COOL_TIME;					//�N�[���^�C��
	m_nCoolTimeCount = MINIMUM_COOL_TIME;				//�N�[���^�C���J�E���g
	m_nBurningTime = BURNING_MINIMUM_TIME;				//�R�ă^�C��
	m_nBurningTiming = BURNING_MINIMUM_TIME;			//�R�ă^�C�~���O
	m_nBurningTimeCount = BURNING_MINIMUM_TIME;			//�R�ăJ�E���g
	m_fSpeed = MINIMUM_SPEED;							//����
	m_fWalkSpeed = MINIMUM_WALK_SPEED;					//���s���x
	m_fDashSpeed = MINIMUM_DASH_SPEED;					//�_�b�V�����x
	m_fDirectionValue = MINIMUM_ADD_DIRECTION_VALUE;	//�����̒l
	m_fCameraDistance = MINIMUM_CAMERA_DISTANCE;		//�J�����Ƃ̋���
	m_bWeapon = false;									//������g�p���Ă邩
	m_bBurning = false;									//�R���Ă邩
	m_State = STATE_NONE;								//���
	m_Input = INPUT_NONE;								//���͏��
	m_pRoundShadow = nullptr;							//�ۉe�̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CPlayer::ModelLoad(void)
{
	//�}�e���A���̃|�C���^
	D3DXMATERIAL * pMaterial;
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�p�X�̃|�C���^
	char * pPass = nullptr;
	//�����p�X�̃|�C���^��nullptr�̏ꍇ
	if (pPass == nullptr)
	{
		//�p�X���擾
		pPass = CModel::LoadModelText(MODEL_PASS);
	}
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�����p�X�̃|�C���^��nullptr����Ȃ��ꍇ
		if (pPass != nullptr)
		{
			//���f���ǂݍ���
			D3DXLoadMeshFromX(pPass,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_aPlayerModelData[nCount].pBuffMat,
				NULL,
				&m_aPlayerModelData[nCount].nNumMat,
				&m_aPlayerModelData[nCount].pMesh);
			//�������f���̃}�e���A�����NULL����Ȃ��ꍇ
			if (m_aPlayerModelData[nCount].pBuffMat != NULL)
			{
				//�}�e���A���̃|�C���^���擾
				pMaterial = (D3DXMATERIAL *)m_aPlayerModelData[nCount].pBuffMat->GetBufferPointer();
				//���f���f�[�^������
				for (int nCountMat = 0; nCountMat < (int)m_aPlayerModelData[nCount].nNumMat; nCountMat++)
				{
					//�����t�@�C���l�[����NULL����Ȃ��ꍇ
					if (pMaterial[nCountMat].pTextureFilename != NULL)
					{
						//�e�N�X�`����ǂݍ���
						D3DXCreateTextureFromFile(pDevice, pMaterial[nCountMat].pTextureFilename, &m_aPlayerModelData[nCount].pTexture[nCountMat]);
					}
				}
			}
			//�|�C���^���̂Ă�
			pPass += MAX_TEXT;
		}
	}
	return S_OK;
}

//=============================================================================
// ���f���j���֐�
//=============================================================================
void CPlayer::ModelUnload(void)
{
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���f�[�^�̃��[���h�ϊ��s��NULL�ł͂Ȃ��ꍇ
		if (m_aPlayerModelData[nCount].mtxWorld != NULL)
		{
			//�������f���f�[�^�̃}�e���A�����NULL�ł͂Ȃ��ꍇ
			if (m_aPlayerModelData[nCount].pBuffMat != NULL)
			{
				//���f���f�[�^�̃}�e���A������j��
				m_aPlayerModelData[nCount].pBuffMat->Release();
			}
			//�������f���f�[�^�̃��b�V�����NULL�ł͂Ȃ��ꍇ
			if (m_aPlayerModelData[nCount].pMesh != NULL)
			{
				//���f���f�[�^�̃��b�V������j��
				m_aPlayerModelData[nCount].pMesh->Release();
			}
			//�}�e���A���̍ő吔����
			for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
			{
				//�������f���f�[�^�̃e�N�X�`���̃|�C���^��NULL�ł͂Ȃ��ꍇ
				if (m_aPlayerModelData[nCount].pTexture[nCountTexture] != NULL)
				{
					//���f���f�[�^�̃e�N�X�`���̃|�C���^��j��
					m_aPlayerModelData[nCount].pTexture[nCountTexture]->Release();
				}
			}
		}
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CPlayer * CPlayer::Create()
{
	//�v���C���[�̃|�C���^
	CPlayer * pPlayer = nullptr;
	//�v���C���[�̃|�C���^��nullptr�̏ꍇ
	if (pPlayer == nullptr)
	{
		//�v���C���[�̃������m��
		pPlayer = new CPlayer;
		//�v���C���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pPlayer != nullptr)
		{
			//�v���C���[�̏����������֐��Ăяo��
			pPlayer->Init();
		}
	}
	//�v���C���[�̃|�C���^��Ԃ�
	return pPlayer;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//�f�[�^�ǂݍ��݊֐��Ăяo��
	DataLoad();
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//���f�����̐ݒ�
	SetModelData(m_aPlayerModelData);
	//�L�����N�^�[�̏����������֐��Ăяo��
	CCharacter::Init();
	//�����ۉe�̃|�C���^��nullptr�̏ꍇ
	if (m_pRoundShadow == nullptr)
	{
		//�ۉe�̐���
		m_pRoundShadow = CRoundShadow::Create(D3DXVECTOR3(Position.x,Position.y + 0.5f, Position.z), ROUND_SHADOW_SIZE, ROUND_SHADOW_COLOR);
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPlayer::Uninit(void)
{
	//�L�����N�^�[�̏I�������֐��Ăяo��
	CCharacter::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPlayer::Update(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�L�����N�^�[�̍X�V�����֐��Ăяo��
	CCharacter::Update();
	//������Ԃ����S��Ԃł͂Ȃ��ꍇ
	if (m_State != STATE_DEATH)
	{
		//���͏����֐��Ăяo��
		Input();
	}
	//�ʒu�X�V
	Position += m_Move;
	//�����ۉe�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pRoundShadow != nullptr)
	{
		//�ۉe�Ɉʒu��ݒ肷��
		m_pRoundShadow->SetPosition(D3DXVECTOR3(Position.x, Position.y + 0.5f, Position.z));
	}
	//�ʒu��ݒ肷��
	SetPosition(Position);
	//���[�V���������֐��Ăяo��
	Motion();
	//�����R�Ă����ꍇ
	if (m_bBurning == true)
	{
		//�R�ď����֐��Ăяo��
		Burning();
	}
	//�����̗͂��ŏ��l�ȉ��ɂȂ�����
	if (m_nLife <= MINIMUM_LIFE)
	{
		//������Ԃ����S��Ԃł͂Ȃ��ꍇ
		if (m_State != STATE_DEATH)
		{
			//���S�����֐��Ăяo��
			Death();
		}
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPlayer::Draw(void)
{
	//�L�����N�^�[�̕`�揈���֐��Ăяo��
	CCharacter::Draw();
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
	//���[�V�����̃|�C���^���擾����
	CMotion * pMotion = GetpMotion();
	//�ړ��ʂ�0�ɂ���
	m_Move = INITIAL_D3DXVECTOR3;
	//�����_�b�V���L�[��������Ă�����
	if (pKeyboard->GetKeyboardPress(DIK_LSHIFT) || pJoystick->GetJoystickPress(JS_RB))
	{
		//��Ԃ��_�b�V����Ԃɂ���
		m_State = STATE_DASH;
	}
	else
	{
		//��Ԃ𖳂ɂ���
		m_State = STATE_NONE;
	}
	//��ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_W) || lpDIDevice != NULL &&js.lY == -1000)
	{
		//�����_�b�V����Ԃł͂Ȃ��ꍇ
		if (m_State != STATE_DASH)
		{
			//��Ԃ���s��Ԃɂ���
			m_State = STATE_WALK;
		}
		//���̓L�[������ɂ���
		m_Input = INPUT_UP;
		//�ړ������֐��Ăяo��
		Move();
	}
	//���ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_S) || lpDIDevice != NULL &&js.lY == 1000)
	{
		//�����_�b�V����Ԃł͂Ȃ��ꍇ
		if (m_State != STATE_DASH)
		{
			//��Ԃ���s��Ԃɂ���
			m_State = STATE_WALK;
		}
		//���̓L�[�������ɂ���
		m_Input = INPUT_DOWN;
		//�ړ������֐��Ăяo��
		Move();
	}
	//���ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
	{
		//�����_�b�V����Ԃł͂Ȃ��ꍇ
		if (m_State != STATE_DASH)
		{
			//��Ԃ���s��Ԃɂ���
			m_State = STATE_WALK;
		}
		//���̓L�[�������ɂ���
		m_Input = INPUT_LEFT;
		//�ړ������֐��Ăяo��
		Move();
	}
	//�E�ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
	{
		//�����_�b�V����Ԃł͂Ȃ��ꍇ
		if (m_State != STATE_DASH)
		{
			//��Ԃ���s��Ԃɂ���
			m_State = STATE_WALK;
		}
		//���̓L�[�����E�ɂ���
		m_Input = INPUT_RIGHT;
		//�ړ������֐��Ăяo��
		Move();
	}
	//�U������
	if (pKeyboard->GetKeyboardTrigger(DIK_L) || pJoystick->GetJoystickTrigger(JS_Y))
	{
		//����������g�p���Ă�����
		if (m_bWeapon == true)
		{
			//�U�������֐��Ăяo��
			Attack();
		}
		else
		{
			//������g�p����
			m_bWeapon = true;
		}
	}
	//�[������
	if (pKeyboard->GetKeyboardTrigger(DIK_I) || pJoystick->GetJoystickTrigger(JS_X))
	{
		//����̎g�p���~�߂�
		m_bWeapon = false;
	}
	//�K�[�h����
	if (pKeyboard->GetKeyboardPress(DIK_G) || pJoystick->GetJoystickPress(JS_RT))
	{
		//�K�[�h�����֐��Ăяo��
		Guard();
	}
	else
	{
		//��Ԃ𖳂ɂ���
		STATE_NONE;
	}
	if (pKeyboard->GetKeyboardTrigger(DIK_O))
	{
		m_nLife = 0;
	}
	if (pKeyboard->GetKeyboardTrigger(DIK_L))
	{
		m_bBurning = true;
	}
}

//=============================================================================
// �ړ������֐�
//=============================================================================
void CPlayer::Move(void)
{
	//��]���擾
	D3DXVECTOR3 Rotation = GetRotation();
	switch (m_State)
	{
	case STATE_WALK:
		//���x����s���x�ɂ���
		m_fSpeed = m_fWalkSpeed;
		break;
	case STATE_DASH:
		//���x���_�b�V�����x�ɂ���
		m_fSpeed = m_fDashSpeed;
		break;
	default:
		break;
	}
	//�J�����̎擾
	CCamera * pCamera = CManager::GetGameMode()->GetCamera();
	//�����J�����̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (pCamera != nullptr)
	{
		//�J�����̉�]���擾
		D3DXVECTOR3 CameraRotation = pCamera->GetRotation();
		switch (m_Input)
		{
			//�������͏�񂪏�̏ꍇ
		case INPUT_UP:
			m_Move.x = sinf(-(CameraRotation.y + D3DXToRadian(90.0f))) * m_fSpeed;
			m_Move.z = cosf(-(CameraRotation.y + D3DXToRadian(90.0f))) * m_fSpeed;
			break;
			//�������͏�񂪉��̏ꍇ
		case INPUT_DOWN:
			m_Move.x = sinf(-(CameraRotation.y + D3DXToRadian(90.0f))) * -m_fSpeed;
			m_Move.z = cosf(-(CameraRotation.y + D3DXToRadian(90.0f))) * -m_fSpeed;
			break;
			//�������͏�񂪍��̏ꍇ
		case INPUT_LEFT:
			m_Move.x = sinf(-(CameraRotation.y + D3DXToRadian(180.0f))) * m_fSpeed;
			m_Move.z = cosf(-(CameraRotation.y + D3DXToRadian(180.0f))) * m_fSpeed;
			break;
			//�������͏�񂪉E�̏ꍇ
		case INPUT_RIGHT:
			m_Move.x = sinf(-(CameraRotation.y + D3DXToRadian(0.0f))) * m_fSpeed;
			m_Move.z = cosf(-(CameraRotation.y + D3DXToRadian(0.0f))) * m_fSpeed;
			break;
		default:
			break;
		}
		//�ړI�̌�����ݒ肷��
		m_DirectionDest = D3DXVECTOR3(D3DXToRadian(0.0f), atan2f(m_Move.x, m_Move.z) + D3DXToRadian(180.0f), D3DXToRadian(0.0f));
		while (m_DirectionDest.y - Rotation.y < D3DXToRadian(-180))
		{
			m_DirectionDest.y += D3DXToRadian(360);
		}
		while (m_DirectionDest.y - Rotation.y > D3DXToRadian(180))
		{
			m_DirectionDest.y -= D3DXToRadian(360);
		}
		//�v���C���[�̌������X�V����
		Rotation += (m_DirectionDest - Rotation) * 0.1f;
		//��]��ݒ�
		SetRotation(Rotation);
	}
}

//=============================================================================
// �U�������֐�
//=============================================================================
void CPlayer::Attack(void)
{
	//�����U����Ԃ�false�̏ꍇ
	if (m_State != STATE_ATTACK)
	{
		//�����U���R���{���ő吔��艺�̏ꍇ
		if (m_nAttackCombo < ATTACK_3)
		{
			//�U���R���{�����Z����
			m_nAttackCombo++;
			//��Ԃ��U����Ԃɂ���
			m_State = STATE_ATTACK;
		}
		else
		{
			//�U���R���{������������
			m_nAttackCombo = ATTACK_NONE;
		}
	}
	//�e�U���R���{�̏���
	switch (m_nAttackCombo)
	{
	case ATTACK_1:
		//�N�[���^�C���̐ݒ�
		m_nCoolTime = ATTACK1_COOL_TIME;
		break;
	case ATTACK_2:
		//�N�[���^�C���̐ݒ�
		m_nCoolTime = ATTACK2_COOL_TIME;
		break;
	case ATTACK_3:
		//�N�[���^�C���̐ݒ�
		m_nCoolTime = ATTACK3_COOL_TIME;
		break;
	default:
		break;
	}
	//�N�[���^�C�������Z����
	m_nCoolTimeCount++;
	//�������݂̃N�[���^�C�����w��̎��Ԃ��z������
	if (m_nCoolTimeCount >= m_nCoolTime)
	{
	}
}

//=============================================================================
// �K�[�h�����֐�
//=============================================================================
void CPlayer::Guard(void)
{
}

//=============================================================================
// �R�ď����֐�
//=============================================================================
void CPlayer::Burning(void)
{
	//�̗͂���莞�Ԃ��ƂɌ���������
	if (m_nBurningTimeCount <= m_nBurningTime)
	{
		//�R�ăJ�E���g�����Z����
		m_nBurningTimeCount++;
		//�����R�ă^�C�~���O�ɂȂ����ꍇ
		if (m_nBurningTimeCount % m_nBurningTiming == BURNING_MINIMUM_TIME)
		{
			//�̗͂����Z����
			m_nLife -= BURNING_SUB_LIFE;
		}
	}
	else
	{
		//�R�ď�Ԃ��~�߂�
		m_bBurning = false;
		//�R�ăJ�E���g������������
		m_nBurningTimeCount = BURNING_MINIMUM_TIME;
	}
}

//=============================================================================
// �q�b�g�����֐�
//=============================================================================
void CPlayer::Hit(void)
{
}

//=============================================================================
// �̗͉��Z�����֐�
//=============================================================================
void CPlayer::AddLife(int nValue)
{
	//�����̗͂��ő�l�ȉ��̏ꍇ
	if (m_nLife < m_nMaxLife)
	{
		//�̗͂����Z����
		m_nLife += nValue;
		//�����̗͂��ő�l���z�����ꍇ
		if (m_nLife > m_nMaxLife)
		{
			//�̗͂��ő�l�ɂ���
			m_nLife = m_nMaxLife;
		}
	}
}

//=============================================================================
// �̗͌��Z�����֐�
//=============================================================================
void CPlayer::SubLife(int nValue)
{
	//�����̗͂�0��葽���̏ꍇ
	if (m_nLife > MINIMUM_LIFE)
	{
		//�̗͂����Z����
		m_nLife -= nValue;
		//�����̗͂��ő�l���z�����ꍇ
		if (m_nLife <= MINIMUM_LIFE)
		{
			//�̗͂�0�ɂ���
			m_nLife = MINIMUM_LIFE;
		}
	}
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CPlayer::Death(void)
{
	//��Ԃ����S��Ԃɂ���
	m_State = STATE_DEATH;
	//�Q�[���I�[�o�[���S�̐���
	CGameOverLogo::Create();
}

//=============================================================================
// �Փ˔��菈���֐�
//=============================================================================
void CPlayer::Collision(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�ߋ��̈ʒu���擾����
	D3DXVECTOR3 PositionOld = GetPositionOld();
	//�T�C�Y���擾����
	D3DXVECTOR3 CollisionSize = GetCollisionSize();
	//�Փ˔���p�̔��̐ݒ�
	D3DXVECTOR3 PlayerBoxMax = D3DXVECTOR3(CollisionSize.x / 2, CollisionSize.y / 2, CollisionSize.z / 2) + Position;
	D3DXVECTOR3 PlayerBoxMin = D3DXVECTOR3(-CollisionSize.x / 2, -CollisionSize.y / 2, -CollisionSize.z / 2) + Position;
	//�h���S���̎擾
	CDragon * pDragon = CManager::GetGameMode()->GetDragon();
	//�����h���S���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (pDragon != nullptr)
	{
		//�h���S���̈ʒu���擾
		D3DXVECTOR3 DragonPosition = pDragon->GetPosition();
		//�h���S���̏Փ˔���p�T�C�Y�̎擾
		D3DXVECTOR3 DragonCollisionSize = pDragon->GetCollisionSize();
		//�Փ˔���p�̔��̐ݒ�
		D3DXVECTOR3 DragonBoxMax = D3DXVECTOR3(DragonCollisionSize.x / 2, DragonCollisionSize.y / 2, DragonCollisionSize.z / 2) + DragonPosition;
		D3DXVECTOR3 DragonBoxMin = D3DXVECTOR3(-DragonCollisionSize.x / 2, -DragonCollisionSize.y / 2, -DragonCollisionSize.z / 2) + DragonPosition;
	}
}

//=============================================================================
// ���[�V���������֐�
//=============================================================================
void CPlayer::Motion(void)
{
	//���[�V�����̃|�C���^���擾����
	CMotion * pMotion = GetpMotion();
	//�������[�V�����̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (pMotion != nullptr)
	{
		switch (m_State)
		{
		case STATE_NONE:
			//����������g�p���Ă��Ȃ��ꍇ
			if (m_bWeapon == false)
			{
				//�A�C�h�����[�V������ݒ肷��
				pMotion->SetMotion(MOTION_IDLE);
			}
			else
			{
				//���폊���A�C�h�����[�V�����̍Đ�
				pMotion->SetMotion(MOTION_IDLE_WEAPON);
			}
			break;
		case STATE_WALK:
			//����������g�p���Ă��Ȃ��ꍇ
			if (m_bWeapon == false)
			{
				//���s���[�V������ݒ肷��
				pMotion->SetMotion(MOTION_WALK);
			}
			else
			{
				//���폊�����s���[�V������ݒ肷��
				pMotion->SetMotion(MOTION_WALK_WEAPON);
			}
			break;
		case STATE_DASH:
			//����������g�p���Ă��Ȃ��ꍇ
			if (m_bWeapon == false)
			{

			}
			else
			{

			}
			break;
		case STATE_DEATH:
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// �f�[�^�ǂݍ��݊֐�
//=============================================================================
void CPlayer::DataLoad(void)
{
	D3DXVECTOR3 Position = INITIAL_D3DXVECTOR3;			//�ʒu
	D3DXVECTOR3 Size = INITIAL_D3DXVECTOR3;				//�T�C�Y
	D3DXVECTOR3 CollisionSize = INITIAL_D3DXVECTOR3;	//�Փ˔���p�T�C�Y
	D3DXVECTOR3 Rotation = INITIAL_D3DXVECTOR3;			//��]
	char aReadText[MAX_TEXT];							//�ǂݍ��񂾃e�L�X�g
	char aCurrentText[MAX_TEXT];						//���݂̃e�L�X�g
	char aUnnecessaryText[MAX_TEXT];					//�s�K�v�ȃe�L�X�g
	memset(aReadText, NULL, sizeof(aReadText));
	memset(aCurrentText, NULL, sizeof(aCurrentText));
	memset(aUnnecessaryText, NULL, sizeof(aUnnecessaryText));
	//�t�@�C���̃|�C���^
	FILE *pFile = nullptr;
	//�����t�@�C���̃|�C���^��nullptr�̏ꍇ
	if (pFile == nullptr)
	{
		//�t�@�C���̓ǂݍ���
		pFile = fopen(SCRIPT_PASS, "r");
	}
	//�t�@�C�����J�����Ƃ��ł�����
	if (pFile != nullptr)
	{
		//SCRIPT�̕�����������
		while (strcmp(aCurrentText, "SCRIPT") != 0)
		{
			//�ǂݍ��񂾃e�L�X�g���i�[����
			fgets(aReadText, sizeof(aReadText), pFile);
			//�ǂݍ��񂾃e�L�X�g�����݂̃e�L�X�g�Ɋi�[
			sscanf(aReadText, "%s", &aCurrentText);
		}
		//���݂̃e�L�X�g��SCRIPT��������
		if (strcmp(aCurrentText, "SCRIPT") == 0)
		{
			//END_SCRIPT�̕�����������܂œǂ�
			while (strcmp(aCurrentText, "END_SCRIPT") != 0)
			{
				//�ǂݍ��񂾃e�L�X�g���i�[����
				fgets(aReadText, sizeof(aReadText), pFile);
				//�ǂݍ��񂾃e�L�X�g�����݂̃e�L�X�g�Ɋi�[
				sscanf(aReadText, "%s", &aCurrentText);
				//���݂̃e�L�X�g��PARAMETER_SET��������
				if (strcmp(aCurrentText, "PARAMETER_SET") == 0)
				{
					//END_PARAMETER_SET�̕�����������܂œǂ�
					while (strcmp(aCurrentText, "END_PARAMETER_SET") != 0)
					{
						//�ǂݍ��񂾃e�L�X�g���i�[����
						fgets(aReadText, sizeof(aReadText), pFile);
						//�ǂݍ��񂾃e�L�X�g�����݂̃e�L�X�g�Ɋi�[
						sscanf(aReadText, "%s", &aCurrentText);
						//���݂̃e�L�X�g��Position��������
						if (strcmp(aCurrentText, "Position") == 0)
						{
							//�ʒu���ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Position.x, &Position.y, &Position.z);
							//�ʒu��ݒ肷��
							SetPosition(Position);
						}
						//���݂̃e�L�X�g��Size��������
						if (strcmp(aCurrentText, "Size") == 0)
						{
							//�T�C�Y���ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Size.x, &Size.y, &Size.z);
							//�T�C�Y��ݒ肷��
							SetSize(Size);
						}
						//���݂̃e�L�X�g��CollisionSize��������
						if (strcmp(aCurrentText, "CollisionSize") == 0)
						{
							//�Փ˔���p�T�C�Y�̎擾
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &CollisionSize.x, &CollisionSize.y, &CollisionSize.z);
							//�Փ˔���p�T�C�Y�̐ݒ�
							SetCollisionSize(CollisionSize);
						}
						//���݂̃e�L�X�g��Rotation��������
						if (strcmp(aCurrentText, "Rotation") == 0)
						{
							//��]���̓ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Rotation.x, &Rotation.y, &Rotation.z);
							//��]�̐ݒ�
							SetRotation(Rotation);
						}
						//���݂̃e�L�X�g��Move��������
						if (strcmp(aCurrentText, "Move") == 0)
						{
							//�T�C�Y�̐ݒ�
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Move.x, &m_Move.y, &m_Move.z);
						}
						//���݂̃e�L�X�g��Life��������
						if (strcmp(aCurrentText, "Life") == 0)
						{
							//�ő�̗͂̐ݒ�
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nMaxLife);
							//�̗͂̐ݒ�
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nLife);
						}
						//���݂̃e�L�X�g��BurningTime��������
						if (strcmp(aCurrentText, "BurningTime") == 0)
						{
							//�R�Ď��Ԃ̐ݒ�
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nBurningTime);
						}
						//���݂̃e�L�X�g��BurningTiming��������
						if (strcmp(aCurrentText, "BurningTiming") == 0)
						{
							//�R�ă^�C�~���O�̐ݒ�
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nBurningTiming);
						}
						//���݂̃e�L�X�g��WalkSpeed��������
						if (strcmp(aCurrentText, "WalkSpeed") == 0)
						{
							//���s���x�̐ݒ�̐ݒ�
							sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fWalkSpeed);
						}
						//���݂̃e�L�X�g��DashSpeed��������
						if (strcmp(aCurrentText, "DashSpeed") == 0)
						{
							//�_�b�V�����x�̐ݒ�
							sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fDashSpeed);
						}
						//���݂̃e�L�X�g��CameraDistance��������
						if (strcmp(aCurrentText, "CameraDistance") == 0)
						{
							//�J�����Ƃ̋����̐ݒ�
							sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fCameraDistance);
						}
					}
				}
			}
		}
		//�t�@�C�������
		fclose(pFile);
	}
	//���f���̃X�N���v�g�p�X��ݒ�
	SetModelScriptPass(MODEL_PASS);
}