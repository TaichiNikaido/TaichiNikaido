//=============================================================================
//
// ���O���� [name.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/sound.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "name.h"
#include "Polygon2d/letter.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MINIMUM_COLUMNS (0)		//��̍ŏ��l
#define MINIMUM_ROWS (0)		//�s�̍ŏ��l
#define SUB_LETTER (-1)			//�����̌��Z��

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CName::CName()
{
	m_nColumns = MINIMUM_COLUMNS;							//��
	m_nLetter = MINIMUM_ALPHABET;							//�����ԍ�
	m_nNameCount = MINIMUM_NAME;							//���O�̕������J�E���^
	memset(m_aLetter,NULL,sizeof(m_aLetter));				//����
	memset(m_aName,NULL,sizeof(m_aName));					//���O
	memset(m_apLetter, NULL, sizeof(m_apLetter));			//����
	memset(m_apNameLetter,NULL,sizeof(m_apNameLetter));		//���O�̕���
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CName::~CName()
{
}

//=============================================================================
// ���������֐��Ăяo��
//=============================================================================
CName * CName::Create()
{
	//���O���͂̃|�C���^
	CName * pName = nullptr;
	//���O���͂̃|�C���^��nullptr�̏ꍇ
	if (pName == nullptr)
	{
		//���O���͂̃������m��
		pName = new CName;
		//���O���͂̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pName != nullptr)
		{
			//���O���͂̏����������֐��Ăяo��
			pName->Init();
		}
	}
	//���O���͂̃{�^���̃|�C���^��Ԃ�
	return pName;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CName::Init()
{
	//�����ǂݍ��݊֐�
	LetterLoad();
	//�����S���������֐��Ăяo��
	InitAllCreate();
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CName::Uninit(void)
{
	//�A���t�@�x�b�g�̍ő吔����
	for (int nCount = MINIMUM_ALPHABET; nCount < MAX_ALPHABET; nCount++)
	{
		//�����̏I�������֐��Ăяo��
		m_apLetter[nCount]->Uninit();
	}
	//���O�̍ő吔����
	for (int nCount = MINIMUM_NAME; nCount < MAX_NAME; nCount++)
	{
		//���O�̕����̏I�������֐��Ăяo��
		m_apNameLetter[nCount]->Uninit();
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CName::Update(void)
{
	//���͏����֐��Ăяo��
	Input();
	//�A���t�@�x�b�g�̍ő吔����
	for (int nCount = MINIMUM_ALPHABET; nCount < MAX_ALPHABET; nCount++)
	{
		//���ݑI������Ă��Ȃ������̐F��ύX
		m_apLetter[nCount]->NotSelectColor();
	}
	//�s���Ƃ̏���
	switch (m_nColumns)
	{
	case COLUMNS_1:
		//�I�����̐F�ɕύX����
		m_apLetter[m_nLetter]->SelectColor();
		break;
	case COLUMNS_2:
		//�I�����̐F�ɕύX����
		m_apLetter[10 + m_nLetter]->SelectColor();
		break;
	case COLUMNS_3:
		//�I�����̐F�ɕύX����
		m_apLetter[19 + m_nLetter]->SelectColor();
		break;
	default:
		break;
	}
	//�A���t�@�x�b�g�̍ő吔����
	for (int nCount = MINIMUM_ALPHABET; nCount < MAX_ALPHABET; nCount++)
	{
		//�����̍X�V�����֐��Ăяo��
		m_apLetter[nCount]->Update();
	}
	//���O�̍ő吔����
	for (int nCount = MINIMUM_NAME; nCount < MAX_NAME; nCount++)
	{
		//���O�̕����̍X�V�����֐��Ăяo��
		m_apNameLetter[nCount]->Update();
	}
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CName::Draw(void)
{
	//�A���t�@�x�b�g�̍ő吔����
	for (int nCount = MINIMUM_ALPHABET; nCount < MAX_ALPHABET; nCount++)
	{
		//�����̕`�揈���֐��Ăяo��
		m_apLetter[nCount]->Draw();
	}
	//���O�̍ő啶��������
	for (int nCount = MINIMUM_NAME; nCount < MAX_NAME; nCount++)
	{
		//���O�̕����̕`�揈���֐��Ăяo��
		m_apNameLetter[nCount]->Draw();
	}
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CName::Input(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
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
	//����L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetKeyboardTrigger(DIK_UP))
	{
		//�������݂̗񂪍ŏ��l����̏ꍇ
		if (m_nColumns > MINIMUM_COLUMNS)
		{
			//������Z����
			m_nColumns--;
		}
	}
	//�����L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetKeyboardTrigger(DIK_DOWN))
	{
		//���݂̗񂪍ő吔��艺��������
		if (m_nColumns < COLUMNS_3)
		{
			//���݂̗�����Z����
			m_nColumns++;
		}
		//�񂲂Ƃ̏���
		switch (m_nColumns)
		{
		case COLUMNS_1:
			//�������݂̕����ԍ���P����̏ꍇ
			if (m_nLetter > P)
			{
				//���݂̕����ԍ���P�ɂ���
				m_nLetter = P;
			}
			break;
		case COLUMNS_2:
			//�������݂̕����ԍ���L����̏ꍇ
			if (m_nLetter > L)
			{
				//���݂̕����ԍ���L�ɂ���
				m_nLetter = L;
			}
			break;
		case COLUMNS_3:
			//�������݂̕����ԍ���M����̏ꍇ
			if (m_nLetter > M)
			{
				//���݂̕����ԍ���M�ɂ���
				m_nLetter = M;
			}
			break;
		default:
			break;
		}
	}
	//�������L�[�����͂��ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_LEFT))
	{
		//�������݂̕����ԍ���0����̏ꍇ
		if (m_nLetter > MINIMUM_ALPHABET)
		{
			//�����ԍ������Z����
			m_nLetter--;
		}
	}
	//�����E�L�[�����͂��ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_RIGHT))
	{
		//�񂲂Ƃ̏���
		switch (m_nColumns)
		{
		case COLUMNS_1:
			//�������݂̕����ԍ���P��艺�̏ꍇ
			if (m_nLetter < P)
			{
				//�����ԍ������Z����
				m_nLetter++;
			}
			break;
		case COLUMNS_2:
			//�������݂̕����ԍ���L��艺�̏ꍇ
			if (m_nLetter < L)
			{
				//�����ԍ������Z����
				m_nLetter++;
			}
			break;
		case COLUMNS_3:
			//�������݂̕����ԍ���M��艺�̏ꍇ
			if (m_nLetter < M)
			{
				//�����ԍ������Z����
				m_nLetter++;
			}
			break;
		default:
			break;
		}
	}
	//����ENTER�L�[����A�{�^���������ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pJoystick->GetJoystickTrigger(JS_A))
	{
		//�������O�̕������J�E���^���ő吔��艺�̏ꍇ
		if (m_nNameCount < MAX_NAME)
		{
			int nIndex = 0;
			//���O�̕������i�[����
			m_aName[m_nNameCount] = m_aLetter[m_nColumns][m_nLetter];
			//�񂲂Ƃ̏���
			switch (m_nColumns)
			{
			case COLUMNS_1:
				nIndex = m_nLetter;
				break;
			case COLUMNS_2:
				nIndex = 10 + m_nLetter;
				break;
			case COLUMNS_3:
				nIndex = 10 + 9 + m_nLetter;
				break;
			}
			//���O�̕�����ݒ肷��
			m_apNameLetter[m_nNameCount]->SetLetter(nIndex);
			//���O�̕������J�E���^�����Z����
			m_nNameCount++;
		}
	}
	//����BACK_SPACE�L�[����B�{�^���������ꂽ��
	if (pKeyboard->GetKeyboardTrigger(DIK_BACK) || pJoystick->GetJoystickTrigger(JS_B))
	{
		//�������O�̕����J�E���^��0����̏ꍇ
		if (m_nNameCount > MINIMUM_NAME)
		{
			//���O�̕����J�E���^�����Z����
			m_nNameCount--;
			//���O�̕�����ݒ肷��
			m_apNameLetter[m_nNameCount]->SetLetter(SUB_LETTER);
			//���݂̖��O�̕��������Z����
			m_aName[m_nNameCount] = NULL;
		}
	}
	if (pKeyboard->GetKeyboardTrigger(DIK_X) || pJoystick->GetJoystickTrigger(JS_START))
	{
		//�T�E���h�̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pSound != NULL)
		{
			//���艹�̍Đ�
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);
		}
		//�Q�[�����[�h�ɑJ�ڂ���
		CManager::StartFade(CManager::MODE_GAME);
	}
}

//=============================================================================
// �����ǂݍ��݊֐�
//=============================================================================
void CName::LetterLoad(void)
{
	//�������i�[
	m_aLetter[0][0] = 'Q';
	m_aLetter[0][1] = 'W';
	m_aLetter[0][2] = 'E';
	m_aLetter[0][3] = 'R';
	m_aLetter[0][4] = 'T';
	m_aLetter[0][5] = 'Y';
	m_aLetter[0][6] = 'U';
	m_aLetter[0][7] = 'I';
	m_aLetter[0][8] = 'O';
	m_aLetter[0][9] = 'P';
	m_aLetter[1][0] = 'A';
	m_aLetter[1][1] = 'S';
	m_aLetter[1][2] = 'D';
	m_aLetter[1][3] = 'F';
	m_aLetter[1][4] = 'G';
	m_aLetter[1][5] = 'H';
	m_aLetter[1][6] = 'J';
	m_aLetter[1][7] = 'K';
	m_aLetter[1][8] = 'L';
	m_aLetter[2][0] = 'Z';
	m_aLetter[2][1] = 'X';
	m_aLetter[2][2] = 'C';
	m_aLetter[2][3] = 'V';
	m_aLetter[2][4] = 'B';
	m_aLetter[2][5] = 'N';
	m_aLetter[2][6] = 'M';
}

//=============================================================================
// �����S���������֐�
//=============================================================================
void CName::InitAllCreate(void)
{
	int nIndex = 0;			//�s�ԍ�
	int nCreateCount = 0;	//������
	//��s�ڂ̃A���t�@�x�b�g�̍ő吔������
	for (int nCount = 0; nCount < 10; nCount++)
	{
		//�����̉摜����
		m_apLetter[nCount] = CLetter::Create(D3DXVECTOR3(400.0f + 120.0f * nCount, 600.0f + 125.0f * nIndex, 0.0f));
		m_apLetter[nCount]->SetLetter(nCreateCount);
		//�����������Z����
		nCreateCount++;
	}
	//�s�ԍ������Z����
	nIndex++;
	//��s�ڂ̃A���t�@�x�b�g�̍ő吔����
	for (int nCount = 10; nCount < 19; nCount++)
	{
		//�����̉摜����
		m_apLetter[nCount] = CLetter::Create(D3DXVECTOR3(460.0f + 120.0f * (nCount - 10), 600.0f + 125.0f * nIndex, 0.0f));
		//������ݒ肷��
		m_apLetter[nCount]->SetLetter(nCreateCount);
		//�����������Z����
		nCreateCount++;
	}
	//�s�ԍ������Z����
	nIndex++;
	//�O�s�ڂ̃A���t�@�x�b�g�̍ő吔����
	for (int nCount = 19; nCount < 26; nCount++)
	{
		//�����̉摜����
		m_apLetter[nCount] = CLetter::Create(D3DXVECTOR3(580.0f + 120.0f * (nCount - 19), 600.0f + 125.0f * nIndex, 0.0f));
		//������ݒ肷��
		m_apLetter[nCount]->SetLetter(nCreateCount);
		//�����������Z����
		nCreateCount++;
	}
	//���O�̍ő吔����
	for (int nCount = 0; nCount < MAX_NAME; nCount++)
	{
		//�����̉摜����
		m_apNameLetter[nCount] = CLetter::Create(D3DXVECTOR3(520.0f + 120.0f * nCount, 400.0f, 0.0f));
		//������ݒ肷��
		m_apNameLetter[nCount]->SetLetter(-1);
	}
}