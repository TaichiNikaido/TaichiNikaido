//=============================================================================
//
// ���[�V���� [motion.cpp]
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
#include "motion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INITIAL_POSITON (D3DXVECTOR3(0.0f,0.0f,0.0f))				//�ʒu�̏����l
#define INITIAL_POSITION_ORIGINAL (D3DXVECTOR3(0.0f,0.0f,0.0f))		//�����ʒu�̏����l
#define INITIAL_POSITION_DIFFERENCE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//�ʒu�̍����̏����l
#define INITIAL_DIRECTION_DIFFERENCE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//�����̍����̏����l
#define INITIAL_ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))				//��]�̏����l
#define INITIAL_ROTATION_DIFFERENCE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//��]�̍����̏����l
#define INITIAL_INDEX (0)											//���f���ԍ��̏����l
#define INITIAL_PARENTS (0)											//���f���̐e�ԍ�
#define INITIAL_NUMKEY (0)											//���[�V�����L�[���̏����l
#define INITIAL_FLAME (0)											//�t���[�����̏����l
#define INITIAL_CURRENT_KEY (1)										//���݂̃L�[��
#define INITIAL_ADD_CHANGE_FLAME (1)								//���[�V�����ύX���ɉ��Z����t���[��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMotion::CMotion()
{
	m_MotionState = MOTION_IDLE;					//���[�V�������
	m_MotionOldState = MOTION_IDLE;					//�Â����[�V�������
	m_nAddChangeFreme = INITIAL_ADD_CHANGE_FLAME;	//���[�V�����ύX���ɉ��Z����t���[��
	m_nFrame = INITIAL_FLAME;						//�t���[����
	m_nCurrentKey = INITIAL_CURRENT_KEY;			//���݂̃L�[��
	m_bChange = false;								//�ύX������
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		m_ModelParent[nCount].nIndex = INITIAL_INDEX;							//���f���ԍ�
		m_ModelParent[nCount].nParents = INITIAL_PARENTS;						//���f���̐e�ԍ�
		m_ModelParent[nCount].Position = INITIAL_POSITON;						//�ʒu		
		m_ModelParent[nCount].PositionOrigin = INITIAL_POSITION_ORIGINAL;		//�����ʒu
		m_ModelParent[nCount].Rotation = INITIAL_ROTATION;						//��]
		m_NumPositionDifference[nCount] = INITIAL_POSITION_DIFFERENCE;			//�ʒu�̍���
		m_NumDirectionDifference[nCount] = INITIAL_DIRECTION_DIFFERENCE;		//�����̍���
		m_NumRotationDifference[nCount] = INITIAL_ROTATION_DIFFERENCE;			//��]�̍���
	}
	//���[�V�����̍ő吔����
	for (int nCountMotion = 0; nCountMotion < MOTION_MAX; nCountMotion++)
	{
		m_Motion[nCountMotion].bLoop = false;				//���[�v���邩
		m_Motion[nCountMotion].nNumKey = INITIAL_NUMKEY;	//���[�V�����L�[��
		//���[�V�����L�[�̍ő吔
		for (int nCountKey = 0; nCountKey < MOTIONKEY_SET_MAX; nCountKey++)
		{
			m_Motion[nCountMotion].KeyInformation[nCountKey].nFrame = INITIAL_FLAME;	//�t���[����
			//�p�[�c�̍ő吔����
			for (int nCountParts = 0; nCountParts < MAX_PARTS; nCountParts++)
			{
				m_Motion[nCountMotion].KeyInformation[nCountKey].Position[nCountParts] = INITIAL_POSITON;	//�ʒu
				m_Motion[nCountMotion].KeyInformation[nCountKey].Rotation[nCountParts] = INITIAL_ROTATION;	//��]
			}
		}
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMotion::~CMotion()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CMotion * CMotion::Create(void)
{
	//���[�V�����̃|�C���^
	CMotion * pMotion = NULL;
	//�������[�V�����̃|�C���^��NULL�̏ꍇ
	if (pMotion == NULL)
	{
		//���[�V�����̃������m��
		pMotion = new CMotion;
	}
	//���[�V�����̃|�C���^��Ԃ�
	return pMotion;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CMotion::Uninit(void)
{
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CMotion::Update(void)
{
	// ���[�V������1�t���[���O�̃��[�V�����ƈ������
	if (m_MotionOldState != m_MotionState)
	{
		m_nFrame = 0;
		m_nCurrentKey = 0;
	}
	for (int nCntMotion = 0; nCntMotion < MAX_PARTS; nCntMotion++)
	{
		//�t���[���J�n���ɁA�ύX��̉�]�̒l��ʒu�̒l�Ȃǂ�ݒ�
		if (m_nFrame == 0)
		{
			m_NumPositionDifference[nCntMotion] = ((m_Motion[m_MotionState].KeyInformation[m_nCurrentKey].Position[nCntMotion] -
				(m_ModelParent[nCntMotion].Position - m_ModelParent[nCntMotion].PositionOrigin)) / float(m_Motion[m_MotionState].KeyInformation[m_nCurrentKey].nFrame));

			m_NumDirectionDifference[nCntMotion] = m_Motion[m_MotionState].KeyInformation[m_nCurrentKey].Rotation[nCntMotion] - m_ModelParent[nCntMotion].Rotation;

			m_NumRotationDifference[nCntMotion] = (m_NumDirectionDifference[nCntMotion] / float(m_Motion[m_MotionState].KeyInformation[m_nCurrentKey].nFrame));
		}
		// �ύX��̉�]�̒l��ʒu�̒l�����Z
		m_ModelParent[nCntMotion].Position += m_NumPositionDifference[nCntMotion];
		m_ModelParent[nCntMotion].Rotation += m_NumRotationDifference[nCntMotion];

		if (m_ModelParent[nCntMotion].Rotation.x >= D3DXToRadian(180.0f) && m_bChange == false)//���̒l�𒴂���Ɖ��Ȃ��Ȃ�̂Ō��Z���Ă���
		{
			m_ModelParent[nCntMotion].Rotation.x = D3DXToRadian(-180.0f);
			m_bChange = true;
		}
		if (m_ModelParent[nCntMotion].Rotation.x <= D3DXToRadian(-180.0f) && m_bChange == false)//���̒l�𒴂���Ɖ��Ȃ��Ȃ�̂Ō��Z���Ă���
		{
			m_ModelParent[nCntMotion].Rotation.x = D3DXToRadian(180.0f);
			m_bChange = true;
		}

		if (m_ModelParent[nCntMotion].Rotation.y >= D3DXToRadian(180.0f) && m_bChange == false)//���̒l�𒴂���Ɖ��Ȃ��Ȃ�̂Ō��Z���Ă���
		{
			m_ModelParent[nCntMotion].Rotation.y = D3DXToRadian(-180.0f);
			m_bChange = true;
		}
		if (m_ModelParent[nCntMotion].Rotation.y <= D3DXToRadian(-180.0f) && m_bChange == false)//���̒l�𒴂���Ɖ��Ȃ��Ȃ�̂Ō��Z���Ă���
		{
			m_ModelParent[nCntMotion].Rotation.y = D3DXToRadian(180.0f);
			m_bChange = true;
		}

		if (m_ModelParent[nCntMotion].Rotation.z >= D3DXToRadian(180.0f) && m_bChange == false)//���̒l�𒴂���Ɖ��Ȃ��Ȃ�̂Ō��Z���Ă���
		{
			m_ModelParent[nCntMotion].Rotation.z = D3DXToRadian(-180.0f);
			m_bChange = true;
		}
		if (m_ModelParent[nCntMotion].Rotation.z <= D3DXToRadian(-180.0f) && m_bChange == false)//���̒l�𒴂���Ɖ��Ȃ��Ȃ�̂Ō��Z���Ă���
		{
			m_ModelParent[nCntMotion].Rotation.z = D3DXToRadian(180.0f);
			m_bChange = true;
		}
	}
	// ���݂̃��[�V�����̋L�^
	m_MotionOldState = m_MotionState;
	// ���[�v����Ƃ�
	if (m_nFrame >= m_Motion[m_MotionState].KeyInformation[m_nCurrentKey].nFrame && m_Motion[m_MotionState].bLoop == 1)
	{
		m_nFrame = 0;
		m_bChange = false;
		m_nCurrentKey++;
		// �L�[���L�^����Ă���L�[���傫���Ȃ�����
		if (m_nCurrentKey >= m_Motion[m_MotionState].nNumKey)
		{
			m_nCurrentKey = 0;
		}
	}
	// ���[�v���Ȃ��Ƃ�
	else if (m_nFrame >= m_Motion[m_MotionState].KeyInformation[m_nCurrentKey].nFrame && m_Motion[m_MotionState].bLoop == 0)
	{
		m_nFrame = 0;
		m_bChange = false;
		m_nCurrentKey++;

		// �L�[���L�^����Ă���L�[���傫���Ȃ�����
		if (m_nCurrentKey >= m_Motion[m_MotionState].nNumKey)
		{
			for (int nCntMotion = 0; nCntMotion < MAX_PARTS; nCntMotion++)
			{
				m_NumPositionDifference[nCntMotion] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_NumRotationDifference[nCntMotion] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			m_nCurrentKey = 0;
			m_MotionState = MOTION_IDLE;
		}
	}
	else
	{
		m_nFrame += m_nAddChangeFreme;
	}
}

//=============================================================================
// ���[�V�����ǂݍ��݊֐�
//=============================================================================
void CMotion::LoadMotion(const char * cText)
{
	int  nCntLoad = 0;				//�ǂݍ��񂾃J�E���g
	int	 nCntKey = 0;				//�L�[�̐��̃J�E���g
	int	 nCntMotion = 0;			//���[�V�����̐��̃J�E���g
	char aReadText[MAX_TEXT];		//�����Ƃ��ēǂݎ��p
	char aCurrentText[MAX_TEXT];	//�����̔��ʗp
	char aDie[MAX_TEXT];			//�g��Ȃ�����
	//�t�@�C���̃|�C���^
	FILE * pFile = NULL;
	//�����t�@�C���̃|�C���^��NULL�̏ꍇ
	if (pFile == NULL)
	{
		//�t�@�C�����J��
		pFile = fopen(cText, "r");
	}
	//�����t�@�C���̃|�C���^��NULL����Ȃ��ꍇ
	if (pFile != NULL)
	{
		//SCRIPT�̕�����������܂�
		while (strcmp(aCurrentText, "SCRIPT") != 0)
		{
			//�e�L�X�g����aReadText��������ǂݍ���
			fgets(aReadText, sizeof(aReadText), pFile);
			//�ǂݍ��񂾕�������aCurrentText�Ɋi�[
			sscanf(aReadText, "%s", &aCurrentText);
		}
		//aCurrentText��SCRIPT��������
		if (strcmp(aCurrentText, "SCRIPT") == 0)
		{
			//END_SCRIPT�̕�����������܂�
			while (strcmp(aCurrentText, "END_SCRIPT") != 0)
			{
				//�e�L�X�g����aReadText��������ǂݍ���
				fgets(aReadText, sizeof(aReadText), pFile);
				// �ǂݍ��񂾕�������aCurrentText�Ɋi�[
				sscanf(aReadText, "%s", &aCurrentText);

				//aCurrentText��MOTIONSET��������
				if (strcmp(aCurrentText, "MOTIONSET") == 0)
				{
					//END_MOTIONSET�̕�����������܂�
					while (strcmp(aCurrentText, "END_MOTIONSET") != 0)
					{
						//�e�L�X�g����aReadText��������ǂݍ���
						fgets(aReadText, sizeof(aReadText), pFile);
						//�ǂݍ��񂾕�������aCurrentText�Ɋi�[
						sscanf(aReadText, "%s", &aCurrentText);

						//aCurrentText��MOTIONSET��������
						if (strcmp(aCurrentText, "LOOP") == 0)
						{
							//m_nLoop�Ƀ��[�v�����邩�i�[
							sscanf(aReadText, "%s %s %d", &aDie, &aDie, (int *)&m_Motion[nCntMotion].bLoop);
						}

						//aCurrentText��NUM_KEY��������
						if (strcmp(aCurrentText, "NUM_KEY") == 0)
						{
							//m_nNumKey�ɃL�[�̐����i�[
							sscanf(aReadText, "%s %s %d", &aDie, &aDie, &m_Motion[nCntMotion].nNumKey);
						}

						//aCurrentText��KEYSET��������
						if (strcmp(aCurrentText, "KEYSET") == 0)
						{
							//END_KEYSET�̕�����������܂�
							while (strcmp(aCurrentText, "END_KEYSET") != 0)
							{
								//�e�L�X�g����aReadText��������ǂݍ���
								fgets(aReadText, sizeof(aReadText), pFile);
								//�ǂݍ��񂾕�������aCurrentText�Ɋi�[
								sscanf(aReadText, "%s", &aCurrentText);

								//aCurrentText��FRAME��������
								if (strcmp(aCurrentText, "FRAME") == 0)
								{
									//m_nFrame�Ƀt���[�������i�[
									sscanf(aReadText, "%s %s %d", &aDie, &aDie, &m_Motion[nCntMotion].KeyInformation[nCntKey].nFrame);
								}
								//aCurrentText��KEY��������
								if (strcmp(aCurrentText, "KEY") == 0)
								{
									//END_KEY�̕�����������܂�
									while (strcmp(aCurrentText, "END_KEY") != 0)
									{
										//�e�L�X�g����aReadText��������ǂݍ���
										fgets(aReadText, sizeof(aReadText), pFile);
										//�ǂݍ��񂾕�������aCurrentText�Ɋi�[
										sscanf(aReadText, "%s", &aCurrentText);

										//aCurrentText��POS��������
										if (strcmp(aCurrentText, "POS") == 0)
										{
											//m_pos�ɍ��W���i�[
											sscanf(aReadText, "%s %s %f %f %f", &aDie, &aDie,
												&m_Motion[nCntMotion].KeyInformation[nCntKey].Position[nCntLoad].x,
												&m_Motion[nCntMotion].KeyInformation[nCntKey].Position[nCntLoad].y,
												&m_Motion[nCntMotion].KeyInformation[nCntKey].Position[nCntLoad].z);
										}
										//aCurrentText��ROT��������
										if (strcmp(aCurrentText, "ROT") == 0)
										{
											//m_rot�ɉ�]���i�[
											sscanf(aReadText, "%s %s %f %f %f", &aDie, &aDie,
												&m_Motion[nCntMotion].KeyInformation[nCntKey].Rotation[nCntLoad].x,
												&m_Motion[nCntMotion].KeyInformation[nCntKey].Rotation[nCntLoad].y,
												&m_Motion[nCntMotion].KeyInformation[nCntKey].Rotation[nCntLoad].z);
										}
									}
									//�J�E���g�̉��Z
									nCntLoad++;
								}
							}
							//�ǂݍ��񂾃J�E���g�̏�����
							nCntLoad = 0;
							//�J�E���g�̉��Z
							nCntKey++;
						}
					}
					//�L�[�̐��̏�����
					nCntKey = 0;
					//�J�E���g�̉��Z
					nCntMotion++;
				}
			}
			//�t�@�C�������
			fclose(pFile);
		}
	}
}

//=============================================================================
// ���f�����ǂݍ��݊֐�
//=============================================================================
void CMotion::LoadModelInformation(const char * cText)
{
	int  nCntLoad = 0;				//�ǂݍ��񂾃J�E���g
	char aReadText[MAX_TEXT];		//�����Ƃ��ēǂݎ��p
	char aCurrentText[MAX_TEXT];	//�����̔��ʗp
	char aDie[MAX_TEXT];			//�g��Ȃ�����
	//�t�@�C���̃|�C���^
	FILE *pFile = NULL;
	//�����t�@�C����NULL�̏ꍇ
	if (pFile == NULL)
	{
		//�t�@�C�����J��
		pFile = fopen(cText, "r");
	}
	//�����t�@�C����NULL����Ȃ��ꍇ
	if (pFile != NULL)
	{
		// CHARACTERSET�̕�����������܂�
		while (strcmp(aCurrentText, "CHARACTERSET") != 0)
		{
			// �e�L�X�g����aReadText���������󂯎��
			fgets(aReadText, sizeof(aReadText), pFile);
			// aReadText��aCurrentText�Ɋi�[
			sscanf(aReadText, "%s", &aCurrentText);
		}

		// aCurrentText��CHARACTERSET�̎�
		if (strcmp(aCurrentText, "CHARACTERSET") == 0)
		{
			// aCurrentText��END_CHARACTERSET�ɂȂ�܂�
			while (strcmp(aCurrentText, "END_CHARACTERSET") != 0)
			{
				// �e�L�X�g����aReadText���������󂯎��
				fgets(aReadText, sizeof(aReadText), pFile);
				// aReadText��aCurrentText�Ɋi�[
				sscanf(aReadText, "%s", &aCurrentText);

				// aCurrentText�����s�̎�
				if (strcmp(aCurrentText, "\n") == 0)
				{
				}
				// aCurrentText��PARTSSET�̎�
				else if (strcmp(aCurrentText, "PARTSSET") == 0)
				{
					// aCurrentText��END_PARTSSET�ɂȂ�܂�
					while (strcmp(aCurrentText, "END_PARTSSET") != 0)
					{
						// �e�L�X�g����aReadText���������󂯎��
						fgets(aReadText, sizeof(aReadText), pFile);
						// aReadText��aCurrentText�Ɋi�[
						sscanf(aReadText, "%s", &aCurrentText);

						// aCurrentText��INDEX�ɂȂ�܂�
						if (strcmp(aCurrentText, "INDEX") == 0)
						{
							// �e�L�X�g��INDEX�̒l��m_nIndex�Ɋi�[
							sscanf(aReadText, "%s %s %d", &aDie, &aDie, &m_ModelParent[nCntLoad].nIndex);
						}

						// aCurrentText��PARENT�ɂȂ�܂�
						if (strcmp(aCurrentText, "PARENT") == 0)
						{
							// �e�L�X�g��PARENT�̒l��m_nParents�Ɋi�[
							sscanf(aReadText, "%s %s %d", &aDie, &aDie, &m_ModelParent[nCntLoad].nParents);
						}

						// aCurrentText��POS�ɂȂ�܂�
						if (strcmp(aCurrentText, "POS") == 0)
						{
							// �e�L�X�g��POS�̒l��m_posOrigin�Ɋi�[
							sscanf(aReadText, "%s %s %f %f %f", &aDie, &aDie,
								&m_ModelParent[nCntLoad].PositionOrigin.x,
								&m_ModelParent[nCntLoad].PositionOrigin.y,
								&m_ModelParent[nCntLoad].PositionOrigin.z);

							// m_posOrigin�̒l��m_pos�ɑ��
							m_ModelParent[nCntLoad].Position = m_ModelParent[nCntLoad].PositionOrigin;
						}

						// aCurrentText��ROT�ɂȂ�܂�
						if (strcmp(aCurrentText, "ROT") == 0)
						{
							// �e�L�X�g��ROT�̒l��m_rot�Ɋi�[
							sscanf(aReadText, "%s %s %f %f %f", &aDie, &aDie,
								&m_ModelParent[nCntLoad].Rotation.x,
								&m_ModelParent[nCntLoad].Rotation.y,
								&m_ModelParent[nCntLoad].Rotation.z);
						}
					}
					// �J�E���g���Z
					nCntLoad++;
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
}
