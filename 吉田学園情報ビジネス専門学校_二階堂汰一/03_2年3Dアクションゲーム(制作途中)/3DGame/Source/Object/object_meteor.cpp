//=============================================================================
//
// ���e�I [object_meteor.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "object_meteor.h"
#include "Polygon3d/round_shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PASS ("Data/Model/Object/meteor.x")						//���f���X�N���v�g�̃p�X
#define ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))							//��]
#define MOVE (D3DXVECTOR3(0.0f,-5.0f,0.0f))								//�ړ���
#define SIZE (D3DXVECTOR3(2.0f,2.0f,2.0f))								//�T�C�Y
#define COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))							//�F
#define METEOR_SHADOW_POSITION (D3DXVECTOR3(0.0f,1.0f,0.0f))			//���e�I�̉e�̈ʒu
#define MINIMUM_METEOR_HEIGHT (0.0f)									//���e�I�̍����̍ŏ��l
#define INITIAL_METEOR_SHADOW_SIZE (D3DXVECTOR3(150.0f,150.0f,150.0f))	//���e�I�̉e�̏����T�C�Y
#define METEOR_SHADOW_MAX_SIZE (80.0f)									//���e�I�̉e�̃T�C�Y�̍ő�l
#define MAX_ALPHA (1.0f)												//�A���t�@�l�̍ő�l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODEL_DATA CMeteor::m_MeteorModelData = {};		//���f���f�[�^�̃|�C���^
D3DXMATERIAL * CMeteor::m_pMaterial = NULL;				//�}�e���A���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeteor::CMeteor()
{
	m_Move = INITIAL_D3DXVECTOR3;					//�ړ���
	m_MeteorShadowSize = INITIAL_D3DXVECTOR3;		//���e�I�̉e�̃T�C�Y
	m_MeteorShadowColor = INITIAL_D3DXCOLOR;		//���e�I�̉e�̐F
	m_fMeteorMaxHeight = MINIMUM_METEOR_HEIGHT;		//���e�I�̍����̍ŏ��l
	m_fMeteorHeight = MINIMUM_METEOR_HEIGHT;		//覐΂̌��݂̍���
	m_pRoundShadow = nullptr;						//�ۉe�̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeteor::~CMeteor()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CMeteor::ModelLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�p�X�̃|�C���^
	char * pPass = NULL;
	//�����p�X�̃|�C���^��NULL�̏ꍇ
	if (pPass == NULL)
	{
		//�p�X���擾
		pPass = MODEL_PASS;
		//�����p�X�̃|�C���^��NULL����Ȃ��ꍇ
		if (pPass != NULL)
		{
			//���f���ǂݍ���
			D3DXLoadMeshFromX(pPass,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_MeteorModelData.pBuffMat,
				NULL,
				&m_MeteorModelData.nNumMat,
				&m_MeteorModelData.pMesh);
			//�������f���̃}�e���A�����NULL����Ȃ��ꍇ
			if (m_MeteorModelData.pBuffMat != NULL)
			{
				//�}�e���A���̃|�C���^���擾
				m_pMaterial = (D3DXMATERIAL *)m_MeteorModelData.pBuffMat->GetBufferPointer();
				//���f���f�[�^������
				for (int nCountMat = 0; nCountMat < (int)m_MeteorModelData.nNumMat; nCountMat++)
				{
					//�����t�@�C���l�[����NULL����Ȃ��ꍇ
					if (m_pMaterial[nCountMat].pTextureFilename != NULL)
					{
						//�e�N�X�`����ǂݍ���
						D3DXCreateTextureFromFile(pDevice, m_pMaterial[nCountMat].pTextureFilename, &m_MeteorModelData.pTexture[nCountMat]);
					}
				}
			}
		}
	}
	return S_OK;
}

