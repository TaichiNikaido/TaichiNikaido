//=============================================================================
//
// �L�����N�^�[ [character.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "character.h"
#include "Polygon3d/shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SHADOW_SIZE (D3DXVECTOR3(500.0f,500.0f,500.0f))					//�e�̃T�C�Y
#define SHADOW_ROTATION (D3DXToRadian(D3DXVECTOR3(-90.0f,0.0f,0.0f)))	//�e�̉�]
#define SHADOW_COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))					//�e�̐F

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharacter::CCharacter(int nPriority) : CScene3d(nPriority)
{
	memset(m_apModelScriptPass, NULL, sizeof(m_apModelScriptPass));		//���f���̃X�N���v�g�p�X
	memset(m_aModelData, NULL, sizeof(m_aModelData));					//���f���f�[�^
	m_CollisionSize = INITIAL_D3DXVECTOR3;								//�Փ˔���p�T�C�Y
	memset(m_apModel,NULL,sizeof(m_apModel));							//���f���̃|�C���^
	m_pMotion = nullptr;												//���[�V�����̃|�C���^
	//m_pShadow = nullptr;
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
	//�������[�V�����̃|�C���^��nullptr�̏ꍇ
	if (m_pMotion == nullptr)
	{
		//���[�V�����̐���
		m_pMotion = CMotion::Create();
		//�������[�V�����̃|�C���^��nullptr����Ȃ��ꍇ
		if (m_pMotion != nullptr)
		{
			//���[�V�����̓ǂݍ���
			m_pMotion->LoadMotion(m_apModelScriptPass[0]);
			//���[�V�������̓ǂݍ���
			m_pMotion->LoadModelInformation(m_apModelScriptPass[0]);
			//�ő�p�[�c������
			for (int nCount = 0; nCount < MAX_PARTS; nCount++)
			{
				//�������f���f�[�^�̃��b�V����nullptr����Ȃ��ꍇ
				if (m_aModelData[nCount].pMesh != nullptr)
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
					m_apModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), GetSize());
				}
			}
			//�p�[�c�̍ő吔����
			for (int nCount = 0; nCount < MAX_PARTS; nCount++)
			{
				//�����e�̃��f�������݂�����
				if (m_apModel[m_aModelData[nCount].nIndexModelParent] != nullptr && m_aModelData[nCount].nIndexModelParent != -1)
				{
					//�������f���f�[�^�̃��b�V����nullptr����Ȃ��ꍇ
					if (m_aModelData[nCount].pMesh != nullptr)
					{
						//�e�̃��f���|�C���^���󂯎��
						m_aModelData[nCount].pParent = m_apModel[m_aModelData[nCount].nIndexModelParent];
						// ���f���̊��蓖��
						m_apModel[nCount]->BindModel(m_aModelData[nCount]);
					}
				}
			}
			// ���W�A��]�A�T�C�Y�̃Z�b�g
			m_apModel[0]->SetModel(m_pMotion->GetPosition(0) + GetPosition(), m_pMotion->GetRotation(0) + GetRotation(), GetSize());
		}
	}
	//�e�̐��������֐��Ăяo��
	ShadowCreate();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CCharacter::Uninit(void)
{
	//�������[�V�����̃|�C���^��nullptr�̏ꍇ
	if (m_pMotion != nullptr)
	{
		//�I�������֐��Ăяo��
		m_pMotion->Uninit();
	}
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_apModel[nCount] != nullptr)
		{
			//���f���̏I�������֐��Ăяo��
			m_apModel[nCount]->Uninit();
		}
	}
	////�����e�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	//if (m_pShadow != nullptr)
	//{
	//	//�e�̏I�������֐��Ăяo��
	//	m_pShadow->Uninit();
	//}
	//�j�������֐��Ăяo��
	Release();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CCharacter::Update(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�������[�V�����̃|�C���^��nullptr�̏ꍇ
	if (m_pMotion != nullptr)
	{
		//�X�V�����֐��Ăяo��
		m_pMotion->Update();
	}
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���̃|�C���^��nullptr�ł͂Ȃ��ꍇ	
		if (m_apModel[nCount] != nullptr)
		{
			//���f���̍X�V�����֐��Ăяo��
			m_apModel[nCount]->Update();
			// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
			m_apModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), GetSize());
		}
	}
	////�����e�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	//if (m_pShadow != nullptr)
	//{
	//	//�e�̈ʒu��ݒ肷��
	//	m_pShadow->SetPosition(Position);
	//	//�e�̃T�C�Y��ݒ肷��
	//	m_pShadow->SetSize(SHADOW_SIZE);
	//	//�e�̉�]��ݒ肷��
	//	m_pShadow->SetRotation(SHADOW_ROTATION);
	//	//�e�̐F��ݒ肷��
	//	m_pShadow->SetColor(SHADOW_COLOR);
	//	//�e�̍X�V�����֐��Ăяo��
	//	m_pShadow->Update();
	//}
	//�ʒu��ۑ�����
	m_PositionOld = Position;
	// ���W�A��]�A�T�C�Y�̃Z�b�g
	m_apModel[0]->SetModel(m_pMotion->GetPosition(0) + GetPosition(), m_pMotion->GetRotation(0) + GetRotation(), GetSize());
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CCharacter::Draw(void)
{
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (m_apModel[nCount] != nullptr)
		{
			//���f���̕`�揈���֐��Ăяo��
			m_apModel[nCount]->Draw();
		}
	}
	////�[�x�e�X�g�̐ݒ�(�K���s���i�ɂ���)
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
	////�X�e���V���e�X�g��L���ɂ���
	//pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	////�X�e���V���o�b�t�@�֏������ގQ�ƒl�ݒ�
	//pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	//pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	////�X�e���V���o�b�t�@�ɏ������ޏ���
	//pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	//// �X�e���V���e�X�g�̃e�X�g�ݒ�
	//pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	//pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
	//pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	////�ʒu��ݒ肷��
	//m_apModel[0]->SetPosition(Position);
	////��]��ݒ肷��
	//m_apModel[0]->SetRotation(D3DXToRadian(D3DXVECTOR3(90.0f, 0.0f, 0.0f)));
	////�p�[�c�̍ő吔����
	//for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	//{
	//	//�������f���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	//	if (m_apModel[nCount] != nullptr)
	//	{
	//		//���f���̕`�揈���֐��Ăяo��
	//		m_apModel[nCount]->Draw();
	//	}
	//}
	////�[�x�e�X�g�̐ݒ�
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	////�X�e���V���Q�ƒl�̐ݒ�
	//pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	////�X�e���V���}�X�N�̐ݒ�
	//pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	//pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	////�X�e���V���e�X�g�̃e�X�g�ݒ�
	//pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	//pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	//pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	////�����e�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	//if (m_pShadow != nullptr)
	//{
	//	//�e�̕`�揈���֐��Ăяo��
	//	m_pShadow->Draw();
	//}
	////�X�e���V���e�X�g�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//=============================================================================
