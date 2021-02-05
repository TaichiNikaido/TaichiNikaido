//=============================================================================
//
// �`���[�g���A���w�i [background_tutorial.cpp]
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
#include "background_tutorial.h"
#include "joystick.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define KEYBOARD_GUID_TEXTURE ("Data/Texture/Background/background_keyboard_guid.png")
#define JOYSTICK_GUID_TEXTURE ("Data/Texture/Background/background_joystick_guid.png")
#define SIZE (D3DXVECTOR3(1920.0f,1080.0f,0.0f))
#define FLAME (0)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBackgroundTutorial::m_apTexture[TEXTURE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBackgroundTutorial::CBackgroundTutorial(int nPriority) : CBackground(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBackgroundTutorial::~CBackgroundTutorial()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CBackgroundTutorial::TextureLoad(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		KEYBOARD_GUID_TEXTURE,					// �t�@�C���̖��O
		&m_apTexture[TEXTURE_KEYBOARD_GUID]);	// �ǂݍ��ރ������[
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		JOYSTICK_GUID_TEXTURE,					// �t�@�C���̖��O
		&m_apTexture[TEXTURE_JOYSTICK_GUID]);	// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���j���֐�
//=============================================================================
void CBackgroundTutorial::TextureUnload(void)
{
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// ���������֐�
//=============================================================================
CBackgroundTutorial * CBackgroundTutorial::Create(D3DXVECTOR3 Position)
{
	CBackgroundTutorial * pBackgroundTutorial;
	pBackgroundTutorial = new CBackgroundTutorial;
	pBackgroundTutorial->Init();
	pBackgroundTutorial->SetPosition(Position);
	return pBackgroundTutorial;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBackgroundTutorial::Init(void)
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
	//�����W���C�X�e�B�b�N��NULL��������
	if (CJoystick::GetDevice() == NULL)
	{
		//�e�N�X�`���̊��蓖��
		BindTexture(m_apTexture[TEXTURE_KEYBOARD_GUID]);
	}
	else
	{
		//�e�N�X�`���̊��蓖��
		BindTexture(m_apTexture[TEXTURE_JOYSTICK_GUID]);
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CBackgroundTutorial::Uninit(void)
{
	//�w�i�̏I������
	CBackground::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBackgroundTutorial::Update(void)
{
	//�w�i�̍X�V����
	CBackground::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBackgroundTutorial::Draw(void)
{
	//�w�i�̕`�揈��
	CBackground::Draw();
}
