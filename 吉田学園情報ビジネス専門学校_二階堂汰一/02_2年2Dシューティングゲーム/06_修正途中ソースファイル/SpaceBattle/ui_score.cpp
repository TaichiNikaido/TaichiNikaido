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
#define MINIMUM_INTEGER (0)
#define MINIMUM_COUNT_NUMBER (0)
#define NUM_CONVERSION (10.0f)

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
	//スコアのUIのポインタ
	CScoreUI * pScoreUI = NULL;
	//もしスコアのUIのポインタがNULLの場合
	if (pScoreUI == NULL)
	{
		//スコアのUIのメモリ確保
		pScoreUI = new CScoreUI;
	}
	//初期化処理関数呼び出し
	pScoreUI->Init();
	return pScoreUI;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CScoreUI::Init(void)
{
	//最大桁数分回す
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		//数字のテクスチャの生成処理関数呼び出し
		m_apNumberTexture[nCount] = CUINumberTexture::Create(D3DXVECTOR3(POSITION.x - (SIZE.x * nCount), POSITION.y, 0.0f),SIZE);
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CScoreUI::Uninit(void)
{
	//最大桁数分回す
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		//もし数字のテクスチャがNULLじゃない場合
		if (m_apNumberTexture[nCount] != NULL)
		{
			//数字のテクスチャの終了処理関数呼び出し
			m_apNumberTexture[nCount]->Uninit();
			//数字のテクスチャのメモリ破棄
			delete m_apNumberTexture[nCount];
			//数字のテクスチャをNULLにする
			m_apNumberTexture[nCount] = NULL;
		}
	}
	//破棄処理関数呼び出し
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
	//最大桁数分回す
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		//数字のテクスチャの描画処理関数呼び出し
		m_apNumberTexture[nCount]->Draw();
	}
}

//=============================================================================
// スコア設定関数
//=============================================================================
void CScoreUI::SetScore(int nScore)
{
	int integer = MINIMUM_INTEGER;			//計算用変数
	int nCntNumber = MINIMUM_COUNT_NUMBER;	//番号カウンタ
	//最大桁数分回す
	for (int nCntDigit = 1; nCntDigit <= MAX_NUMBER; nCntDigit++, nCntNumber++)
	{
		//出したい値の桁数の一つ上の桁数の数字抽出
		integer = int(nScore / std::pow(NUM_CONVERSION, nCntDigit));
		//切り捨てた数字を桁数分掛ける
		integer = int(integer * std::pow(NUM_CONVERSION, nCntDigit));
		//数字を設定する上の桁数の数字と下の桁数の数字を引いて取り除く
		m_apNumberTexture[nCntNumber]->SetNumber(int((nScore - integer) / std::pow(NUM_CONVERSION, nCntDigit - 1)));
	}
}
