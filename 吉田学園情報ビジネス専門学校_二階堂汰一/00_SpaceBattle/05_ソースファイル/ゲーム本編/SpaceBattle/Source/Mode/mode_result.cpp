//=============================================================================
//
// ���U���g���[�h [mode_result.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/sound.h"
#include "mode_result.h"
#include "Background/background_result.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "System/result.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResultMode::CResultMode()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResultMode::~CResultMode()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CResultMode * CResultMode::Create()
{
	//���U���g���[�h�̃|�C���^
	CResultMode * pResultMode = NULL;
	//�������U���g���[�h�̃|�C���^��NULL�̏ꍇ
	if (pResultMode == NULL)
	{
		//���U���g���[�h�̃������m��
		pResultMode = new CResultMode;
		//�������U���g���[�h�̃|�C���^��NULL����Ȃ��ꍇ
		if (pResultMode != NULL)
		{
			//���U���g���[�h�̏����������֐��Ăяo��
			pResultMode->Init();
		}
	}
	//���U���g���[�h�̃|�C���^��Ԃ�
	return pResultMode;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CResultMode::Init(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//BGM�̍Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);
	//�S���������֐��Ăяo��
	CreateAll();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CResultMode::Uninit(void)
{
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CResultMode::Update(void)
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
		CManager::StartFade(CManager::MODE_RANKING);
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CResultMode::Draw(void)
{
}

//=============================================================================
// �S���������֐�
//=============================================================================
void CResultMode::CreateAll(void)
{
	CBackgroundResult::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pResult = CResult::Create();
}
