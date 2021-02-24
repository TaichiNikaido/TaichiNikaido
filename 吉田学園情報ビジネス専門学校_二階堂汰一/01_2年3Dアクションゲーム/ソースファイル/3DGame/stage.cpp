//=============================================================================
//
// �X�e�[�W [stage.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "stage.h"
#include "object_wood_house.h"
#include "object_stone_house.h"
#include "object_fountain.h"
#include "object_fence.h"
#include "object_corpse.h"
#include "ui_village_life.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INITIAL_LIFE (0)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStage::CStage()
{
	m_nLife = INITIAL_LIFE;							//�̗�
	memset(m_apObject, NULL, sizeof(m_apObject));	//�I�u�W�F�N�g�̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStage::~CStage()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CStage * CStage::Create()
{
	//�X�e�[�W�̃|�C���^
	CStage * pStage = NULL;
	//�����X�e�[�W�̃|�C���^��NULL�������ꍇ
	if (pStage == NULL)
	{
		//�X�e�[�W�̃������m��
		pStage = new CStage;
	}
	//�����X�e�[�W�̃|�C���^��NULL����Ȃ��ꍇ
	if (pStage != NULL)
	{
		//�X�e�[�W�̏������֐��Ăяo��
		pStage->Init();
	}
	//�X�e�[�W�̃|�C���^��Ԃ�
	return pStage;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CStage::Init(void)
{
	//�����S���������֐��Ăяo��
	InitCreateAll();
	int nLife = 0;	//�̗�
	//�I�u�W�F�N�g�̍ő吔����
	for (int nCount = 0; nCount < 5; nCount++)
	{
		//�����I�u�W�F�N�g�̃|�C���^��NULL����Ȃ��ꍇ
		if (m_apObject[nCount] != NULL)
		{
			//���C�t�����Z����
			nLife += m_apObject[nCount]->GetLife();
		}
	}
	//�̗͂�ۑ�����
	m_nLife = nLife;
	
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CStage::Uninit(void)
{
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CStage::Update(void)
{
	int nLife = 0;	//�̗�
	//�I�u�W�F�N�g�̍ő吔����
	for (int nCount = 0; nCount < 5; nCount++)
	{
		//�����I�u�W�F�N�g�̃|�C���^��NULL����Ȃ��ꍇ
		if (m_apObject[nCount] != NULL)
		{
			//���C�t�����Z����
			nLife += m_apObject[nCount]->GetLife();
		}
	}
	//�̗͂�ۑ�����
	m_nLife = nLife;
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CStage::Draw(void)
{
}

//=============================================================================
// �����S���������֐�
//=============================================================================
void CStage::InitCreateAll(void)
{
	m_apObject[0] = CStoneHouse::Create(D3DXVECTOR3(1100.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	m_apObject[1] = CStoneHouse::Create(D3DXVECTOR3(800.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	m_apObject[2] = CStoneHouse::Create(D3DXVECTOR3(500.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	m_apObject[3] = CWoodHouse::Create(D3DXVECTOR3(-850.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	m_apObject[4] = CWoodHouse::Create(D3DXVECTOR3(-900.0f, 0.0f, 750.0f), D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f));
	m_apObject[5] = CWoodHouse::Create(D3DXVECTOR3(1050.0f, 0.0f, 750.0f), D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f));
	m_apObject[5] = CFountain::Create(D3DXVECTOR3(20.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));



	CFence::Create(D3DXVECTOR3(600.0f, 0.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CFence::Create(D3DXVECTOR3(-600.0f, 0.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CFence::Create(D3DXVECTOR3(-1150.0f, 0.0f, 550.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	CFence::Create(D3DXVECTOR3(-1150.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	CFence::Create(D3DXVECTOR3(1275.0f, 0.0f, 550.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	CFence::Create(D3DXVECTOR3(1275.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	CFence::Create(D3DXVECTOR3(600.0f, 0.0f, -1225.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CFence::Create(D3DXVECTOR3(-600.0f, 0.0f, -1225.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CCorpse::Create(D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}