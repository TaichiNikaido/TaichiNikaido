//=============================================================================
//
// ドラゴンのライフのUI [ui_village_life.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "renderer.h"
#include "ui_dragon_life.h"
#include "ui_gauge.h"
#include "ui_gauge_flame.h"
#include "enemy_dragon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INITIAL_LIFE (0)	//体力の初期値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CDragonLifeUI::CDragonLifeUI()
{
	m_nMaxLife = INITIAL_LIFE;	//最大体力
	m_nLife = INITIAL_LIFE;		//体力
	m_pGauge = NULL;			//ゲージのポインタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CDragonLifeUI::~CDragonLifeUI()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CDragonLifeUI * CDragonLifeUI::Create(void)
{
	//ドラゴンの体力UIのポインタ
	CDragonLifeUI * pDragonLifeUI = NULL;
	//ドラゴンの体力UIのポインタがNULLの場合
	if (pDragonLifeUI == NULL)
	{
		//ドラゴンの体力UIのメモリ確保
		pDragonLifeUI = new CDragonLifeUI;
	}
	//ドラゴンの体力UIのポインタがNULLじゃない場合
	if (pDragonLifeUI != NULL)
	{
		//ドラゴンの体力のUIの初期化処理関数呼び出し
		pDragonLifeUI->Init();
	}
	//ドラゴンの体力UIのポインタを返す
	return pDragonLifeUI;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CDragonLifeUI::Init(void)
{
	//初期全生成処理関数呼び出し
	InitCreateAll();
	//ドラゴンの取得
	CDragon * pDragon = CGameMode::GetDragon();
	//もしステージのポインタがNULLの場合
	if (pDragon != NULL)
	{
		//ドラゴンの体力の最大値の取得
		m_nMaxLife = pDragon->GetLife();
		//ドラゴンの体力の取得
		m_nLife = pDragon->GetLife();
	}
	//もしゲージのポインタがNULLじゃない場合
	if (m_pGauge != NULL)
	{
		//ゲージに参照したい値の最大値を設定
		m_pGauge->SetMaxValue(m_nMaxLife);
		//ゲージに参照したい値を設定する
		m_pGauge->SetValue(m_nLife);
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CDragonLifeUI::Uninit(void)
{
	//もしゲージのポインタがNULLじゃない場合
	if (m_pGauge != NULL)
	{
		//ゲージの終了処理関数呼び出し
		m_pGauge->Uninit();
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CDragonLifeUI::Update(void)
{
	//ドラゴンの取得
	CDragon * pDragon = CGameMode::GetDragon();
	//もしドラゴンのポインタがNULLの場合
	if (pDragon != NULL)
	{
		//ドラゴンの体力の取得
		m_nLife = pDragon->GetLife();
	}
	//もしゲージのポインタがNULLじゃない場合
	if (m_pGauge != NULL)
	{
		//ゲージに参照したい値を設定する
		m_pGauge->SetValue(m_nLife);
		//ゲージの更新処理関数呼び出し
		m_pGauge->Update();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CDragonLifeUI::Draw(void)
{
	//もしゲージのポインタがNULLじゃない場合
	if (m_pGauge != NULL)
	{
		//ゲージの描画処理関数呼び出し
		m_pGauge->Draw();
	}
}

//=============================================================================
// 初期全生成処理関数
//=============================================================================
void CDragonLifeUI::InitCreateAll(void)
{
	//ゲージの生成処理関数呼び出し
	m_pGauge = CGauge::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, 1000.0f, 0.0f), D3DXVECTOR3(1400.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	CGaugeFlame::Create(D3DXVECTOR3(1200.0f, 1000.0f, 0.0f), D3DXVECTOR3(1400.0f, 90.0f, 0.0f));
}
