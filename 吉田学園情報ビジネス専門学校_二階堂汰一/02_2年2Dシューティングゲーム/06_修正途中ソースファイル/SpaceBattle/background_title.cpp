//=============================================================================
//
// �^�C�g���w�i [background_title.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "renderer.h"
#include "scene2d.h"
#include "background.h"
#include "background_title.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Background/background_title.png")
#define SIZE (D3DXVECTOR3(1920.0f,1080.0f,0.0f))
#define FLAME (0)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBackgroundTitle::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBackgroundTitle::CBackgroundTitle(int nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBackgroundTitle::~CBackgroundTitle()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBackgroundTitle::TextureLoad(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
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
void CBackgroundTitle::TextureUnload(void)
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
CBackgroundTitle * CBackgroundTitle::Create(D3DXVECTOR3 Position)
{
	CBackgroundTitle * pBackgroundTitle;
	pBackgroundTitle = new CBackgroundTitle;
	pBackgroundTitle->Init();
	pBackgroundTitle->SetPosition(Position);
	return pBackgroundTitle;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBackgroundTitle::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�w�i�̏���������
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
void CBackgroundTitle::Uninit(void)
{
	//�w�i�̏I������
	CBackground::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBackgroundTitle::Update(void)
{
	//�w�i�̍X�V����
	CBackground::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBackgroundTitle::Draw(void)
{
	//�w�i�̕`�揈��
	CBackground::Draw();
}
