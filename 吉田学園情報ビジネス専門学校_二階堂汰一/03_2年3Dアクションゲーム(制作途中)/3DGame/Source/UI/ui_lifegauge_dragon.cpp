//=============================================================================
//
// ドラゴンの体力UI [ui_life_dragon.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Mode/mode_game.h"
#include "ui_life_gauge_dragon.h"
#include "Polygon2d/gauge.h"
#include "Character/enemy_dragon.h"
#include "Character/player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE (D3DXVECTOR3(800.0f,15.0f,0.0f))
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2 - (SIZE.x / 2),SCREEN_HEIGHT / 6,0.0f))
#define COLOR (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CDragonLifeGaugeUI::CDragonLifeGaugeUI()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CDragonLifeGaugeUI::~CDragonLifeGaugeUI()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CDragonLifeGaugeUI * CDragonLifeGaugeUI::Create()
{
	//ドラゴンの体力UIポインタ
	CDragonLifeGaugeUI * pDragonLifeUI = nullptr;
	//ドラゴンの体力UIポインタがnullptrの場合
	if (pDragonLifeUI == nullptr)
	{
		//ドラゴンの体力UIのメモリ確保
		pDragonLifeUI = new CDragonLifeGaugeUI;
		//ドラゴンの体力UIのポインタがNULLではない場合
		if (pDragonLifeUI != nullptr)
		{
			//ドラゴンの体力UIの位置を設定する
			pDragonLifeUI->SetPosition(POSITION);
			//ドラゴンの体力UIのサイズを設定する
			pDragonLifeUI->SetSize(SIZE);
			//ドラゴンの体力UIの色を設定する
			pDragonLifeUI->SetColor(COLOR);
			//ドラゴンの体力UIの初期化処理関数呼び出し
			pDragonLifeUI->Init();
		}
	}
	//ドラゴンの体力UIのポインタを返す
	return pDragonLifeUI;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CDragonLifeGaugeUI::Init(void)
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	D3DXVECTOR3 Size = GetSize();
	D3DXCOLOR Color = GetColor();
	//ドラゴンを取得する
	CDragon * pDragpn = CGameMode::GetDragon();
	//もしドラゴンのポインタがnullptrじゃない場合
	if (pDragpn != nullptr)
	{
		//ドラゴンの体力を取得
		int nLife = pDragpn->GetLife();
		//体力の最大値を設定
		SetMaxLife(nLife);
		//体力を設定
		SetLife(nLife);
	}
	//ゲージの生成処理関数呼び出し
	SetGauge(CGauge::Create(Position, Size, Color));
	//ライフの初期化処理関数呼び出し
	CLifeGaugeUI::Init();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CDragonLifeGaugeUI::Uninit(void)
{
	//ライフのUIの終了処理関数呼び出し
	CLifeGaugeUI::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CDragonLifeGaugeUI::Update(void)
{
	//体力UIの更新処理関数呼び出し
	CLifeGaugeUI::Update();
	//ドラゴンを取得する
	CDragon * pDragon = CGameMode::GetDragon();
	//もしドラゴンのポインタがnullptrじゃない場合
	if (pDragon != nullptr)
	{
		//ドラゴンの体力を取得
		int nLife = pDragon->GetLife();
		//体力を設定
		SetLife(nLife);
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CDragonLifeGaugeUI::Draw(void)
{
	//ライフゲージUIの描画処理関数呼び出し
	CLifeGaugeUI::Draw();
}