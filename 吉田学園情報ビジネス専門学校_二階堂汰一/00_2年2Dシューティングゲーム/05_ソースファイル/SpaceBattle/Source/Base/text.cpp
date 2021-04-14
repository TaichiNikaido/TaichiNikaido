//=============================================================================
//
// �e�L�X�g [text.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "Mode/mode_result.h"
#include "Mode/mode_ranking.h"
#include "renderer.h"
#include "System/result.h"
#include "System/ranking.h"
#include "text.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FONT_NAME ("PixelMplus12")
#define INIT_POSIITION_X (SCREEN_WIDTH - 650)
#define INIT_POSITION_Y (SCREEN_HEIGHT - 550)

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
char CText::m_str[256] = {};
bool CText::m_IsDraw = true;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CText::CText()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CText::~CText()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CText * CText::Create(void)
{
	//�e�L�X�g�̃|�C���^
	CText * pText = NULL;
	//�����e�L�X�g�̃|�C���^��NULL�̏ꍇ
	if (pText == NULL)
	{
		//�e�L�X�g�̃������m��
		pText = new CText;
		//�����e�L�X�g�̃|�C���^��NULL����Ȃ��ꍇ
		if (pText != NULL)
		{
			//�e�L�X�g�̏����������֐��Ăяo��
			pText->Init();
		}
	}
	//�e�L�X�g�̃|�C���^��Ԃ�
	return pText;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CText::Init(void)
{
	//�����_���[�̎擾
	CRenderer * pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �t�H���g�̐���
	D3DXCreateFont(pDevice, 32, 25, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FONT_NAME, &m_pFont);
	m_nPosX = INIT_POSIITION_X;
	m_nPosY = INIT_POSITION_Y;
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CText::Uninit(void)
{
	// �t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CText::Update(void)
{
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CText::Draw(void)
{
	CResultMode * pResultMode;			//���U���g���[�h�ւ̃|�C���^
	CRankingMode * pRankingMode;		//�����L���O���[�h�ւ̃|�C���^
	CResult::PLAYER_DATA pPlayerData;	//�v���C���[�f�[�^
	CRanking::RankingData * pRankingData;	//�����L���O�f�[�^
	if (m_IsDraw == true)
	{
		switch (CManager::GetMode())
		{
		case CManager::MODE_RESULT:
			//���U���g���[�h�̎擾
			pResultMode = CManager::GetResultMode();
			if (pResultMode != NULL)
			{
				//�v���C���[�f�[�^�̎擾
				pPlayerData = pResultMode->GetResult()->GetPlayerData();
				m_nPosX = 200;
				m_nPosY = 500;
				wsprintf(m_str, "�����O: %s \n", &pPlayerData.aName);
				m_Rect[0] = { m_nPosX + 2, m_nPosY + 2 + (-1 * 100) , SCREEN_WIDTH, SCREEN_HEIGHT };
				m_Rect[1] = { m_nPosX, m_nPosY + (-1 * 100), SCREEN_WIDTH, SCREEN_HEIGHT };
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
				wsprintf(m_str, "�Q�[���X�R�A�@    �F�@%d\n", pPlayerData.nScore);
				m_Rect[0] = { m_nPosX + 2, m_nPosY + 2 + (0 * 100) , SCREEN_WIDTH, SCREEN_HEIGHT };
				m_Rect[1] = { m_nPosX, m_nPosY + (0 * 100), SCREEN_WIDTH, SCREEN_HEIGHT };
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
				wsprintf(m_str, "�g�����{�����@�F�@%d\n", pPlayerData.nBomb);
				m_Rect[0] = { m_nPosX + 2, m_nPosY + 2 + (1 * 100) , SCREEN_WIDTH, SCREEN_HEIGHT };
				m_Rect[1] = { m_nPosX, m_nPosY + (1 * 100), SCREEN_WIDTH, SCREEN_HEIGHT };
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
				wsprintf(m_str, "�R���e�B�j���[���@�F�@%d\n", pPlayerData.nContinue);
				m_Rect[0] = { m_nPosX + 2, m_nPosY + 2 + (2 * 100) , SCREEN_WIDTH, SCREEN_HEIGHT };
				m_Rect[1] = { m_nPosX, m_nPosY + (2 * 100), SCREEN_WIDTH, SCREEN_HEIGHT };
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
				wsprintf(m_str, "���񂾉񐔁@�F�@%d\n", pPlayerData.nDeath);
				m_Rect[0] = { m_nPosX + 2, m_nPosY + 2 + (3 * 100) , SCREEN_WIDTH, SCREEN_HEIGHT };
				m_Rect[1] = { m_nPosX, m_nPosY + (3 * 100), SCREEN_WIDTH, SCREEN_HEIGHT };
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
			}
			break;
		case CManager::MODE_RANKING:
			//���U���g���[�h�̎擾
			pRankingMode = CManager::GetRankingMode();
			if (pRankingMode != NULL)
			{
				pRankingData = pRankingMode->GetRanking()->GetRankingData();
			}
			for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
			{
				m_nPosX = int(SCREEN_WIDTH - (SCREEN_WIDTH / 1.5f));
				m_nPosY = SCREEN_HEIGHT / 5;
				m_Rect[0] = { m_nPosX + 2, m_nPosY + (nCnt + 1) * 70 + 2, SCREEN_WIDTH, SCREEN_HEIGHT };
				m_Rect[1] = { m_nPosX , m_nPosY + (nCnt + 1) * 70 , SCREEN_WIDTH, SCREEN_HEIGHT };
				char str[256];
				wsprintf(str, "%d�ʁ@%s : �X�R�A:%d\n", nCnt + 1, pRankingData[nCnt].aName, pRankingData[nCnt].nScore);
				m_pFont->DrawText(NULL, str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
				m_pFont->DrawText(NULL, str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
			}
			break;
		default:
			break;
		}
	}
}
