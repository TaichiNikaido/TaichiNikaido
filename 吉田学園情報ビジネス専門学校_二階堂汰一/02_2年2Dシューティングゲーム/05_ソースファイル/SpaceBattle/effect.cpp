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
#define TEXTURE ("Data/Texture/Bullet/Bullet.png")	//�e�N�X�`��
#define SCALE (1.0f)								//�g�k
#define MINIMUM_SCALE (0.0f)
#define ALPHA (255.0f)
#define SUB_ALPHA (10.0f)
#define SUB_SCALE (0.1f)
#define MINIMUM_LIFE (0)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect(int nPriority)
{
	m_fScale = MINIMUM_SCALE;	//�g�k
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
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
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
CEffect * CEffect::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size, D3DXCOLOR Color, int nLife)
{
	//�G�t�F�N�g�̃|�C���^
	CEffect * pEffect = NULL;
	//�����G�t�F�N�g�̃|�C���^��NULL�̏ꍇ
	if (pEffect == NULL)
	{
		//�G�t�F�N�g�̃������m��
		pEffect = new CEffect;
	}
	//�����G�t�F�N�g�̃|�C���^��NULL����Ȃ��ꍇ
	if (pEffect != NULL)
	{
		//�����������֐��Ăяo��
		pEffect->Init(Position, Size, Color, nLife);
	}
	//�G�t�F�N�g�̃|�C���^��Ԃ�
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
	//�J���[�̏����ݒ�
	SetColor(Color);
	//���C�t�̏����ݒ�
	m_nLife = nLife;
	//�X�P�[���̏����ݒ�
	m_fScale = SCALE;
	//�g�k��ݒ肷��
	SetScale(m_fScale);
	//�A���t�@�l�̑��
	m_fAlpha = ALPHA;
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
	if (m_nLife <= MINIMUM_LIFE)
	{
		//�I�������֐��Ăяo��
		Uninit();
		return;
	}
	//�������C�t��0���ゾ������
	if (m_nLife > MINIMUM_LIFE)
	{
		//�A���t�@�l�����Z����
		m_fAlpha -= SUB_ALPHA;
		//�k������
		m_fScale -= SUB_SCALE;
	}
	//���C�t�����Z����
	m_nLife--;
	//�F��������
	D3DXCOLOR Color = D3DXCOLOR(GetColor().r, GetColor().g, GetColor().b,m_fAlpha);
	//�F��ݒ肷��
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
	//�����_���[�̎擾
	CRenderer * pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�A���t�@�u�����h
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//�`�揈���֐��Ăяo��
	CScene2d::Draw();
	//�A���t�@�u�����h�����ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
