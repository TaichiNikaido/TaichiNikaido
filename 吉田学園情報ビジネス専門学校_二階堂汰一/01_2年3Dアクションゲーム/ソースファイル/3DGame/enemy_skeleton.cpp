//=============================================================================
//
// �X�P���g�� [enemy_skeleton.cpp]
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
#include "mode_game.h"
#include "renderer.h"
#include "model.h"
#include "enemy_skeleton.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PASS ("Data/Script/Enemy/Skeleton/Model.txt")		//���f���X�N���v�g�̃p�X
#define SCRIPT_PASS ("Data/Script/Enemy/Skeleton/Data.txt")		//�X�P���g���̃X�N���v�g�̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODEL_DATA CSkeleton::m_aModelData[MAX_PARTS] = {};		//���f���f�[�^�̃|�C���^
D3DXMATERIAL * CSkeleton::m_pMaterial = NULL;					//�}�e���A���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSkeleton::CSkeleton()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSkeleton::~CSkeleton()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CSkeleton::ModelLoad(void)
{
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
				&m_aModelData[nCount].pBuffMat,
				NULL,
				&m_aModelData[nCount].nNumMat,
				&m_aModelData[nCount].pMesh);
			//�������f���̃}�e���A�����NULL����Ȃ��ꍇ
			if (m_aModelData[nCount].pBuffMat != NULL)
			{
				//�}�e���A���̃|�C���^���擾
				m_pMaterial = (D3DXMATERIAL *)m_aModelData[nCount].pBuffMat->GetBufferPointer();
				//���f���f�[�^������
				for (int nCountMat = 0; nCountMat < (int)m_aModelData[nCount].nNumMat; nCountMat++)
				{
					//�����t�@�C���l�[����NULL����Ȃ��ꍇ
					if (m_pMaterial[nCountMat].pTextureFilename != NULL)
					{
						//�e�N�X�`����ǂݍ���
						D3DXCreateTextureFromFile(pDevice, m_pMaterial[nCountMat].pTextureFilename, &m_aModelData[nCount].pTexture[nCountMat]);
					}
				}
			}
			//�|�C���^���̂Ă�
			pPass += MAX_TEXT;
		}
	}
	return S_OK;
}

//=============================================================================
// ���f���j���֐�
//=============================================================================
void CSkeleton::ModelUnload(void)
{
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���f�[�^�̃��[���h�ϊ��s��NULL����ȏꍇ
		if (m_aModelData[nCount].mtxWorld != NULL)
		{
			//�������f���f�[�^�̃}�e���A�����NULL����ȏꍇ
			if (m_aModelData[nCount].pBuffMat != NULL)
			{
				//���f���f�[�^�̃}�e���A������j��
				m_aModelData[nCount].pBuffMat->Release();
			}
			//�������f���f�[�^�̃��b�V�����NULL����ȏꍇ
			if (m_aModelData[nCount].pMesh != NULL)
			{
				//���f���f�[�^�̃��b�V������j��
				m_aModelData[nCount].pMesh->Release();
			}
			//�}�e���A���̍ő吔����
			for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
			{
				//�������f���f�[�^�̃e�N�X�`���̃|�C���^��NULL����ȏꍇ
				if (m_aModelData[nCount].pTexture[nCountTexture] != NULL)
				{
					//���f���f�[�^�̃e�N�X�`���̃|�C���^��j��
					m_aModelData[nCount].pTexture[nCountTexture]->Release();
				}
			}
		}
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CSkeleton * CSkeleton::Create()
{
	//�X�P���g���̃|�C���^
	CSkeleton * pEnemySkeleton = NULL;
	//�X�P���g���̃|�C���^��NULL�̏ꍇ
	if (pEnemySkeleton == NULL)
	{
		//�X�P���g���̃������m��
		pEnemySkeleton = new CSkeleton;
		//�X�P���g���̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pEnemySkeleton != NULL)
		{
			//�X�P���g���̏����������֐��Ăяo��
			pEnemySkeleton->Init();
		}
	}
	//�X�P���g���̃|�C���^��Ԃ�
	return pEnemySkeleton;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CSkeleton::Init(void)
{
	//���f���̃p�X��ݒ�
	SetMotionPass(MODEL_PASS);
	//���f���f�[�^�̐ݒ�
	SetModelData(m_aModelData);
	//�G�̏����������֐��Ăяo��
	CEnemy::Init();
	//�f�[�^�ǂݍ��݊֐��Ăяo��
	DataLoad();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CSkeleton::Uninit(void)
{
	//�G�̏I�������֐��Ăяo��
	CEnemy::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CSkeleton::Update(void)
{
	//�G�̍X�V�����֐��Ăяo��
	CEnemy::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CSkeleton::Draw(void)
{
	//�G�̕`�揈���֐��Ăяo��
	CEnemy::Draw();
}

//=============================================================================
// �f�[�^�ǂݍ��݊֐�
//=============================================================================
void CSkeleton::DataLoad(void)
{
	D3DXVECTOR3 Position = INITIAL_D3DXVECTOR3;				//�ʒu
	D3DXVECTOR3 Size = INITIAL_D3DXVECTOR3;					//�T�C�Y
	D3DXVECTOR3 CollisionSize = INITIAL_D3DXVECTOR3;		//�Փ˔���p�T�C�Y
	D3DXVECTOR3 Rotation = INITIAL_ROTATION;				//��]
	D3DXVECTOR3 Move = INITIAL_D3DXVECTOR3;					//�ړ���
	int nLife = 0;											//�̗�
	int nAttack = 0;										//�U����
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
						//���݂̃e�L�X�g��POS��������
						if (strcmp(aCurrentText, "POS") == 0)
						{
							//�ʒu���̓ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Position.x, &Position.y, &Position.z);
							//�ʒu��ݒ肷��
							SetPosition(Position);
						}
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
						//���݂̃e�L�X�g��ROT��������
						if (strcmp(aCurrentText, "ROT") == 0)
						{
							//��]���̓ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Rotation.x, &Rotation.y, &Rotation.z);
							//��]�̐ݒ�
							SetRotation(D3DXVECTOR3(D3DXToRadian(Rotation.x), D3DXToRadian(Rotation.y), D3DXToRadian(Rotation.z)));
						}
						//���݂̃e�L�X�g��MOVE��������
						if (strcmp(aCurrentText, "MOVE") == 0)
						{
							//�ړ��ʂ̓ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Move.x, &Move.y, &Move.z);
							//�ړ��ʂ̓ǂݍ���
							SetMove(Move);
						}
						//���݂̃e�L�X�g��LIFE��������
						if (strcmp(aCurrentText, "LIFE") == 0)
						{
							//�̗͏��̓ǂݍ���
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &nLife);
							//�̗͂̐ݒ�
							SetLife(nLife);
						}
						//���݂̃e�L�X�g��ATTACK��������
						if (strcmp(aCurrentText, "ATTACK") == 0)
						{
							//�U���͏��̓ǂݍ���
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &nAttack);
							//�U���͂̐ݒ�
							SetAttack(nAttack);
						}
					}
				}
			}
		}
		//�t�@�C�������
		fclose(pFile);
	}
}
