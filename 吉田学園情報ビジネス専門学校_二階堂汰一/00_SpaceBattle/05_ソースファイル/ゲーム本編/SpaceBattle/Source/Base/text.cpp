//=============================================================================
//
// テキスト [text.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
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
// マクロ定義
//*****************************************************************************
#define FONT_NAME ("PixelMplus12")
#define INIT_POSIITION_X (SCREEN_WIDTH - 650)
#define INIT_POSITION_Y (SCREEN_HEIGHT - 550)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
char CText::m_str[256] = {};
bool CText::m_IsDraw = true;

//=============================================================================
// コンストラクタ
//=============================================================================
CText::CText()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CText::~CText()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CText * CText::Create(void)
{
	//テキストのポインタ
	CText * pText = NULL;
	//もしテキストのポインタがNULLの場合
	if (pText == NULL)
	{
		//テキストのメモリ確保
		pText = new CText;
		//もしテキストのポインタがNULLじゃない場合
		if (pText != NULL)
		{
			//テキストの初期化処理関数呼び出し
			pText->Init();
		}
	}
	//テキストのポインタを返す
	return pText;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CText::Init(void)
{
	//レンダラーの取得
	CRenderer * pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// フォントの生成
	D3DXCreateFont(pDevice, 32, 25, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FONT_NAME, &m_pFont);
	m_nPosX = INIT_POSIITION_X;
	m_nPosY = INIT_POSITION_Y;
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CText::Uninit(void)
{
	// フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CText::Update(void)
{
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CText::Draw(void)
{
	CResultMode * pResultMode;			//リザルトモードへのポインタ
	CRankingMode * pRankingMode;		//ランキングモードへのポインタ
	CResult::PLAYER_DATA pPlayerData;	//プレイヤーデータ
	CRanking::RankingData * pRankingData;	//ランキングデータ
	if (m_IsDraw == true)
	{
		switch (CManager::GetMode())
		{
		case CManager::MODE_RESULT:
			//リザルトモードの取得
			pResultMode = CManager::GetResultMode();
			if (pResultMode != NULL)
			{
				//プレイヤーデータの取得
				pPlayerData = pResultMode->GetResult()->GetPlayerData();
				m_nPosX = 200;
				m_nPosY = 500;
				wsprintf(m_str, "お名前: %s \n", &pPlayerData.aName);
				m_Rect[0] = { m_nPosX + 2, m_nPosY + 2 + (-1 * 100) , SCREEN_WIDTH, SCREEN_HEIGHT };
				m_Rect[1] = { m_nPosX, m_nPosY + (-1 * 100), SCREEN_WIDTH, SCREEN_HEIGHT };
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
				wsprintf(m_str, "ゲームスコア　    ：　%d\n", pPlayerData.nScore);
				m_Rect[0] = { m_nPosX + 2, m_nPosY + 2 + (0 * 100) , SCREEN_WIDTH, SCREEN_HEIGHT };
				m_Rect[1] = { m_nPosX, m_nPosY + (0 * 100), SCREEN_WIDTH, SCREEN_HEIGHT };
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
				wsprintf(m_str, "使ったボム数　：　%d\n", pPlayerData.nBomb);
				m_Rect[0] = { m_nPosX + 2, m_nPosY + 2 + (1 * 100) , SCREEN_WIDTH, SCREEN_HEIGHT };
				m_Rect[1] = { m_nPosX, m_nPosY + (1 * 100), SCREEN_WIDTH, SCREEN_HEIGHT };
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
				wsprintf(m_str, "コンティニュー数　：　%d\n", pPlayerData.nContinue);
				m_Rect[0] = { m_nPosX + 2, m_nPosY + 2 + (2 * 100) , SCREEN_WIDTH, SCREEN_HEIGHT };
				m_Rect[1] = { m_nPosX, m_nPosY + (2 * 100), SCREEN_WIDTH, SCREEN_HEIGHT };
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
				wsprintf(m_str, "死んだ回数　：　%d\n", pPlayerData.nDeath);
				m_Rect[0] = { m_nPosX + 2, m_nPosY + 2 + (3 * 100) , SCREEN_WIDTH, SCREEN_HEIGHT };
				m_Rect[1] = { m_nPosX, m_nPosY + (3 * 100), SCREEN_WIDTH, SCREEN_HEIGHT };
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
				m_pFont->DrawText(NULL, m_str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
			}
			break;
		case CManager::MODE_RANKING:
			//リザルトモードの取得
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
				wsprintf(str, "%d位　%s : スコア:%d\n", nCnt + 1, pRankingData[nCnt].aName, pRankingData[nCnt].nScore);
				m_pFont->DrawText(NULL, str, -1, &m_Rect[0], DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
				m_pFont->DrawText(NULL, str, -1, &m_Rect[1], DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
			}
			break;
		default:
			break;
		}
	}
}
