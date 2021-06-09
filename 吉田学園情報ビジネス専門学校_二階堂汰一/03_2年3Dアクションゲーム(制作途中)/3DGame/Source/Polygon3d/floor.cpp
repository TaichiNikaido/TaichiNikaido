//=============================================================================
//
// �� [floor.cpp]
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
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "floor.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCRIPT_PASS ("Data/Script/FloorData.txt")	//�v���C���[�f�[�^�̃X�N���v�g�̃p�X
#define TEXTURE_PASS ("Data/Texture/ground.png")	//�e�N�X�`���̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CFloor::m_pTexture = nullptr;	//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFloor::CFloor()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFloor::~CFloor()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CFloor::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,	//�f�o�C�X�ւ̃|�C���^
		TEXTURE_PASS,					//�t�@�C���̖��O
		&m_pTexture);					//�ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CFloor::TextureUnload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`����nullptr�ɂ���
		m_pTexture = nullptr;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CFloor * CFloor::Create()
{
	//���̃|�C���^
	CFloor * pFloor = nullptr;
	//���̃|�C���^��nullptr�̏ꍇ
	if (pFloor == nullptr)
	{
		//���̃������m��
		pFloor = new CFloor;
		//���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pFloor != nullptr)
		{
			//���̏����������֐��Ăяo��
			pFloor->Init();
		}
	}
	//���̃|�C���^��Ԃ�
	return pFloor;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CFloor::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�|���S��3D�̏����������֐��Ăяo��
	CPolygon3d::Init();
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	//�f�[�^�ǂݍ��݊֐��Ăяo��
	DataLoad();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CFloor::Uninit(void)
{
	//�|���S��3D�̏I�������֐��Ăяo��
	CPolygon3d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CFloor::Update(void)
{
	//�|���S��3D�̍X�V�����֐��Ăяo��
	CPolygon3d::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CFloor::Draw(void)
{
	//�|���S��3D�̕`�揈���֐��Ăяo��
	CPolygon3d::Draw();
}

//=============================================================================
// �f�[�^�ǂݍ��݊֐�
//=============================================================================
void CFloor::DataLoad(void)
{
	D3DXVECTOR3 Position = D3DXVECTOR3(0.0f,0.0f,0.0f);		//�ʒu
	D3DXVECTOR3 Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�T�C�Y
	D3DXVECTOR3 Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//��]
	char aReadText[MAX_TEXT];								//�ǂݍ��񂾃e�L�X�g
	char aCurrentText[MAX_TEXT];							//���݂̃e�L�X�g
	char aUnnecessaryText[MAX_TEXT];						//�s�K�v�ȃe�L�X�g
	memset(aReadText, NULL, sizeof(aReadText));
	memset(aCurrentText, NULL, sizeof(aCurrentText));
	memset(aUnnecessaryText, NULL, sizeof(aUnnecessaryText));
	//�t�@�C���̃|�C���^
	FILE *pFile = nullptr;
	//�����t�@�C���̃|�C���^��nullptr�̏ꍇ
	if (pFile == nullptr)
	{
		//�t�@�C���̓ǂݍ���
		pFile = fopen(SCRIPT_PASS, "r");
	}
	//�t�@�C�����J�����Ƃ��ł�����
	if (pFile != nullptr)
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
							//�ʒu���ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Position.x, &Position.y, &Position.z);
							//�ʒu��ݒ肷��
							SetPosition(Position);
						}
						//���݂̃e�L�X�g��SIZE��������
						if (strcmp(aCurrentText, "SIZE") == 0)
						{
							//�T�C�Y���ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Size.x, &Size.y, &Size.z);
							//�T�C�Y��ݒ肷��
							SetSize(Size);
						}
						//���݂̃e�L�X�g��ROT��������
						if (strcmp(aCurrentText, "ROT") == 0)
						{
							//��]���ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Rotation.x, &Rotation.y, &Rotation.z);
							//��]��ݒ肷��
							SetRotation(D3DXVECTOR3(D3DXToRadian(Rotation.x),D3DXToRadian(Rotation.y),D3DXToRadian(Rotation.z)));
						}
					}	
				}
			}
		}
		//�t�@�C�������
		fclose(pFile);
	}
}
