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
#define MODEL_PASS ("Data/Script/Player/Model.txt")															//���f���X�N���v�g�̃p�X
#define SCRIPT_PASS ("Data/Script/Player/Data.txt")															//�v���C���[�f�[�^�̃X�N���v�g�̃p�X
#define INITIAL_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))														//�����ʒu
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))															//�����T�C�Y
#define INITIAL_COLLISIION_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))												//���������蔻��p�T�C�Y
#define INITIAL_ROTATION (D3DXVECTOR3(D3DXToRadian(0.0f),D3DXToRadian(0.0f),D3DXToRadian(0.0f)))			//������]
#define INITIAL_DIRECTION_DEST (D3DXVECTOR3(D3DXToRadian(0.0f),D3DXToRadian(0.0f),D3DXToRadian(0.0f)))		//�ڕW�̌����̏����l
#define INITIAL_MOVE (D3DXVECTOR3(0.0f,0.0f,0.0f))															//�����ړ���
#define INITIAL_LIFE (0)																					//�����̗�
#define MINIMUM_LIFE (0)																					//�̗͂̍ŏ��l
#define INITIAL_ATTACK (0)																					//�����U����
#define INITIAL_COOL_TIME (0)																				//�N�[���^�C��
#define INITIAL_SPEED (0.0f)																				//��������
#define INITIAL_WALK_SPEED (0.0f)																			//�������s���x
#define INITIAL_DASH_SPEED (0.0f)																			//�����_�b�V�����x
#define INITIAL_ADD_DIRECTION_VALUE (D3DXToRadian(0.75f))													//�����̉��Z�l�̏����l
#define INITIAL_CAMERA_DISTANCE (0.0f)																		//�J�����Ƃ̋���

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODEL_DATA CPlayer::m_ModelData[MAX_PARTS] = {};	//���f���f�[�^
D3DXMATERIAL * CPlayer::m_pMaterial = NULL;					//�}�e���A��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer()
{
	m_Position = INITIAL_POSITION;									//�ʒu
	m_PositionOld = INITIAL_POSITION;								//�O�̈ʒu
	m_Size = INITIAL_SIZE;											//�T�C�Y
	m_CollisionSize = INITIAL_COLLISIION_SIZE;						//�����蔻��p�T�C�Y
	m_Rotation = INITIAL_ROTATION;									//��]
	m_DirectionDest = INITIAL_DIRECTION_DEST;						//�ړI�̌���
	m_Move = INITIAL_MOVE;											//�ړ���
	m_nLife = INITIAL_LIFE;											//�̗�
	memset(m_nAttack, INITIAL_ATTACK, sizeof(m_nAttack));			//�U����
	memset(m_nCoolTime, INITIAL_COOL_TIME, sizeof(m_nCoolTime));	//�N�[���^�C��
	m_nCoolTimeCount = INITIAL_COOL_TIME;							//�N�[���^�C���J�E���g
	m_fSpeed = INITIAL_SPEED;										//����
	m_fWalkSpeed = INITIAL_WALK_SPEED;								//���s���x
	m_fDashSpeed = INITIAL_DASH_SPEED;								//�_�b�V�����x
	m_fDirectionValue = INITIAL_ADD_DIRECTION_VALUE;				//�����̒l
	m_fCameraDistance = INITIAL_CAMERA_DISTANCE;					//�J�����Ƃ̋���
	m_bDash = false;												//�_�b�V�����Ă邩
	m_State = STATE_NONE;											//���
	m_Input = INPUT_NONE;											//���͏��
	m_Attack = ATTACK_NONE;											//�U�����
	m_Direction = DIRECTION_FRONT;									//����
	memset(m_pModel, NULL, sizeof(m_pModel));						//���f���̃|�C���^
	m_pMotion = NULL;												//���[�V�����̃|�C���^
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
				&m_ModelData[nCount].pBuffMat,
				NULL,
				&m_ModelData[nCount].nNumMat,
				&m_ModelData[nCount].pMesh);
			//�������f���̃}�e���A�����NULL����Ȃ��ꍇ
 			if (m_ModelData[nCount].pBuffMat != NULL)
			{
				//�}�e���A���̃|�C���^���擾
				m_pMaterial = (D3DXMATERIAL *)m_ModelData[nCount].pBuffMat->GetBufferPointer();
				//���f���f�[�^������
				for (int nCountMat = 0; nCountMat < (int)m_ModelData[nCount].nNumMat; nCountMat++)
				{
					//�����t�@�C���l�[����NULL����Ȃ��ꍇ
					if (m_pMaterial[nCountMat].pTextureFilename != NULL)
					{
						//�e�N�X�`����ǂݍ���
						D3DXCreateTextureFromFile(pDevice, m_pMaterial[nCountMat].pTextureFilename, &m_ModelData[nCount].pTexture[nCountMat]);
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
		//�������f���f�[�^�̃��[���h�ϊ��s��NULL����ȏꍇ
		if (m_ModelData[nCount].mtxWorld != NULL)
		{
			//�������f���f�[�^�̃}�e���A�����NULL����ȏꍇ
			if (m_ModelData[nCount].pBuffMat != NULL)
			{
				//���f���f�[�^�̃}�e���A������j��
				m_ModelData[nCount].pBuffMat->Release();
			}
			//�������f���f�[�^�̃��b�V�����NULL����ȏꍇ
			if (m_ModelData[nCount].pMesh != NULL)
			{
				//���f���f�[�^�̃��b�V������j��
				m_ModelData[nCount].pMesh->Release();
			}
			//�}�e���A���̍ő吔����
			for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
			{
				//�������f���f�[�^�̃e�N�X�`���̃|�C���^��NULL����ȏꍇ
				if (m_ModelData[nCount].pTexture[nCountTexture] != NULL)
				{
					//���f���f�[�^�̃e�N�X�`���̃|�C���^��j��
					m_ModelData[nCount].pTexture[nCountTexture]->Release();
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
	//���[�V���������֐��Ăяo��
	Motion();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPlayer::Uninit(void)
{
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���̃|�C���^��NULL����Ȃ��ꍇ
		if (m_pModel[nCount] != NULL)
		{
			//���f���̏I�������֐��Ăяo��
			m_pModel[nCount]->Uninit();
		}
	}
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPlayer::Update(void)
{
	//�ߋ��̈ʒu��ۑ�����
	m_PositionOld = m_Position;
	//�������[�V�����̃|�C���^��NULL�̏ꍇ
	if (m_pMotion != NULL)
	{
		//�X�V�����֐��Ăяo��
		m_pMotion->Update();
	}
	//�����ړ��ʂ������l�̏ꍇ
	if (m_Move == INITIAL_MOVE)
	{
		//���[�V������ݒ肷��
		m_pMotion->SetMotion(CMotion::MOTION_PLAYER_IDLE);
	}
	//���͏����֐��Ăяo��
	Input();
	//�����ύX�����֐�
	Direction();
	//�ʒu�X�V
	m_Position += m_Move;
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���̃|�C���^��NULL����Ȃ��ꍇ	
		if (m_pModel[nCount] != NULL)
		{
			//���f���̍X�V�����֐��Ăяo��
			m_pModel[nCount]->Update();
			// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
			m_pModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), m_Size);
		}
	}
	// ���W�A��]�A�T�C�Y�̃Z�b�g
	m_pModel[0]->SetModel(m_pMotion->GetPosition(0) + m_Position, m_pMotion->GetRotation(0) + m_Rotation, m_Size);
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
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���̃|�C���^��NULL����Ȃ��ꍇ
		if (m_pModel[nCount] != NULL)
		{
			//���f���̕`�揈���֐��Ăяo��
			m_pModel[nCount]->Draw();
		}
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
		//������O���ɂ���
		m_Direction = DIRECTION_FRONT;
		//�ړ������֐��Ăяo��
		Move();
	}
	//���ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_S) || lpDIDevice != NULL &&js.lY == 1000)
	{
		//���̓L�[�������ɂ���
		m_Input = INPUT_DOWN;
		//����������ɂ���
		m_Direction = DIRECTION_BACK;
		//�ړ������֐��Ăяo��
		Move();
	}
	//���ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
	{
		//���̓L�[�������ɂ���
		m_Input = INPUT_LEFT;
		//���������ɂ���
		m_Direction = DIRECTION_LEFT;
		//�ړ������֐��Ăяo��
		Move();
	}
	//�E�ړ�����
	if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
	{
		//���̓L�[�����E�ɂ���
		m_Input = INPUT_RIGHT;
		//�������E�ɂ���
		m_Direction = DIRECTION_RIGHT;
		//�ړ������֐��Ăяo��
		Move();
	}
}

//=============================================================================
// �ړ������֐�
//=============================================================================
void CPlayer::Move(void)
{
	//�����_�b�V�����Ă�����
	if (m_bDash == true)
	{
		//���x���_�b�V�����x�ɂ���
		m_fSpeed = m_fDashSpeed;
		//���[�V������ݒ肷��
		m_pMotion->SetMotion(CMotion::MOTION_PLAYER_DASH);
	}
	else
	{
		//���x����s���x�ɂ���
		m_fSpeed = m_fWalkSpeed;
		//���[�V������ݒ肷��
		m_pMotion->SetMotion(CMotion::MOTION_PLAYER_WALK);
	}
	//�J�����̎擾
	CCamera * pCamera = CGameMode::GetCamera();
	//�����J�����̃|�C���^��NULL����Ȃ��ꍇ
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
		}
	}
}

