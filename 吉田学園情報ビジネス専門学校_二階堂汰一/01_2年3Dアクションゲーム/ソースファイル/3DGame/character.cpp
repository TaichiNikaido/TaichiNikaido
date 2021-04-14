//=============================================================================
//
// �L�����N�^�[ [character.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "character.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharacter::CCharacter()
{
	memset(m_apModelScriptPass, NULL, sizeof(m_apModelScriptPass));		//���f���̃X�N���v�g�p�X
	memset(m_aModelData, NULL, sizeof(m_aModelData));					//���f���f�[�^
	memset(m_pModel,NULL,sizeof(m_pModel));								//���f���̃|�C���^
	m_pMotion = nullptr;												//���[�V�����̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharacter::~CCharacter()
{
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CCharacter::Init(void)
{
	//�������[�V�����̃|�C���^��NULL�̏ꍇ
	if (m_pMotion == NULL)
	{
		//���[�V�����̐���
		m_pMotion = CMotion::Create();
	}
	//�������[�V�����̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pMotion != NULL)
	{
		//���[�V�����̓ǂݍ���
		m_pMotion->LoadMotion(m_apModelScriptPass[0]);
		//���[�V�������̓ǂݍ���
		m_pMotion->LoadModelInformation(m_apModelScriptPass[0]);
		//�ő�p�[�c������
		for (int nCount = 0; nCount < MAX_PARTS; nCount++)
		{
			//�������f���f�[�^�̃��b�V����NULL����Ȃ��ꍇ
			if (m_aModelData[nCount].pMesh != NULL)
			{
				//�e���f���̔ԍ��󂯎��
				m_aModelData[nCount].nIndexModelParent = m_pMotion->GetParents(nCount);
				//���f���̐���
				m_pModel[nCount] = CModel::Create(m_aModelData[nCount]);
				//���[�V�����̈ʒu���擾
				m_pMotion->GetPosition(nCount);
				//���[�V�����̉�]���擾
				m_pMotion->GetRotation(nCount);
				//���f���̊��蓖��
				m_pModel[nCount]->BindModel(m_aModelData[nCount]);
				// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
				m_pModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), GetSize());
			}
		}
		//�p�[�c�̍ő吔����
		for (int nCount = 0; nCount < MAX_PARTS; nCount++)
		{
			//�����e�̃��f�������݂�����
			if (m_pModel[m_aModelData[nCount].nIndexModelParent] != NULL && m_aModelData[nCount].nIndexModelParent != -1)
			{
				//�������f���f�[�^�̃��b�V����NULL����Ȃ��ꍇ
				if (m_aModelData[nCount].pMesh != NULL)
				{
					//�e�̃��f���|�C���^���󂯎��
					m_aModelData[nCount].pParent = m_pModel[m_aModelData[nCount].nIndexModelParent];
					// ���f���̊��蓖��
					m_pModel[nCount]->BindModel(m_aModelData[nCount]);
				}
			}
		}
		// ���W�A��]�A�T�C�Y�̃Z�b�g
		m_pModel[0]->SetModel(m_pMotion->GetPosition(0) + GetPosition(), m_pMotion->GetRotation(0) + GetRotation(), GetSize());
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CCharacter::Uninit(void)
{
	//�������[�V�����̃|�C���^��NULL�̏ꍇ
	if (m_pMotion != NULL)
	{
		//�I�������֐��Ăяo��
		m_pMotion->Uninit();
	}
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (m_pModel[nCount] != NULL)
		{
			//���f���̏I�������֐��Ăяo��
			m_pModel[nCount]->Uninit();
		}
	}
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CCharacter::Update(void)
{
	//�������[�V�����̃|�C���^��NULL�̏ꍇ
	if (m_pMotion != NULL)
	{
		//�X�V�����֐��Ăяo��
		m_pMotion->Update();
	}
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���̃|�C���^��NULL�ł͂Ȃ��ꍇ	
		if (m_pModel[nCount] != NULL)
		{
			//���f���̍X�V�����֐��Ăяo��
			m_pModel[nCount]->Update();
			// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
			m_pModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), GetSize());
		}
	}
	// ���W�A��]�A�T�C�Y�̃Z�b�g
	m_pModel[0]->SetModel(m_pMotion->GetPosition(0) + GetPosition(), m_pMotion->GetRotation(0) + GetRotation(), GetSize());
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CCharacter::Draw(void)
{
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (m_pModel[nCount] != NULL)
		{
			//���f���̕`�揈���֐��Ăяo��
			m_pModel[nCount]->Draw();
		}
	}
}

//=============================================================================
// ���f�����̐ݒ菈���֐�
//=============================================================================
void CCharacter::SetModelData(CModel::MODEL_DATA ModelData[MAX_PARTS])
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		if (ModelData[nCount].pMesh != NULL)
		{
			m_aModelData[nCount] = ModelData[nCount];
		}
	}
}
