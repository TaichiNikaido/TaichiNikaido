//=============================================================================
//
// �c�[�����[�h [mode_tool.cpp]
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
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "tool.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx9.h"
#include "Imgui/imgui_impl_win32.h"
#include <d3d9.h>
#include <dinput.h>
#include <tchar.h>
#include "particle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTool::CTool()
{
	m_Position = INITIAL_D3DXVECTOR3;						//�ʒu
	m_Rotation = INITIAL_D3DXVECTOR3;						//��]
	m_Size = INITIAL_D3DXVECTOR3;							//�T�C�Y
	m_Move = INITIAL_D3DXVECTOR3;							//�ړ���
	m_Color = INITIAL_D3DXCOLOR;							//�F
	m_nLife = 0;											//�̗�
	m_nCreateInterval = 0;									//�����Ԋu
	m_nCreateTime = 0;										//��������
	m_fScale = 0.0f;										//�g�k
	m_fAngle = D3DXToRadian(0.0f);							//�p�x
	memset(m_aSaveTextName,NULL,sizeof(m_aSaveTextName));	//�Z�[�u�e�L�X�g�̖��O
	memset(m_aLoadTextName, NULL, sizeof(m_aLoadTextName));	//���[�h�e�L�X�g�̖��O
	m_bWindow = true;										//�E�B���h�E���g�p���Ă��邩
	m_bScale = false;										//�g�k���g�p���邩
	m_bLife = false;										//�̗͂��g�p���邩
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTool::~CTool()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CTool::Init(void)
{
	m_nCreateInterval = 1;				//�����Ԋu
	m_nCreateTime = 10;					//��������
	m_fAngle = 360.0f;	//�p�x
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CTool::Uninit(void)
{
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CTool::Update(void)
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	if (m_bWindow)
	{
		ImGui::Begin("Data");
		ImGui::DragFloat3("Position", (float*)&m_Position,1.0f);
		ImGui::DragFloat3("Rotation", (float*)&m_Rotation, 1.0f);
		ImGui::DragFloat3("Size", (float*)&m_Size, 1.0f);
		ImGui::DragFloat3("Move", (float*)&m_Move, 1.0f);
		ImGui::ColorEdit4("Color", (float*)&m_Color);
		ImGui::DragInt("CreateInterval", (int*)&m_nCreateInterval,1,1,10);
		ImGui::DragFloat("Angle", (float*)&m_fAngle, 1.0f, 1.0f, 360.0f);
		ImGui::Checkbox("UseScale", (bool*)&m_bScale);
		if (m_bScale == true)
		{
			ImGui::DragFloat("ScaleValue", (float*)&m_fScale, 0.01f);
		}
		ImGui::Checkbox("UseLife", (bool*)&m_bLife);
		if (m_bLife == true)
		{
			ImGui::DragInt("Life", (int*)&m_nLife, 1, 1, 100);
		}
		ImGui::InputTextWithHint("SaveText", "Save_Text_Name", m_aSaveTextName,sizeof(m_aSaveTextName));
		if (ImGui::Button("Save"))
		{
			TextSave();
		}
		ImGui::InputTextWithHint("LoadText", "Load_Text_Name", m_aLoadTextName, sizeof(m_aLoadTextName));
		if (ImGui::Button("Load"))
		{
			TextLoad();
		}
		ImGui::End();
	}
	ImGui::EndFrame();

	if (m_nCreateTime % m_nCreateInterval == 0)
	{
		CParticle::Create();
	}
	m_nCreateTime++;
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CTool::Draw(void)
{
}

//=============================================================================
// �e�L�X�g�Z�[�u�����֐�
//=============================================================================
void CTool::TextSave(void)
{
	//�t�@�C���̃|�C���^
	FILE * pFile = NULL;
	char aSaveText[MAX_TEXT];	//�������񂾃e�L�X�g
	memset(aSaveText, NULL, sizeof(aSaveText));
	//��������
	sprintf(aSaveText, "%s.txt", m_aSaveTextName);
	// NULL�̏ꍇ
	if (pFile == NULL)
	{
		// �t�@�C���̏����o��
		pFile = fopen(aSaveText, "w");
		// �t�@�C�����󂶂�Ȃ���
		if (pFile != NULL)
		{
			fprintf(pFile, "#==============================================================================\n");
			fprintf(pFile, "#\n");
			fprintf(pFile, "# �w�x [%s.txt]\n", m_aSaveTextName);
			fprintf(pFile, "#  Author :\n");
			fprintf(pFile, "#\n");
			fprintf(pFile, "#==============================================================================\n");
			fprintf(pFile, "SCRIPT #���̍s�͐�΂ɏ����Ȃ�����!\n");
			fprintf(pFile, "\n");
			fprintf(pFile, "#================================================\n");
			fprintf(pFile, "# �p�����[�^�̐ݒ�\n");
			fprintf(pFile, "#================================================\n");
			fprintf(pFile, "PARAMETER_SET\n");
			fprintf(pFile, "\n");
			fprintf(pFile, "Position = %.1f %.1f %.1f\n", m_Position.x, m_Position.y, m_Position.z);
			fprintf(pFile, "Rotation = %.1f %.1f %.1f\n", m_Rotation.x, m_Rotation.y, m_Rotation.z);
			fprintf(pFile, "Size = %.1f %.1f %.1f\n", m_Size.x, m_Size.y, m_Size.z);
			fprintf(pFile, "Move = %.1f %.1f %.1f\n", m_Move.x, m_Move.y, m_Move.z);
			fprintf(pFile, "Color = %.1f %.1f %.1f %.1f\n", m_Color.r, m_Color.g, m_Color.b, m_Color.a);
			fprintf(pFile, "Life = %d\n", m_nLife);
			fprintf(pFile, "CreateInterval = %d\n", m_nCreateInterval);
			fprintf(pFile, "\n");
			fprintf(pFile, "END_PARAMETER_SET\n");
			fprintf(pFile, "\n");
			fprintf(pFile, "END_SCRIPT #���̍s�͐�΂ɏ����Ȃ�����!\n");
			// �t�@�C�������
			fclose(pFile);

		}
	}
}

//=============================================================================
// �e�L�X�g���[�h�����֐�
//=============================================================================
void CTool::TextLoad(void)
{
	//char aReadText[MAX_TEXT];			//�ǂݍ��񂾃e�L�X�g
	//char aCurrentText[MAX_TEXT];		//���݂̃e�L�X�g
	//char aUnnecessaryText[MAX_TEXT];	//�s�K�v�ȃe�L�X�g
	//memset(aReadText, NULL, sizeof(aReadText));
	//memset(aCurrentText, NULL, sizeof(aCurrentText));
	//memset(aUnnecessaryText, NULL, sizeof(aUnnecessaryText));
	////�t�@�C���̃|�C���^
	//FILE *pFile = NULL;
	////�����t�@�C���̃|�C���^��NULL�̏ꍇ
	//if (pFile == NULL)
	//{
	//	//�t�@�C���̓ǂݍ���
	//	pFile = fopen(m_aLoadTextName, "r");
	//}
	////�t�@�C�����J�����Ƃ��ł�����
	//if (pFile != NULL)
	//{
	//	//SCRIPT�̕�����������
	//	while (strcmp(aCurrentText, "SCRIPT") != 0)
	//	{
	//		//�ǂݍ��񂾃e�L�X�g���i�[����
	//		fgets(aReadText, sizeof(aReadText), pFile);
	//		//�ǂݍ��񂾃e�L�X�g�����݂̃e�L�X�g�Ɋi�[
	//		sscanf(aReadText, "%s", &aCurrentText);
	//	}
	//	//���݂̃e�L�X�g��SCRIPT��������
	//	if (strcmp(aCurrentText, "SCRIPT") == 0)
	//	{
	//		//END_SCRIPT�̕�����������܂œǂ�
	//		while (strcmp(aCurrentText, "END_SCRIPT") != 0)
	//		{
	//			//�ǂݍ��񂾃e�L�X�g���i�[����
	//			fgets(aReadText, sizeof(aReadText), pFile);
	//			//�ǂݍ��񂾃e�L�X�g�����݂̃e�L�X�g�Ɋi�[
	//			sscanf(aReadText, "%s", &aCurrentText);
	//			//���݂̃e�L�X�g��PARAMETER_SET��������
	//			if (strcmp(aCurrentText, "PARAMETER_SET") == 0)
	//			{
	//				//END_PARAMETER_SET�̕�����������܂œǂ�
	//				while (strcmp(aCurrentText, "END_PARAMETER_SET") != 0)
	//				{
	//					//�ǂݍ��񂾃e�L�X�g���i�[����
	//					fgets(aReadText, sizeof(aReadText), pFile);
	//					//�ǂݍ��񂾃e�L�X�g�����݂̃e�L�X�g�Ɋi�[
	//					sscanf(aReadText, "%s", &aCurrentText);
	//					//���݂̃e�L�X�g��Position��������
	//					if (strcmp(aCurrentText, "Position") == 0)
	//					{
	//						//�ʒu�̐ݒ�
	//						sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Position.x, &m_Position.y, &m_Position.z);
	//					}
	//					//���݂̃e�L�X�g��Size��������
	//					if (strcmp(aCurrentText, "Size") == 0)
	//					{
	//						//�T�C�Y�̐ݒ�
	//						sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Size.x, &m_Size.y, &m_Size.z);
	//					}
	//					//���݂̃e�L�X�g��CollisionSize��������
	//					if (strcmp(aCurrentText, "CollisionSize") == 0)
	//					{
	//						//�T�C�Y�̐ݒ�
	//						sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_CollisionSize.x, &m_CollisionSize.y, &m_CollisionSize.z);
	//					}
	//					//���݂̃e�L�X�g��ROT��������
	//					if (strcmp(aCurrentText, "Rotation") == 0)
	//					{
	//						//��]���̓ǂݍ���
	//						sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
	//					}
	//					//���݂̃e�L�X�g��Move��������
	//					if (strcmp(aCurrentText, "Move") == 0)
	//					{
	//						//�T�C�Y�̐ݒ�
	//						sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Move.x, &m_Move.y, &m_Move.z);
	//					}
	//					//���݂̃e�L�X�g��Life��������
	//					if (strcmp(aCurrentText, "Life") == 0)
	//					{
	//						//�̗͂̐ݒ�
	//						sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nLife);
	//					}
	//					//���݂̃e�L�X�g��WalkSpeed��������
	//					if (strcmp(aCurrentText, "WalkSpeed") == 0)
	//					{
	//						//���s���x�̐ݒ�̐ݒ�
	//						sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fWalkSpeed);
	//					}
	//					//���݂̃e�L�X�g��DashSpeed��������
	//					if (strcmp(aCurrentText, "DashSpeed") == 0)
	//					{
	//						//�_�b�V�����x�̐ݒ�
	//						sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fDashSpeed);
	//					}
	//					//���݂̃e�L�X�g��CameraDistance��������
	//					if (strcmp(aCurrentText, "CameraDistance") == 0)
	//					{
	//						//�J�����Ƃ̋����̐ݒ�
	//						sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fCameraDistance);
	//					}
	//				}
	//			}
	//		}
	//	}
	//	//�t�@�C�������
	//	fclose(pFile);
	//}
}
