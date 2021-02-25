//=============================================================================
//
// �w�i�Ǘ����� [background_manager.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "background_manager.h"
#include "background_under_layer.h"
#include "background_middle_layer.h"
#include "background_upper_layer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BACKGROUND_UNDER_LAYR_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))		//���w�w�i�̈ʒu
#define BACKGROUND_MIDDLE_LAYER_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))	//���w�w�i�̈ʒu
#define BACKGROUND_UPPER_LAYER_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))	//��w�w�i�̈ʒu

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBackgroundManager::CBackgroundManager()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBackgroundManager::~CBackgroundManager()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CBackgroundManager * CBackgroundManager::Create()
{
	//�w�i�Ǘ��̃|�C���^
	CBackgroundManager * pBackgroundManager = NULL;
	//�����w�i�Ǘ��̃|�C���^��NULL�̏ꍇ
	if (pBackgroundManager == NULL)
	{
		//�w�i�Ǘ��̃������m��
		pBackgroundManager = new CBackgroundManager;
		//�����w�i�Ǘ��̃|�C���^��NULL����Ȃ��ꍇ
		if (pBackgroundManager != NULL)
		{
			//�w�i�Ǘ��̏����������֐��Ăяo��
			pBackgroundManager->Init();
		}
	}
	//�w�i�Ǘ��̃|�C���^��Ԃ�
	return pBackgroundManager;
}

//=============================================================================
// �����������֐�
//=============================================================================
void CBackgroundManager::Init(void)
{
	//���w�w�i�̐���
	CBackgroundUnderLayer::Create(BACKGROUND_UNDER_LAYR_POSITION);
	//���w�w�i�̐���
	CBackgroundMiddleLayer::Create(BACKGROUND_MIDDLE_LAYER_POSITION);
	//��w�w�i�̐���
	CBackgroundUpperLayer::Create(BACKGROUND_UPPER_LAYER_POSITION);
}