//=============================================================================
// �����ύX�����֐�
//=============================================================================
void CPlayer::Direction(void)
{
	//�e�����̏���
	switch (m_Direction)
	{
	case DIRECTION_FRONT:
		m_DirectionDest = D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f));
		break;
	case DIRECTION_BACK:
		m_DirectionDest = D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(180.0f), D3DXToRadian(0.0f));
		break;
	case DIRECTION_LEFT:
		m_DirectionDest = D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(-90.0f), D3DXToRadian(0.0f));
		break;
	case DIRECTION_RIGHT:
		m_DirectionDest = D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(90.0f), D3DXToRadian(0.0f));
		break;
	}
	//�v���C���[�̌������X�V����
	m_Rotation += (m_DirectionDest - m_Rotation) * 0.1f;
}

//=============================================================================
// �U�������֐�
//=============================================================================
void CPlayer::Attack(void)
{
	switch (m_Attack)
	{
	case ATTACK_1:
		break;
	case ATTACK_2:
		break;
	case ATTACK_3:
		break;
	default:
		break;
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
	//�h���S���̎擾
	CDragon * pDragon = CGameMode::GetDragon();
	//�����h���S���̃|�C���^��NULL����Ȃ��ꍇ
	if (pDragon != NULL)
	{
		//�h���S���̈ʒu���擾
		D3DXVECTOR3 DragonPosition = pDragon->GetPosition();
		//�h���S���̏Փ˔���p�T�C�Y�̎擾
		D3DXVECTOR3 DragonCollisionSize = pDragon->GetCollisionSize();
	}
}

//=============================================================================
// ���[�V���������֐�
//=============================================================================
void CPlayer::Motion(void)
{
	//�������[�V�����̃|�C���^��NULL�̏ꍇ
	if (m_pMotion == NULL)
	{
		//���[�V�����̐���
		m_pMotion = CMotion::Create();
	}
	//�������[�V�����̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pMotion != NULL)
	{
		//���[�V�����̓ǂݍ���
		m_pMotion->LoadMotion(MODEL_PASS);
		//���[�V�������̓ǂݍ���
		m_pMotion->LoadModelInformation(MODEL_PASS);
		//�ő�p�[�c������
		for (int nCount = 0; nCount < MAX_PARTS; nCount++)
		{
			//�������f���f�[�^�̃��b�V����NULL����Ȃ��ꍇ
			if (m_ModelData[nCount].pMesh != NULL)
			{
				//�e���f���̔ԍ��󂯎��
				m_ModelData[nCount].nIndexModelParent = m_pMotion->GetParents(nCount);
				//���f���̐���
				m_pModel[nCount] = CModel::Create(m_ModelData[nCount]);
				//���[�V�����̈ʒu���擾
				m_pMotion->GetPosition(nCount);
				//���[�V�����̉�]���擾
				m_pMotion->GetRotation(nCount);
				//���f���̊��蓖��
				m_pModel[nCount]->BindModel(m_ModelData[nCount]);
				// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
				m_pModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), m_Size);
			}
		}
		//�p�[�c�̍ő吔����
		for (int nCount = 0; nCount < MAX_PARTS; nCount++)
		{
			//�����e�̃��f�������݂�����
			if (m_pModel[m_ModelData[nCount].nIndexModelParent] != NULL && m_ModelData[nCount].nIndexModelParent != -1)
			{
				//�������f���f�[�^�̃��b�V����NULL����Ȃ��ꍇ
				if (m_ModelData[nCount].pMesh != NULL)
				{
					//�e�̃��f���|�C���^���󂯎��
					m_ModelData[nCount].pParent = m_pModel[m_ModelData[nCount].nIndexModelParent];
					// ���f���̊��蓖��
					m_pModel[nCount]->BindModel(m_ModelData[nCount]);
				}
			}
		}
		// ���W�A��]�A�T�C�Y�̃Z�b�g
		m_pModel[0]->SetModel(m_pMotion->GetPosition(0) + m_Position, m_pMotion->GetRotation(0) + m_Rotation, m_Size);
	}
}

