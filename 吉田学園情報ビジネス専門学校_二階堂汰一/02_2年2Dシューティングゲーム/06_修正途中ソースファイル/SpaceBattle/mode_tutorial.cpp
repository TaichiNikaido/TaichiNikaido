//=============================================================================
//
// �`���[�g���A�����[�h [mode_tutorial.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "mode_tutorial.h"
#include "background_tutorial.h"
#include "keyboard.h"
#include "joystick.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorialMode::CTutorialMode()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorialMode::~CTutorialMode()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CTutorialMode * CTutorialMode::Create()
{
	CTutorialMode * pTutorialMode;
	pTutorialMode = new CTutorialMode;
	pTutorialMode->Init();
	return pTutorialMode;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CTutorialMode::Init(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//BGM�̍Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);
	//�S���������֐��Ăяo��
	CreateAll();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CTutorialMode::Uninit(void)
{
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CTutorialMode::Update(void)
{
	//�L�[�{�[�h�̎擾
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
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
	//����ENTER��A�{�^�����������Ƃ�
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pJoystick->GetJoystickTrigger(JS_A))
	{
		//�T�E���h�̒�~
		pSound->StopSound();
		//�����L���O�Ɉړ�
		CManager::StartFade(CManager::MODE_GAME);
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CTutorialMode::Draw(void)
{
}

//=============================================================================
// �S���������֐�
//=============================================================================
void CTutorialMode::CreateAll(void)
{
	//�`���[�g���A���w�i����
	CBackgroundTutorial::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
}
