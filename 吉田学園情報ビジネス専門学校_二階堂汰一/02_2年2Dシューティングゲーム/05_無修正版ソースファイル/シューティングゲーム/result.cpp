//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : ��K������
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "result.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "sound.h"
#include <stdio.h>
#include <stdlib.h>

LPDIRECT3DTEXTURE9 CResult::m_apTexture[MAX_RESULT_TEXTURE] = {};
CResult::PLAYER_DATA CResult::m_PlayerData = {0,0,0,0,0};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult(int nPriority) : CScene(nPriority)
{
	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		m_apScene[nCount] = NULL;
	}
	memset(m_col, 0, sizeof(m_col));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
CResult::~CResult()
{
}

//=============================================================================
// �e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CResult::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RESULT1,								// �t�@�C���̖��O
		&m_apTexture[0]);								// �ǂݍ��ރ������[

														// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RESULT1,								// �t�@�C���̖��O
		&m_apTexture[1]);								// �ǂݍ��ރ������[

														// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RESULT1,								// �t�@�C���̖��O
		&m_apTexture[2]);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h�֐�
//=============================================================================
void CResult::Unload(void)
{
	for (int nCount = 0; nCount < MAX_RESULT_TEXTURE; nCount++)
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
CResult * CResult::Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	CResult * pResult;
	pResult = new CResult;
	pResult->Init(pos, SizeHeight, SizeWidth);
	return pResult;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_RESULT);

	m_pos = pos;
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_fWidth = SizeWidth;
	m_fHeight = SizeHeight;

	for (int nCount = 0; nCount < MAX_RESULT_TEXTURE; nCount++)
	{
		m_apScene[nCount] = new CScene2d;
		m_apScene[nCount]->Init(pos, SizeHeight, SizeWidth);
		m_apScene[nCount]->SetVertexPosition(m_vpos);
		m_apScene[nCount]->BindTexture(m_apTexture[nCount]);

		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255,255,255,255);
		}
		m_apScene[nCount]->SetColor(m_col);
	}
	TextLoad();
}

//=============================================================================
// �I���֐�
//=============================================================================
void CResult::Uninit(void)
{
	//for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	//{
	//	if (m_apScene[nCount] != NULL)
	//	{
	//		m_apScene[nCount]->Uninit();
	//		m_apScene[nCount] = NULL;
	//	}
	//}
	CScene::Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CResult::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�W���C�X�e�B�b�N�̎擾
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
	DIJOYSTATE js;

	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	//m_fMove += 0.001f;
	//m_fFastMove += 0.01f;
	//m_fSlowMove += 0.001f;

	for (int nCount = 0; nCount < MAX_RESULT_TEXTURE; nCount++)
	{
		m_apScene[nCount]->Update();
		m_apScene[nCount]->SetVertexPosition(m_vpos);
		m_apScene[nCount]->SetTex(0.0f, 0.0f, 1.0f,1.0f);
	}
	m_apScene[0]->SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	//m_apScene[1]->SetTex(m_fTextureX, m_fTextureY - m_fFastMove, 1.0f);
	//m_apScene[2]->SetTex(m_fTextureX, m_fTextureY - m_fSlowMove, 1.0f);

	// ���_���W��ݒ�
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);

	//����ENTER��A�{�^�����������Ƃ�
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A))
	{
		pSound->StopSound();
		//�����L���O�Ɉړ�
		CManager::StartFade(CManager::MODE_RANKING);
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void CResult::Draw(void)
{
}

void CResult::TextLoad(void)
{
	FILE *pFile;
	int nNumPlayer = 0;

	pFile = fopen("data/TEXT/PlayerData.txt", "r"); //�t�@�C���̓ǂݍ���

	if (pFile != NULL)
	{
		//fscanf(pFile, "%d", &nNumPlayer); //�v���C���[�̐l��

			fscanf(pFile, "%s", &m_PlayerData.aName);//���O����
			fscanf(pFile, "%d", &m_PlayerData.nDeath);	//���񂾉�
			fscanf(pFile, "%d", &m_PlayerData.nContinue);//�R���e�B�j���[������
			fscanf(pFile, "%d",& m_PlayerData.nBomb);//�g�p�����{���̌�
			fscanf(pFile, "%d",& m_PlayerData.nScore);

		fclose(pFile); //�t�@�C�������
	}
}
