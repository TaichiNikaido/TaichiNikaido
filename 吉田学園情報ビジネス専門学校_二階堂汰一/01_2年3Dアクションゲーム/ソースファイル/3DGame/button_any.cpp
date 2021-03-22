//=============================================================================
//
// ���炩�̃{�^�� [button_any.cpp]
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
#include "keyboard.h"
#include "joystick.h"
#include "sound.h"
#include "button_any.h"
#include "title_button_manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/Button/Button_Any.png")
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT - SCREEN_HEIGHT / 4,0.0f))

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CAnyButton::m_pTexture;	//�e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CAnyButton::CAnyButton()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CAnyButton::~CAnyButton()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//=============================================================================
HRESULT CAnyButton::TextureLoad(void)
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
void CAnyButton::TextureUnload(void)
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
CAnyButton * CAnyButton::Create()
{
	//���炩�̃{�^���̃|�C���^
	CAnyButton * pAnyButton = NULL;
	//���炩�̃{�^���̃|�C���^��NULL�̏ꍇ
	if (pAnyButton == NULL)
	{
		//���炩�̃{�^���̃������m��
		pAnyButton = new CAnyButton;
		//���炩�̃{�^���̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pAnyButton != NULL)
		{
			//���炩�̃{�^���̈ʒu�ݒ�
			pAnyButton->SetPosition(POSITION);
			//���炩�̃{�^���̏����������֐��Ăяo��
			pAnyButton->Init();
		}
	}
	//���炩�̃{�^���̃|�C���^��Ԃ�
	return pAnyButton;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CAnyButton::Init(void)
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
	//�I�����F�ύX�����֐��Ăяo��
	SelectColor();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CAnyButton::Uninit(void)
{
	//�{�^���̏I�������֐��Ăяo��
	CButton::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CAnyButton::Update(void)
{
	//�{�^���̍X�V�����֐��Ăяo��
	CButton::Update();
	//���͏����֐��Ăяo��
	Input();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CAnyButton::Draw(void)
{
	//�{�^���̕`�揈���֐��Ăяo��
	CButton::Draw();
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CAnyButton::Input(void)
{
	//�L�[�{�[�h�̎擾
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//�W���C�X�e�B�b�N�̐U���擾
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//�C�ӂ̃{�^��������
	for (int nCount = 0; nCount <= JS_START; nCount++)
	{
		//�����C�ӂ̃{�^���������ꂽ��
		if (pJoystick->GetJoystickTrigger(nCount))
		{
			//�v���X�����֐��Ăяo��
			Press();
		}
	}
}

//=============================================================================
// �v���X�����֐�
//=============================================================================
void CAnyButton::Press(void)
{
	//�L�[�{�[�h�̎擾
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//�W���C�X�e�B�b�N�̐U���擾
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�����T�E���h�̃|�C���^��NULL����Ȃ��ꍇ
	if (pSound != NULL)
	{
		//���艹�̍Đ�
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);
	}
	//�^�C�g���{�^���}�l�[�W���[�̐���
	CTitleButtonManager::Create();
	//�L�[�{�[�h�̍X�V�����֐��Ăяo��
	pKeyboard->Update();
	//�W���C�X�e�B�b�N�̍X�V�����֐��Ăяo��
	pJoystick->Update();
	//�I�������֐��Ăяo��
	Uninit();
	return;
}