//=============================================================================
//
// UI�̃Q�[�W [ui_gauge.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "gauge.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/UI/Gauge.png")		//�e�N�X�`���̃p�X
#define INITIAL_VALUE (0)								//�l�̏����l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGauge::m_pTexture = nullptr;	//�e�N�X�`��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGauge::CGauge()
{
	m_pVtxBuff = nullptr;				//���_�o�b�t�@�̃|�C���^
	m_Position = INITIAL_D3DXVECTOR3;	//�ʒu
	m_Size = INITIAL_D3DXVECTOR3;		//�T�C�Y
	m_Color = INITIAL_D3DXCOLOR;		//�F
	m_nMaxValue = INITIAL_VALUE;		//�l�̍ő�l
	m_nValue = INITIAL_VALUE;			//�l
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGauge::~CGauge()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CGauge::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PASS,					// �t�@�C���̖��O
		&m_pTexture);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CGauge::TextureUnload(void)
{
	// �e�N�X�`���̔j��
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
CGauge * CGauge::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size, D3DXCOLOR Color)
{
	//�Q�[�W�̃|�C���^
	CGauge * pGauge = nullptr;
	//�Q�[�W�̃|�C���^��nullptr�̏ꍇ
	if (pGauge == nullptr)
	{
		//�Q�[�W�̃������m��
		pGauge = new CGauge;
		//�Q�[�W�̃|�C���^��nullptr����Ȃ��ꍇ
		if (pGauge != nullptr)
		{
			//�ʒu��ݒ肷��
			pGauge->SetPosition(Position);
			//�T�C�Y��ݒ肷��
			pGauge->SetSize(Size);
			//�F��ݒ肷��
			pGauge->SetColor(Color);
			//�Q�[�W�̏����������֐��Ăяo��
			pGauge->Init();
		}
	}
	//�Q�[�W�̃|�C���^��Ԃ�
	return pGauge;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CGauge::Init(void)
{
	//�����_���[�̎擾
	CRenderer * pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}
	//���_���̃|�C���^
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (-m_Size.x / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (-m_Size.x / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (m_Size.x / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (m_Size.x / 2), 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CGauge::Uninit(void)
{
	//�������_�o�b�t�@��nullptr����Ȃ��ꍇ
	if (m_pVtxBuff != nullptr)
	{
		//�j�������֐��Ăяo��
		m_pVtxBuff->Release();
		//���_�o�b�t�@��nullptr�ɂ���
		m_pVtxBuff = nullptr;
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CGauge::Update(void)
{
	//���_���̃|�C���^
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// ���_���W��ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Position.x, m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Position.x + m_Size.x * (m_nValue / m_nMaxValue), m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Position.x, m_Position.y + (m_Size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Position.x + m_Size.x * (m_nValue / m_nMaxValue), m_Position.y + (m_Size.y / 2), 0.0f);
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CGauge::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
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
