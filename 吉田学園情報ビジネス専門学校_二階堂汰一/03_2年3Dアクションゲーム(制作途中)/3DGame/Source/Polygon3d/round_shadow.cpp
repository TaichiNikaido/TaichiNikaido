//=============================================================================
//
// �ۉe [round_shadow.cpp]
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
#include "round_shadow.h"
#include "Character/player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/shadow.png")			//�e�N�X�`��
#define ROTATION (D3DXVECTOR3(D3DXToRadian(-90.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)))	//��]

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CRoundShadow::m_pTexture = nullptr;		//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRoundShadow::CRoundShadow(int nPriority) : CPolygon3d(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRoundShadow::~CRoundShadow()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CRoundShadow::TextureLoad(void)
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
void CRoundShadow::TextureUnload(void)
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
CRoundShadow * CRoundShadow::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size, D3DXCOLOR Color)
{
	//�ۉe�̃|�C���^
	CRoundShadow * pRoundShadow = nullptr;
	//�����ۉe�̃|�C���^��nullptr�̏ꍇ
	if (pRoundShadow == nullptr)
	{
		//�ۉe�̃������m��
		pRoundShadow = new CRoundShadow;
		//�����ۉe��nullptr�ł͂Ȃ��ꍇ
		if (pRoundShadow != nullptr)
		{
			//�ۉe�̈ʒu��ݒ�
			pRoundShadow->SetPosition(Position);
			//�ۉe�̃T�C�Y��ݒ�
			pRoundShadow->SetSize(Size);
			//�ۉe�̐F��ݒ�
			pRoundShadow->SetColor(Color);
			//�ۉe�̏����������֐��Ăяo��
			pRoundShadow->Init();
		}
	}
	//�ۉe�̃|�C���^��Ԃ�
	return pRoundShadow;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CRoundShadow::Init(void)
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
void CRoundShadow::Uninit(void)
{
	//�|���S��3D�̏I�������֐��Ăяo��
	CPolygon3d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CRoundShadow::Update(void)
{
	//�|���S��3D�̍X�V�����֐��Ăяo��
	CPolygon3d::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CRoundShadow::Draw(void)
{
	//�|���S��3D�̕`�揈���֐��Ăяo��
	CPolygon3d::Draw();
}