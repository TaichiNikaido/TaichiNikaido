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
#include "Character/player.h"
#include "Polygon2d/game_clear_logo.h"
#include "AttackPattern/attack_pattern_meteor.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PASS ("Data/Script/Dragon/DragonModel.txt")		//���f���X�N���v�g�̃p�X
#define SCRIPT_PASS ("Data/Script/Dragon/DragonData.txt")		//�X�P���g���̃X�N���v�g�̃p�X
#define MINIMUM_LIFE (0)										//�̗͂̍ŏ��l
#define ATTACK_AREA (1200.0f)									//�U���J�n�͈�
#define BITING_AREA (300.0f)									//���݂��͈�

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODEL_DATA CDragon::m_aModelData[MAX_PARTS] = {};		//���f���f�[�^�̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDragon::CDragon()
{
	m_bGameClearLogoCreate = false;		//�Q�[���N���A���S�𐶐�������
	m_AttackPattern = ATTACK_NONE;		//�U���p�^�[��
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
	CAttackPatternMeteor::Create();
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
	int nLife = GetLife();
	if (pKeyboard->GetKeyboardTrigger(DIK_H))
	{
		nLife -= 20;
		SetLife(nLife);
	}
	//�G�̍X�V�����֐��Ăяo��
	CEnemy::Update();
	//AI�����֐��Ăяo��
	AI();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CDragon::Draw(void)
{
	//�G�̕`�揈���֐��Ăяo��
	CEnemy::Draw();
}

//=============================================================================
// AI�����֐�
//=============================================================================
void CDragon::AI(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 Position = GetPosition();
	//��]�̎擾
	D3DXVECTOR3 Rotation = GetRotation();
	//�̗͂̎擾
	int nLife = GetLife();
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�����v���C���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (pPlayer != nullptr)
	{
		//�v���C���[�̈ʒu���擾����
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//�v���C���[�̏Փ˔���p�̃T�C�Y���擾����
		D3DXVECTOR3 PlayerCollisionSize = pPlayer->GetCollisionSize();
		//�v���C���[�܂ł̋��������߂�
		D3DXVECTOR3 PlayerDistance = D3DXVECTOR3(PlayerPosition.x - Position.x, PlayerPosition.y - Position.y, PlayerPosition.z - Position.z);
		//�x�N�g���̒��������߂�
		float Vector_length = sqrtf((PlayerDistance.x * PlayerDistance.x) * (PlayerDistance.y * PlayerDistance.y));
		//�G�ƃv���C���[�̋��������ꂼ��̔��a�̘a��菬����������Փ�
		if (powf(PlayerDistance.x, 2) + powf(PlayerDistance.z, 2)
			<= pow(((ATTACK_AREA / 2) + (PlayerCollisionSize.x / 2)), 2))
		{
			//�������E�̒��Ƀv���C���[������ꍇ
			if (Visibility() == true)
			{
				//�G�ƃv���C���[�̋��������ꂼ��̔��a�̘a��菬����������Փ�
				if (powf(PlayerDistance.x, 2) + powf(PlayerDistance.z, 2)
					<= pow(((BITING_AREA / 2) + (PlayerCollisionSize.x / 2)), 2))
				{
					//�U���p�^�[�������݂��ɂ���
					m_AttackPattern = ATTACK_BITING;
				}
			}
		}
	}
	//�e�U���p�^�[���ɂ�鏈��
	switch (m_AttackPattern)
	{
	case ATTACK_BITING:
		break;
	}
	//�����̗͂�3����ȉ��ɂȂ����ꍇ
	if (nLife <= nLife * 0.3)
	{
	}
	//�����̗͂�0�ɂȂ����ꍇ
	if (nLife <= MINIMUM_LIFE)
	{
		//���S�����֐��Ăяo��
		Death();
	}
}

//=============================================================================
// ���݂������֐�
//=============================================================================
bool CDragon::Biting(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 Position = GetPosition();
	//��]�̎擾
	D3DXVECTOR3 Rotation = GetRotation();
	//�̗͂̎擾
	int nLife = GetLife();
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�����v���C���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (pPlayer != nullptr)
	{
		//�v���C���[�̈ʒu���擾����
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//�v���C���[�̏Փ˔���p�̃T�C�Y���擾����
		D3DXVECTOR3 PlayerCollisionSize = pPlayer->GetCollisionSize();
		//�v���C���[�ƃh���S���̃x�N�g�������߂�
		D3DXVECTOR3 PlayerDistance = D3DXVECTOR3(PlayerPosition.x - Position.x, PlayerPosition.y - Position.y, PlayerPosition.z - Position.z);
		////�v���C���[�ƃh���S���̃x�N�g���̒��������߂�
		float Vector_length = sqrtf((PlayerDistance.x * PlayerDistance.x) + (PlayerDistance.z * PlayerDistance.z));
		//�x�N�g���Ɛ�̒����̔�r
		if (ATTACK_AREA < Vector_length)
		{
			return false;
		}
		D3DXVECTOR3 fan_dir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		D3DXVECTOR3 rotate_fan_dir = D3DXVECTOR3(
			fan_dir.x * cosf(D3DXToRadian(Rotation.y - 90.0f)) + fan_dir.z * -sinf(D3DXToRadian(Rotation.y - 90.0f)),
			0.0f,
			fan_dir.x * 1.0f * sinf(D3DXToRadian(Rotation.y - 90.0f)) + fan_dir.z * cosf(D3DXToRadian(Rotation.y - 90.0f)));
		// ��Ɠ_�̃x�N�g����P�ʃx�N�g���ɂ���
		D3DXVECTOR3 normal_fan_to_point = D3DXVECTOR3(
			PlayerDistance.x / Vector_length,
			0.0f,
			PlayerDistance.z / Vector_length);
		// ���όv�Z
		float dot = normal_fan_to_point.x* rotate_fan_dir.x + normal_fan_to_point.z * rotate_fan_dir.z;
		// ��͈̔͂�cos�ɂ���
		float fan_cos = cosf(D3DXToRadian(120.0f / 2.0f));
		// �_����͈͓̔��ɂ��邩���r����
		if (fan_cos > dot)
		{
			// �������ĂȂ�
			return false;
		}
	}
	return true;
}

//=============================================================================
// ���E�����֐�
//=============================================================================
bool CDragon::Visibility(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 Position = GetPosition();
	//��]�̎擾
	D3DXVECTOR3 Rotation = GetRotation();
	//�̗͂̎擾
	int nLife = GetLife();
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�����v���C���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (pPlayer != nullptr)
	{
		//�v���C���[�̈ʒu���擾����
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//�v���C���[�̏Փ˔���p�̃T�C�Y���擾����
		D3DXVECTOR3 PlayerCollisionSize = pPlayer->GetCollisionSize();
		//�v���C���[�ƃh���S���̃x�N�g�������߂�
		D3DXVECTOR3 PlayerDistance = D3DXVECTOR3(PlayerPosition.x - Position.x, PlayerPosition.y - Position.y, PlayerPosition.z - Position.z);
		////�v���C���[�ƃh���S���̃x�N�g���̒��������߂�
		float Vector_length = sqrtf((PlayerDistance.x * PlayerDistance.x) + (PlayerDistance.z * PlayerDistance.z));
		//�x�N�g���Ɛ�̒����̔�r
		if (ATTACK_AREA < Vector_length)
		{
			return false;
		}
		D3DXVECTOR3 fan_dir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		D3DXVECTOR3 rotate_fan_dir = D3DXVECTOR3(
			fan_dir.x * cosf(D3DXToRadian(Rotation.y - 90.0f)) + fan_dir.z * -sinf(D3DXToRadian(Rotation.y - 90.0f)),
			0.0f,
			fan_dir.x * 1.0f * sinf(D3DXToRadian(Rotation.y - 90.0f)) + fan_dir.z * cosf(D3DXToRadian(Rotation.y - 90.0f)));
		//��Ɠ_�̃x�N�g����P�ʃx�N�g���ɂ���
		D3DXVECTOR3 normal_fan_to_point = D3DXVECTOR3(
			PlayerDistance.x / Vector_length,
			0.0f,
			PlayerDistance.z / Vector_length);
		//���όv�Z
		float dot = normal_fan_to_point.x* rotate_fan_dir.x + normal_fan_to_point.z * rotate_fan_dir.z;
		//��͈̔͂�cos�ɂ���
		float fan_cos = cosf(D3DXToRadian(120.0f / 2.0f));
		//�_����͈͓̔��ɂ��邩���r����
		if (fan_cos > dot)
		{
			// �������ĂȂ�
			return false;
		}
	}
	return true;
}

//=============================================================================
// ���S�����֐�
//=============================================================================
void CDragon::Death(void)
{
	//�����Q�[���N���A���S���������Ă��Ȃ��ꍇ
	if (m_bGameClearLogoCreate == false)
	{
		//�Q�[���N���A���S�̐���
		CGameClearLogo::Create();
		//�Q�[���N���A���S�𐶐�������Ԃɂ���
		m_bGameClearLogoCreate = true;
	}

}
