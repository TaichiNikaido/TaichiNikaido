//=============================================================================
//
// �G [enemy.cpp]
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
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MINIMUM_LIFE (0)	//�̗͂̍ŏ��l
#define MINIMUM_ATTACK (0)	//�U���͂̍ŏ��l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy()
{
	m_Move = INITIAL_D3DXVECTOR3;							//�ړ���
	m_CollisionSize = INITIAL_D3DXVECTOR3;					//�Փ˔���p�T�C�Y
	m_nLife = MINIMUM_LIFE;									//�̗�
	m_nAttack = MINIMUM_ATTACK;								//�U����
	memset(m_apScriptPass, NULL, sizeof(m_apScriptPass));	//�X�N���v�g�̃p�X
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CEnemy::Init(void)
{
	//�f�[�^�ǂݍ��݊֐��Ăяo��
	DataLoad();
	//�L�����N�^�[�̏����������֐��Ăяo��
	CCharacter::Init();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CEnemy::Uninit(void)
{
	//�L�����N�^�[�̏I�������֐��Ăяo��
	CCharacter::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CEnemy::Update(void)
{
	//�L�����N�^�[�̍X�V�����֐��Ăяo��
	CCharacter::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CEnemy::Draw(void)
{
	//�L�����N�^�[�̕`�揈���֐��Ăяo��
	CCharacter::Draw();
}

//=============================================================================
// �q�b�g�����֐�
//=============================================================================
void CEnemy::Hit(void)
{
}

//=============================================================================
// �̗͌��Z�����֐�
//=============================================================================
void CEnemy::SubLife(void)
{
}

//=============================================================================
// �f�[�^�ǂݍ��݊֐�
//=============================================================================
void CEnemy::DataLoad(void)
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
		pFile = fopen(m_apScriptPass[0], "r");
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
							//���݂̃e�L�X�g��Position��������
							if (strcmp(aCurrentText, "Position") == 0)
							{
								//�ʒu���̓ǂݍ���
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Position.x, &Position.y, &Position.z);
								//�ʒu��ݒ肷��
								SetPosition(Position);
							}
							//���݂̃e�L�X�g��Size��������
							if (strcmp(aCurrentText, "Size") == 0)
							{
								//�T�C�Y���̓ǂݍ���
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Size.x, &Size.y, &Size.z);
								//�T�C�Y��ݒ肷��
								SetSize(Size);
							}
							//���݂̃e�L�X�g��CollisionSize��������
							if (strcmp(aCurrentText, "CollisionSize") == 0)
							{
								//�Փ˔���p�T�C�Y���̓ǂݍ���
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &CollisionSize.x, &CollisionSize.y, &CollisionSize.z);
								//�Փ˔���p�T�C�Y�̐ݒ�
								SetCollisionSize(CollisionSize);
							}
							//���݂̃e�L�X�g��Rotation��������
							if (strcmp(aCurrentText, "Rotation") == 0)
							{
								//��]���̓ǂݍ���
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Rotation.x, &Rotation.y, &Rotation.z);
								//��]��ݒ肷��
								SetRotation(Rotation);
							}
							//���݂̃e�L�X�g��Move��������
							if (strcmp(aCurrentText, "Move") == 0)
							{
								//�ړ��ʂ̓ǂݍ���
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Move.x, &Move.y, &Move.z);
								//�ړ��ʂ̓ǂݍ���
								SetMove(Move);
							}
							//���݂̃e�L�X�g��Life��������
							if (strcmp(aCurrentText, "Life") == 0)
							{
								//�̗͏��̓ǂݍ���
								sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &nLife);
								//�̗͂̐ݒ�
								SetLife(nLife);
							}
							//���݂̃e�L�X�g��Attack��������
							if (strcmp(aCurrentText, "Attack") == 0)
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
}
