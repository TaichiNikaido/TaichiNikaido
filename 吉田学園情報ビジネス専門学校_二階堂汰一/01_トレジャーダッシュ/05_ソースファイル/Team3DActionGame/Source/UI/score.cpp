//================================================
//
// スコア処理 [score.cpp]
// Author : 佐藤颯紀
//
//================================================

//================================================
// インクルードファイル
//================================================
#include "score.h"
#include "number.h"
#include "Base/manager.h"
#include "ui_daiya.h"

//================================================
// 静的メンバ変数宣言
//================================================

//================================================
// クリエイト処理
//================================================
CScore *CScore::Create()
{
	CScore *pScore;
	pScore = new CScore;
	pScore->Init();

	return pScore;
}

//====================================================
// コンストラクタ
//====================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	m_nScore = 0;	// スコア
}

//====================================================
// デストラクタ
//====================================================
CScore::~CScore()
{

}

//================================================
// 初期化処理
//================================================
HRESULT CScore::Init()
{
	// ダイヤの数取得
	m_nDaiya = 0;

	// スコアの初期値
	m_nScore = 0;

	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		// 数字の生成
		m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(SCORE_POS_X + nCount*SCORE_SIZE, SCORE_POS_Y, 0.0f), D3DXVECTOR3(SCORE_SIZE, SCORE_SIZE, 0.0f), CNumber::NUMBERTYPE_SCORE);
	}

	AddScore();

	return S_OK;
}

//================================================
// 終了処理
//================================================
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		//ナンバー処理の終了と開放
		if (m_apNumber[nCount] != NULL)
		{
			// 終了処理
			m_apNumber[nCount]->Uninit();
			m_apNumber[nCount] = NULL;
		}
	}
	// 開放
	Release();
}

//================================================
// 更新処理
//================================================
void CScore::Update(void)
{
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		// 更新処理
		m_apNumber[nCount]->Update();
	}
}

//================================================
// 描画処理
//================================================
void CScore::Draw(void)
{
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		// 描画処理
		m_apNumber[nCount]->Draw();
	}

}

//================================================
// スコア加算処理
//================================================
void CScore::AddScore(void)
{
	// ダイヤの数の情報を取得
	m_nDaiya = CDaiyaUI::GetDaiya();

	// スコアにダイヤの数を加算する
	m_nScore += m_nDaiya;

	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		// 表示してる数字に加算させる
		m_apNumber[nCount]->SetNumber(m_nScore % (int)powf(10, MAX_SCORE - nCount) / (int)powf(10, MAX_SCORE - nCount - 1));
	}
}