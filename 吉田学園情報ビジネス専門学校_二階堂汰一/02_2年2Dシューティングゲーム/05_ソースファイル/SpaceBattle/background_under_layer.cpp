//=============================================================================
//
// ���w�w�i [background_under_layer.cpp]
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
#include "background_under_layer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Background/background_under_layer.png")
#define SIZE (D3DXVECTOR3(1120.0f,1080.0f,0.0f))
#define FLAME (3)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBackgroundUnderLayer::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBackgroundUnderLayer::CBackgroundUnderLayer()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBackgroundUnderLayer::~CBackgroundUnderLayer()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBackgroundUnderLayer::TextureLoad(void)
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
void CBackgroundUnderLayer::TextureUnload(void)
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
CBackgroundUnderLayer * CBackgroundUnderLayer::Create(D3DXVECTOR3 Position)
{
	//���w�w�i�̃|�C���^
	CBackgroundUnderLayer * pBackgroundUnderLayer = NULL;
	//�������w�w�i�̃|�C���^��NULL�̏ꍇ
	if (pBackgroundUnderLayer == NULL)
	{
		//���w�w�i�̃������m��
		pBackgroundUnderLayer = new CBackgroundUnderLayer;
	}
	//�������w�w�i�̃|�C���^��NULL����Ȃ��ꍇ
	if (pBackgroundUnderLayer == NULL)
	{
		//�����������֐��Ăяo��
		pBackgroundUnderLayer->Init();
		//�ʒu��ݒ肷��
		pBackgroundUnderLayer->SetPosition(Position);
	}
	return pBackgroundUnderLayer;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBackgroundUnderLayer::Init(void)
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
void CBackgroundUnderLayer::Uninit(void)
{
	//�w�i�̏I������
	CBackground::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBackgroundUnderLayer::Update(void)
{
	//�w�i�̍X�V����
	CBackground::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBackgroundUnderLayer::Draw(void)
{
	//�w�i�̕`�揈��
	CBackground::Draw();
}
