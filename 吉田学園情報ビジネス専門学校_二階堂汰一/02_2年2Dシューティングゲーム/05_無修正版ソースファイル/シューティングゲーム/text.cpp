//=============================================================================
//
// テキストの処理 [text.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "text.h"
#include "result.h"
#include "ranking.h"

bool CText::m_IsDraw = false;
char CText::m_str[256] = {};
CText::CText()
{
	m_pFont = NULL;
	m_Rect[0] = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	m_Rect[1] = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	m_Rect[2] = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	m_Rect[3] = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	memset(m_str, 0, sizeof(m_str));
	/*memset(&m_playerData, 0, sizeof(m_playerData));*/
	posX = 0;
	posY = 0;
}
CText::~CText()
{

}

CText * CText::Create(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight)
{
	CText *pText;

	pText = new CText;
	pText->Init(pos, fSizeWidth, fSizeHeight);

	return pText;
}

HRESULT CText::Init(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// フォントの生成
	D3DXCreateFont(pDevice, 32, 25, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FONT_NAME, &m_pFont);

	posX = SCREEN_WIDTH - 650;
	posY = SCREEN_HEIGHT - 550;
	return S_OK;
}

void CText::Uninit(void)
{
	// フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

void CText::Update(void)
{


}

void CText::Draw(void)
{
	if (m_IsDraw == true)
	{
		switch (CManager::GetMode())
		{
		case CManager::MODE_GAME:
			//m_Rect[0] = { posX + 2, posY + 2 , posX + 2 + 400, posY + 2 + 100 };
			//m_Rect[1] = { posX, posY, posX + 400, posY + 100 };

			//posX = FIELD_WIDTH - 650;
			//posY = FIELD_HEIGHT - 550;

			////m_Rect[0] = { posX + 2, posY + 2 , posX + 2 + 400, posY + 2 + 100 };
			////m_Rect[1] = { posX, posY, posX + 400, posY + 100 };
			////wsprintf(m_str, &m_str[0]);
			//// テキスト描画
			//wsprintf(m_str, "testssssssssssssssssss");
			//m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 100));
			//m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
			//m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
			break;
		case CManager::MODE_RESULT:
			posX = 200;
			posY = 500;
			CResult::PLAYER_DATA playerData = CResult::GetPlayerData();
			wsprintf(m_str, "お名前: %s \n", &playerData.aName);
			m_Rect[0] = { posX + 2, posY + 2 + (-1 * 100) , SCREEN_WIDTH, SCREEN_HEIGHT };
			m_Rect[1] = { posX, posY + (-1 * 100), SCREEN_WIDTH, SCREEN_HEIGHT };
			m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
			m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

			wsprintf(m_str, "ゲームスコア　    ：　%d\n", playerData.nScore);
			m_Rect[0] = { posX + 2, posY + 2 + (0 * 100) , SCREEN_WIDTH, SCREEN_HEIGHT };
			m_Rect[1] = { posX, posY + (0 * 100), SCREEN_WIDTH, SCREEN_HEIGHT };
			m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
			m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

			wsprintf(m_str, "使ったボム数　：　%d\n", playerData.nBomb);
			m_Rect[0] = { posX + 2, posY + 2 + (1 * 100) , SCREEN_WIDTH, SCREEN_HEIGHT };
			m_Rect[1] = { posX, posY + (1 * 100), SCREEN_WIDTH, SCREEN_HEIGHT };
			m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
			m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

			wsprintf(m_str, "コンティニュー数　：　%d\n", playerData.nContinue);
			m_Rect[0] = { posX + 2, posY + 2 + (2 * 100) , SCREEN_WIDTH, SCREEN_HEIGHT };
			m_Rect[1] = { posX, posY + (2 * 100), SCREEN_WIDTH, SCREEN_HEIGHT };
			m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
			m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

			wsprintf(m_str, "死んだ回数　：　%d\n", playerData.nDeath);
			m_Rect[0] = { posX + 2, posY + 2 + (3 * 100) , SCREEN_WIDTH, SCREEN_HEIGHT };
			m_Rect[1] = { posX, posY + (3 * 100), SCREEN_WIDTH, SCREEN_HEIGHT };
			m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
			m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

			break;
		case CManager::MODE_RANKING:
			for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
			{
				posX = int(SCREEN_WIDTH - (SCREEN_WIDTH / 1.5f));
				posY = SCREEN_HEIGHT / 5;
				m_Rect[0] = { posX + 2, posY + (nCnt + 1) * 70 + 2, SCREEN_WIDTH, SCREEN_HEIGHT };
				m_Rect[1] = { posX , posY + (nCnt + 1) * 70 , SCREEN_WIDTH, SCREEN_HEIGHT };
				char str[256];
				CRanking::RankingData * RankingData = CRanking::GetRankingData();

				wsprintf(str, "%d位　%s : スコア:%d\n", nCnt + 1, RankingData[nCnt].aName, RankingData[nCnt].nScore);

				// テキスト描画
				m_pFont->DrawText(NULL, str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
				m_pFont->DrawText(NULL, str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
			}
		default:
			break;
		}
	}
}
