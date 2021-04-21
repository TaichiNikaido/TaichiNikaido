//=============================================================================
//
// ���f�� [model.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �x������
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModel::CModel()
{
	ZeroMemory(&m_aModelData, sizeof(m_aModelData));	//���f���f�[�^�̏�����
	m_Position = INITIAL_D3DXVECTOR3;			//�ʒu
	m_Rotation = INITIAL_D3DXVECTOR3;			//��]
	m_Size = INITIAL_D3DXVECTOR3;				//�T�C�Y
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
// ���f���e�L�X�g�ǂݍ��݊֐�
//=============================================================================
char * CModel::LoadModelText(const char * cText)
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	int	 nCntModel = 0;					//���[�V�����̐��̃J�E���g
	char aReadText[MAX_TEXT];			//�����Ƃ��ēǂݎ��p
	char aCurrentText[MAX_TEXT];		//�����̔��ʗp
	char cDie[MAX_TEXT];				//�g��Ȃ�����
	MODEL_DATA ModelData[MAX_PARTS];	//���f���f�[�^
	char aPass[MAX_PARTS][MAX_TEXT];
	memset(aReadText, NULL, sizeof(aReadText));
	memset(aCurrentText, NULL, sizeof(aCurrentText));
	memset(cDie, NULL, sizeof(cDie));
	memset(ModelData, NULL, sizeof(ModelData));
	memset(aPass, NULL, sizeof(aPass));
	//�t�@�C���̃|�C���^
	FILE *pFile = nullptr;
	//�����t�@�C���̃|�C���^��nullptr�̏ꍇ
	if (pFile == nullptr)
	{
		// �t�@�C�����J��
		pFile = fopen(cText, "r");
	}
	//�����t�@�C���̃|�C���^��nullptr����Ȃ��ꍇ
	if (pFile != nullptr)
	{
		// SCRIPT�̕�����������܂�
		while (strcmp(aCurrentText, "SCRIPT") != 0)
		{
			// �e�L�X�g����aReadText��������ǂݍ���
			fgets(aReadText, sizeof(aReadText), pFile);
			// �ǂݍ��񂾕�������aCurrentText�Ɋi�[
			sscanf(aReadText, "%s", &aCurrentText);
		}
		// aCurrentText��SCRIPT��������
		if (strcmp(aCurrentText, "SCRIPT") == 0)
		{
			// END_SCRIPT�̕�����������܂�
			while (strcmp(aCurrentText, "END_SCRIPT") != 0)
			{
				// �e�L�X�g����aReadText��������ǂݍ���
				fgets(aReadText, sizeof(aReadText), pFile);
				// �ǂݍ��񂾕�������aCurrentText�Ɋi�[
				sscanf(aReadText, "%s", &aCurrentText);
				// aCurrentText��MODEL_FILENAME��������
				if (strcmp(aCurrentText, "MODEL_FILENAME") == 0)
				{
					// ���f���p�[�c�̃p�X���i�[
					sscanf(aReadText, "%s %s %s", &cDie, &cDie, &aPass[nCntModel]);
					// �J�E���g�̉��Z
					nCntModel++;
				}
			}
			// �t�@�C�������
			fclose(pFile);
		}
	}
	return aPass[0];
}

