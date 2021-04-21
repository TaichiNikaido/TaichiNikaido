//=============================================================================
//
// ���� [letter.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "letter.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/letter.png")	//�e�N�X�`���̃p�X
#define SIZE (D3DXVECTOR3(125.0f,125.0f,0.0f))		//�T�C�Y
#define SELECT_ALPHA (0.5f)							//�I�����̃��l
#define NOT_SELECT_ALPHA (1.0f)						//���I�����̃��l

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLetter::m_pTexture = nullptr;		//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLetter::CLetter()
{
	m_pVtxBuff = nullptr;							//�o�b�t�@�ւ̃|�C���^
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�T�C�Y
	m_fAlpha = 0.0f;								//�����x
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLetter::~CLetter()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CLetter::TextureLoad(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,		//�f�o�C�X�ւ̃|�C���^
		TEXTURE_PASS,						//�t�@�C���̖��O
		&m_pTexture);						//�ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CLetter::TextureUnload(void)
{
	//�����e�N�X�`����nullptr�ł͂Ȃ��ꍇ
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
CLetter * CLetter::Create(D3DXVECTOR3 Position)
{
	//�ԍ��̃e�N�X�`���̃|�C���^
	CLetter * pLetter = nullptr;
	//�����ԍ��̃e�N�X�`���̃|�C���^��NULL�̏ꍇ
	if (pLetter == nullptr)
	{
		//�ԍ��̃e�N�X�`���̃������m��
		pLetter = new CLetter;
		//�����ԍ��̃e�N�X�`���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pLetter != nullptr)
		{
			//�ʒu��ݒ肷��
			pLetter->SetPostion(Position);
			//�T�C�Y��ݒ肷��
			pLetter->SetSize(SIZE);
			//�����������֐��Ăяo��
			pLetter->Init();
		}
	}
	//�ԍ��̃e�N�X�`���̃|�C���^��Ԃ�
	return pLetter;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CLetter::Init(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	//���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			//���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				//�g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			//���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				//���_�o�b�t�@�ւ̃|�C���^
		NULL)))						//NULL�ɐݒ�
	{
		return E_FAIL;
	}
	//���_����ݒ�
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (m_Size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (m_Size.y / 2), 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((1.0f / 26.0f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / 26.0f) + (1.0f / 26.0f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / 26.0f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / 26.0f) + (1.0f / 26.0f), 1.0f);
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CLetter::Uninit(void)
{
	//�������_�o�b�t�@�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
	if (m_pVtxBuff != nullptr)
	{
		//���_�o�b�t�@�̔j�������֐��Ăяo��
		m_pVtxBuff->Release();
		//���_�o�b�t�@�̃|�C���^��nullptr�ɂ���
		m_pVtxBuff = nullptr;
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CLetter::Update(void)
{
	//���_����ݒ�
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CLetter::Draw(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�Ƀ����_���[�̃f�o�C�X����
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// �I�����F�ύX�����֐�
//=============================================================================
void CLetter::SelectColor(void)
{
	//���l��ݒ肷��
	m_fAlpha = SELECT_ALPHA;
}

//=============================================================================
// ���I�����F�ύX�����֐�
//=============================================================================
void CLetter::NotSelectColor(void)
{
	//���l��ݒ肷��
	m_fAlpha = NOT_SELECT_ALPHA;
}

//=============================================================================
// �������蓖�ď����֐�
//=============================================================================
void CLetter::SetLetter(int nLetter)
{
	//���_���
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	if (nLetter != -1)//-1����Ȃ���Εs������
	{
		//�����x��ݒ肷��
		m_fAlpha = 1.0f;
		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(nLetter * (1.0f / 26.0f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nLetter * (1.0f / 26.0f) + (1.0f / 26.0f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nLetter * (1.0f / 26.0f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nLetter * (1.0f / 26.0f) + (1.0f / 26.0f), 1.0f);
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
	}
	else
	{
		//�����x��ݒ肷��
		m_fAlpha = 0.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
	}
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
