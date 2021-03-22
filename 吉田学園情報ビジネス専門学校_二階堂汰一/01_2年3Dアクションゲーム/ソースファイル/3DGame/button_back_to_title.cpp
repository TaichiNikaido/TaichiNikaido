//=============================================================================
//
// �^�C�g���ɖ߂�{�^�� [button_back_to_title.cpp]
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
#include "renderer.h"
#include "sound.h"
#include "button_back_to_title.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/Button/Button_Ranking.png")		//�e�N�X�`���̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBackToTitleButton::m_pTexture;	//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBackToTitleButton::CBackToTitleButton()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBackToTitleButton::~CBackToTitleButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBackToTitleButton::TextureLoad(void)
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
void CBackToTitleButton::TextureUnload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j�������֐��Ăяo��
		m_pTexture->Release();
		//�e�N�X�`����NULL�ɂ���
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���������֐��Ăяo��
//=============================================================================
CBackToTitleButton * CBackToTitleButton::Create(D3DXVECTOR3 Position)
{
	//�^�C�g���ɖ߂�{�^���̃|�C���^
	CBackToTitleButton * pBackToTitleButton = NULL;
	//�^�C�g���ɖ߂�{�^���|�C���^��NULL�̏ꍇ
	if (pBackToTitleButton == NULL)
	{
		//�^�C�g���ɖ߂�{�^���̃������m��
		pBackToTitleButton = new CBackToTitleButton;
		//�^�C�g���ɖ߂�{�^���̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pBackToTitleButton != NULL)
		{
			//�^�C�g���ɖ߂�{�^���̈ʒu�ݒ�
			pBackToTitleButton->SetPosition(Position);
			//�^�C�g���ɖ߂�{�^���̏����������֐��Ăяo��
			pBackToTitleButton->Init();
		}
	}
	//�^�C�g���ɖ߂�{�^���̃|�C���^��Ԃ�
	return pBackToTitleButton;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBackToTitleButton::Init(void)
{
	//�e�N�X�`����UV���W�̐ݒ�
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//�{�^���̏����������֐��Ăяo��
	CButton::Init();
	//�e�N�X�`���̐ݒ�
	SetTexture(aTexture);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CBackToTitleButton::Uninit(void)
{
	//�{�^���̏I�������֐��Ăяo��
	CButton::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBackToTitleButton::Update(void)
{
	//�{�^���̍X�V�����֐��Ăяo��
	CButton::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBackToTitleButton::Draw(void)
{
	//�{�^���̕`�揈���֐��Ăяo��
	CButton::Draw();
}

//=============================================================================
// �v���X�����֐�
//=============================================================================
void CBackToTitleButton::Press(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�����T�E���h�̃|�C���^��NULL����Ȃ��ꍇ
	if (pSound != NULL)
	{
		//���艹�̍Đ�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);
	}
	//�^�C�g�����[�h�ɑJ�ڂ���
	CManager::StartFade(CManager::MODE_TITLE);
}