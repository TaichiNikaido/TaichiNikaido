//=============================================================================
//
// �����L���O�w�i [background_ranking.cpp]
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
#include "background_ranking.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/Background/background_ranking.png")	//�e�N�X�`��
#define SIZE (D3DXVECTOR3(1920.0f,1080.0f,0.0f))					//�T�C�Y
#define FLAME (0)													//�t���[��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBackgroundRanking::m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBackgroundRanking::CBackgroundRanking()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBackgroundRanking::~CBackgroundRanking()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBackgroundRanking::TextureLoad(void)
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
void CBackgroundRanking::TextureUnload(void)
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
CBackgroundRanking * CBackgroundRanking::Create(D3DXVECTOR3 Position)
{
	//�����L���O�w�i�̃|�C���^
	CBackgroundRanking * pbackgeroundRanking = NULL;
	//���������L���O�w�i��NULL�̏ꍇ
	if (pbackgeroundRanking == NULL)
	{
		//�����L���O�w�i�̃��������m�ۂ���
		pbackgeroundRanking = new CBackgroundRanking;
		//���������L���O�w�i��NULL����Ȃ��ꍇ
		if (pbackgeroundRanking != NULL)
		{
			//�����������֐��Ăяo��
			pbackgeroundRanking->Init();
			//�ʒu��ݒ肷��
			pbackgeroundRanking->SetPosition(Position);
		}
	}
	//�����L���O�w�i��Ԃ�
	return pbackgeroundRanking;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBackgroundRanking::Init(void)
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
void CBackgroundRanking::Uninit(void)
{
	//�w�i�̏I������
	CBackground::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBackgroundRanking::Update(void)
{
	//�w�i�̍X�V����
	CBackground::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBackgroundRanking::Draw(void)
{
	//�w�i�̕`�揈��
	CBackground::Draw();
}
