//=============================================================================
//
// ��w�w�i [background_upper_layer.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "background_upper_layer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Background/background_upper_layer.png")	//�e�N�X�`��
#define SIZE (D3DXVECTOR3(1120.0f,1080.0f,0.0f))						//�T�C�Y
#define FLAME (5)														//�t���[��
#define MOVE_VALUE (0.003f)												//�ړ���

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBackgroundUpperLayer::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBackgroundUpperLayer::CBackgroundUpperLayer()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBackgroundUpperLayer::~CBackgroundUpperLayer()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBackgroundUpperLayer::TextureLoad(void)
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
void CBackgroundUpperLayer::TextureUnload(void)
{
	//�����e�N�X�`����NULL�ł͂Ȃ��ꍇ
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
CBackgroundUpperLayer * CBackgroundUpperLayer::Create(D3DXVECTOR3 Position)
{
	//��w�w�i�̃|�C���^
	CBackgroundUpperLayer * pBackgroundUpperLayer = NULL;
	//������w�w�i�̃|�C���^��NULL�̏ꍇ
	if (pBackgroundUpperLayer == NULL)
	{
		//������w�w�i�̃��������m��
		pBackgroundUpperLayer = new CBackgroundUpperLayer;
		//������w�w�i�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pBackgroundUpperLayer != NULL)
		{
			//�����������֐��Ăяo��
			pBackgroundUpperLayer->Init();
			//�ʒu��ݒ肷��
			pBackgroundUpperLayer->SetPosition(Position);
		}
	}
	//��w�w�i�̃|�C���^��Ԃ�
	return pBackgroundUpperLayer;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBackgroundUpperLayer::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�w�i�̏����������֐��Ăяo��
	CBackground::Init();
	//�T�C�Y�̏����ݒ�
	SetSize(SIZE);
	//�t���[���̏����ݒ�
	SetFlame(FLAME);
	//�ړ��ʂ�ݒ�
	SetMove(MOVE_VALUE);
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CBackgroundUpperLayer::Uninit(void)
{
	//�w�i�̏I�������֐��Ăяo��
	CBackground::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBackgroundUpperLayer::Update(void)
{
	//�w�i�̍X�V�����֐��Ăяo��
	CBackground::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBackgroundUpperLayer::Draw(void)
{
	//�w�i�̕`�揈���֐��Ăяo��
	CBackground::Draw();
}
