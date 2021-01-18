//=============================================================================
//
// ���O�̓��͏���[name.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "name.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "joystick.h"
#include "player.h"
#include "name.h"
#include "sound.h"

#define COUNT_TRIGGER 20

//�e�N�X�`���̏�����
LPDIRECT3DTEXTURE9 CName::m_apTexture[MAX_NAME_TEXTURE] = {};
//�����i�[�p�ϐ��̏�����
CName::Letter CName::m_aLetter[MAX_COLUMN][COLUMN_MAXNUMBER] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CName::CName(int nPriority) : CScene(nPriority)
{
	
	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		m_apSceneBG[nCount] = NULL;
	}
	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		m_apScene[nCount] = NULL;
	}
	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		m_apSceneText[nCount] = NULL;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vPos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	m_fTextureX = 0.0f;
	m_fTextureY = 0.0f;
	m_fMove = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	memset(m_aName, NULL, sizeof(m_aName));
	m_bName = false;
	m_bCanselName = false;
	m_bColumnDown = false;
	m_bColumnUp = false;
	m_bLetterRight = false;
	m_bLetterLeft = false;
	m_bOK = false;
	m_nColumnCount = 0;
	m_nLetterCount = 0;
	m_nNameCount = 0;
	m_IsTrigger.Down.bTrigger = false;//������Ă邩�ǂ���
	m_IsTrigger.Up.bTrigger = false;
	m_IsTrigger.Left.bTrigger = false;
	m_IsTrigger.Right.bTrigger = false;
	m_IsTrigger.Down.nCount = 0;//������Ă邩�ǂ���
	m_IsTrigger.Up.nCount = 0;
	m_IsTrigger.Left.nCount = 0;
	m_IsTrigger.Right.nCount = 0;
	m_TriggerCount = 0;//�������̃J�E���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CName::~CName()
{
}

//=============================================================================
// �e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CName::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME,								// �t�@�C���̖��O
		&m_apTexture[0]);								// �ǂݍ��ރ������[
														// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAMEBG,								// �t�@�C���̖��O
		&m_apTexture[1]);								// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h�֐�
