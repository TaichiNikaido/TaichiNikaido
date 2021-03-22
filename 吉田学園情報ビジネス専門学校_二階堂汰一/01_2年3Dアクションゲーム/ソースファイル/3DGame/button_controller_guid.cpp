//=============================================================================
//
// �Q�[���ɖ߂�{�^�� [button_quit_game.cpp]
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
#include "button_controller_guid.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/Button/Button_Ranking.png")		//�e�N�X�`���̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CControllerGuidButton::m_pTexture;	//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControllerGuidButton::CControllerGuidButton()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControllerGuidButton::~CControllerGuidButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CControllerGuidButton::TextureLoad(void)
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
void CControllerGuidButton::TextureUnload(void)
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
CControllerGuidButton * CControllerGuidButton::Create(D3DXVECTOR3 Position)
{
	//��������{�^���̃|�C���^
	CControllerGuidButton * pControllerGuidButton = NULL;
	//��������{�^���|�C���^��NULL�̏ꍇ
	if (pControllerGuidButton == NULL)
	{
		//��������{�^���̃������m��
		pControllerGuidButton = new CControllerGuidButton;
		//��������{�^���̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pControllerGuidButton != NULL)
		{
			//��������{�^���̈ʒu�ݒ�
			pControllerGuidButton->SetPosition(Position);
			//��������{�^���̏����������֐��Ăяo��
			pControllerGuidButton->Init();
		}
	}
	//��������{�^���̃|�C���^��Ԃ�
	return pControllerGuidButton;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CControllerGuidButton::Init(void)
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
void CControllerGuidButton::Uninit(void)
{
	//�{�^���̏I�������֐��Ăяo��
	CButton::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CControllerGuidButton::Update(void)
{
	//�{�^���̍X�V�����֐��Ăяo��
	CButton::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CControllerGuidButton::Draw(void)
{
	//�{�^���̕`�揈���֐��Ăяo��
	CButton::Draw();
}

//=============================================================================
// �v���X�����֐�
//=============================================================================
void CControllerGuidButton::Press(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�����T�E���h�̃|�C���^��NULL����Ȃ��ꍇ
	if (pSound != NULL)
	{
		//���艹�̍Đ�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);
	}
}