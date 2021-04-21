//=============================================================================
//
// �h���S�� [enemy_dragon.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/model.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "Mode/mode_game.h"
#include "enemy_dragon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PASS ("Data/Script/Dragon/DragonModel.txt")		//���f���X�N���v�g�̃p�X
#define SCRIPT_PASS ("Data/Script/Dragon/DragonData.txt")		//�X�P���g���̃X�N���v�g�̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODEL_DATA CDragon::m_aModelData[MAX_PARTS] = {};		//���f���f�[�^�̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDragon::CDragon()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDragon::~CDragon()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CDragon::ModelLoad(void)
{
	//�}�e���A���̃|�C���^
	D3DXMATERIAL * pMaterial;
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�p�X�̃|�C���^
	char * pPass = nullptr;
	//�����p�X�̃|�C���^��nullptr�̏ꍇ
	if (pPass == nullptr)
	{
		//�p�X���擾
		pPass = CModel::LoadModelText(MODEL_PASS);
		//�p�[�c�̍ő吔����
		for (int nCount = 0; nCount < MAX_PARTS; nCount++)
		{
			//�����p�X�̃|�C���^��nullptr����Ȃ��ꍇ
			if (pPass != nullptr)
			{
				//���f���ǂݍ���
				D3DXLoadMeshFromX(pPass,
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&m_aModelData[nCount].pBuffMat,
					NULL,
					&m_aModelData[nCount].nNumMat,
					&m_aModelData[nCount].pMesh);
				//�������f���̃}�e���A�����NULL����Ȃ��ꍇ
				if (m_aModelData[nCount].pBuffMat != nullptr)
				{
					//�}�e���A���̃|�C���^���擾
					pMaterial = (D3DXMATERIAL *)m_aModelData[nCount].pBuffMat->GetBufferPointer();
					//���f���f�[�^������
					for (int nCountMat = 0; nCountMat < (int)m_aModelData[nCount].nNumMat; nCountMat++)
					{
						//�����t�@�C���l�[����NULL����Ȃ��ꍇ
						if (pMaterial[nCountMat].pTextureFilename != NULL)
						{
							//�e�N�X�`����ǂݍ���
							D3DXCreateTextureFromFile(pDevice, pMaterial[nCountMat].pTextureFilename, &m_aModelData[nCount].pTexture[nCountMat]);
						}
					}
				}
				//�|�C���^���̂Ă�
				pPass += MAX_TEXT;
			}
		}
	}
	return S_OK;
}

//=============================================================================
// ���f���j���֐�
//=============================================================================
void CDragon::ModelUnload(void)
{
	//�p�[�c�̍ő吔����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//�������f���f�[�^�̃��[���h�ϊ��s��NULL�ł͂Ȃ��ꍇ
		if (m_aModelData[nCount].mtxWorld != NULL)
		{
			//�������f���f�[�^�̃}�e���A�����NULL�ł͂Ȃ��ꍇ
			if (m_aModelData[nCount].pBuffMat != NULL)
			{
				//���f���f�[�^�̃}�e���A������j��
				m_aModelData[nCount].pBuffMat->Release();
			}
			//�������f���f�[�^�̃��b�V�����NULL�ł͂Ȃ��ꍇ
			if (m_aModelData[nCount].pMesh != NULL)
			{
				//���f���f�[�^�̃��b�V������j��
				m_aModelData[nCount].pMesh->Release();
			}
			//�}�e���A���̍ő吔����
			for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
			{
				//�������f���f�[�^�̃e�N�X�`���̃|�C���^��NULL�ł͂Ȃ��ꍇ
				if (m_aModelData[nCount].pTexture[nCountTexture] != NULL)
				{
					//���f���f�[�^�̃e�N�X�`���̃|�C���^��j��
					m_aModelData[nCount].pTexture[nCountTexture]->Release();
				}
			}
		}
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CDragon * CDragon::Create()
{
	//�h���S���̃|�C���^
	CDragon * pDragon = nullptr;
	//�h���S���̃|�C���^��nullptr�̏ꍇ
	if (pDragon == nullptr)
	{
		//�h���S���̃������m��
		pDragon = new CDragon;
		//�h���S���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pDragon != nullptr)
		{
			//�h���S���̏����������֐��Ăяo��
			pDragon->Init();
		}
	}
	//�h���S���̃|�C���^��Ԃ�
	return pDragon;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CDragon::Init(void)
{
	//�X�N���v�g�̃p�X��ݒ�
	SetScriptPass(SCRIPT_PASS);
	//���f���̃p�X��ݒ�
	SetModelScriptPass(MODEL_PASS);
	//���f���f�[�^�̐ݒ�
	SetModelData(m_aModelData);
	//�G�̏����������֐��Ăяo��
	CEnemy::Init();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CDragon::Uninit(void)
{
	//�G�̏I�������֐��Ăяo��
	CEnemy::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CDragon::Update(void)
{
	//�L�[�{�[�h�̎擾
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//�W���C�X�e�B�b�N�̐U���擾
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != nullptr)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//�G�̍X�V�����֐��Ăяo��
	CEnemy::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CDragon::Draw(void)
{
	//�G�̕`�揈���֐��Ăяo��
	CEnemy::Draw();
}