//=============================================================================
// ���������֐�
//=============================================================================
CModel * CModel::Create(MODEL_DATA modeldata)
{
	//���f���̃|�C���^
	CModel* pModel = nullptr;
	//���f���̃|�C���^��NULL�̏ꍇ
	if (pModel == nullptr)
	{
		//���f���̃������m��
		pModel = new CModel;
	}
	//���f���̃|�C���^��nullptr����Ȃ��ꍇ
	if (pModel != nullptr)
	{
		//�e����̐ݒ�
		pModel->m_aModelData = modeldata;
		// ����������
		pModel->Init();
	}
	//���f���̃|�C���^��Ԃ�
	return pModel;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CModel::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CModel::Uninit(void)
{
	m_aModelData.pBuffMat = NULL;
	m_aModelData.nNumMat = NULL;
	m_aModelData.pMesh = NULL;
	memset(m_aModelData.pTexture, NULL, sizeof(m_aModelData.pTexture));
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CModel::Update(void)
{
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CModel::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	//�s��
	D3DXMATERIAL * pMat;					//�}�e���A���̃|�C���^
	D3DXMATRIX mtxParent;					//�e�̍s��
	//���[���h�ϊ��s��̏�����
	D3DXMatrixIdentity(&m_aModelData.mtxWorld);
	//�g��k���s��̐����ƌv�Z
	D3DXMatrixScaling(&mtxScale, m_Size.x, m_Size.y, m_Size.z);
	D3DXMatrixMultiply(&m_aModelData.mtxWorld, &m_aModelData.mtxWorld, &mtxScale);
	//��]�s��̐����ƌv�Z
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixMultiply(&m_aModelData.mtxWorld, &m_aModelData.mtxWorld, &mtxRot);
	//���s�ړ��s��̐����ƌv�Z
	D3DXMatrixTranslation(&mtxTrans, m_Position.x, m_Position.y, m_Position.z);
	D3DXMatrixMultiply(&m_aModelData.mtxWorld, &m_aModelData.mtxWorld, &mtxTrans);
	//�����e���f����NULL����Ȃ��ꍇ
	if (m_aModelData.pParent != NULL)
	{
		//�e�̃}�g���N�X��ݒ�
		mtxParent = m_aModelData.pParent->m_aModelData.mtxWorld;
		//���f���p�[�c�ɐe�̃}�g���b�N�X���|�����킹�邱�ƂŁA�ʒu���]��e�ɒǏ]������
		D3DXMatrixMultiply(&m_aModelData.mtxWorld, &m_aModelData.mtxWorld, &mtxParent);
	}
	else
	{
		//�g�����X�t�[�����擾
		pDevice->GetTransform(D3DTS_WORLD2, &mtxParent);
		//���f���p�[�c�Ƀ}�g���b�N�X���|�����킹�邱�ƂŁA�ʒu���]��e�ɒǏ]������
		D3DXMatrixMultiply(&m_aModelData.mtxWorld, &m_aModelData.mtxWorld, &mtxParent);
	}
	//�v�Z���ʂ�K�p
	pDevice->SetTransform(D3DTS_WORLD, &m_aModelData.mtxWorld);
	//�����}�e���A����NULL����Ȃ��ꍇ
	if (m_aModelData.pBuffMat != NULL)
	{
		//�}�e���A���̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_aModelData.pBuffMat->GetBufferPointer();
	}
	//�}�e���A�����̐ݒ�ƃ}�e���A�����Ƃɕ`��
	for (int nCntMat = 0; nCntMat < (int)m_aModelData.nNumMat; nCntMat++)
	{
		//�}�e���A����ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�}�e���A���̃e�N�X�`����ݒ�
		pDevice->SetTexture(0, m_aModelData.pTexture[nCntMat]);
		//�g�U���̐ݒ�
		pMat[nCntMat].MatD3D.Emissive = pMat[nCntMat].MatD3D.Diffuse;
		//���b�V����NULL����Ȃ��ꍇ
		if (m_aModelData.pMesh != NULL)
		{
			//���b�V����`�悷��
			m_aModelData.pMesh->DrawSubset(nCntMat);
		}
	}
}

//=============================================================================
// �e���f���̐ݒ�֐�
//=============================================================================
void CModel::SetParentModel(CModel * pParentModel)
{
	//�e���f���̃|�C���^��ݒ�
	m_aModelData.pParent = pParentModel;
}

//=============================================================================
// ���f���̐ݒ�֐�
//=============================================================================
void CModel::SetModel(D3DXVECTOR3 Position, D3DXVECTOR3 Rotation, D3DXVECTOR3 Size)
{
	//�ʒu��ݒ肷��
	m_Position = Position;
	//��]��ݒ肷��
	m_Rotation = Rotation;
	//�T�C�Y��ݒ肷��
	m_Size = Size;
}

//=============================================================================
// �e�N�X�`���̊��蓖�Ċ֐�
//=============================================================================
void CModel::BindTexture(LPDIRECT3DTEXTURE9 pTexture, int nCount)
{
	//�e�N�X�`���̃|�C���^��ݒ肷��
	m_aModelData.pTexture[nCount] = pTexture;
}
