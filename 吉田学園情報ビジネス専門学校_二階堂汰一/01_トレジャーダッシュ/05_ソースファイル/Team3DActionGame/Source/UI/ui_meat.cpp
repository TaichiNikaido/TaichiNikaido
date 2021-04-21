//================================================
//
// ui_number処理 [ui_number.h]
// Author : 佐藤颯紀
//
//================================================

//================================================
// インクルードファイル
//================================================
#include "ui_meat.h"
#include "number.h"
#include "Base/manager.h"
#include "Mode/mode_game.h"
#include "Character/player.h"

//================================================
// 静的メンバ変数宣言
//================================================
int CMeatUI::m_nMeat = NULL;

//================================================
// クリエイト処理
//================================================
CMeatUI *CMeatUI::Create()
{
	CMeatUI *pMeat;
	pMeat = new CMeatUI;
	pMeat->Init();

	return pMeat;
}

//====================================================
// コンストラクタ
//====================================================
CMeatUI::CMeatUI(int nPriority) : CScene(nPriority)
{

}

//====================================================
// デストラクタ
//====================================================
CMeatUI::~CMeatUI()
{

}

//================================================
// 初期化処理
//================================================
HRESULT CMeatUI::Init()
{
	m_nMeat = MEAT_POSSESSION;		// 肉の初期値

	for (int nCount = 0; nCount < MEATE_MAX_DIGITS; nCount++)
	{
		// 数字の生成
		m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(MEAT_NUMBER_POS_X + nCount*MEAT_NUMBER_SIZE, MEAT_NUMBER_POS_Y, 0.0f),
			D3DXVECTOR3(MEAT_NUMBER_SIZE, MEAT_NUMBER_SIZE, 0.0f),
			CNumber::NUMBERTYPE_MEAT);
	}
	return S_OK;
}

//================================================
// 終了処理
//================================================
void CMeatUI::Uninit(void)
{
	for (int nCount = 0; nCount < MEATE_MAX_DIGITS; nCount++)
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
void CMeatUI::Update(void)
{
	CPlayer * pPlayer = CGameMode::GetPlayer();

	for (int nCount = 0; nCount < MEATE_MAX_DIGITS; nCount++)
	{
		// 更新処理
		m_apNumber[nCount]->Update();
	}
	//もしプレイヤーのポインタがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//プレイヤーの肉の数を取得する
		m_nMeat = pPlayer->GetMeat();
	}
	for (int nCount = 0; nCount < MEATE_MAX_DIGITS; nCount++)
	{
		// 表示してる数字に加算させる
		m_apNumber[nCount]->SetNumber(m_nMeat % (int)powf(10, MEATE_MAX_DIGITS - nCount) / powf(10, MEATE_MAX_DIGITS - nCount - 1));
	}
}

//================================================
// 描画処理
//================================================
void CMeatUI::Draw(void)
{
	for (int nCount = 0; nCount < MEATE_MAX_DIGITS; nCount++)
	{
		// 描画処理
		m_apNumber[nCount]->Draw();
	}
}

