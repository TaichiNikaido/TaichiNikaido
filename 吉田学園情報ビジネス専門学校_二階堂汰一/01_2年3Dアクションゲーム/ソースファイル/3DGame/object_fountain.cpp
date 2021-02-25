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
#include "object_fountain.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PASS ("Data/Model/Fountain.x")					//���f���X�N���v�g�̃p�X
#define SCRIPT_PASS ("Data/Script/Script/FountainData.txt")		//�X�N���v�g�̃p�X
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))				//�T�C�Y�̏����l
#define INITIAL_COLLISION_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//�Փ˔���p�T�C�Y�̏����l
#define INITIAL_LIFE (0)										//�̗͂̏����l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODEL_DATA CFountain::m_ModelData = {};			//���f���f�[�^�̃|�C���^
D3DXMATERIAL * CFountain::m_pMaterial = NULL;			//�}�e���A���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFountain::CFountain()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFountain::~CFountain()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CFountain::ModelLoad(void)
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
void CFountain::ModelUnload(void)
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
CFountain * CFountain::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Rotation)
{
	//�����̃|�C���^
	CFountain * pFountain = NULL;
	//�����̃|�C���^��NULL�̏ꍇ
	if (pFountain == NULL)
	{
		//�����̃������m��
		pFountain = new CFountain;
	}
	//�����̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (pFountain != NULL)
	{
		//�����̈ʒu��ݒ肷��
		pFountain->SetPosition(Position);
		//�����̉�]��ݒ肷��
		pFountain->SetRotation(Rotation);
		//�����̏����������֐��Ăяo��
		pFountain->Init();
	}
	//�����̃|�C���^��Ԃ�
	return pFountain;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CFountain::Init(void)
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
void CFountain::Uninit(void)
{
	//�I�u�W�F�N�g�̏I�������֐��Ăяo��
	CObject::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CFountain::Update(void)
{
	//�I�u�W�F�N�g�̍X�V�����֐��Ăяo��
	CObject::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CFountain::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈���֐��Ăяo��
	CObject::Draw();
}