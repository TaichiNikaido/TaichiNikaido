//=============================================================================
//
// スコア処理 [Score.cpp]
// Author: 二階堂汰一
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "score.h"
#include "player.h"
#include <cmath>

//=============================================================================
// コンストラクタ
//=============================================================================
CScore::CScore(int nPriority) :CScene(nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_nScore = 0;	//スコア
}

//=============================================================================
//デストラクタ
//=============================================================================
CScore::~CScore()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CScore * CScore::Create(D3DXVECTOR3 pos, float SizeWidth,float SizeHeight)
{
	CScore * pScore;
	pScore = new CScore;
	pScore->Init(pos, SizeWidth, SizeHeight);
	return pScore;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CScore::Init(D3DXVECTOR3 pos, float SizeWidth,float SizeHeight)
{

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(pos.x - (SizeWidth * nCount), pos.y, 0.0f), SizeHeight, SizeWidth);
	}
	m_nScore = 0;	//スコア
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//Uninit,delete,NULL代入
			m_apNumber[nCount]->Uninit();
			delete m_apNumber[nCount];
			m_apNumber[nCount] = NULL;
		}
	}
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CScore::Update(void)
{
	CPlayer::SetPlayerScpre(m_nScore);
}

//=============================================================================
// 描画関数
//=============================================================================
void CScore::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->Draw();
	}
}

//=============================================================================
// 加算関数
//=============================================================================
void CScore::AddScore(int nValue)
{
	//スコアに引数の値を加算
	m_nScore += nValue;
	//スコアをセットする
	SetScore(m_nScore);
}

void CScore::SubScore(int nValue)
{
	//スコアに引数の値を加算
	m_nScore -= nValue;
	//スコアをセットする
	SetScore(m_nScore);
}

//=============================================================================
// セット関数
//=============================================================================
void CScore::SetScore(int nScore)
{
	//スコアに引数を代入
	m_nScore = nScore;

	int integer = 0;	//計算用変数
	int nCntNumber = 0;	//番号カウンタ

	for (int nCntDigit = 1; nCntDigit <= MAX_NUMBER; nCntDigit++, nCntNumber++)
	{
		integer = int(m_nScore / std::pow(10.0f, nCntDigit)); //1の位以下を切り捨てる
		integer = int(integer * std::pow(10.0f, nCntDigit));
		m_apNumber[nCntNumber]->SetNumber(int((m_nScore - integer) / std::pow(10.0f, nCntDigit - 1)));
	}
}