// ���f�����̐ݒ菈���֐�
//=============================================================================
void CCharacter::SetModelData(CModel::MODEL_DATA ModelData[MAX_PARTS])
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		if (ModelData[nCount].pMesh != nullptr)
		{
			m_aModelData[nCount] = ModelData[nCount];
		}
	}
}

//=============================================================================
// �e���������֐�
//=============================================================================
void CCharacter::ShadowCreate(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	////�����e�̃|�C���^��nullptr�̏ꍇ
	//if (m_pShadow == nullptr)
	//{
	//	//�e�̐���
	//	m_pShadow = new CShadow;
	//	//�����e�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	//	if (m_pShadow != nullptr)
	//	{
	//		//�e�̈ʒu��ݒ肷��
	//		m_pShadow->SetPosition(Position);
	//		//�e�̃T�C�Y��ݒ肷��
	//		m_pShadow->SetSize(SHADOW_SIZE);
	//		//�e�̉�]��ݒ肷��
	//		m_pShadow->SetRotation(SHADOW_ROTATION);
	//		//�e�̐F��ݒ肷��
	//		m_pShadow->SetColor(SHADOW_COLOR);
	//		//�e�̒��_���W��ݒ肷��
	//		m_pShadow->SetTexture(aTexture);
	//		//�e�̏����������֐��Ăяo��
	//		m_pShadow->Init();
	//	}
	//}
}
