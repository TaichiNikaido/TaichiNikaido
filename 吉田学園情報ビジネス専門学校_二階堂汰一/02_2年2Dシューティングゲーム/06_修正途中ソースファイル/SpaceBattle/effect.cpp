//=============================================================================
//
// �G�t�F�N�g [effect.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/Bullet.png")
#define SCALE (1.0f)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect(int nPriority)
{
	m_fScale = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CEffect::TextureLoad(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE,									// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CEffect::TextureUnload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CEffect * CEffect::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size, D3DXCOLOR Color, int nLife)
{
	CEffect * pEffect;
	pEffect = new CEffect;
	pEffect->Init(Position, Size, Color, nLife);
	return pEffect;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 Position, D3DXVECTOR3 Size, D3DXCOLOR Color, int nLife)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//2D�V�[���̏����������֐��Ăяo��
	CScene2d::Init();
	//�ʒu�̏����ݒ�
	SetPosition(Position);
	//�T�C�Y�̏����ݒ�
	SetSize(Size);
	SetColor(Color);
	//���C�t�̏����ݒ�
	m_nLife = nLife;
	//�X�P�[���̏����ݒ�
	m_fScale = SCALE;
	SetScale(m_fScale);
	m_fAlpha = 255.0f;
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CEffect::Uninit(void)
{
	//2D�V�[���̏I�������֐��Ăяo��
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CEffect::Update(void)
{
	//�ʒu���擾
	D3DXVECTOR3 Position = GetPosition();
	//�T�C�Y���擾
	D3DXVECTOR3 Size = GetSize();
	//2D�V�[���̍X�V�����֐��Ăяo��
	CScene2d::Update();
	//���C�t��0�ɂȂ�����
	if (m_nLife <= 0)
	{
		//�I�������֐��Ăяo��
		Uninit();
		return;
	}

	if (m_nLife > 0)
	{
		m_fAlpha -= 10.0f;
		m_fScale -= 0.1f;
	}

	//���C�t�����Z����
	m_nLife--;

	//�F��ݒ肷��
	D3DXCOLOR Color = D3DXCOLOR(GetColor().r, GetColor().g, GetColor().b,m_fAlpha);
	SetColor(Color);
	//�ʒu��ݒ�
	SetPosition(Position);
	//�T�C�Y��ݒ�
	SetSize(Size);
	//�X�P�[����ݒ�
	SetScale(m_fScale);
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CEffect::Draw(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	CScene2d::Draw();
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
