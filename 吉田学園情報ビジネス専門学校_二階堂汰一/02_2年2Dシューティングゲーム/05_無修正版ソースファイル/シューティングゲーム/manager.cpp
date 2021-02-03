//=============================================================================
//
// manager���� [manager.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "keyboard.h"
#include "player.h"
#include "wormhole.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
#include "background.h"
#include "enemy.h"
#include "dragon.h"
#include "number.h"
#include "score.h"
#include "item.h"
#include "own.h"
#include "ownui.h"
#include "bomb.h"
#include "effect.h"
#include "joystick.h"
#include "title.h"
#include "name.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "bombtexture.h"
#include "fade.h"
#include "text.h"
#include "warning.h"
#include "flame.h"
#include "tutorial.h"

CRenderer * CManager::m_pRenderer = NULL;
CInputKeyboard * CManager::m_pInputKeyboard = NULL;
CInputJoystick * CManager::m_pInputJoystick = NULL;
CSound * CManager::m_pSound = NULL;
CTitle * CManager::m_pTitle = NULL;
CTutorial * CManager::m_pTutorial = NULL;
CName * CManager::m_pName = NULL;
CGame * CManager::m_pGame = NULL;
CResult * CManager::m_pResult = NULL;
CRanking * CManager::m_pRanking = NULL;
CFade * CManager::m_pFade = NULL;
CText * CManager::m_pText = NULL;
CManager::MODE CManager::m_mode = MODE_NONE;
bool CManager::m_bUseFade = false;
bool CManager::m_bPause = false;
//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow)
{
	CEnemy::TYPE type;
	type = CEnemy::TYPE_NONE;

	//�����_���[�̐���
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new  CRenderer;
	}
	//����������
	m_pRenderer->Init(hWnd, TRUE);

	//���͂̐���
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyboard;
	}

	//�L�[�{�[�h�̏�����
	m_pInputKeyboard->InitInput(hInsitance, hWnd);

	//�W���C�X�e�B�b�N�̐���
	if (m_pInputJoystick == NULL)
	{
		m_pInputJoystick = new CInputJoystick;
	}

	//�W���C�X�e�B�b�N�̏�����
	m_pInputJoystick->InitInput(hInsitance, hWnd);

	//�T�E���h�̐���
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}

	//�T�E���h�̏�����
	m_pSound->Init(hWnd);

	//�e�L�X�g�𐶐�
	m_pText = CText::Create(D3DXVECTOR3(FIELD_WIDTH, FIELD_HEIGHT, 0.0f), FIELD_WIDTH, FIELD_HEIGHT);

	//�v���C���[�̃e�N�X�`�����[�h
	CPlayer::Load();

	//�G�̃��[�h
	CEnemy::Load();

	//�h���S���̃��[�h
	CDragon::Load();

	//�e�̃e�N�X�`�����[�h
	CBullet::Load();

	//�����̃e�N�X�`�����[�h
	CExplosion::Load();

	//�w�i�̃��[�h
	CBg::Load();

	//�A�C�e���̃��[�h
	CItem::Load();

	//�ԍ��̃��[�h
	CNumber::Load();

	//���@�̃��[�h
	COwn::Load();

	//���[���z�[���̃��[�h
	CWormhole::Load();

	//���e�̃��[�h
	CBomb::Load();

	//�G�t�F�N�g�̃��[�h
	CEffect::Load();

	//�^�C�g���̃��[�h
	CTitle::Load();

	//���O���͉�ʂ̃��[�h
	CName::Load();

	//���U���g�̃��[�h
	CResult::Load();

	//�����L���O�̃��[�h
	CRanking::Load();

	//���e�̃e�N�X�`�����[�h
	CBombTexture::Load();

	//�댯�n�т̃e�N�X�`���̃��[�h
	CWarning::Load();

	CFlame::Load();

	CTutorial::Load();
	
	SetMode(MODE_TITLE);

	//�t�F�[�h�̐���
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, m_mode);

	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();

	//���[���z�[���̃A�����[�h
	CWormhole::Unload();

	//���@�̃A�����[�h
	COwn::Unload();

	//�ԍ��̃A�����[�h
	CNumber::Unload();

	//���O���͉�ʂ̃A�����[�h
	CName::Unload();

	//�A�C�e���̃A�����[�h
	CItem::Unload();

	//�w�i�̃e�N�X�`���A�����[�h
	CBg::Unload();

	//�����̃e�N�X�`���A�����[�h
	CExplosion::Unload();

	//�e�̃e�N�X�`���A�����[�h
	CBullet::Unload();

	//�G�̃A�����[�h
	CEnemy::Unload();

	//�h���S���̃A�����[�h
	CDragon::Unload();

	//�v���C���[�̃e�N�X�`���A�����[�h
	CPlayer::Unload();

	//���e�̃A�����[�h
	CBomb::Unload();

	//�G�t�F�N�g�̃A�����[�h
	CEffect::Unload();

	//�^�C�g���̃A�����[�h
	CTitle::Unload();

	//���U���g�̃A�����[�h
	CResult::Unload();

	//�����L���O�̃A�����[�h
	CRanking::Unload();

	//���e�̃e�N�X�`���A�����[�h
	CBombTexture::Unload();

	//�댯�n�т̃e�N�X�`���̃A�����[�h
	CWarning::Unload();

	CFlame::Unload();

	CTutorial::Unload();

	//�L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->UninitInput();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	//�W���C�X�e�B�b�N�̔j��
	if (m_pInputJoystick != NULL)
	{
		m_pInputJoystick->UninitInput();
		delete m_pInputJoystick;
		m_pInputJoystick = NULL;
	}
	//�����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	//�T�E���h�̒�~
	m_pSound->StopSound();

	//�T�E���h�̔j��
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	//�t�F�[�h�̔j��
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}

	//�e�L�X�g�̔j��
	if (m_pText != NULL)
	{
		m_pText->Uninit();
		delete m_pText;
		m_pText = NULL;
	}
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CManager::Update(void)
{
	//�L�[�{�[�h�̍X�V
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->UpdateInput();
	}

	//�L�[�{�[�h�̍X�V
	if (m_pInputJoystick != NULL)
	{
		m_pInputJoystick->UpdateInput();
	}

	//�`��̍X�V
	if (m_pRenderer != NULL)
	{
 		m_pRenderer->Update();
	}

	//�t�F�[�h�X�V
	if (m_bUseFade == true)
	{
		if (m_pFade != NULL)
		{
			m_pFade->Update();
		}
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw(); // �`�揈��
}

