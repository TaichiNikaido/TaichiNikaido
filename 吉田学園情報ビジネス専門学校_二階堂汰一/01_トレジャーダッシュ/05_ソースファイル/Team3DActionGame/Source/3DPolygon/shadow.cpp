//=============================================================================
//
// �e [shadow.cpp]
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
#include "shadow.h"
#include "Character/player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/shadow.png")			//�e�N�X�`��
#define SIZE (D3DXVECTOR3(150.0f,150.0f,0.0f))		//�T�C�Y
#define FLAME (0)									//�t���[��
#define COLOR (D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f))	//�F
#define ROTATION (D3DXVECTOR3(D3DXToRadian(-90.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f)))	//��]

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CShadow::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShadow::CShadow(int nPriority) : CPolygon3d(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShadow::~CShadow()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CShadow::TextureLoad(void)
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
void CShadow::TextureUnload(void)
{
	//�����e�N�X�`����NULL����Ȃ��ꍇ
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`����NULL�ɂ���
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CShadow * CShadow::Create(void)
{
	//�e�̃|�C���^
	CShadow * pShadow = NULL;
	//�����e�̃|�C���^��NULL�̏ꍇ
	if (pShadow == NULL)
	{
		//�e�̃������m��
		pShadow = new CShadow;
		//�����e��NULL����Ȃ��ꍇ
		if (pShadow != NULL)
		{
			//�����������֐��Ăяo��
			pShadow->Init();
		}
	}
	//�e�̃|�C���^��Ԃ�
	return pShadow;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CShadow::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�����v���C���[�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̈ʒu���擾����
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPos();
		//�ʒu��ݒ肷��
		SetPosition(D3DXVECTOR3(PlayerPosition.x, 10.0f, PlayerPosition.z));
	}
	//�T�C�Y��ݒ肷��
	SetSize(SIZE);
	//�F��ݒ肷��
	SetColor(COLOR);
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
void CShadow::Uninit(void)
{
	//�|���S��3D�̏I�������֐��Ăяo��
	CPolygon3d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CShadow::Update(void)
{
	//�|���S��3D�̍X�V�����֐��Ăяo��
	CPolygon3d::Update();
	//�v���C���[�̎擾
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//�����v���C���[�̃|�C���^��NULL�ł͂Ȃ��ꍇ
	if (pPlayer != NULL)
	{
		//�v���C���[�̈ʒu���擾����
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPos();
		//�ʒu��ݒ肷��
		SetPosition(D3DXVECTOR3(PlayerPosition.x, 10.0f, PlayerPosition.z));
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CShadow::Draw(void)
{
	//�|���S��3D�̕`�揈���֐��Ăяo��
	CPolygon3d::Draw();
}
