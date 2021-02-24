//=============================================================================
//
// �����L���O���[�h [mode_ranking.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "mode_ranking.h"
#include "background_ranking.h"
#include "keyboard.h"
#include "joystick.h"
#include "ranking.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRankingMode::CRankingMode()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRankingMode::~CRankingMode()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CRankingMode * CRankingMode::Create()
{
	//�����L���O���[�h�̃|�C���^
	CRankingMode * pRankingMode = NULL;
	//���������L���O���[�h�̃|�C���^��NULL�̏ꍇ
	if (pRankingMode == NULL)
	{
		//�����L���O���[�h�̃������m��
		pRankingMode = new CRankingMode;
		//���������L���O���[�h�̃|�C���^��NULL����Ȃ��ꍇ
		if (pRankingMode != NULL)
		{
			//�����L���O���[�h�̏����������֐��Ăяo��
			pRankingMode->Init();
		}
	}
	//�����L���O���[�h�̃|�C���^��Ԃ�
	return pRankingMode;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CRankingMode::Init(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//BGM�̍Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_RANKING);
	//�S���������֐��Ăяo��
	CreateAll();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CRankingMode::Uninit(void)
{
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CRankingMode::Update(void)
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
		CManager::StartFade(CManager::MODE_TITLE);
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CRankingMode::Draw(void)
{
}

//=============================================================================
// �S���������֐�
//=============================================================================
void CRankingMode::CreateAll(void)
{
	//�����L���O�w�i����
	CBackgroundRanking::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pRanking = CRanking::Create();
}