void CManager::SetMode(MODE mode)
{
	CScene::ReleaseAll();
	m_mode = mode;
	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = CTitle::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 ,0.0f), SCREEN_HEIGHT, SCREEN_WIDTH);
		break;
	case MODE_TUTORIAL:
		m_pTutorial = CTutorial::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH);
		break;
	case MODE_NAME:
		m_pName = CName::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH);
		break;
	case MODE_GAME:
		m_pGame = CGame::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH);
		break;
	case MODE_RESULT:
		m_pResult = CResult::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH);
		break;
	case MODE_RANKING:
		m_pRanking = CRanking::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH);
		break;
	default:
		break;
	}
	m_pInputKeyboard->UpdateInput();
	m_pInputJoystick->UpdateInput();
}

CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

CInputKeyboard * CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

CInputJoystick * CManager::GetInputJoystick(void)
{
	return m_pInputJoystick;
}

CSound * CManager::GetSound(void)
{
	return m_pSound;
}

CFade * CManager::GetFade(void)
{
	return m_pFade;
}

//----------------------------------------------------
//�t�F�[�h�̊J�n
//----------------------------------------------------
void CManager::StartFade(MODE mode)
{
	m_mode = mode;
	m_bUseFade = true;
	CText::IsDrawText(false);
}
//----------------------------------------------------
//�t�F�[�h�̍X�V�I��
//----------------------------------------------------
void CManager::StopFade(void)
{
	m_bUseFade = false;
	CText::IsDrawText(true);
}
CScene2d * CManager::GetScene2d(void)
{
	return m_pScene2d;
}
