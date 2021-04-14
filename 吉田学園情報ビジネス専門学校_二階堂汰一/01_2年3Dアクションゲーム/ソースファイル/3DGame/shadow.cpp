//=============================================================================
//
// �e [shadow.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PASS ("Data/Script/Player/PlayerModel.txt")	//���f���X�N���v�g�̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODEL_DATA CShadow::m_aShadowModelData[MAX_PARTS] = {};		//���f�����

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShadow::CShadow()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShadow::~CShadow()
{
}

HRESULT CShadow::ModelLoad(void)
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
				&m_aShadowModelData[nCount].pBuffMat,
				NULL,
				&m_aShadowModelData[nCount].nNumMat,
				&m_aShadowModelData[nCount].pMesh);
			//�������f���̃}�e���A�����NULL����Ȃ��ꍇ
			if (m_aShadowModelData[nCount].pBuffMat != NULL)
			{
				//�}�e���A���̃|�C���^���擾
				pMaterial = (D3DXMATERIAL *)m_aShadowModelData[nCount].pBuffMat->GetBufferPointer();
				//���f���f�[�^������
				for (int nCountMat = 0; nCountMat < (int)m_aShadowModelData[nCount].nNumMat; nCountMat++)
				{
					//�����t�@�C���l�[����NULL����Ȃ��ꍇ
					if (pMaterial[nCountMat].pTextureFilename != NULL)
					{
						//�e�N�X�`����ǂݍ���
						D3DXCreateTextureFromFile(pDevice, pMaterial[nCountMat].pTextureFilename, &m_aShadowModelData[nCount].pTexture[nCountMat]);
					}
				}
			}
			//�|�C���^���̂Ă�
			pPass += MAX_TEXT;
		}
	}
	return S_OK;
}

void CShadow::ModelUnload(void)
{
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���f�[�^�̃��[���h�ϊ��s��NULL�ł͂Ȃ��ꍇ
		if (m_aShadowModelData[nCount].mtxWorld != NULL)
		{
			//�������f���f�[�^�̃}�e���A�����NULL�ł͂Ȃ��ꍇ
			if (m_aShadowModelData[nCount].pBuffMat != NULL)
			{
				//���f���f�[�^�̃}�e���A������j��
				m_aShadowModelData[nCount].pBuffMat->Release();
			}
			//�������f���f�[�^�̃��b�V�����NULL�ł͂Ȃ��ꍇ
			if (m_aShadowModelData[nCount].pMesh != NULL)
			{
				//���f���f�[�^�̃��b�V������j��
				m_aShadowModelData[nCount].pMesh->Release();
			}
			//�}�e���A���̍ő吔����
			for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
			{
				//�������f���f�[�^�̃e�N�X�`���̃|�C���^��NULL�ł͂Ȃ��ꍇ
				if (m_aShadowModelData[nCount].pTexture[nCountTexture] != NULL)
				{
					//���f���f�[�^�̃e�N�X�`���̃|�C���^��j��
					m_aShadowModelData[nCount].pTexture[nCountTexture]->Release();
				}
			}
		}
	}
}

CShadow * CShadow::Create()
{
	//�e�̃|�C���^
	CShadow * pShadow = NULL;
	//�e�̃|�C���^��NULL�̏ꍇ
	if (pShadow == NULL)
	{
		//�e�̃������m��
		pShadow = new CShadow;
		//�e�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pShadow != NULL)
		{
			//�e�̏����������֐��Ăяo��
			pShadow->Init();
		}
	}
	//�e�̃|�C���^��Ԃ�
	return pShadow;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CShadow::Init(void)
{
	D3DXVECTOR3 Position = D3DXVECTOR3(0.0f,0.0f,400.0f);
	SetPosition(Position);
	D3DXVECTOR3 Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetRotation(Rotation);
	D3DXVECTOR3 Size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	SetSize(Size);
	SetModelScriptPass(MODEL_PASS);
	//���f�����̐ݒ�
	SetModelData(m_aShadowModelData);
	//�L�����N�^�[�̏����������֐��Ăяo��
	CCharacter::Init();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CShadow::Uninit(void)
{
	//�L�����N�^�[�̏I�������֐��Ăяo��
	CCharacter::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CShadow::Update(void)
{
	//�L�����N�^�[�̍X�V�����֐��Ăяo��
	CCharacter::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CShadow::Draw(void)
{
	//�L�����N�^�[�̕`�揈���֐��Ăяo��
	CCharacter::Draw();
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	//�[�x�e�X�g��s���i�ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
	//�X�e���V���Q�ƒl��ݒ肷��
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x05);
	//�X�e���V���}�X�N�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	//�X�e���V���o�b�t�@�ɏ������ޏ����̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	//�������ޒl�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
}