//=============================================================================
void CName::Unload(void)
{
	for (int nCount = 0; nCount < 2; nCount++)
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
CName * CName::Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	CName * pName;
	pName = new CName;
	pName->Init(pos, SizeHeight, SizeWidth);
	return pName;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CName::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_NAME);

	m_pos = pos;

	//�w�i
	m_apSceneBG[0] = new CScene2d;
	m_apSceneBG[0]->Init(pos, TEXT_SIZE, TEXT_SIZE);
	m_apSceneBG[0]->BindTexture(m_apTexture[1]);

	// ���_���W��ݒ�
	m_vPos[0] = D3DXVECTOR3(SCREEN_WIDTH / 2 + (-SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + (-SCREEN_HEIGHT / 2), 0.0f);
	m_vPos[1] = D3DXVECTOR3(SCREEN_WIDTH / 2 + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + (-SCREEN_HEIGHT / 2), 0.0f);
	m_vPos[2] = D3DXVECTOR3(SCREEN_WIDTH / 2 + (-SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + (SCREEN_HEIGHT / 2), 0.0f);
	m_vPos[3] = D3DXVECTOR3(SCREEN_WIDTH / 2 + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + (SCREEN_HEIGHT / 2), 0.0f);
	//���_���W�̃Z�b�g
	m_apSceneBG[0]->SetVertexPosition(m_vPos);

	//�e�N�X�`�����W�̃Z�b�g
	m_apSceneBG[0]->SetTex(
		0.0f,
		0.0f,
		1.0f,
		1.0f);
	//�e�N�X�`�����W�̃Z�b�g
	m_apSceneBG[0]->SetColor(m_col);
	for (int nCount = 0; nCount < 26; nCount++)
	{
		m_apScene[nCount] = new CScene2d;
		m_apScene[nCount]->Init(pos, TEXT_SIZE, TEXT_SIZE);
		m_apScene[nCount]->BindTexture(m_apTexture[0]);

		if (nCount < 10)
		{
			// ���_���W��ݒ�
			m_vPos[0] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (-TEXT_SIZE / 2), pos.y + (-TEXT_SIZE / 2), 0.0f);
			m_vPos[1] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (TEXT_SIZE / 2), pos.y + (-TEXT_SIZE / 2), 0.0f);
			m_vPos[2] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (-TEXT_SIZE / 2), pos.y + (TEXT_SIZE / 2), 0.0f);
			m_vPos[3] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (TEXT_SIZE / 2), pos.y + (TEXT_SIZE / 2), 0.0f);
		}
		if (nCount >= 10 && nCount < 19)
		{
			// ���_���W��ݒ�
			m_vPos[0] = D3DXVECTOR3(pos.x + 25.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 10)) + (-TEXT_SIZE / 2), pos.y + 100.0f * TEXT_SCALE + (-TEXT_SIZE / 2), 0.0f);
			m_vPos[1] = D3DXVECTOR3(pos.x + 25.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 10)) + (TEXT_SIZE / 2), pos.y + 100.0f * TEXT_SCALE + (-TEXT_SIZE / 2), 0.0f);
			m_vPos[2] = D3DXVECTOR3(pos.x + 25.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 10)) + (-TEXT_SIZE / 2), pos.y + 100.0f * TEXT_SCALE + (TEXT_SIZE / 2), 0.0f);
			m_vPos[3] = D3DXVECTOR3(pos.x + 25.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 10)) + (TEXT_SIZE / 2), pos.y + 100.0f * TEXT_SCALE + (TEXT_SIZE / 2), 0.0f);
		}
		if (nCount >= 19 && nCount < 26)
		{
			// ���_���W��ݒ�
			m_vPos[0] = D3DXVECTOR3(pos.x + 75.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 19)) + (-TEXT_SIZE / 2), pos.y + 200.0f * TEXT_SCALE + (-TEXT_SIZE / 2), 0.0f);
			m_vPos[1] = D3DXVECTOR3(pos.x + 75.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 19)) + (TEXT_SIZE / 2), pos.y + 200.0f * TEXT_SCALE + (-TEXT_SIZE / 2), 0.0f);
			m_vPos[2] = D3DXVECTOR3(pos.x + 75.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 19)) + (-TEXT_SIZE / 2), pos.y + 200.0f * TEXT_SCALE + (TEXT_SIZE / 2), 0.0f);
			m_vPos[3] = D3DXVECTOR3(pos.x + 75.0f * TEXT_SCALE + (50.0f * TEXT_SCALE * (nCount - 19)) + (TEXT_SIZE / 2), pos.y + 200.0f * TEXT_SCALE + (TEXT_SIZE / 2), 0.0f);
		}
		//���_���W�̃Z�b�g
		m_apScene[nCount]->SetVertexPosition(m_vPos);

		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(200, 100, 0, 255);
		}
		//�F�̃Z�b�g
		m_apScene[nCount]->SetColor (m_col);

		//�e�N�X�`�����W�̃Z�b�g
		m_apScene[nCount]->SetTex(
			0.03846f * nCount,
			0.0f,
			0.03846f * nCount + 0.03846f,
			1.0f);
	}

	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		m_apSceneText[nCount] = new CScene2d;
		m_apSceneText[nCount]->Init(pos, TEXT_SIZE, TEXT_SIZE);
		m_apSceneText[nCount]->BindTexture(m_apTexture[0]);

		// ���_���W��ݒ�
		m_vPos[0] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (-TEXT_SIZE / 2), pos.y + -150.0f + (-TEXT_SIZE / 2), 0.0f);
		m_vPos[1] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (TEXT_SIZE / 2), pos.y + -150.0f + (-TEXT_SIZE / 2), 0.0f);
		m_vPos[2] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (-TEXT_SIZE / 2), pos.y + -150.0f + (TEXT_SIZE / 2), 0.0f);
		m_vPos[3] = D3DXVECTOR3(pos.x + (50.0f * TEXT_SCALE * nCount) + (TEXT_SIZE / 2), pos.y + -150.0f + (TEXT_SIZE / 2), 0.0f);

		//���_���W�̃Z�b�g
		m_apSceneText[nCount]->SetVertexPosition(m_vPos);

		//�F�̃Z�b�g
		m_apSceneText[nCount]->SetColor(m_col);

		//�e�N�X�`�����W�̃Z�b�g(���������ĂȂ����)
		m_apSceneText[nCount]->SetTex(
			0.0f,
			0.00001f,
			1.0f,
			0.0f);
	}

	m_fWidth = SizeWidth;	//��
	m_fHeight = SizeHeight;	//����

	//������2�����z��ɕ������i�[
	m_aLetter[0][0].aLetter = 'Q';
	m_aLetter[0][1].aLetter = 'W';
	m_aLetter[0][2].aLetter = 'E';
	m_aLetter[0][3].aLetter = 'R';
	m_aLetter[0][4].aLetter = 'T';
	m_aLetter[0][5].aLetter = 'Y';
	m_aLetter[0][6].aLetter = 'U';
	m_aLetter[0][7].aLetter = 'I';
	m_aLetter[0][8].aLetter = 'O';
	m_aLetter[0][9].aLetter = 'P';
	m_aLetter[1][0].aLetter = 'A';
	m_aLetter[1][1].aLetter = 'S';
	m_aLetter[1][2].aLetter = 'D';
	m_aLetter[1][3].aLetter = 'F';
	m_aLetter[1][4].aLetter = 'G';
	m_aLetter[1][5].aLetter = 'H';
	m_aLetter[1][6].aLetter = 'J';
	m_aLetter[1][7].aLetter = 'K';
	m_aLetter[1][8].aLetter = 'L';
	m_aLetter[2][0].aLetter = 'Z';
	m_aLetter[2][1].aLetter = 'X';
	m_aLetter[2][2].aLetter = 'C';
	m_aLetter[2][3].aLetter = 'V';
	m_aLetter[2][4].aLetter = 'B';
	m_aLetter[2][5].aLetter = 'N';
	m_aLetter[2][6].aLetter = 'M';

	//������2�����z��ɕ������i�[
	m_aLetter[0][0].LetterIndex = 0;
	m_aLetter[0][1].LetterIndex = 1;
	m_aLetter[0][2].LetterIndex = 2;
	m_aLetter[0][3].LetterIndex = 3;
	m_aLetter[0][4].LetterIndex = 4;
	m_aLetter[0][5].LetterIndex = 5;
	m_aLetter[0][6].LetterIndex = 6;
	m_aLetter[0][7].LetterIndex = 7;
	m_aLetter[0][8].LetterIndex = 8;
	m_aLetter[0][9].LetterIndex = 9;
	m_aLetter[1][0].LetterIndex = 10;
	m_aLetter[1][1].LetterIndex = 11;
	m_aLetter[1][2].LetterIndex = 12;
	m_aLetter[1][3].LetterIndex = 13;
	m_aLetter[1][4].LetterIndex = 14;
	m_aLetter[1][5].LetterIndex = 15;
	m_aLetter[1][6].LetterIndex = 16;
	m_aLetter[1][7].LetterIndex = 17;
	m_aLetter[1][8].LetterIndex = 18;
	m_aLetter[2][0].LetterIndex = 19;
	m_aLetter[2][1].LetterIndex = 20;
	m_aLetter[2][2].LetterIndex = 21;
	m_aLetter[2][3].LetterIndex = 22;
	m_aLetter[2][4].LetterIndex = 23;
	m_aLetter[2][5].LetterIndex = 24;
	m_aLetter[2][6].LetterIndex = 25;

	memset(m_aName, 0, sizeof(m_aName));	//���O�i�[�p�ϐ��̏�����
	m_bName = false;						//���O�̋L�^���
	m_bCanselName = false;
	m_bColumnDown = false;					//����󔻒�
	m_bColumnUp = false;					//���󔻒�
	m_bLetterRight = false;					//�E��󔻒�
	m_bLetterLeft = false;					//�����
	m_bOK = false;
	m_nColumnCount = 0;						//�s���J�E���^
	m_nLetterCount = 0;						//�������J�E���^
	m_nNameCount = 0;						//���O�̕������J�E���^

	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		//�v���C���[�ɖ��O���Z�b�g
		CPlayer::SetPlayerName(nCount, NULL);
	}

	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CName::Uninit(void)
{
	for (int nCount = 0; nCount < 26; nCount++)
	{
		if (m_apScene[nCount] != NULL)
		{
			m_apScene[nCount]->Uninit();
			m_apScene[nCount] = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		if (m_apSceneText[nCount] != NULL)
		{
			m_apSceneText[nCount]->Uninit();
			m_apSceneText[nCount] = NULL;
		}
	}
	for (int nCount = 0; nCount < 1; nCount++)
	{
		if (m_apSceneBG[nCount] != NULL)
		{
			m_apSceneBG[nCount]->Uninit();
			m_apSceneBG[nCount] = NULL;
		}
	}
	CName::Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CName::Update(void)
{
	CSound * pSound = CManager::GetSound();
	//�L�[�{�[�h�̎擾
	CInputKeyboard * pInputKeyboard = CManager::GetInputKeyboard();

	//�W���C�X�e�B�b�N�̎擾
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
	DIJOYSTATE js;

	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);

	}

	if (lpDIDevice != NULL &&js.lX == -1000)//��
	{
		m_IsTrigger.Left.nCount++;
	}
	if (lpDIDevice != NULL &&js.lX == 1000)//�E
	{
		m_IsTrigger.Right.nCount++;
	}
	if (lpDIDevice != NULL &&js.lY == -1000)//��
	{
		m_IsTrigger.Up.nCount++;
	}
	if (lpDIDevice != NULL &&js.lY == 1000)//��
	{
		m_IsTrigger.Down.nCount++;
	}

	if (m_IsTrigger.Left.nCount > COUNT_TRIGGER)
	{
		m_IsTrigger.Left.bTrigger = true;
		m_IsTrigger.Left.nCount = COUNT_TRIGGER - 5;
	}
	if (m_IsTrigger.Right.nCount > COUNT_TRIGGER)
	{
		m_IsTrigger.Right.bTrigger = true;
		m_IsTrigger.Right.nCount = COUNT_TRIGGER - 5;
	}
	if (m_IsTrigger.Up.nCount > COUNT_TRIGGER)
	{
		m_IsTrigger.Up.bTrigger = true;
		m_IsTrigger.Up.nCount = COUNT_TRIGGER - 5;
	}
	if (m_IsTrigger.Down.nCount > COUNT_TRIGGER)
	{
		m_IsTrigger.Down.bTrigger = true;
		m_IsTrigger.Down.nCount = COUNT_TRIGGER - 5;
	}
	//��������󂪉�����炽��
	if (pInputKeyboard->GetKeyboardTrigger(DIK_DOWN) || m_IsTrigger.Down.bTrigger == true)
	{
		//������^�ɂ���
		m_bColumnDown = true;

		//��������󂪐^�̂Ƃ�
		if (m_bColumnDown == true)
		{
			//���݂̍s����3�s�ڂ�艺��������
			if (m_nColumnCount < 2)
			{
				//�s�̉��Z
				m_nColumnCount++;
				//�������U�ɂ���
				m_bColumnDown = false;
			}
			//����2�s�ڂ̎�
			if (m_nColumnCount == 1)
			{
				//�����I�𒆂̕�����8�Ԗڂ��ゾ������
				if (m_nLetterCount > 8)
				{
					//�I�𒆂̕�����8�Ԗڂɂ���
					m_nLetterCount = 8;
				}
			}
			//����3�s�ڂ̎�
			if (m_nColumnCount == 2)
			{
				//�����I�𒆂̕�����6�Ԗڂ��ゾ������
				if (m_nLetterCount > 6)
				{
					//�I�𒆂̕�����6�Ԗڂɂ���
					m_nLetterCount = 6;
				}
			}
		}
		m_IsTrigger.Down.bTrigger = false;
	}

	//�������󂪉������
	if (pInputKeyboard->GetKeyboardTrigger(DIK_UP) || m_IsTrigger.Up.bTrigger == true)
	{
		//�����^�ɂ���
		m_bColumnUp = true;

		//�������󂪐^��������
		if (m_bColumnUp == true)
		{
			//�������݂̍s����1�s�ڂ��ゾ������
			if (m_nColumnCount > 0)
			{
				//�s�̌��Z
				m_nColumnCount--;
				//������U�ɂ���
				m_bColumnUp = false;
			}
		}
		m_IsTrigger.Up.bTrigger = false;
	}

	//�����E��󂪉����ꂽ��
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RIGHT) || m_IsTrigger.Right.bTrigger == true)
	{
		//�E����^�ɂ���
		m_bLetterRight = true;

		////�����E��󂪐^��������
		if (m_bLetterRight == true)
		{
			//�������݂̍s����1�s�ڂ�������
			if (m_nColumnCount == 0)
			{
				//�������݂̕����̈ʒu��9�Ԗڂ�艺��������
				if (m_nLetterCount < 9)
				{
					//�����̈ʒu�̉��Z
					m_nLetterCount++;
					//�E�����U�ɂ���
					m_bLetterRight = false;
				}
			}
			//�������݂̍s����2�s�ڂ�������
			if (m_nColumnCount == 1)
			{
				//�������݂̕����̈ʒu��8�Ԗڂ�艺��������
				if (m_nLetterCount < 8)
				{
					//�����̈ʒu�̉��Z
					m_nLetterCount++;
					//�E�����U�ɂ���
					m_bLetterRight = false;
				}
			}
			//�������݂̍s����3�s�ڂ�������
			if (m_nColumnCount == 2)
			{
				//�������݂̕����̈ʒu��7�Ԗڂ�艺��������
				if (m_nLetterCount < 6)
				{
					//�����̈ʒu�̉��Z
					m_nLetterCount++;
					//�E�����U�ɂ���
					m_bLetterRight = false;
				}
			}
		}
		m_IsTrigger.Right.bTrigger = false;
	}

	//��������󂪉����ꂽ��
	if (pInputKeyboard->GetKeyboardTrigger(DIK_LEFT) || m_IsTrigger.Left.bTrigger == true)
	{
		//������^�ɂ���
		m_bLetterLeft = true;

		//��������󂪐^�̂Ƃ�
		if (m_bLetterLeft == true)
		{
			//�������݂̍s����1�s�ڂ�������
			if (m_nColumnCount == 0)
			{
				//�������݂̍s����1�s�ڂ��ゾ������
				/*	if (m_nColumnCount > 0)
				{*/
				//�������݂̕����̈ʒu��0���ゾ������
				if (m_nLetterCount > 0)
				{
					//�����̈ʒu�����Z
					m_nLetterCount--;
					//�������U�ɂ���
					m_bLetterLeft = false;
				}
				//}
			}
			//�������݂̍s����2�s�ڂ�������
			if (m_nColumnCount == 1)
			{
				//�������݂̍s����1�s�ڂ��ゾ������
				if (m_nColumnCount > 0)
				{
					//�������݂̕����̈ʒu��0���ゾ������
					if (m_nLetterCount > 0)
					{
						//�����̈ʒu�����Z
						m_nLetterCount--;
						//�������U�ɂ���
						m_bLetterLeft = false;
					}
				}
			}
			//�������݂̍s����3�s�ڂ�������
			if (m_nColumnCount == 2)
			{
				//�������݂̍s����1�s�ڂ��ゾ������
				if (m_nColumnCount > 0)
				{
					//�������݂̕����̈ʒu��0���ゾ������
					if (m_nLetterCount > 0)
					{
						//�����̈ʒu�����Z
						m_nLetterCount--;
						//�������U�ɂ���
						m_bLetterLeft = false;
					}
				}
			}
		}
		m_IsTrigger.Left.bTrigger = false;
	}

	if (m_bOK == false)
	{
		//����ENTER��A�{�^�����������Ƃ�
		if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A))
		{
			//���O�̋L�^���\��Ԃɂ���
			m_bName = true;

			//�������O�̋L�^���\��Ԃ�������
			if (m_bName == true && m_nNameCount < 8)
			{
				//���͂��ꂽ�����𖼑O�i�[�p�ϐ��Ɉꕶ�����i�[����
				m_aName[m_nNameCount] = m_aLetter[m_nColumnCount][m_nLetterCount].aLetter;

				//���O�̕����������Z����
				if (m_nNameCount < 8)
				{
					//�e�N�X�`�����W�̃Z�b�g
					m_apSceneText[m_nNameCount]->SetTex(
						0.03846f * m_aLetter[m_nColumnCount][m_nLetterCount].LetterIndex,
						0.0f,
						0.03846f * m_aLetter[m_nColumnCount][m_nLetterCount].LetterIndex + 0.03846f,
						1.0f);
					m_nNameCount++;
				}

				//���O�̋L�^��s�\��Ԃɂ���
				m_bName = false;
			}
		}
	}

	//�������O�ɕ����������Ă���Ƃ�
	if (m_aName[0] != NULL)
	{
		//����BACKSPACE��B�{�^�����������Ƃ�
		if (pInputKeyboard->GetKeyboardTrigger(DIK_BACK) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_B))
		{
			//���O�̎��������\��Ԃɂ���
			m_bCanselName = true;
			//�������O�̎��������\��Ԃ�������
			if (m_bCanselName == true)
			{
				//���͂��ꂽ�����𖼑O�i�[�p�ϐ�����ꕶ�����j������
				m_aName[m_nNameCount] = NULL;

				if (m_nNameCount < 8)
				{
					//�e�N�X�`�����W�̃Z�b�g(���������ĂȂ����)
					m_apSceneText[m_nNameCount]->SetTex(
						0.00001f,
						0.0f,
						0.0f,
						0.0f);
				}

				//���O�̕����������Z����
				if (m_nNameCount > 0)
				{
					m_nNameCount--;
				}

			}
			//���O�̎�������s�\��Ԃɂ���
			m_bName = false;
		}
	}

	if (m_bOK == false)
	{
		//����SPACEKEY��JOYSTICK��START�������ꂽ�Ƃ�
		if (pInputKeyboard->GetKeyboardTrigger(DIK_SPACE) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(11))
		{
			//���O�i�[�p�ϐ���NULL����Ȃ��Ƃ�
			if (m_aName[0] != NULL)
			{
				//���O�������Ԃɂ���
				m_bOK = true;
			}
			else
			{
				m_aName[0] = 'U';
				m_aName[1] = 'N';
				m_aName[2] = 'K';
				m_aName[3] = 'N';
				m_aName[4] = 'O';
				m_aName[5] = 'W';
				m_aName[6] = 'N';
				m_aName[7] = NULL;
				m_nNameCount = 7;
				//���O�������Ԃɂ���
				m_bOK = true;

				for (int nCount = 0; nCount < m_nNameCount; nCount++)
				{
					//�v���C���[�ɖ��O���Z�b�g
  					CPlayer::SetPlayerName(nCount, m_aName[nCount]);
				}
				pSound->StopSound();
				//�Q�[���Ɉړ�
				CManager::StartFade(CManager::MODE_TUTORIAL);
			}
		}
	}

	//�������O�̌��肵���Ƃ�
	if (m_bOK == true)
	{
		//���O���v���C���[�ɓn��
		for (int nCount = 0; nCount < m_nNameCount ; nCount++)
		{
			CPlayer::SetPlayerName(nCount, m_aName[nCount]);
		}
		pSound->StopSound();
		//�Q�[���Ɉړ�
		CManager::StartFade(CManager::MODE_TUTORIAL);
	}

	for (int nCount = 0; nCount < 26; nCount++)
	{
		m_apScene[nCount]->Update();

		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 100, 0, 255);
		}
		//�F�̃Z�b�g
		m_apScene[nCount]->SetColor(m_col);

	}

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	//�F�̃Z�b�g
	m_apScene[m_aLetter[m_nColumnCount][m_nLetterCount].LetterIndex]->SetColor(m_col);
	//�L�[�{�[�h�̃A�b�v�f�[�g(���ꂪ�Ȃ���Trigger������ɋ@�\���Ȃ�)
	pInputKeyboard->UpdateInput();
	//�W���C�X�e�B�b�N�̃A�b�v�f�[�g(���ꂪ�Ȃ���Trigger������ɋ@�\���Ȃ�)
	pInputJoystick->UpdateInput();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CName::Draw(void)
{
}