//=============================================================================
//
// �Α��̉� [object_house.cpp]
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
#include "renderer.h"
#include "object_stone_house.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PASS ("Data/Model/House/StoneHouse.x")			//���f���X�N���v�g�̃p�X
#define SCRIPT_PASS ("Data/Script/Object/StoneHouseData.txt")	//�X�N���v�g�̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODEL_DATA CStoneHouse::m_ModelData = {};			//���f���f�[�^�̃|�C���^
D3DXMATERIAL * CStoneHouse::m_pMaterial = NULL;				//�}�e���A���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStoneHouse::CStoneHouse()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStoneHouse::~CStoneHouse()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CStoneHouse::ModelLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�p�X�̃|�C���^
	char * pPass = NULL;
	//�����p�X�̃|�C���^��NULL�̏ꍇ
	if (pPass == NULL)
	{
		//�p�X���擾
		pPass = MODEL_PASS;
	}
	//�����p�X�̃|�C���^��NULL����Ȃ��ꍇ
	if (pPass != NULL)
	{
		//���f���ǂݍ���
		D3DXLoadMeshFromX(pPass,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_ModelData.pBuffMat,
			NULL,
			&m_ModelData.nNumMat,
			&m_ModelData.pMesh);
		//�������f���̃}�e���A�����NULL����Ȃ��ꍇ
		if (m_ModelData.pBuffMat != NULL)
		{
			//�}�e���A���̃|�C���^���擾
			m_pMaterial = (D3DXMATERIAL *)m_ModelData.pBuffMat->GetBufferPointer();
			//���f���f�[�^������
			for (int nCountMat = 0; nCountMat < (int)m_ModelData.nNumMat; nCountMat++)
			{
				//�����t�@�C���l�[����NULL����Ȃ��ꍇ
				if (m_pMaterial[nCountMat].pTextureFilename != NULL)
				{
					//�e�N�X�`����ǂݍ���
					D3DXCreateTextureFromFile(pDevice, m_pMaterial[nCountMat].pTextureFilename, &m_ModelData.pTexture[nCountMat]);
				}
			}
		}
	}
	return S_OK;
}

//=============================================================================
// ���f���j���֐�
//=============================================================================
void CStoneHouse::ModelUnload(void)
{
	//�������f���f�[�^�̃��[���h�ϊ��s��NULL����ȏꍇ
	if (m_ModelData.mtxWorld != NULL)
	{
		//�������f���f�[�^�̃}�e���A�����NULL����ȏꍇ
		if (m_ModelData.pBuffMat != NULL)
		{
			//���f���f�[�^�̃}�e���A������j��
			m_ModelData.pBuffMat->Release();
		}
		//�������f���f�[�^�̃��b�V�����NULL����ȏꍇ
		if (m_ModelData.pMesh != NULL)
		{
			//���f���f�[�^�̃��b�V������j��
			m_ModelData.pMesh->Release();
		}
		//�}�e���A���̍ő吔����
		for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
		{
			//�������f���f�[�^�̃e�N�X�`���̃|�C���^��NULL����ȏꍇ
			if (m_ModelData.pTexture[nCountTexture] != NULL)
			{
				//���f���f�[�^�̃e�N�X�`���̃|�C���^��j��
				m_ModelData.pTexture[nCountTexture]->Release();
			}
		}
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CStoneHouse * CStoneHouse::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Rotation)
{
	//�Α��̉Ƃ̃|�C���^
	CStoneHouse * pStoneHouse = NULL;
	//�Α��̉Ƃ̃|�C���^��NULL�̏ꍇ
	if (pStoneHouse == NULL)
	{
		//�Α��̉Ƃ̃������m��
		pStoneHouse = new CStoneHouse;
		//�Α��̉Ƃ̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pStoneHouse != NULL)
		{
			//�Α��̉Ƃ̈ʒu��ݒ肷��
			pStoneHouse->SetPosition(Position);
			//�Α��̉Ƃ̉�]��ݒ肷��
			pStoneHouse->SetRotation(Rotation);
			//�Α��̉Ƃ̏����������֐��Ăяo��
			pStoneHouse->Init();
		}
	}
	//�Α��̉Ƃ̃|�C���^��Ԃ�
	return pStoneHouse;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CStoneHouse::Init(void)
{
	//���f���f�[�^�̐ݒ�
	SetModelData(m_ModelData);
	//�X�N���v�g�̃p�X��ݒ�
	SetScriptPass(SCRIPT_PASS);
	//�I�u�W�F�N�g�̏����������֐��Ăяo��
	CObject::Init();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CStoneHouse::Uninit(void)
{
	//�I�u�W�F�N�g�̏I�������֐��Ăяo��
	CObject::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CStoneHouse::Update(void)
{
	//�I�u�W�F�N�g�̍X�V�����֐��Ăяo��
	CObject::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CStoneHouse::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈���֐��Ăяo��
	CObject::Draw();
}
