//=============================================================================
//
// �J���� [camera.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "renderer.h"
#include "keyboard.h"
#include "joystick.h"
#include "camera.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCRIPT_PASS ("Data/Script/Camera/Data.txt")			//�v���C���[�f�[�^�̃X�N���v�g�̃p�X
#define INITIAL_POSITION_V (D3DXVECTOR3(0.0f, 0.0f, 0.0f))	//���_�̏����l
#define INITIAL_POSITION_R (D3DXVECTOR3(0.0f,0.0f,0.0f))	//�����_�̏����l
#define INITIAL_VECTOR_U (D3DXVECTOR3(0.0f,0.0f,0.0f))		//������x�N�g��
#define INITIAL_ROTAION (D3DXVECTOR3(0.0f,0.0f,0.0f))		//��]�̏����l
#define INITIAL_DISTANCE (0.0f)								//�����̏����l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	m_PositionV = INITIAL_POSITION_V;	//���_�̈ʒu
	m_PositionR = INITIAL_POSITION_R;	//�����_�̈ʒu
	m_VectorU = INITIAL_VECTOR_U;		//������x�N�g��
	m_Rotation = INITIAL_ROTAION;		//��]
	m_fDistance = INITIAL_DISTANCE;		//���_�ƒ����_�̋���
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CCamera::Init(void)
{
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�����v���C���[�̃|�C���^��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(pPlayer->GetModel(3)->GetModelData().mtxWorld._41, pPlayer->GetModel(3)->GetModelData().mtxWorld._42, pPlayer->GetModel(3)->GetModelData().mtxWorld._43);
		//�v���C���[�܂ł̋������擾
		float PlayerDistance = pPlayer->GetCameraDistance();
		//���_��ݒ肷��
		m_PositionV = D3DXVECTOR3(PlayerPosition.x, PlayerPosition.y, PlayerPosition.z + PlayerDistance);
		//�����_�̐ݒ�
		m_PositionR = D3DXVECTOR3(PlayerPosition.x, PlayerPosition.y, PlayerPosition.z);
	}
	//������x�N�g���̏����ݒ�
	m_VectorU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//��]�����̏����ݒ�
	m_Rotation = D3DXVECTOR3(0.0f, D3DXToRadian(80.0f), D3DXToRadian(80.0f));
	//���_�ƒ����_�̋�����ݒ�
	m_fDistance = sqrtf(powf(m_PositionV.z - m_PositionR.z, 2) + powf(m_PositionV.y - m_PositionR.y, 2));
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CCamera::Update(void)
{
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�����v���C���[�̃|�C���^��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(pPlayer->GetModel(3)->GetModelData().mtxWorld._41, pPlayer->GetModel(3)->GetModelData().mtxWorld._42, pPlayer->GetModel(3)->GetModelData().mtxWorld._43);
		//�e�J�������W�̐ݒ�
		m_PositionV.x = PlayerPosition.x + m_fDistance * sinf(m_Rotation.z) * cosf(m_Rotation.y);
		m_PositionV.y = PlayerPosition.y + m_fDistance * cosf(m_Rotation.z);
		m_PositionV.z = PlayerPosition.z + m_fDistance * sinf(m_Rotation.z) * sinf(m_Rotation.y);
		//�����_�̐ݒ�
		m_PositionR = D3DXVECTOR3(PlayerPosition.x, PlayerPosition.y, PlayerPosition.z);
	}
	//���͏����֐��Ăяo��
	Input();
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CCamera::Input(void)
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
	//��
	if (lpDIDevice != NULL &&js.lRz == -1000)
	{
		if (m_Rotation.z > D3DXToRadian(5.0f))
		{
			//��]��Z�����Z����
			m_Rotation.z -= D3DXToRadian(1.75f);
		}
	}
	//��
	if (lpDIDevice != NULL &&js.lRz == 1000)
	{
		if (m_Rotation.z < D3DXToRadian(175.0f))
		{
			m_Rotation.z += D3DXToRadian(1.75f);
		}
	}
	//��
	if (lpDIDevice != NULL &&js.lZ == -1000)
	{
		m_Rotation.y += D3DXToRadian(1.75f);
	}
	//�E
	if (lpDIDevice != NULL &&js.lZ == 1000)
	{
		m_Rotation.y -= D3DXToRadian(1.75f);
	}
	if (pJoystick->GetJoystickPress(JS_Y))
	{
		DataLoad();
	}
}

//=============================================================================
// �J�����ݒ�֐�
//=============================================================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_MtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_MtxView, &m_PositionV, &m_PositionR, &m_VectorU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_MtxView);
	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_MtxProjection);
	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_MtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 10000.0f);
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_MtxProjection);
}

//=============================================================================
// �f�[�^�ǂݍ��݊֐�
//=============================================================================
void CCamera::DataLoad()
{
}
