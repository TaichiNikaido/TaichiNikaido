//================================================
//
// ui_number処理 [ui_number.h]
// Author : 佐藤颯紀
//
//================================================

//================================================
// インクルードファイル
//================================================
#include "ui_daiya.h"
#include "number.h"
#include "Base/manager.h"
#include "Mode/mode_game.h"
#include "Character/player.h"

//================================================
// 静的メンバ変数宣言
//================================================
int CDaiyaUI::m_nDaiya = NULL;

//================================================
// クリエイト処理
//================================================
CDaiyaUI *CDaiyaUI::Create()
{
	CDaiyaUI *pDaiya;
	pDaiya = new CDaiyaUI;
	pDaiya->Init();

	return pDaiya;
}

//====================================================
// コンストラクタ
//====================================================
CDaiyaUI::CDaiyaUI(int nPriority) : CScene(nPriority)
{

}

//====================================================
// デストラクタ
//====================================================
CDaiyaUI::~CDaiyaUI()
{

}

//================================================
// 初期化処理
//================================================
HRESULT CDaiyaUI::Init()
{
	m_nDaiya = 0;		// ダイヤの初期値

	for (int nCount = 0; nCount < DAIYA_MAX_DIGITS; nCount++)
	{
		// 数字の生成
		m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(DAIYA_NUMBER_POS_X + nCount*DAIYA_NUMBER_SIZE, DAIYA_NUMBER_POS_Y, 0.0f),
			D3DXVECTOR3(DAIYA_NUMBER_SIZE, DAIYA_NUMBER_SIZE, 0.0f),
			CNumber::NUMBERTYPE_DAIYA);
	}

	// 加算
	AddDaiya(0);

	return S_OK;
}

//================================================
// 終了処理
//================================================
void CDaiyaUI::Uninit(void)
{
	for (int nCount = 0; nCount < DAIYA_MAX_DIGITS; nCount++)
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
void CDaiyaUI::Update(void)
{
	CPlayer * pPlayer = CGameMode::GetPlayer();
	for (int nCount = 0; nCount < DAIYA_MAX_DIGITS; nCount++)
	{
		// 更新処理
		m_apNumber[nCount]->Update();
	}
	//もしプレイヤーのポインタがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//プレイヤーのダイアの数を取得する
		m_nDaiya = pPlayer->GetDiamond();
	}

	for (int nCount = 0; nCount < DAIYA_MAX_DIGITS; nCount++)
	{
		// 表示してる数字に加算させる
		m_apNumber[nCount]->SetNumber(m_nDaiya % (int)powf(10, DAIYA_MAX_DIGITS - nCount) / powf(10, DAIYA_MAX_DIGITS - nCount - 1));
	}
}

//================================================
// 描画処理
//================================================
void CDaiyaUI::Draw(void)
{
	for (int nCount = 0; nCount < DAIYA_MAX_DIGITS; nCount++)
	{
		// 描画処理
		m_apNumber[nCount]->Draw();
	}

}

//================================================
// ダイヤの加算
//================================================
void CDaiyaUI::AddDaiya(int nValue)
{
}