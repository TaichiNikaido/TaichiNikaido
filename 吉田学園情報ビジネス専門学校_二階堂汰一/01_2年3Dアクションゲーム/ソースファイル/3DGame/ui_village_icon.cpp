//=============================================================================
//
// UI�̃Q�[�W [ui_gauge.cpp]
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
#include "scene2d.h"
#include "ui_village_icon.h"
#include "stage.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/UI/VillageIcon.png")		//�e�N�X�`���̃p�X
#define SCRIPT_PASS ("Data/Script/UI/Village_Icon/Data.txt")	//�v���C���[�f�[�^�̃X�N���v�g�̃p�X
#define INITIAL_PATTERN_ANIME (0)								//�p�^�[���A�j��
#define INITIAL_ANIMATION_VALUE (0.0f)							//�A�j���[�V�����̏����l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CVillageIcon::m_pTexture = NULL;	//�e�N�X�`��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CVillageIcon::CVillageIcon()
{
	m_nPatternAnime = INITIAL_PATTERN_ANIME;		//�p�^�[���A�j��
	m_fAnimationValue = INITIAL_ANIMATION_VALUE;	//�A�j���[�V�����̒l
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CVillageIcon::~CVillageIcon()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CVillageIcon::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PASS,					// �t�@�C���̖��O
		&m_pTexture);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CVillageIcon::TextureUnload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`����NULL�ɂ���
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CVillageIcon * CVillageIcon::Create(void)
{
	//���̃A�C�R���̃|�C���^
	CVillageIcon * pVillageIcon = NULL;
	//���̃A�C�R����NULL�̏ꍇ
	if (pVillageIcon == NULL)
	{
		//���̃A�C�R���̃������m��
		pVillageIcon = new CVillageIcon;
	}
	//���̃A�C�R����NULL�ł͂Ȃ��ꍇ
	if (pVillageIcon != NULL)
	{
		//���̃A�C�R���̏����������֐��Ăяo��
		pVillageIcon->Init();
	}
	//���̃A�C�R���̃|�C���^��Ԃ�
	return pVillageIcon;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CVillageIcon::Init(void)
{
	//�f�[�^�ǂݍ��݊֐��Ăяo��
	DataLoad();
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_fAnimationValue * ICON_1, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_fAnimationValue * ICON_1 + m_fAnimationValue, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_fAnimationValue * ICON_1, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_fAnimationValue * ICON_1 + m_fAnimationValue, 1.0f);
	//2D�V�[���Ǘ������������֐��Ăяo��
	CScene2d::Init();
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CVillageIcon::Uninit(void)
{
	//2D�V�[���Ǘ��I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CVillageIcon::Update(void)
{
	//�X�e�[�W�̎擾
	CStage * pStage = CGameMode::GetStage();
	//���S�̂̃��C�t���擾����
	int nVillageLife = pStage->GetLife();
	//2D�V�[���Ǘ��X�V�����֐��Ăяo��
	CScene2d::Update();
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_fAnimationValue * ICON_1, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_fAnimationValue * ICON_1 + m_fAnimationValue, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_fAnimationValue * ICON_1, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_fAnimationValue * ICON_1 + m_fAnimationValue, 1.0f);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CVillageIcon::Draw(void)
{
	//2D�V�[���Ǘ��`�揈���֐��Ăяo��
	CScene2d::Draw();
}

//=============================================================================
// �f�[�^�ǂݍ��݊֐�
//=============================================================================
void CVillageIcon::DataLoad(void)
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
							//�ʒu�̏��ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Position.x, &Position.y, &Position.z);
							//�ʒu�̐ݒ�
							SetPosition(Position);
						}
						//���݂̃e�L�X�g��SIZE��������
						if (strcmp(aCurrentText, "SIZE") == 0)
						{
							//�T�C�Y�̏��ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Size.x, &Size.y, &Size.z);
							//�T�C�Y��ݒ肷��
							SetSize(Size);
						}
						//���݂̃e�L�X�g��ROT��������
						if (strcmp(aCurrentText, "ROT") == 0)
						{
							//��]���̓ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Rotation.x, &Rotation.y, &Rotation.z);
							//��]��ݒ肷��
							SetRotation(Rotation);
						}
						//���݂̃e�L�X�g��ANIMATION_VALUE��������
						if (strcmp(aCurrentText, "ANIMATION_VALUE") == 0)
						{
							//�A�j���[�V�����̒l���̓ǂݍ���
							sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fAnimationValue);
						}
					}
				}
			}
		}
		//�t�@�C�������
		fclose(pFile);
	}
}
