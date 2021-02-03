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
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE ("Data/Texture/UI/word.png")
#define COUNT_TRIGGER 4
#define ALPHABET_COL D3DCOLOR_RGBA(0, 170, 255, 255)//�����J���[

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
//�e�N�X�`���̏�����
LPDIRECT3DTEXTURE9 CName::m_apTexture[MAX_NAME_TEXTURE] = {};
//�����i�[�p�ϐ��̏�����
CName::Letter CName::m_aLetter[MAX_ROW][MAX_COLUMN] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CName::CName()
{
	for (int nCount = 0; nCount < MAX_WORD; nCount++)
	{
		m_apScene[nCount] = NULL;
	}
	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		m_apSceneText[nCount] = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMove = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	memset(m_aName, NULL, sizeof(m_aName));
	m_bOK = false;
	m_nNameCount = 0;
	m_IsTrigger.Down.bTrigger = false;//������Ă邩�ǂ���
	m_IsTrigger.Up.bTrigger = false;
	m_IsTrigger.Left.bTrigger = false;
	m_IsTrigger.Right.bTrigger = false;
	m_IsTrigger.Down.nCount = 0;//������Ă邩�ǂ���
	m_IsTrigger.Up.nCount = 0;
	m_IsTrigger.Left.nCount = 0;
	m_IsTrigger.Right.nCount = 0;
	m_nColumn = 0;
	m_nRow = 0;
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
HRESULT CName::TextureLoad(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE,
		&m_apTexture[0]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h�֐�
//=============================================================================
void CName::TextureUnload(void)
{
	for (int nCount = 0; nCount < MAX_NAME_TEXTURE; nCount++)
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
	CName * pNamePad;
	pNamePad = new CName;
	if (pNamePad != NULL)
	{
		pNamePad->Init(pos, SizeHeight, SizeWidth);
	}
	return pNamePad;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CName::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	m_pos = pos;

	memset(m_aName, NULL, sizeof(m_aName));	//���O�i�[�p�ϐ��̏�����
	m_bOK = false;
	m_nNameCount = 0;						//���O�̕������J�E���^

	//------------------------------------------
	//�L�[�{�[�h�̐ݒ�
	//------------------------------------------
	int nAlphabetCount = 0;//�A���t�@�x�b�g����

	for (int nCountRow = 0; nCountRow < MAX_ROW; nCountRow++)
	{
		for (int nCountCol = 0; nCountCol < MAX_COLUMN; nCountCol++)
		{
			m_apScene[nAlphabetCount] = new CScene2d;
			//���_���W�̃Z�b�g
			m_apScene[nAlphabetCount]->SetPosition(D3DXVECTOR3(pos.x + (WORD_BUTTON_INTERVEL * TEXT_SCALE * nCountCol), pos.y + (WORD_BUTTON_INTERVEL *TEXT_SCALE * nCountRow), 0.0f));
			//�F�̃Z�b�g
			m_apScene[nAlphabetCount]->SetColor(ALPHABET_COL);
			//�T�C�Y�̃Z�b�g
			m_apScene[nAlphabetCount]->SetSize(D3DXVECTOR3(TEXT_SIZE, TEXT_SIZE, 0.0f));
			//�e�N�X�`����UV���W�̐ݒ�
			D3DXVECTOR2 aTexture[NUM_VERTEX];
			aTexture[0] = D3DXVECTOR2(nAlphabetCount * 0.037037f, 0.0f);
			aTexture[1] = D3DXVECTOR2(nAlphabetCount * 0.037037f + 0.037037f, 0.0f);
			aTexture[2] = D3DXVECTOR2(nAlphabetCount * 0.037037f, 1.0f);
			aTexture[3] = D3DXVECTOR2(nAlphabetCount * 0.037037f + 0.037037f, 1.0f);
			//�e�N�X�`�����W�̃Z�b�g
			m_apScene[nAlphabetCount]->SetTexture(aTexture);

			m_apScene[nAlphabetCount]->Init();
			//�e�N�X�`���̊��蓖��
			m_apScene[nAlphabetCount]->BindTexture(m_apTexture[0]);

			nAlphabetCount++;
		}
	}

	//------------------------------------------
	//���͕����\�������ݒ�
	//------------------------------------------
	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		m_apSceneText[nCount] = new CScene2d;
		//���_���W�̃Z�b�g
		m_apSceneText[nCount]->SetPosition(D3DXVECTOR3(300.0f + (WORD_BUTTON_INTERVEL * TEXT_SCALE * nCount), pos.y + -200.0f, 0.0f));
		//�F�̃Z�b�g
		m_apSceneText[nCount]->SetColor(ALPHABET_COL);
		//�T�C�Y�̃Z�b�g
		m_apSceneText[nCount]->SetSize(D3DXVECTOR3(TEXT_SIZE, TEXT_SIZE, 0.0f));
		//�e�N�X�`����UV���W�̐ݒ�
		D3DXVECTOR2 aTexture[NUM_VERTEX];
		aTexture[0] = D3DXVECTOR2(0.00001f, 0.0f);
		aTexture[1] = D3DXVECTOR2(0.0f, 0.0f);
		aTexture[2] = D3DXVECTOR2(0.00001f, 1.0f);
		aTexture[3] = D3DXVECTOR2(0.0f, 1.0f);
		//�e�N�X�`�����W�̃Z�b�g
		m_apSceneText[nCount]->SetTexture(aTexture);

		m_apSceneText[nCount]->Init();
		//�e�N�X�`���̊��蓖��
		m_apSceneText[nCount]->BindTexture(m_apTexture[0]);
	}

	m_fWidth = SizeWidth;	//��
	m_fHeight = SizeHeight;	//����

	//�����z��ɕ����i�[
	int nCountColumn = 0;//��
	int nCountRow = 0;//�s
	int nLetterIndex = 0;//�z�񏇔�
	for (char cAlphabet = 'A'; cAlphabet <= 'Z'; cAlphabet++, nCountColumn++)//�A���t�@�x�b�g���Ɋi�[
	{
		m_aLetter[nCountRow][nCountColumn].aLetter = cAlphabet;//�����i�[
		m_aLetter[nCountRow][nCountColumn].LetterIndex = nLetterIndex;//���Ԋi�[
		if (nCountColumn == 9)
		{
			nCountColumn = 0;
			nCountRow++;
		}
		nLetterIndex++;
	}
	m_aLetter[MAX_ROW - 1][MAX_COLUMN - 1].LetterIndex = MAX_WORD - 1;//�I���R�}���h

	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CName::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_WORD; nCount++)
	{
		m_apScene[nCount]->Uninit();
	}
	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		m_apSceneText[nCount]->Uninit();
	}
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CName::Update(void)
{
	//�T�E���h
	CSound * pSound = CManager::GetSound();
	//�L�[�{�[�h�̎擾
	CKeyboard * pKeyboard = CManager::GetKeyboard();

	//�W���C�X�e�B�b�N�̎擾
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
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

	//��������󂪉����ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_DOWN) || m_IsTrigger.Down.bTrigger == true)
	{
		//���ݍs����s������
		m_nRow++;

		//�s�𒴂���Ə�ɖ߂�	
		if (m_nRow >= MAX_ROW)
		{
			m_nRow = 0;
		}
		//�ړ����̍Đ�
		//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_IsTrigger.Down.bTrigger = false;
	}

	//�������󂪉������
	if (pKeyboard->GetKeyboardTrigger(DIK_UP) || m_IsTrigger.Up.bTrigger == true)
	{
		//���ݍs����s������
		m_nRow--;

		//�s�𒴂���Ɖ��ɖ߂�	
		if (m_nRow < 0)
		{
			m_nRow = MAX_ROW - 1;
		}

		//�ړ����̍Đ�
		//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_IsTrigger.Up.bTrigger = false;
	}

	//�����E��󂪉����ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_RIGHT) || m_IsTrigger.Right.bTrigger == true)
	{
		//���ݗ���E�ɂ��炷
		m_nColumn++;

		//��𒴂���ƍ��[�ɖ߂�
		if (m_nColumn >= MAX_COLUMN)
		{
			m_nColumn = 0;
		}

		//�ړ����̍Đ�
		//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_IsTrigger.Right.bTrigger = false;
	}

	//��������󂪉����ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_LEFT) || m_IsTrigger.Left.bTrigger == true)
	{
		//���ݗ�����ɂ��炷
		m_nColumn--;

		//��𒴂���ƉE�[�ɖ߂�
		if (m_nColumn < 0)
		{
			m_nColumn = MAX_COLUMN - 1;
		}

		//�ړ����̍Đ�
		//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_IsTrigger.Left.bTrigger = false;
	}

	//����ENTER��A�{�^�����������Ƃ�
	if (pKeyboard->GetKeyboardTrigger(DIK_SPACE) || lpDIDevice != NULL &&pJoystick->GetJoystickTrigger(JS_A))
	{
		//���艹�̍Đ�
		//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_ENTER);

		//���͏I����������
		if (m_aLetter[m_nRow][m_nColumn].LetterIndex == MAX_WORD - 1)
		{
			//���O�������Ԃɂ���
			m_bOK = true;
		}
		else
		{
			//�������O�̋L�^���\��Ԃ�������
			if (m_nNameCount < 8)
			{
				//���͂��ꂽ�����𖼑O�i�[�p�ϐ��Ɉꕶ�����i�[����
				m_aName[m_nNameCount] = m_aLetter[m_nRow][m_nColumn].aLetter;

				//�e�N�X�`����UV���W�̐ݒ�
				D3DXVECTOR2 aTexture[NUM_VERTEX];
				aTexture[0] = D3DXVECTOR2(m_aLetter[m_nRow][m_nColumn].LetterIndex * 0.037037f, 0.0f);
				aTexture[1] = D3DXVECTOR2(m_aLetter[m_nRow][m_nColumn].LetterIndex * 0.037037f + 0.037037f, 0.0f);
				aTexture[2] = D3DXVECTOR2(m_aLetter[m_nRow][m_nColumn].LetterIndex * 0.037037f, 1.0f);
				aTexture[3] = D3DXVECTOR2(m_aLetter[m_nRow][m_nColumn].LetterIndex * 0.037037f + 0.037037f, 1.0f);
				//�e�N�X�`�����W�̃Z�b�g
				m_apSceneText[m_nNameCount]->SetTexture(aTexture);

				//���O�̕����������Z����
				if (m_nNameCount < 8)
				{
					m_nNameCount++;
				}
			}
		}
	}

	//�������O�ɕ����������Ă���Ƃ�
	if (m_aName != NULL)
	{
		//����BACKSPACE��B�{�^�����������Ƃ�
		if (pKeyboard->GetKeyboardTrigger(DIK_BACK) || lpDIDevice != NULL &&pJoystick->GetJoystickTrigger(JS_B))
		{
			//�V���b�g���̍Đ�
			//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);

			//���͂��ꂽ�����𖼑O�i�[�p�ϐ�����ꕶ�����j������
			m_aName[m_nNameCount] = NULL;

			if (m_nNameCount < 8)
			{
				//�e�N�X�`����UV���W�̐ݒ�
				D3DXVECTOR2 aTexture[NUM_VERTEX];
				aTexture[0] = D3DXVECTOR2(0.00001f, 0.0f);
				aTexture[1] = D3DXVECTOR2(0.0f, 0.0f);
				aTexture[2] = D3DXVECTOR2(0.00001f, 1.0f);
				aTexture[3] = D3DXVECTOR2(0.0f, 1.0f);
				//�e�N�X�`�����W�̃Z�b�g(���������ĂȂ����)
				m_apSceneText[m_nNameCount]->SetTexture(aTexture);
			}

			//���O�̕����������Z����
			if (m_nNameCount > 0)
			{
				m_nNameCount--;
			}
		}
	}

	//�������O�̌��肵���Ƃ�
	if (m_bOK == true)
	{
		//���O�i�[�p�ϐ���NULL����Ȃ��Ƃ�
		if (m_aName[0] != NULL)
		{
			//���O���v���C���[�ɓn��
			for (int nCount = 0; nCount < m_nNameCount; nCount++)
			{
				//CManager::SetPlayerName(nCount, m_aName[nCount]);
			}
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

			for (int nCount = 0; nCount < m_nNameCount; nCount++)
			{
				//�v���C���[�ɖ��O���Z�b�g
				//CManager::SetPlayerName(nCount, m_aName[nCount]);
			}
		}

		//�Q�[���Ɉړ�
		CManager::StartFade(CManager::MODE_GAME);
	}

	for (int nCount = 0; nCount < MAX_WORD; nCount++)
	{
		m_apScene[nCount]->Update();
		//�F�̃Z�b�g
		m_apScene[nCount]->SetColor(D3DCOLOR_RGBA(0, 170, 255, 255));

	}

	//�F�̃Z�b�g
	m_apScene[m_aLetter[m_nRow][m_nColumn].LetterIndex]->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
}


//=============================================================================
// �`��֐�
//=============================================================================
void CName::Draw(void)
{
	for (int nCount = 0; nCount < MAX_WORD; nCount++)
	{
		m_apScene[nCount]->Draw();
	}
	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		m_apSceneText[nCount]->Draw();
	}
}