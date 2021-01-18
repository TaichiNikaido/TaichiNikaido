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

LPDIRECT3DTEXTURE9 CTitle::m_apTexture[TYPE_MAX] = {};
bool CTitle::m_bReplay = false;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle(int nPriority) : CScene(nPriority)
{
	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		m_apScene[nCount] = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255,100);
	}

	m_fTextureX = 0.0f;
	m_fTextureY = 0.0f;
	m_fFastMove = 0.0f;
	m_fSlowMove = 0.0f;
	m_fMove = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_bReplay = false;
	m_nButtonPos = 2;
	memset(m_aButtonAlpha, 0, sizeof(m_aButtonAlpha));
	m_IsTrigger.Down.bTrigger = false;//������Ă邩�ǂ���
	m_IsTrigger.Up.bTrigger = false;
	m_IsTrigger.Left.bTrigger = false;
	m_IsTrigger.Right.bTrigger = false;
	m_IsTrigger.Down.nCount = 0;//������Ă邩�ǂ���
	m_IsTrigger.Up.nCount = 0;
	m_IsTrigger.Left.nCount = 0;
	m_IsTrigger.Right.nCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// �e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CTitle::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE1,								// �t�@�C���̖��O
		&m_apTexture[TYPE_BG]);								// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE2,								// �t�@�C���̖��O
		&m_apTexture[TYPE_LOGO]);								// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE3,								// �t�@�C���̖��O
		&m_apTexture[TYPE_START]);								// �ǂݍ��ރ������[
																// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE4,								// �t�@�C���̖��O
		&m_apTexture[TYPE_RPLAY]);								// �ǂݍ��ރ������[
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE5,								// �t�@�C���̖��O
		&m_apTexture[TYPE_EXIT]);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h�֐�
