//=============================================================================
//
// �ۉ� [round_fire.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Mode/mode_game.h"
#include "Base/renderer.h"
#include "Base/polygon3d.h"
#include "round_fire.h"
#include "Character/player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/round_fire.png")			//�e�N�X�`��
#define SIZE (D3DXVECTOR3(50.0f,50.0f,50.0f))			//�T�C�Y
#define ROTATION (D3DXVECTOR3(D3DXToRadian(-90.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)))	//��]

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CRoundFire::m_pTexture = nullptr;		//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRoundFire::CRoundFire(int nPriority) : CPolygon3d(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRoundFire::~CRoundFire()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CRoundFire::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE,						// �t�@�C���̖��O
		&m_pTexture);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CRoundFire::TextureUnload(void)
{
	//�����e�N�X�`����nullptr����Ȃ��ꍇ
	if (m_pTexture != nullptr)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`����nullptr�ɂ���
		m_pTexture = nullptr;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CRoundFire * CRoundFire::Create(D3DXVECTOR3 Position)
{
	//�ۉ΂̃|�C���^
	CRoundFire * pRoundFire = nullptr;
	//�����ۉ΂̃|�C���^��nullptr�̏ꍇ
	if (pRoundFire == nullptr)
	{
		//�ۉ΂̃������m��
		pRoundFire = new CRoundFire;
		//�����ۉ΂�nullptr�ł͂Ȃ��ꍇ
		if (pRoundFire != nullptr)
		{
			//�ۉ΂̈ʒu��ݒ�
			pRoundFire->SetPosition(Position);
			//�ۉ΂̏����������֐��Ăяo��
			pRoundFire->Init();
		}
	}
	//�ۉ΂̃|�C���^��Ԃ�
	return pRoundFire;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CRoundFire::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//��]��ݒ肷��
	SetRotation(ROTATION);
	//�|���S��3D�̏����������֐��Ăяo��
	CPolygon3d::Init();
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CRoundFire::Uninit(void)
{
	//�|���S��3D�̏I�������֐��Ăяo��
	CPolygon3d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CRoundFire::Update(void)
{
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�ʒu���擾����
	D3DXVECTOR3 Position = GetPosition();
	//�|���S��3D�̍X�V�����֐��Ăяo��
	CPolygon3d::Update();
	//�����v���C���[�̃|�C���^��nullptr�̏ꍇ
	if (pPlayer != nullptr)
	{
		//�v���C���[�̈ʒu���擾����
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//�v���C���[�܂ł̋��������߂�
		D3DXVECTOR3 Distance = D3DXVECTOR3(PlayerPosition.x - Position.x, PlayerPosition.y - Position.y, PlayerPosition.z - Position.z);
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CRoundFire::Draw(void)
{
	//�|���S��3D�̕`�揈���֐��Ăяo��
	CPolygon3d::Draw();
}