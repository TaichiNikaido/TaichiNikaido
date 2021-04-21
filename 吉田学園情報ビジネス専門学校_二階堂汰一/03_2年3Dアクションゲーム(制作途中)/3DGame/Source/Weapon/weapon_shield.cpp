//=============================================================================
//
// �� [shield.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Mode/mode_game.h"
#include "weapon_shield.h"
#include "Character/player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PASS ("Data/Model/Weapon/Shield.x")	//���f���X�N���v�g�̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODEL_DATA CShield::m_aModelData = {};	//���f���f�[�^�̃|�C���^
D3DXMATERIAL * CShield::m_pMaterial = nullptr;	//�}�e���A���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShield::CShield()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShield::~CShield()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CShield::ModelLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�p�X�̃|�C���^
	char * pPass = nullptr;
	//�����p�X�̃|�C���^��nullptr�̏ꍇ
	if (pPass == nullptr)
	{
		//�p�X���擾
		pPass = MODEL_PASS;
		//�����p�X�̃|�C���^��nullptr����Ȃ��ꍇ
		if (pPass != nullptr)
		{
			//���f���ǂݍ���
			D3DXLoadMeshFromX(pPass,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_aModelData.pBuffMat,
				NULL,
				&m_aModelData.nNumMat,
				&m_aModelData.pMesh);
			//�������f���̃}�e���A�����NULL����Ȃ��ꍇ
			if (m_aModelData.pBuffMat != NULL)
			{
				//�}�e���A���̃|�C���^���擾
				m_pMaterial = (D3DXMATERIAL *)m_aModelData.pBuffMat->GetBufferPointer();
				//���f���f�[�^������
				for (int nCountMat = 0; nCountMat < (int)m_aModelData.nNumMat; nCountMat++)
				{
					//�����t�@�C���l�[����NULL����Ȃ��ꍇ
					if (m_pMaterial[nCountMat].pTextureFilename != NULL)
					{
						//�e�N�X�`����ǂݍ���
						D3DXCreateTextureFromFile(pDevice, m_pMaterial[nCountMat].pTextureFilename, &m_aModelData.pTexture[nCountMat]);
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
void CShield::ModelUnload(void)
{
	//�������f���f�[�^�̃��[���h�ϊ��s��NULL����ȏꍇ
	if (m_aModelData.mtxWorld != NULL)
	{
		//�������f���f�[�^�̃}�e���A�����NULL����ȏꍇ
		if (m_aModelData.pBuffMat != NULL)
		{
			//���f���f�[�^�̃}�e���A������j��
			m_aModelData.pBuffMat->Release();
		}
		//�������f���f�[�^�̃��b�V�����NULL����ȏꍇ
		if (m_aModelData.pMesh != NULL)
		{
			//���f���f�[�^�̃��b�V������j��
			m_aModelData.pMesh->Release();
		}
		//�}�e���A���̍ő吔����
		for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
		{
			//�������f���f�[�^�̃e�N�X�`���̃|�C���^��NULL����ȏꍇ
			if (m_aModelData.pTexture[nCountTexture] != NULL)
			{
				//���f���f�[�^�̃e�N�X�`���̃|�C���^��j��
				m_aModelData.pTexture[nCountTexture]->Release();
			}
		}
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CShield * CShield::Create()
{
	//���̃|�C���^
	CShield * pShield = nullptr;
	//���̃|�C���^��nullptr�̏ꍇ
	if (pShield == nullptr)
	{
		//���̃������m��
		pShield = new CShield;
		//���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pShield != nullptr)
		{
			//���̏����������֐��Ăяo��
			pShield->Init();
		}
	}
	//���̃|�C���^��Ԃ�
	return pShield;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CShield::Init(void)
{
	//�v���C���[���擾����
	CPlayer * pPlayer = CManager::GetGameMode()->GetPlayer();
	//�����v���C���[��nullptr����Ȃ��ꍇ
	if (pPlayer != nullptr)
	{
		//�e���f���̐ݒ�
		SetParentModel(pPlayer->GetModel(9));
	}
	//���f���f�[�^�̐ݒ�
	SetModelData(m_aModelData);
	//����̏����������֐��Ăяo��
	CWeapon::Init();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CShield::Uninit(void)
{
	//����̏I�������֐��Ăяo��
	CWeapon::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CShield::Update(void)
{
	//����̍X�V�����֐��Ăяo��
	CWeapon::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CShield::Draw(void)
{
	//����̕`�揈���֐��Ăяo��
	CWeapon::Draw();
}