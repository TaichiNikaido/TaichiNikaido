//=============================================================================
//
// �U���p�^�[��(���e�I) [attack_pattern_meteor.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "attack_pattern_meteor.h"
#include "Object/object_meteor.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MINIMUM_METEOR_CREATE_TIME (0)		//���e�I�𐶐����鎞�Ԃ̍ŏ��l
#define MINIMUM_METEOR_CREATE_COUNT (0)		//���e�I�̐������̍ŏ��l
#define MAX_METEOR (32)						//�������郁�e�I�̍ő吔
#define METEOR_CREATE_POSITION_Y (1000.0f)	//���e�I�𐶐�����ʒu(Y��)
#define METEOR_CREATE_MAX_AREA (500)		//���e�I�𐶐�����ő�G���A
#define METEOR_SIZE (50.0f)					//���e�I�̑傫��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CAttackPatternMeteor::CAttackPatternMeteor()
{
	m_nMeteorCreateTime = MINIMUM_METEOR_CREATE_TIME;		//���e�I�𐶐����鎞��
	m_nMeteorCreateCount = MINIMUM_METEOR_CREATE_COUNT;		//���e�I�̐�����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CAttackPatternMeteor::~CAttackPatternMeteor()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CAttackPatternMeteor * CAttackPatternMeteor::Create(void)
{
	//�U���p�^�[��(���e�I)�̃|�C���^
	CAttackPatternMeteor * pAttackPatternMeteor = nullptr;
	//�U���p�^�[��(���e�I)��nullptr�̏ꍇ
	if (pAttackPatternMeteor == nullptr)
	{
		//�U���p�^�[��(���e�I)�̃������m��
		pAttackPatternMeteor = new CAttackPatternMeteor;
		//�U���p�^�[��(���e�I)�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pAttackPatternMeteor != nullptr)
		{
			//�U���p�^�[��(���e�I)�̏����������֐��Ăяo��
			pAttackPatternMeteor->Init();
		}
	}
	//�U���p�^�[��(���e�I)�̃|�C���^��Ԃ�
	return pAttackPatternMeteor;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CAttackPatternMeteor::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CAttackPatternMeteor::Uninit(void)
{
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CAttackPatternMeteor::Update(void)
{
	if (m_nMeteorCreateTime % 60 == 0)
	{
		//�������e�I�̐������邪�ő�l�ɓ��B���Ă��Ȃ��ꍇ
		if (m_nMeteorCreateCount <= MAX_METEOR)
		{
			//���e�I�𐶐�����
			MeteorCreate();
		}
	}
	//���e�I�̐������Ԃ����Z����
	m_nMeteorCreateTime++;
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CAttackPatternMeteor::Draw(void)
{
}

//=============================================================================
// ���e�I���������֐�
//=============================================================================
void CAttackPatternMeteor::MeteorCreate(void)
{
	//�����̐^�U
	bool bCreate = false;
	//�����̐^�U���U�̏ꍇ
	while (bCreate == false)
	{
		//���e�I�̐����ʒu
		D3DXVECTOR3 MeteorCreatePosition = INITIAL_D3DXVECTOR3;
		//���e�I�̐����ʒu��X���W�������_���ŋ��߂�
		MeteorCreatePosition.x = float((rand() % METEOR_CREATE_MAX_AREA * 2) - METEOR_CREATE_MAX_AREA);
		//���e�I�̐����ʒu��Z���W�������_���ŋ��߂�
		MeteorCreatePosition.z = float((rand() % METEOR_CREATE_MAX_AREA * 2) - METEOR_CREATE_MAX_AREA);
		//���_���烁�e�I�܂ł̋��������߂�
		D3DXVECTOR3 Distance = D3DXVECTOR3(MeteorCreatePosition.x - INITIAL_D3DXVECTOR3.x, MeteorCreatePosition.y - INITIAL_D3DXVECTOR3.y, MeteorCreatePosition.z - INITIAL_D3DXVECTOR3.z);
		//�x�N�g���̒��������߂�
		float Vector_length = sqrtf((Distance.x * Distance.x) * (Distance.z * Distance.z));
		//���e�I�𐶐�����͈�(�~�`)�����߂�
		if (powf(Distance.x, 2) + powf(Distance.z, 2)
			<= pow(((METEOR_CREATE_MAX_AREA / 2) + (METEOR_SIZE / 2)), 2))
		{
			//���e�I�𐶐����Ȃ��͈�(�~�`)�����߂�
			if (powf(Distance.x, 2) + powf(Distance.z, 2)
				>= pow(((METEOR_CREATE_MAX_AREA / 6) + (METEOR_SIZE / 2)), 2))
			{
				//���e�I�𐶐�����
				CMeteor::Create(D3DXVECTOR3(MeteorCreatePosition.x, METEOR_CREATE_POSITION_Y, MeteorCreatePosition.z));
				//�����̐^�U��^�ɂ���
				bCreate = true;
				//���e�I�̐����������Z����
				m_nMeteorCreateCount++;
			}
		}
	}
}