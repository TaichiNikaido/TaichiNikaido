//=============================================================================
//
// UI�p�̗͂̃e�N�X�`������ [ui_life_texture.h]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "ui_life_texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/UI/ui_life.png")

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CUILifeTexture::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CUILifeTexture::CUILifeTexture()
{
	m_pVtxBuff = NULL;		//�o�b�t�@
	m_nPatternAnim = 0;		//�A�j���p�^�[��
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CUILifeTexture::~CUILifeTexture()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CUILifeTexture::TextureLoad(void)
{
	//�����_���[�̐ݒ�
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
void CUILifeTexture::TextureUnload(void)
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
CUILifeTexture * CUILifeTexture::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size)
{
	CUILifeTexture * pUILifeTexture;
	pUILifeTexture = new CUILifeTexture;
	pUILifeTexture->SetPosition(Position);
	pUILifeTexture->SetSize(Size);
	pUILifeTexture->Init();
	return pUILifeTexture;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CUILifeTexture::Init(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (m_Size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (m_Size.y / 2), 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CUILifeTexture::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CUILifeTexture::Update(void)
{
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CUILifeTexture::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// �e�N�X�`���ݒ�֐�
//=============================================================================
void CUILifeTexture::SetLifeTexture(int nAlpha)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nAlpha);

	m_pVtxBuff->Unlock();
}

//=============================================================================
// �ʒu�ݒ�֐�
//=============================================================================
void CUILifeTexture::SetPosition(D3DXVECTOR3 Position)
{
	//�ʒu��ݒ肷��
	m_Position = Position;
}

//=============================================================================
// �T�C�Y�ݒ�֐�
//=============================================================================
void CUILifeTexture::SetSize(D3DXVECTOR3 Size)
{
	//�ʒu��ݒ肷��
	m_Size = Size;
}
