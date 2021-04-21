//=============================================================================
//
// ���U���g�w�i [background_result.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "background_result.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Background/background_result.png")	//�e�N�X�`��
#define SIZE (D3DXVECTOR3(1920.0f,1080.0f,0.0f))					//�T�C�Y
#define FLAME (0)													//�t���[��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBackgroundResult::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBackgroundResult::CBackgroundResult()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBackgroundResult::~CBackgroundResult()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBackgroundResult::TextureLoad(void)
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
void CBackgroundResult::TextureUnload(void)
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
CBackgroundResult * CBackgroundResult::Create(D3DXVECTOR3 Position)
{
	//���U���g�w�i�̃|�C���^
	CBackgroundResult * pBackgroundResult = NULL;
	//�������U���g�w�i�̃|�C���^��NULL�̏ꍇ
	if (pBackgroundResult == NULL)
	{
		//���U���g�w�i�̃������m��
		pBackgroundResult = new CBackgroundResult;
		//�������U���g�w�i�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pBackgroundResult != NULL)
		{
			//���U���g�w�i�̏����������֐��Ăяo��
			pBackgroundResult->Init();
			//���U���g�w�i�̈ʒu��ݒ肷��
			pBackgroundResult->SetPosition(Position);
		}
	}
	//���U���g�̔w�i��Ԃ�
	return pBackgroundResult;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBackgroundResult::Init(void)
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
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CBackgroundResult::Uninit(void)
{
	//�w�i�̏I�������֐��Ăяo��
	CBackground::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBackgroundResult::Update(void)
{
	//�w�i�̍X�V�����֐��Ăяo��
	CBackground::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBackgroundResult::Draw(void)
{
	//�w�i�̕`�揈���֐��Ăяo��
	CBackground::Draw();
}
