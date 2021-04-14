//=============================================================================
//
// �V�[���Ǘ����� [scene.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"

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
	m_nID = 0;					//���݂̃V�[��
	m_nPriority = nPriority;	//�v���C�I���e�B�[
	//�V�[���̍ő吔����
	for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		//�����V�[���̃|�C���^��NULL�̏ꍇ
		if (m_apScene[m_nPriority][nCount] == NULL)
		{
			//�V�[���̊m��
			m_apScene[m_nPriority][nCount] = this;
			m_nID = nCount;
			//�V�[���̑��������Z����
			m_nNumAll++;
			break;
		}
	}
	m_ObjectType = OBJECT_TYPE_NONE;	//�I�u�W�F�N�g�̎��
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// �S�X�V�����֐�
//=============================================================================
void CScene::UpdateAll(void)
{
	//�v���C�I���e�B�[�̍ő吔����
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		//�V�[���̍ő吔����
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			//�����V�[���̃|���^��NULL�ł͂Ȃ��ꍇ
			if (m_apScene[nCountPriority][nCount] != NULL)
			{
				//�V�[���̍X�V�����֐��Ăяo��
				m_apScene[nCountPriority][nCount]->Update();
			}
		}
	}
}

//=============================================================================
// �S�`�揈���֐�
//=============================================================================
void CScene::DrawAll(void)
{
	//�v���C�I���e�B�[�̍ő吔����
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		//�V�[���̍ő吔����
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			//�����V�[���̃|���^��NULL�ł͂Ȃ��ꍇ
			if (m_apScene[nCountPriority][nCount] != NULL)
			{
				//�V�[���̍X�V�����֐��Ăяo��
				m_apScene[nCountPriority][nCount]->Draw();
			}
		}
	}
}

//=============================================================================
// �S�j�������֐�
//=============================================================================
void CScene::ReleaseAll(void)
{
	//�v���C�I���e�B�[�̍ő吔����
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		//�V�[���̍ő吔����
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			//�����V�[���̃|���^��NULL�ł͂Ȃ��ꍇ
			if (m_apScene[nCountPriority][nCount] != NULL)
			{
				//�V�[���̏I�������֐��Ăяo��
				m_apScene[nCountPriority][nCount]->Uninit();
				//�V�[����NULL�ɂ���
				m_apScene[nCountPriority][nCount] = NULL;
			}
		}
	}
}

//=============================================================================
// �j�������֐�
//=============================================================================
void CScene::Release(void)
{
	//�����V�[����NULL�ł͂Ȃ��ꍇ
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;
		//�V�[���̃�������j������
		delete m_apScene[nPriority][nID];
		//�V�[����NULL�ɂ���
		m_apScene[nPriority][nID] = NULL;
		//�V�[���̑��������Z����
		m_nNumAll--;
	}
}