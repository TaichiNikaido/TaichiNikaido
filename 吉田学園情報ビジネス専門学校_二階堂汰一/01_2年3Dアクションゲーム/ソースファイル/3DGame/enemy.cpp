//=============================================================================
//
// �G [enemy.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INITIAL_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))			//�ʒu�̏����l
#define INITIAL_MOVE (D3DXVECTOR3(0.0f,0.0f,0.0f))				//�ړ��ʂ̏����l
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))				//�T�C�Y�̏����l
#define INITIAL_COLLISION_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//�Փ˔���p�T�C�Y�̏����l
#define INITIAL_ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))			//��]�̏����l
#define MINIMUM_LIFE (0)										//�̗͂̍ŏ��l
#define MINIMUM_ATTACK (0)										//�U���͂̍ŏ��l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy()
{
	m_Position = INITIAL_POSITION;						//�ʒu
	m_Move = INITIAL_MOVE;								//�ړ���
	m_Size = INITIAL_SIZE;								//�T�C�Y
	m_CollisionSize = INITIAL_COLLISION_SIZE;			//�Փ˔���p�T�C�Y
	m_Rotation = INITIAL_ROTATION;						//��]
	m_nLife = MINIMUM_LIFE;								//�̗�
	m_nAttack = MINIMUM_ATTACK;							//�U����
	memset(m_apMotionPass,NULL,sizeof(m_apMotionPass));	//���[�V�����f�[�^�̃p�X
	memset(m_apModel, 0, sizeof(m_apModel));				//���f���̃|�C���^
	memset(m_aModelData,NULL,sizeof(m_aModelData));		//���f���f�[�^�̃|�C���^
	m_pMotion = NULL;
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
	//���[�V���������֐��Ăяo��
	Motion();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CEnemy::Uninit(void)
{
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���̃|�C���^��NULL����Ȃ��ꍇ
		if (m_apModel[nCount] != NULL)
		{
			//���f���̏I�������֐��Ăяo��
			m_apModel[nCount]->Uninit();
		}
	}
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CEnemy::Update(void)
{
	//�ʒu�X�V
	m_Position += m_Move;
	//�������[�V�����̃|�C���^��NULL�̏ꍇ
	if (m_pMotion != NULL)
	{
		//�X�V�����֐��Ăяo��
		m_pMotion->Update();
	}
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���̃|�C���^��NULL����Ȃ��ꍇ
		if (m_apModel[nCount] != NULL)
		{
			//���f���̕`�揈���֐��Ăяo��
			m_apModel[nCount]->Update();
			// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
			m_apModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), m_Size);
		}
	}
	// ���W�A��]�A�T�C�Y�̃Z�b�g
	m_apModel[0]->SetModel(m_pMotion->GetPosition(0) + m_Position, m_pMotion->GetRotation(0) + m_Rotation, m_Size);
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CEnemy::Draw(void)
{
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���̃|�C���^��NULL����Ȃ��ꍇ
		if (m_apModel[nCount] != NULL)
		{
			//���f���̕`�揈���֐��Ăяo��
			m_apModel[nCount]->Draw();
		}
	}
}

//=============================================================================
// ���f���f�[�^�Z�b�g�����֐�
//=============================================================================
void CEnemy::SetModelData(CModel::MODEL_DATA ModelData[MAX_PARTS])
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		if (ModelData[nCount].pMesh != NULL)
		{
			m_aModelData[nCount] = ModelData[nCount];
		}
	}
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
// ���[�V���������֐�
//=============================================================================
void CEnemy::Motion(void)
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
		m_pMotion->LoadMotion(m_apMotionPass[0]);
		//���[�V�������̓ǂݍ���
		m_pMotion->LoadModelInformation(m_apMotionPass[0]);
		//�ő�p�[�c������
		for (int nCount = 0; nCount < MAX_PARTS; nCount++)
		{
			//�������f���f�[�^�̃��b�V����NULL����Ȃ��ꍇ
			if (m_aModelData[nCount].pMesh != NULL)
			{
				//�e���f���̔ԍ��󂯎��
				m_aModelData[nCount].nIndexModelParent = m_pMotion->GetParents(nCount);
				//���f���̐���
				m_apModel[nCount] = CModel::Create(m_aModelData[nCount]);
				//���[�V�����̈ʒu���擾
				m_pMotion->GetPosition(nCount);
				//���[�V�����̉�]���擾
				m_pMotion->GetRotation(nCount);
				//���f���̊��蓖��
				m_apModel[nCount]->BindModel(m_aModelData[nCount]);
				// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
				m_apModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), m_Size);
			}
		}
		//�p�[�c�̍ő吔����
		for (int nCount = 0; nCount < MAX_PARTS; nCount++)
		{
			//�����e�̃��f�������݂�����
			if (m_apModel[m_aModelData[nCount].nIndexModelParent] != NULL && m_aModelData[nCount].nIndexModelParent != -1)
			{
				//�������f���f�[�^�̃��b�V����NULL����Ȃ��ꍇ
				if (m_aModelData[nCount].pMesh != NULL)
				{
					//�e�̃��f���|�C���^���󂯎��
					m_aModelData[nCount].pParent = m_apModel[m_aModelData[nCount].nIndexModelParent];
					// ���f���̊��蓖��
					m_apModel[nCount]->BindModel(m_aModelData[nCount]);
				}
			}
		}
		// ���W�A��]�A�T�C�Y�̃Z�b�g
		m_apModel[0]->SetModel(m_pMotion->GetPosition(0) + m_Position, m_pMotion->GetRotation(0) + m_Rotation, m_Size);
	}
}