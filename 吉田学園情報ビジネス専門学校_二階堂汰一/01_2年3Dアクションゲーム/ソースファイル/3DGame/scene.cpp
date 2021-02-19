//=============================================================================
//
// �V�[���Ǘ� [scene.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CScene * CScene::m_apScene[PRIORITY_MAX][MAX_SCENE] = {};	//�V�[���ւ̃|�C���^
int CScene::m_nNumAll = 0;									//�V�[���̑���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	m_nID = 0;
	m_nPriority = nPriority;
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		if (m_apScene[m_nPriority][nCount] == NULL)
		{
			m_apScene[m_nPriority][nCount] = this;
			m_nID = nCount;
			m_nNumAll++;
			break;
		}
	}
	m_objType = OBJTYPE_NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// �S�̍X�V�֐�
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			if (m_apScene[nCountPriority][nCount] != NULL)
			{
				m_apScene[nCountPriority][nCount]->Update();
			}
		}
	}
}

//=============================================================================
// �S�̕`��֐�
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			if (m_apScene[nCountPriority][nCount] != NULL)
			{
				m_apScene[nCountPriority][nCount]->Draw();
			}
		}
	}
}

//=============================================================================
// �S�̔j���֐�
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			if (m_apScene[nCountPriority][nCount] != NULL)
			{
				m_apScene[nCountPriority][nCount]->Uninit();
				m_apScene[nCountPriority][nCount] = NULL;
			}
		}
	}
}

//=============================================================================
// �V�[���̑����擾�֐�
//=============================================================================
int CScene::GetNumAll(void)
{
	return m_nNumAll;
}

//=============================================================================
// �j���֐�
//=============================================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}

//=============================================================================
// ��ނ�ݒ�
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//=============================================================================
// ��ނ��擾
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//=============================================================================
// �擾
//=============================================================================
CScene * CScene::GetScene(int nPriority, int nCnt)
{
	return m_apScene[nPriority][nCnt];
}
