//=============================================================================
//
// �� [object_castle.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "object_castle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PASS ("Data/Model/Object/castle.x")	//���f���X�N���v�g�̃p�X
#define ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))		//��]
#define SIZE (D3DXVECTOR3(2.0f,2.0f,2.0f))			//�T�C�Y

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODEL_DATA CCastle::m_MeteorModelData = {};		//���f���f�[�^�̃|�C���^
D3DXMATERIAL * CCastle::m_pMaterial = NULL;				//�}�e���A���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCastle::CCastle()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCastle::~CCastle()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CCastle::ModelLoad(void)
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
		//�����p�X�̃|�C���^��NULL����Ȃ��ꍇ
		if (pPass != NULL)
		{
			//���f���ǂݍ���
			D3DXLoadMeshFromX(pPass,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_MeteorModelData.pBuffMat,
				NULL,
				&m_MeteorModelData.nNumMat,
				&m_MeteorModelData.pMesh);
			//�������f���̃}�e���A�����NULL����Ȃ��ꍇ
			if (m_MeteorModelData.pBuffMat != NULL)
			{
				//�}�e���A���̃|�C���^���擾
				m_pMaterial = (D3DXMATERIAL *)m_MeteorModelData.pBuffMat->GetBufferPointer();
				//���f���f�[�^������
				for (int nCountMat = 0; nCountMat < (int)m_MeteorModelData.nNumMat; nCountMat++)
				{
					//�����t�@�C���l�[����NULL����Ȃ��ꍇ
					if (m_pMaterial[nCountMat].pTextureFilename != NULL)
					{
						//�e�N�X�`����ǂݍ���
						D3DXCreateTextureFromFile(pDevice, m_pMaterial[nCountMat].pTextureFilename, &m_MeteorModelData.pTexture[nCountMat]);
					}
				}
			}
		}
	}
	return S_OK;
}

//=============================================================================
// ���f���j���֐�
//=============================================================================
void CCastle::ModelUnload(void)
{
	//�������f���f�[�^�̃��[���h�ϊ��s��NULL����ȏꍇ
	if (m_MeteorModelData.mtxWorld != NULL)
	{
		//�������f���f�[�^�̃}�e���A�����NULL����ȏꍇ
		if (m_MeteorModelData.pBuffMat != NULL)
		{
			//���f���f�[�^�̃}�e���A������j��
			m_MeteorModelData.pBuffMat->Release();
		}
		//�������f���f�[�^�̃��b�V�����NULL����ȏꍇ
		if (m_MeteorModelData.pMesh != NULL)
		{
			//���f���f�[�^�̃��b�V������j��
			m_MeteorModelData.pMesh->Release();
		}
		//�}�e���A���̍ő吔����
		for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
		{
			//�������f���f�[�^�̃e�N�X�`���̃|�C���^��NULL����ȏꍇ
			if (m_MeteorModelData.pTexture[nCountTexture] != NULL)
			{
				//���f���f�[�^�̃e�N�X�`���̃|�C���^��j��
				m_MeteorModelData.pTexture[nCountTexture]->Release();
			}
		}
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CCastle * CCastle::Create(D3DXVECTOR3 Position)
{
	//��̃|�C���^
	CCastle * pCastle = NULL;
	//��̃|�C���^��NULL�̏ꍇ
	if (pCastle == NULL)
	{
		//��̃������m��
		pCastle = new CCastle;
		//��̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pCastle != NULL)
		{
			//��̈ʒu��ݒ肷��
			pCastle->SetPosition(Position);
			//��̉�]��ݒ肷��
			pCastle->SetRotation(ROTATION);
			//��̃T�C�Y��ݒ肷��
			pCastle->SetSize(SIZE);
			//��̏����������֐��Ăяo��
			pCastle->Init();
		}
	}
	//��̃|�C���^��Ԃ�
	return pCastle;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CCastle::Init(void)
{
	//���f���f�[�^�̐ݒ�
	SetModelData(m_MeteorModelData);
	//�I�u�W�F�N�g�̏����������֐��Ăяo��
	CObject::Init();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CCastle::Uninit(void)
{
	//�I�u�W�F�N�g�̏I�������֐��Ăяo��
	CObject::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CCastle::Update(void)
{
	//�I�u�W�F�N�g�̍X�V�����֐��Ăяo��
	CObject::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CCastle::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈���֐��Ăяo��
	CObject::Draw();
}