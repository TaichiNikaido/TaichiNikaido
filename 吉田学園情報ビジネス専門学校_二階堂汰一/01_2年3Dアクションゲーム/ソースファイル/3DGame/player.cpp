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
#include "mode_game.h"
#include "renderer.h"
#include "sound.h"
#include "keyboard.h"
#include "joystick.h"
#include "player.h"
#include "camera.h"
#include "weapon_sword.h"
#include "weapon_shield.h"
#include "enemy_dragon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PASS ("Data/Script/Player/PlayerModel.txt")	//���f���X�N���v�g�̃p�X
#define SCRIPT_PASS ("Data/Script/Player/PlayerData.txt")	//�v���C���[�f�[�^�̃X�N���v�g�̃p�X
#define INITIAL_MOVE (D3DXVECTOR3(0.0f,0.0f,0.0f))			//�����ړ���
#define MINIMUM_LIFE (0)									//�̗͂̍ŏ��l
#define MINIMUM_ATTACK (0)									//�U���͂̍ŏ��l
#define MINIMUM_ATTACK_COMBO (0)							//�U���R���{���̍ŏ��l
#define MINIMUM_COOL_TIME (0)								//�N�[���^�C��
#define MINIMUM_SPEED (0.0f)								//��������
#define MINIMUM_WALK_SPEED (0.0f)							//�������s���x
#define MINIMUM_DASH_SPEED (0.0f)							//�����_�b�V�����x
#define MINIMUM_ADD_DIRECTION_VALUE (D3DXToRadian(0.75f))	//�����̉��Z�l�̏����l
#define MINIMUM_CAMERA_DISTANCE (0.0f)						//�J�����Ƃ̋���
#define ATTACK1_COOL_TIME (1)								//�U��(1)�̃N�[���^�C��
#define ATTACK2_COOL_TIME (2)								//�U��(2)�̃N�[���^�C��
#define ATTACK3_COOL_TIME (3)								//�U��(3)�̃N�[���^�C��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODEL_DATA CPlayer::m_aPlayerModelData[MAX_PARTS] = {};	//���f�����

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer()
{
	m_PositionOld = INITIAL_D3DXVECTOR3;				//�O�̈ʒu
	m_CollisionSize = INITIAL_D3DXVECTOR3;				//�����蔻��p�T�C�Y
	m_DirectionDest = INITIAL_D3DXVECTOR3;				//�ړI�̌���
	m_Move = INITIAL_MOVE;								//�ړ���
	m_nLife = MINIMUM_LIFE;								//�̗�
	m_nAttack = MINIMUM_ATTACK;							//�U����
	m_nAttackCombo = MINIMUM_ATTACK_COMBO;				//�U���R���{
	m_nCoolTime = MINIMUM_COOL_TIME;					//�N�[���^�C��
	m_nCoolTimeCount = MINIMUM_COOL_TIME;				//�N�[���^�C���J�E���g
	m_fSpeed = MINIMUM_SPEED;							//����
	m_fWalkSpeed = MINIMUM_WALK_SPEED;					//���s���x
	m_fDashSpeed = MINIMUM_DASH_SPEED;					//�_�b�V�����x
	m_fDirectionValue = MINIMUM_ADD_DIRECTION_VALUE;	//�����̒l
	m_fCameraDistance = MINIMUM_CAMERA_DISTANCE;		//�J�����Ƃ̋���
	m_bDash = false;									//�_�b�V�����Ă邩
	m_bWeapon = false;									//������g�p���Ă邩
	m_bAttack = false;									//�U�����Ă邩
	m_State = STATE_NONE;								//���
	m_Input = INPUT_NONE;								//���͏��
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
	char * pPass = NULL;
	//�����p�X�̃|�C���^��NULL�̏ꍇ
	if (pPass == NULL)
	{
		//�p�X���擾
		pPass = CModel::LoadModelText(MODEL_PASS);
	}
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�����p�X�̃|�C���^��NULL����Ȃ��ꍇ
		if (pPass != NULL)
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
	CPlayer * pPlayer = NULL;
	//�v���C���[�̃|�C���^��NULL�̏ꍇ
	if (pPlayer == NULL)
	{
		//�v���C���[�̃������m��
		pPlayer = new CPlayer;
		//�v���C���[�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pPlayer != NULL)
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
	//UI�搶�����֐��Ăяo��
	UICreate();
	//���f�����̐ݒ�
	SetModelData(m_aPlayerModelData);
	//�L�����N�^�[�̏����������֐��Ăяo��
	CCharacter::Init();
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
	//���[�V�����̃|�C���^���擾����
	CMotion * pMotion = GetpMotion();
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�L�����N�^�[�̍X�V�����֐��Ăяo��
	CCharacter::Update();
	//�ߋ��̈ʒu��ۑ�����
	m_PositionOld = GetPosition();
	//�����ړ��ʂ������l�̏ꍇ
	if (m_Move == INITIAL_MOVE)
	{
		//�������[�V�����̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pMotion != NULL)
		{
			//���[�V������ݒ肷��
			pMotion->SetMotion(MOTION_IDLE);
		}
	}
	//���͏����֐��Ăяo��
	Input();
	//�ʒu�X�V
	Position += m_Move;
	//�ʒu��ݒ肷��
	SetPosition(Position);
	//�����̗͂��ŏ��l�ȉ��ɂȂ�����
	if (m_nLife <= MINIMUM_LIFE)
	{
		//���S�����֐��Ăяo��
		Death();
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
	//�v���C���[���ړ����Ă��Ȃ��Ƃ�
	m_Move = INITIAL_MOVE;
	//�����_�b�V���L�[��������Ă�����
	if (pKeyboard->GetKeyboardPress(DIK_LSHIFT) || pJoystick->GetJoystickPress(JS_RB))
	{
		//�_�b�V������
		m_bDash = true;
	}
	else
	{
		//�_�b�V�����~�߂�
		m_bDash = false;
	}
	//��ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_W) || lpDIDevice != NULL &&js.lY == -1000)
	{
		//���̓L�[������ɂ���
		m_Input = INPUT_UP;
		//�ړ������֐��Ăяo��
		Move();
	}
	//���ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_S) || lpDIDevice != NULL &&js.lY == 1000)
	{
		//���̓L�[�������ɂ���
		m_Input = INPUT_DOWN;
		//�ړ������֐��Ăяo��
		Move();
	}
	//���ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
	{
		//���̓L�[�������ɂ���
		m_Input = INPUT_LEFT;
		//�ړ������֐��Ăяo��
		Move();
	}
	//�E�ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
	{
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
}

//=============================================================================
// �ړ������֐�
//=============================================================================
void CPlayer::Move(void)
{
	//���[�V�����̃|�C���^���擾����
	CMotion * pMotion = GetpMotion();
	//��]���擾
	D3DXVECTOR3 Rotation = GetRotation();
	//�����_�b�V�����Ă�����
	if (m_bDash == true)
	{
		//���x���_�b�V�����x�ɂ���
		m_fSpeed = m_fDashSpeed;
		//�������[�V�����̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pMotion != NULL)
		{
			//���[�V������ݒ肷��
			pMotion->SetMotion(MOTION_DASH);
		}
	}
	else
	{
		//���x����s���x�ɂ���
		m_fSpeed = m_fWalkSpeed;
		//�������[�V�����̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pMotion != NULL)
		{
			//���[�V������ݒ肷��
			pMotion->SetMotion(MOTION_WALK);
		}
	}
	//�J�����̎擾
	CCamera * pCamera = CManager::GetGameMode()->GetCamera();
	//�����J�����̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (pCamera != NULL)
	{
		//�J�����̉�]���擾
		D3DXVECTOR3 CameraRotation = pCamera->GetRotation();
		//�������S��Ԃ���Ȃ��Ƃ�
		if (m_State != STATE_DEATH)
		{
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
}

//=============================================================================
// �U�������֐�
//=============================================================================
void CPlayer::Attack(void)
{
	//�����U����Ԃ�false�̏ꍇ
	if (m_bAttack == false)
	{
		//�����U���R���{���ő吔��艺�̏ꍇ
		if (m_nAttackCombo < ATTACK_3)
		{
			//�U���R���{�����Z����
			m_nAttackCombo++;
			//�U����Ԃ�true�ɂ���
			m_bAttack = true;
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
		//�U����Ԃ�false�ɂ���
		m_bAttack = false;
	}
}

//=============================================================================
// �q�b�g�����֐�
//=============================================================================
void CPlayer::Hit(void)
{
	//�̗͌��Z�����֐��Ăяo��
	SubLife();
}

//=============================================================================
// �̗͌��Z�����֐�
//=============================================================================
void CPlayer::SubLife(void)
{
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CPlayer::Death(void)
{
}

//=============================================================================
// �Փ˔��菈���֐�
//=============================================================================
void CPlayer::Collision(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�h���S���̎擾
	CDragon * pDragon = CManager::GetGameMode()->GetDragon();
	//�����h���S���̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (pDragon != NULL)
	{
		//�h���S���̈ʒu���擾
		D3DXVECTOR3 DragonPosition = pDragon->GetPosition();
		//�h���S���̏Փ˔���p�T�C�Y�̎擾
		D3DXVECTOR3 DragonCollisionSize = pDragon->GetCollisionSize();
	}
}

//=============================================================================
// �f�[�^�ǂݍ��݊֐�
//=============================================================================
void CPlayer::DataLoad(void)
{
	D3DXVECTOR3 Position = INITIAL_D3DXVECTOR3;		//�ʒu
	D3DXVECTOR3 Size = INITIAL_D3DXVECTOR3;			//�T�C�Y
	D3DXVECTOR3 Rotation = INITIAL_D3DXVECTOR3;		//��]
	char aReadText[MAX_TEXT];						//�ǂݍ��񂾃e�L�X�g
	char aCurrentText[MAX_TEXT];					//���݂̃e�L�X�g
	char aUnnecessaryText[MAX_TEXT];				//�s�K�v�ȃe�L�X�g
	memset(aReadText, NULL, sizeof(aReadText));
	memset(aCurrentText, NULL, sizeof(aCurrentText));
	memset(aUnnecessaryText, NULL, sizeof(aUnnecessaryText));
	//�t�@�C���̃|�C���^
	FILE *pFile = NULL;
	//�����t�@�C���̃|�C���^��NULL�̏ꍇ
	if (pFile == NULL)
	{
		//�t�@�C���̓ǂݍ���
		pFile = fopen(SCRIPT_PASS, "r");
	}
	//�t�@�C�����J�����Ƃ��ł�����
	if (pFile != NULL)
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
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_CollisionSize.x, &m_CollisionSize.y, &m_CollisionSize.z);
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
							//�̗͂̐ݒ�
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nLife);
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

//=============================================================================
// UI���������֐�
//=============================================================================
void CPlayer::UICreate(void)
{
}