//=============================================================================
// �f�[�^�ǂݍ��݊֐�
//=============================================================================
void CPlayer::DataLoad(void)
{
	char aReadText[MAX_TEXT];			//�ǂݍ��񂾃e�L�X�g
	char aCurrentText[MAX_TEXT];		//���݂̃e�L�X�g
	char aUnnecessaryText[MAX_TEXT];	//�s�K�v�ȃe�L�X�g
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
						//���݂̃e�L�X�g��POS��������
						if (strcmp(aCurrentText, "POS") == 0)
						{
							//�ʒu�̐ݒ�
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Position.x, &m_Position.y, &m_Position.z);
						}
						//���݂̃e�L�X�g��SIZE��������
						if (strcmp(aCurrentText, "SIZE") == 0)
						{
							//�T�C�Y�̐ݒ�
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Size.x, &m_Size.y, &m_Size.z);
						}
						//���݂̃e�L�X�g��COLLISION_SIZE��������
						if (strcmp(aCurrentText, "COLLISION_SIZE") == 0)
						{
							//�T�C�Y�̐ݒ�
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_CollisionSize.x, &m_CollisionSize.y, &m_CollisionSize.z);
						}
						//���݂̃e�L�X�g��ROT��������
						if (strcmp(aCurrentText, "ROT") == 0)
						{
							//��]���̓ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
						}
						//���݂̃e�L�X�g��MOVE��������
						if (strcmp(aCurrentText, "MOVE") == 0)
						{
							//�T�C�Y�̐ݒ�
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Move.x, &m_Move.y, &m_Move.z);
						}
						//���݂̃e�L�X�g��LIFE��������
						if (strcmp(aCurrentText, "LIFE") == 0)
						{
							//�̗͂̐ݒ�
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nLife);
						}
						//���݂̃e�L�X�g��Speed��������
						if (strcmp(aCurrentText, "Speed") == 0)
						{
							//���x�̐ݒ�̐ݒ�
							sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fSpeed);
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
}