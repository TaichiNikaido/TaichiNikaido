//=============================================================================
//
// ���C�t��UI [ui_life.cpp]
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
#include "ui_life.h"
#include "gauge.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INITIAL_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))	//�ʒu�̏����l
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))		//�T�C�Y�̏����l
#define INITIAL_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	//�F�̏����l
#define MINIMUM_LIFE (0)								//�̗͂̍ŏ��l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLifeUI::CLifeUI()
{
	m_Position = INITIAL_POSITION;						//�ʒu
	m_Size = INITIAL_SIZE;								//�T�C�Y
	m_Color = INITIAL_COLOR;							//�F
	m_nMaxLife = MINIMUM_LIFE;							//�̗͂̍ő�l
	m_nLife = MINIMUM_LIFE;								//�̗�
	memset(m_apDataPass,NULL,sizeof(m_apDataPass));		//�f�[�^�X�N���v�g�̃p�X
	m_pGauge = NULL;									//�Q�[�W�̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLifeUI::~CLifeUI()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CLifeUI::Init(void)
{
	//�����Q�[�W�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pGauge != NULL)
	{
		//�Q�[�W�ɒl�̍ő�l��ݒ�
		m_pGauge->SetMaxValue(m_nMaxLife);
		//�Q�[�W�ɒl��ݒ�
		m_pGauge->SetValue(m_nLife);
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CLifeUI::Uninit(void)
{
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CLifeUI::Update(void)
{
	//�����Q�[�W�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pGauge != NULL)
	{
		//�Q�[�W�ɒl�̍ő�l��ݒ�
		m_pGauge->SetMaxValue(m_nMaxLife);
		//�Q�[�W�ɒl��ݒ�
		m_pGauge->SetValue(m_nLife);
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CLifeUI::Draw(void)
{
}

//=============================================================================
// �f�[�^�ǂݍ��݊֐�
//=============================================================================
void CLifeUI::DataLoad(void)
{
	char aReadText[MAX_TEXT];			//�ǂݍ��񂾃e�L�X�g
	char aCurrentText[MAX_TEXT];		//���݂̃e�L�X�g
	char aUnnecessaryText[MAX_TEXT];	//�s�K�v�ȃe�L�X�g
	memset(aReadText, NULL, sizeof(aReadText));
	memset(aCurrentText, NULL, sizeof(aCurrentText));
	memset(aUnnecessaryText, NULL, sizeof(aUnnecessaryText));
	//�t�@�C���̃|�C���^
	FILE *pFile = NULL;
	//�����t�@�C���̃|�C���^��NULL�̏ꍇ
	if (pFile == NULL)
	{
		//�t�@�C���̓ǂݍ���
		pFile = fopen(m_apDataPass[0], "r");
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
							//�T�C�Y���̓ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Position.x, &m_Position.y, &m_Position.z);
						}
						//���݂̃e�L�X�g��SIZE��������
						if (strcmp(aCurrentText, "SIZE") == 0)
						{
							//�T�C�Y���̓ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Size.x, &m_Size.y, &m_Size.z);
						}
						//���݂̃e�L�X�g��COLOR��������
						if (strcmp(aCurrentText, "COLOR") == 0)
						{
							//�T�C�Y���̓ǂݍ���
							sscanf(aReadText, "%s %s %f %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Color.r, &m_Color.g, &m_Color.b, &m_Color.a);
						}
					}
				}
			}
		}
		//�t�@�C�������
		fclose(pFile);
	}
}
