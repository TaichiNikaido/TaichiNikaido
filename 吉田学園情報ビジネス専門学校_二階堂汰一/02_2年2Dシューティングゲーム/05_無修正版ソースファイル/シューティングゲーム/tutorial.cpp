//=============================================================================
//
// �^�C�g�� [title.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "title.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "fade.h"
#include "sound.h"
#include "pause.h"
#include "tutorial.h"

LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial::CTutorial(int nPriority) : CScene(nPriority)
{
	m_pScene = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 100);
	}

	m_fTextureX = 0.0f;
	m_fTextureY = 0.0f;
	m_fFastMove = 0.0f;
	m_fSlowMove = 0.0f;
	m_fMove = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// �e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CTutorial::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TUTORIAL,								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h�֐�
//=============================================================================
void CTutorial::Unload(void)
{
		// �e�N�X�`���̔j��
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}

//=============================================================================
// �����֐�
//=============================================================================
CTutorial * CTutorial::Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	CTutorial * pTutorial;
	pTutorial = new CTutorial;
	pTutorial->Init(pos, SizeHeight, SizeWidth);
	//pBg->SetPosition(pos);
	return pTutorial;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_TUTORIAL);
	m_pos = pos;
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_fWidth = SizeWidth;
	m_fHeight = SizeHeight;
	//�w�i
	m_pScene= new CScene2d;
	m_pScene->Init(pos, SizeHeight, SizeWidth);

	// ���_���W��ݒ�
	m_vpos[0] = D3DXVECTOR3(pos.x + (-SCREEN_WIDTH / 2), pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(pos.x + (SCREEN_WIDTH / 2), pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(pos.x + (-SCREEN_WIDTH / 2), pos.y + (SCREEN_HEIGHT / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(pos.x + (SCREEN_WIDTH / 2), pos.y + (SCREEN_HEIGHT / 2), 0.0f);

	m_pScene->SetVertexPosition(m_vpos);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	m_pScene->SetColor(m_col);
	m_pScene->SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	m_pScene->BindTexture(m_pTexture);

	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CTutorial::Uninit(void)
{
		if (m_pScene != NULL)
		{
			m_pScene->Uninit();
			m_pScene = NULL;
		}
	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CTutorial::Update(void)
{
	CSound * pSound = CManager::GetSound();
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//�W���C�X�e�B�b�N�̎擾
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
	DIJOYSTATE js;

	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	if (pInputKeyboard->GetKeyboardPress(DIK_RETURN) || pInputJoystick->GetJoystickTrigger(JS_A))
	{
		pSound->StopSound();
		CManager::StartFade(CManager::MODE_GAME);
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void CTutorial::Draw(void)
{
}