//=============================================================================
// ���f���j���֐�
//=============================================================================
void CMeteor::ModelUnload(void)
{
	//�������f���f�[�^�̃��[���h�ϊ��s��NULL����ȏꍇ
	if (m_MeteorModelData.mtxWorld != NULL)
	{
		//�������f���f�[�^�̃}�e���A�����NULL����ȏꍇ
		if (m_MeteorModelData.pBuffMat != NULL)
		{
			//���f���f�[�^�̃}�e���A������j��
			m_MeteorModelData.pBuffMat->Release();
		}
		//�������f���f�[�^�̃��b�V�����NULL����ȏꍇ
		if (m_MeteorModelData.pMesh != NULL)
		{
			//���f���f�[�^�̃��b�V������j��
			m_MeteorModelData.pMesh->Release();
		}
		//�}�e���A���̍ő吔����
		for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
		{
			//�������f���f�[�^�̃e�N�X�`���̃|�C���^��NULL����ȏꍇ
			if (m_MeteorModelData.pTexture[nCountTexture] != NULL)
			{
				//���f���f�[�^�̃e�N�X�`���̃|�C���^��j��
				m_MeteorModelData.pTexture[nCountTexture]->Release();
			}
		}
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CMeteor * CMeteor::Create(D3DXVECTOR3 Position)
{
	//���e�I�̃|�C���^
	CMeteor * pMeteor = NULL;
	//���e�I�̃|�C���^��NULL�̏ꍇ
	if (pMeteor == NULL)
	{
		//���e�I�̃������m��
		pMeteor = new CMeteor;
		//���e�I�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pMeteor != NULL)
		{
			//���e�I�̈ʒu��ݒ肷��
			pMeteor->SetPosition(Position);
			//���e�I�̉�]��ݒ肷��
			pMeteor->SetRotation(ROTATION);
			//���e�I�̃T�C�Y��ݒ肷��
			pMeteor->SetSize(SIZE);
			//���e�I�̏����������֐��Ăяo��
			pMeteor->Init();
		}
	}
	//���e�I�̃|�C���^��Ԃ�
	return pMeteor;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CMeteor::Init(void)
{
	//���f���f�[�^�̐ݒ�
	SetModelData(m_MeteorModelData);
	//�I�u�W�F�N�g�̏����������֐��Ăяo��
	CObject::Init();
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//覐΂̍����̍ő�l�����߂�
	m_fMeteorMaxHeight = Position.y;
	//�ړ��ʂ̐ݒ�
	m_Move = MOVE;
	//�����ۉe�̃|�C���^��nullptr�̏ꍇ
	if (m_pRoundShadow == nullptr)
	{
		//���e�I�̉e�̐F��ݒ肷��
		m_MeteorShadowColor = COLOR;
		//�ۉe�̐���
		m_pRoundShadow = CRoundShadow::Create(D3DXVECTOR3(Position.x,INITIAL_D3DXVECTOR3.y + 1.0f,Position.z), INITIAL_METEOR_SHADOW_SIZE, m_MeteorShadowColor);
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CMeteor::Uninit(void)
{
	//�I�u�W�F�N�g�̏I�������֐��Ăяo��
	CObject::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CMeteor::Update(void)
{
	//覐΂Ƃ̋���
	float fMeteorDistance;
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�I�u�W�F�N�g�̍X�V�����֐��Ăяo��
	CObject::Update();
	//覐΂̌��݂̍���
	m_fMeteorHeight = Position.y;
	//�ʒu�X�V
	Position += m_Move;
	//�n�ʂ���覐΂̋��������߂�
	fMeteorDistance = m_fMeteorMaxHeight - INITIAL_D3DXVECTOR3.y;
	//�����ɉ����ĉe�̃T�C�Y�����߂�
	m_MeteorShadowSize.x = (1 - m_fMeteorHeight / fMeteorDistance) * METEOR_SHADOW_MAX_SIZE;
	m_MeteorShadowSize.y = (1 - m_fMeteorHeight / fMeteorDistance) * METEOR_SHADOW_MAX_SIZE;
	m_MeteorShadowSize.z = (1 - m_fMeteorHeight / fMeteorDistance) * METEOR_SHADOW_MAX_SIZE;
	m_MeteorShadowColor.a = (1 - m_fMeteorHeight / fMeteorDistance) * MAX_ALPHA;
	//�����ۉe�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pRoundShadow != nullptr)
	{
		//�e�ɃT�C�Y��ݒ肷��
		m_pRoundShadow->SetSize(m_MeteorShadowSize);
		//�e�ɐF��ݒ肷��
		m_pRoundShadow->SetColor(m_MeteorShadowColor);
	}
	//�����ʒu�������l��艺�ɂȂ����ꍇ
	if (Position.y <= INITIAL_D3DXVECTOR3.y)
	{
		//�����ۉe�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_pRoundShadow != nullptr)
		{
			//�e�̏I�������֐��Ăяo��
			m_pRoundShadow->Uninit();
		}
		//�I�������֐��Ăяo��
		Uninit();
		return;
	}
	//�ʒu��ݒ肷��
	SetPosition(Position);
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CMeteor::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈���֐��Ăяo��
	CObject::Draw();
}