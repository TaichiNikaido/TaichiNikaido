//=============================================================================
//
// �I�u�W�F�N�g [object.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "renderer.h"
#include "object.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INITIAL_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))				//�ʒu�̏����l
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))					//�T�C�Y�̏����l
#define INITIAL_COLLISION_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))		//�Փ˔���p�T�C�Y�̏����l
#define INITIAL_ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))				//��]�̏����l
#define INITIAL_ALL_LIFE (0)										//�S�̗̂̑͂̏����l
#define INITIAL_LIFE (0)											//�̗͂̏����l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject::CObject()
{
	m_Position = INITIAL_POSITION;				//�ʒu
	m_Size = INITIAL_SIZE;						//�T�C�Y
	m_CollisionSize = INITIAL_COLLISION_SIZE;	//�Փ˔���p�T�C�Y
	m_Rotation = INITIAL_ROTATION;				//��]
	m_nLife = INITIAL_LIFE;						//�̗�
	m_pModel = NULL;							//���f���̃|�C���^
	m_ModelData = {};							//���f���f�[�^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CObject::Init(void)
{
	//�������f���̃|�C���^��NULL�̏ꍇ
	if (m_pModel == NULL)
	{
		//���f���̐���
		m_pModel = CModel::Create(m_ModelData);
	}
	//�������f���̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pModel != NULL)
	{
		//���f���̏����������֐��Ăяo��
		m_pModel->Init();
		//���f���Ɉʒu��ݒ肷��
		m_pModel->SetPosition(m_Position);
		//���f���ɃT�C�Y��ݒ肷��
		m_pModel->SetSize(m_Size);
		//���f���ɉ�]��ݒ肷��
		m_pModel->SetRotation(m_Rotation);
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CObject::Uninit(void)
{
	//�������f���̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pModel != NULL)
	{
		//���f���̏I�������֐��Ăяo��
		m_pModel->Uninit();
	}
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CObject::Update(void)
{
	//�������f���̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pModel != NULL)
	{
		//���f���̍X�V�����֐��Ăяo��
		m_pModel->Update();
	}
	//�Փ˔���̉�
	Collision();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CObject::Draw(void)
{
	//�������f���̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pModel != NULL)
	{
		//���f���̕`�揈���֐��Ăяo��
		m_pModel->Draw();
	}
}

//=============================================================================
// �̗͌��Z�����֐�
//=============================================================================
void CObject::SubLife(void)
{
}

//=============================================================================
// �Փˏ����֐�
//=============================================================================
void CObject::Collision(void)
{
	//�v���C���[���擾����
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�����v���C���[�̃|�C���^��NULL����Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̈ʒu���擾����
		//D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(pPlayer->GetModel(0)->GetModelData().mtxWorld._41, pPlayer->GetModel(0)->GetModelData().mtxWorld._42 - 20.0f, pPlayer->GetModel(0)->GetModelData().mtxWorld._43);
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//�v���C���[�̑O�̈ʒu���擾����
		D3DXVECTOR3 PlayerPositionOld = pPlayer->GetPositionOld();
		//�v���C���[�̈ړ��ʂ�ݒ肷��
		D3DXVECTOR3 PlayerMove = pPlayer->GetMove();
		//�v���C���[�̏Փ˔���p�T�C�Y�̎擾
		D3DXVECTOR3 PlayerCollisionSize = pPlayer->GetCollisionSize();
		D3DXVECTOR3 PlayerCollisionMAX = D3DXVECTOR3(PlayerCollisionSize.x / 2, PlayerCollisionSize.y / 2, PlayerCollisionSize.z / 2) + PlayerPosition;
		D3DXVECTOR3 PlayerCollisionMIN = D3DXVECTOR3(-PlayerCollisionSize.x / 2, -PlayerCollisionSize.y / 2, -PlayerCollisionSize.z / 2) + PlayerPosition;
		D3DXVECTOR3 ObjectCollisionMAX = D3DXVECTOR3(m_CollisionSize.x / 2, m_CollisionSize.y / 2, m_CollisionSize.z / 2) + m_Position;
		D3DXVECTOR3 ObjectCollisionMIN = D3DXVECTOR3(-m_CollisionSize.x / 2, -m_CollisionSize.y / 2, -m_CollisionSize.z / 2) + m_Position;
		if (PlayerCollisionMAX.y > ObjectCollisionMIN.y &&
			PlayerCollisionMIN.y < ObjectCollisionMAX.y &&
			PlayerCollisionMAX.x > ObjectCollisionMIN.x &&
			PlayerCollisionMIN.x < ObjectCollisionMAX.x &&
			PlayerCollisionMAX.z > ObjectCollisionMIN.z &&
			PlayerCollisionMIN.z < ObjectCollisionMAX.z)
		{
			if (PlayerCollisionMAX.y > ObjectCollisionMIN.y && PlayerPositionOld.y <= ObjectCollisionMIN.y)
			{
				pPlayer->SetMove(D3DXVECTOR3(PlayerMove.x,0.0f, PlayerMove.z));
				pPlayer->SetPosition(D3DXVECTOR3(pPlayer->GetPosition().x,ObjectCollisionMIN.y - PlayerCollisionSize.y / 2,PlayerPosition.z));
			}
			else if (PlayerCollisionMIN.y < ObjectCollisionMAX.y && PlayerPositionOld.y >= ObjectCollisionMAX.y)
			{
				pPlayer->SetMove(D3DXVECTOR3(PlayerMove.x, 0.0f, PlayerMove.z));
				pPlayer->SetPosition(D3DXVECTOR3(pPlayer->GetPosition().x,ObjectCollisionMAX.y + PlayerCollisionSize.y / 2,PlayerPosition.z));
			}
			else if (PlayerCollisionMAX.x > ObjectCollisionMIN.x && PlayerPositionOld.x <= ObjectCollisionMIN.x)
			{
				pPlayer->SetMove(D3DXVECTOR3(0.0f, PlayerMove.y, PlayerMove.z));
				pPlayer->SetPosition(D3DXVECTOR3(ObjectCollisionMIN.x - PlayerCollisionSize.x / 2,PlayerPosition.y,PlayerPosition.z));
			}
			else if (PlayerCollisionMIN.x < ObjectCollisionMAX.x && PlayerPositionOld.x >= ObjectCollisionMAX.x)
			{
				pPlayer->SetMove(D3DXVECTOR3(0.0f, PlayerMove.y, PlayerMove.z));
				pPlayer->SetPosition(D3DXVECTOR3(ObjectCollisionMAX.x + PlayerCollisionSize.x / 2,PlayerPosition.y,PlayerPosition.z));
			}
			else if (PlayerCollisionMAX.z > ObjectCollisionMIN.z && PlayerPositionOld.z <= ObjectCollisionMIN.z)
			{
				pPlayer->SetMove(D3DXVECTOR3(PlayerMove.x, PlayerMove.y, 0.0f));
				pPlayer->SetPosition(D3DXVECTOR3(PlayerPosition.x,PlayerPosition.y,ObjectCollisionMIN.z - PlayerCollisionSize.z / 2));
			}
			else if (PlayerCollisionMIN.z < ObjectCollisionMAX.z && PlayerPositionOld.z >= ObjectCollisionMAX.z)
			{
				pPlayer->SetMove(D3DXVECTOR3(PlayerMove.x, PlayerMove.y, 0.0f));
				pPlayer->SetPosition(D3DXVECTOR3(PlayerPosition.x, PlayerPosition.y,ObjectCollisionMAX.z + PlayerCollisionSize.z / 2));
			}
		}
	}
}
