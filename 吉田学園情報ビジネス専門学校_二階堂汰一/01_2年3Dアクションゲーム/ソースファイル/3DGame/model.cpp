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
	ZeroMemory(&m_ModelData, sizeof(m_ModelData));	//���f���f�[�^�̏�����
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
	MODEL_DATA ModelData[MAX_PARTS];		//���f���f�[�^
	char aPass[MAX_PARTS][MAX_TEXT];
	memset(aReadText, NULL, sizeof(aReadText));
	memset(aCurrentText, NULL, sizeof(aCurrentText));
	memset(cDie, NULL, sizeof(cDie));
	memset(ModelData, NULL, sizeof(ModelData));
	memset(aPass, NULL, sizeof(aPass));
	//�t�@�C���̃|�C���^
	FILE *pFile = NULL;
	//�����t�@�C���̃|�C���^��NULL�̏ꍇ
	if (pFile == NULL)
	{
		// �t�@�C�����J��
		pFile = fopen(cText, "r");
	}
	//�����t�@�C���̃|�C���^��NULL����Ȃ��ꍇ
	if (pFile != NULL)
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
	CModel* pModel = NULL;
	//���f���̃|�C���^��NULL�̏ꍇ
	if (pModel == NULL)
	{
		//���f���̃������m��
		pModel = new CModel;
	}
	//���f���̃|�C���^��NULL����Ȃ��ꍇ
	if (pModel != NULL)
	{
		//�e����̐ݒ�
		pModel->m_ModelData = modeldata;
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
	D3DXMatrixIdentity(&m_ModelData.mtxWorld);
	//�g��k���s��̐����ƌv�Z
	D3DXMatrixScaling(&mtxScale, GetSize().x, GetSize().y, GetSize().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxScale);
	//��]�s��̐����ƌv�Z
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRotation().y, GetRotation().x, GetRotation().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);
	//���s�ړ��s��̐����ƌv�Z
	D3DXMatrixTranslation(&mtxTrans, GetPosition().x, GetPosition().y, GetPosition().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);
	//�����e���f����NULL����Ȃ��ꍇ
	if (m_ModelData.pParent != NULL)
	{
		//�e�̃}�g���N�X��ݒ�
		mtxParent = m_ModelData.pParent->m_ModelData.mtxWorld;
		//���f���p�[�c�ɐe�̃}�g���b�N�X���|�����킹�邱�ƂŁA�ʒu���]��e�ɒǏ]������
		D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxParent);
	}
	else
	{
		//�g�����X�t�[�����擾
		pDevice->GetTransform(D3DTS_WORLD2, &mtxParent);
		//���f���p�[�c�Ƀ}�g���b�N�X���|�����킹�邱�ƂŁA�ʒu���]��e�ɒǏ]������
		D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxParent);
	}
	//�v�Z���ʂ�K�p
	pDevice->SetTransform(D3DTS_WORLD, &m_ModelData.mtxWorld);
	//�����}�e���A����NULL����Ȃ��ꍇ
	if (m_ModelData.pBuffMat != NULL)
	{
		//�}�e���A���̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_ModelData.pBuffMat->GetBufferPointer();
	}
	//�}�e���A�����̐ݒ�ƃ}�e���A�����Ƃɕ`��
	for (int nCntMat = 0; nCntMat < (int)m_ModelData.nNumMat; nCntMat++)
	{
		//�}�e���A����ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�}�e���A���̃e�N�X�`����ݒ�
		pDevice->SetTexture(0, m_ModelData.pTexture[nCntMat]);
		//�g�U���̐ݒ�
		pMat[nCntMat].MatD3D.Emissive = pMat[nCntMat].MatD3D.Diffuse;
		//���b�V����NULL����Ȃ��ꍇ
		if (m_ModelData.pMesh != NULL)
		{
			//���b�V����`�悷��
			m_ModelData.pMesh->DrawSubset(nCntMat);
		}
	}
}

//=============================================================================
// �e���f���̐ݒ�֐�
//=============================================================================
void CModel::SetParentModel(CModel * pParentModel)
{
	//�e���f���̃|�C���^��ݒ�
	m_ModelData.pParent = pParentModel;
}

//=============================================================================
// ���f���̐ݒ�֐�
//=============================================================================
void CModel::SetModel(D3DXVECTOR3 Position, D3DXVECTOR3 Rotation, D3DXVECTOR3 Size)
{
	//�ʒu��ݒ肷��
	SetPosition(Position);
	//��]�l��ݒ肷��
	SetRotation(Rotation);
	//�T�C�Y��ݒ肷��
	SetSize(Size);
}

//=============================================================================
// �e�N�X�`���̊��蓖�Ċ֐�
//=============================================================================
void CModel::BindTexture(LPDIRECT3DTEXTURE9 pTexture, int nCount)
{
	//�e�N�X�`���̃|�C���^��ݒ肷��
	m_ModelData.pTexture[nCount] = pTexture;
}
