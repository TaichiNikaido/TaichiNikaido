//=============================================================================
//
// スコアのUI [ui_score.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <cmath>
#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "ui_number_texture.h"
#include "ui_score.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POSITION (D3DXVECTOR3(1495.0f,25.0f,0.0f))
#define SIZE (D3DXVECTOR3(47.0f,47.0f,0.0f))

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CScoreUI::CScoreUI(int nPriority) : CScene(nPriority)
{
	memset(m_apNumberTexture, NULL, sizeof(m_apNumberTexture));	//UI用テクスチャへのポインタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CScoreUI::~CScoreUI()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CScoreUI * CScoreUI::Create(void)
{
	CScoreUI * pScoreUI;
	pScoreUI = new CScoreUI;
	pScoreUI->Init();
	return pScoreUI;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CScoreUI::Init(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumberTexture[nCount] = CUINumberTexture::Create(D3DXVECTOR3(POSITION.x - (SIZE.x * nCount), POSITION.y, 0.0f),SIZE);
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CScoreUI::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumberTexture[nCount] != NULL)
		{
			//Uninit,delete,NULL代入
			m_apNumberTexture[nCount]->Uninit();
			delete m_apNumberTexture[nCount];
			m_apNumberTexture[nCount] = NULL;
		}
	}
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CScoreUI::Update(void)
{
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CScoreUI::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumberTexture[nCount]->Draw();
	}
}

//=============================================================================
// スコア設定関数
//=============================================================================
void CScoreUI::SetScore(int nScore)
{
	int integer = 0;	//計算用変数
	int nCntNumber = 0;	//番号カウンタ

	for (int nCntDigit = 1; nCntDigit <= MAX_NUMBER; nCntDigit++, nCntNumber++)
	{
		integer = int(nScore / std::pow(10.0f, nCntDigit)); //1の位以下を切り捨てる
		integer = int(integer * std::pow(10.0f, nCntDigit));
		m_apNumberTexture[nCntNumber]->SetNumber(int((nScore - integer) / std::pow(10.0f, nCntDigit - 1)));
	}
}