//=============================================================================
void CTitle::Unload(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
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
// �����֐�
//=============================================================================
CTitle * CTitle::Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	CTitle * pTitle;
	pTitle = new CTitle;
	pTitle->Init(pos, SizeHeight, SizeWidth);
	//pBg->SetPosition(pos);
	return pTitle;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_TITLE);
	m_pos = pos;
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_fWidth = SizeWidth;
	m_fHeight = SizeHeight;
	//�w�i
		m_apScene[TYPE_BG] = new CScene2d;
		m_apScene[TYPE_BG]->Init(pos, SizeHeight, SizeWidth);

		// ���_���W��ݒ�
		m_vpos[0] = D3DXVECTOR3(pos.x + (-SCREEN_WIDTH / 2), pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
		m_vpos[1] = D3DXVECTOR3(pos.x + (SCREEN_WIDTH / 2), pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
		m_vpos[2] = D3DXVECTOR3(pos.x + (-SCREEN_WIDTH / 2), pos.y + (SCREEN_HEIGHT / 2), 0.0f);
		m_vpos[3] = D3DXVECTOR3(pos.x + (SCREEN_WIDTH / 2), pos.y + (SCREEN_HEIGHT / 2), 0.0f);

		m_apScene[TYPE_BG]->SetVertexPosition(m_vpos);
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		m_apScene[TYPE_BG]->SetColor(m_col);
		m_apScene[TYPE_BG]->SetTex(0.0f, 0.0f, 1.0f, 1.0f);
		m_apScene[TYPE_BG]->BindTexture(m_apTexture[TYPE_BG]);
	//���S
		m_apScene[TYPE_LOGO] = new CScene2d;
		m_apScene[TYPE_LOGO]->Init(pos, SizeHeight, SizeWidth);

		// ���_���W��ݒ�
		m_vpos[0] = D3DXVECTOR3(1200.0f + (-LOGO_SIZE_WIDTH / 2), 300.0f + (-LOGO_SIZE_HEIGHT / 2), 0.0f);
		m_vpos[1] = D3DXVECTOR3(1200.0f + (LOGO_SIZE_WIDTH / 2), 300.0f + (-LOGO_SIZE_HEIGHT / 2), 0.0f);
		m_vpos[2] = D3DXVECTOR3(1200.0f + (-LOGO_SIZE_WIDTH / 2), 300.0f + (LOGO_SIZE_HEIGHT / 2), 0.0f);
		m_vpos[3] = D3DXVECTOR3(1200.0f + (LOGO_SIZE_WIDTH / 2), 300.0f + (LOGO_SIZE_HEIGHT / 2), 0.0f);

		m_apScene[TYPE_LOGO]->SetVertexPosition(m_vpos);
		m_apScene[TYPE_LOGO]->SetTex(0.0f, 0.0f, 1.0f, 1.0f);
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		m_apScene[TYPE_LOGO]->SetColor(m_col);
		m_apScene[TYPE_LOGO]->BindTexture(m_apTexture[TYPE_LOGO]);

	//�{�^��
	for (int nCount = TYPE_START; nCount < TYPE_MAX; nCount++)
	{
		m_apScene[nCount] = new CScene2d;
		m_apScene[nCount]->Init(pos, SizeHeight, SizeWidth);

		// ���_���W��ݒ�
		m_vpos[0] = D3DXVECTOR3(1400.0f + (-TBUTTON_SIZE_WIDTH / 2), 500.0f + nCount * 100.0f + (-TBUTTON_SIZE_HEIGHT / 2), 0.0f);
		m_vpos[1] = D3DXVECTOR3(1400.0f + (TBUTTON_SIZE_WIDTH / 2), 500.0f + nCount * 100.0f + (-TBUTTON_SIZE_HEIGHT / 2), 0.0f);
		m_vpos[2] = D3DXVECTOR3(1400.0f + (-TBUTTON_SIZE_WIDTH / 2), 500.0f + nCount * 100.0f + (TBUTTON_SIZE_HEIGHT / 2), 0.0f);
		m_vpos[3] = D3DXVECTOR3(1400.0f + (TBUTTON_SIZE_WIDTH / 2), 500.0f + nCount * 100.0f + (TBUTTON_SIZE_HEIGHT / 2), 0.0f);

		m_apScene[nCount]->SetVertexPosition(m_vpos);
		m_apScene[nCount]->SetTex(0.0f, 0.0f, 1.0f, 1.0f);
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 100);
		}
		m_apScene[nCount]->BindTexture(m_apTexture[nCount]);
	}


	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CTitle::Uninit(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apScene[nCount] != NULL)
		{
			m_apScene[nCount]->Uninit();
			m_apScene[nCount] = NULL;
		}
	}
	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CTitle::Update(void)
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

	if (lpDIDevice != NULL &&js.lY == -1000 || pInputKeyboard->GetKeyboardPress(DIK_W))//��
	{
		m_IsTrigger.Up.nCount++;
	}
	if (lpDIDevice != NULL &&js.lY == 1000 || pInputKeyboard->GetKeyboardPress(DIK_S))//��
	{
		m_IsTrigger.Down.nCount++;
	}

	if (m_IsTrigger.Up.nCount > COUNT_TRIGGER_PAUSE)
	{
		m_IsTrigger.Up.bTrigger = true;
		m_IsTrigger.Up.nCount = COUNT_TRIGGER_PAUSE - 5;
	}
	if (m_IsTrigger.Down.nCount > COUNT_TRIGGER_PAUSE)
	{
		m_IsTrigger.Down.bTrigger = true;
		m_IsTrigger.Down.nCount = COUNT_TRIGGER_PAUSE - 5;
	}

	//��������󂪉�����炽��
	if (m_IsTrigger.Down.bTrigger == true)
	{

		m_IsTrigger.Down.bTrigger = false;
		if (m_nButtonPos < 4)
		{
			////�V���b�g���̍Đ�
			//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			m_nButtonPos++;
		}
	}

	//�������󂪉������
	if (m_IsTrigger.Up.bTrigger == true)
	{

		m_IsTrigger.Up.bTrigger = false;
		if (m_nButtonPos > 2)
		{
			////�V���b�g���̍Đ�
			//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			m_nButtonPos--;
		}
	}

	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A))
	{
		////�V���b�g���̍Đ�
		//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_ENTER);
		switch (m_nButtonPos)
		{
		case 2://�X�^�[�g
			   //���O���͂Ɉړ�
			pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
			CManager::StartFade(CManager::MODE_NAME);
			pSound->StopSound();
			m_nButtonPos = 2;
			break;
		case 3://���v���C�{�^��
			pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
			pSound->StopSound();
			m_bReplay = true;
			//���O���͂Ɉړ�
			CManager::StartFade(CManager::MODE_GAME);
			m_nButtonPos = 2;
			break;
		case 4://�I��
			pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
			exit(0);
			return;
			m_nButtonPos = 2;
			break;
		default:
			break;
		}
	}

	for (int nCnt = 2; nCnt < TYPE_MAX; nCnt++)
	{
		m_aButtonAlpha[nCnt] = 100;
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 100);
		}
		m_apScene[nCnt]->SetColor(m_col);
	}
	switch (m_nButtonPos)
	{
	case 2://�Q�[������
		m_aButtonAlpha[TYPE_START] = 255;
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		m_apScene[TYPE_START]->SetColor(m_col);
		break;
	case 3://���v���C
		m_aButtonAlpha[TYPE_RPLAY] = 255;
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		m_apScene[TYPE_RPLAY]->SetColor(m_col);
		break;
	case 4://�^�C�g���ɂ��ǂ�
		m_aButtonAlpha[TYPE_EXIT] = 255;
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		m_apScene[TYPE_EXIT]->SetColor(m_col);
		break;
	default:
		break;
	}
	//m_fMove += 0.001f;
	//m_fFastMove += 0.01f;
	//m_fSlowMove += 0.001f;

	//for (int nCount = 0; nCount < MAX_TITLE_TEXTURE; nCount++)
	//{
	//	m_apScene[nCount]->Update();
	//	m_apScene[nCount]->SetVertexPosition(m_vpos);
	//	m_apScene[nCount]->SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	//}
	//m_apScene[0]->SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	////m_apScene[1]->SetTex(m_fTextureX, m_fTextureY - m_fFastMove, 1.0f);
	////m_apScene[2]->SetTex(m_fTextureX, m_fTextureY - m_fSlowMove, 1.0f);

	//// ���_���W��ݒ�
	//m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	//m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	//m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	//m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);

	//����ENTER��A�{�^�����������Ƃ�
	//if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A))
	//{
	//	//���O���͂Ɉړ�
	//	pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
	//	CManager::StartFade(CManager::MODE_NAME);
	//	pSound->StopSound();
	//}

	//if (pInputKeyboard->GetKeyboardTrigger(DIK_R))
	//{
	//	pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
	//	pSound->StopSound();
	//	m_bReplay = true;
	//	//���O���͂Ɉړ�
	//	CManager::StartFade(CManager::MODE_GAME);
	//}
}

//=============================================================================
// �`��֐�
//=============================================================================
void CTitle::Draw(void)
{
}
