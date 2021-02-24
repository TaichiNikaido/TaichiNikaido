//=============================================================================
//
// �� [object_house.cpp]
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
#include "renderer.h"
#include "object_corpse.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PASS ("Data/Model/CorpseSW.x")					//���f���X�N���v�g�̃p�X
#define SCRIPT_PASS ("Data/Script/Corpse/Data.txt")				//�Ƃ̃X�N���v�g�̃p�X
#define INITIAL_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))			//�ʒu�̏����l
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))				//�T�C�Y�̏����l
#define INITIAL_COLLISION_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//�Փ˔���p�T�C�Y�̏����l
#define INITIAL_ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))			//��]�̏����l
#define INITIAL_LIFE (0)										//�̗͂̏����l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODEL_DATA CCorpse::m_ModelData = {};			//���f���f�[�^�̃|�C���^
D3DXMATERIAL * CCorpse::m_pMaterial = NULL;				//�}�e���A���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCorpse::CCorpse()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCorpse::~CCorpse()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CCorpse::ModelLoad(void)
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
void CCorpse::ModelUnload(void)
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
CCorpse * CCorpse::Create(D3DXVECTOR3 Position,D3DXVECTOR3 Rotation)
{
	//�r�̃|�C���^
	CCorpse * pCorpse = NULL;
	//�r�̃|�C���^��NULL�̏ꍇ
	if (pCorpse == NULL)
	{
		//�r�̃������m��
		pCorpse = new CCorpse;
	}
	//�r�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (pCorpse != NULL)
	{
		//�r�̈ʒu��ݒ肷��
		pCorpse->SetPosition(Position);
		//�r�̉�]��ݒ肷��
		pCorpse->SetRotation(Rotation);
		//�r�̏����������֐��Ăяo��
		pCorpse->Init();
	}
	//�r�̃|�C���^��Ԃ�
	return pCorpse;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CCorpse::Init(void)
{
	//���f���f�[�^�̐ݒ�
	SetModelData(m_ModelData);
	//�f�[�^���[�h�����֐��Ăяo��
	DataLoad();
	//�I�u�W�F�N�g�̏����������֐��Ăяo��
	CObject::Init();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CCorpse::Uninit(void)
{
	//�I�u�W�F�N�g�̏I�������֐��Ăяo��
	CObject::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CCorpse::Update(void)
{
	//�I�u�W�F�N�g�̍X�V�����֐��Ăяo��
	CObject::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CCorpse::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈���֐��Ăяo��
	CObject::Draw();
}

//=============================================================================
// �f�[�^�ǂݍ��݊֐�
//=============================================================================
void CCorpse::DataLoad(void)
{
	D3DXVECTOR3 Size = INITIAL_SIZE;						//�T�C�Y
	D3DXVECTOR3 CollisionSize = INITIAL_COLLISION_SIZE;		//�Փ˔���p�T�C�Y
	int nLife = INITIAL_LIFE;								//�̗�
	char aReadText[MAX_TEXT];								//�ǂݍ��񂾃e�L�X�g
	char aCurrentText[MAX_TEXT];							//���݂̃e�L�X�g
	char aUnnecessaryText[MAX_TEXT];						//�s�K�v�ȃe�L�X�g
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
						//���݂̃e�L�X�g��SIZE��������
						if (strcmp(aCurrentText, "SIZE") == 0)
						{
							//�T�C�Y���̓ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Size.x, &Size.y, &Size.z);
							//�T�C�Y��ݒ肷��
							SetSize(Size);
						}
						//���݂̃e�L�X�g��COLLISION_SIZE��������
						if (strcmp(aCurrentText, "COLLISION_SIZE") == 0)
						{
							//�Փ˔���p�T�C�Y���̓ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &CollisionSize.x, &CollisionSize.y, &CollisionSize.z);
							//�Փ˔���p�T�C�Y�̐ݒ�
							SetCollisionSize(CollisionSize);
						}
					}
				}
			}
		}
		//�t�@�C�������
		fclose(pFile);
	}
}
