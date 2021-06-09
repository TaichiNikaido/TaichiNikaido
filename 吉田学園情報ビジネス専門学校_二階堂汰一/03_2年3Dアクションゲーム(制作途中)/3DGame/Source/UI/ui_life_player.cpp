//=============================================================================
//
// プレイヤーの体力UI [ui_life_player.cpp]
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
#include "ui_life_player.h"
#include "Polygon2d/heart_icon.h"
#include "Character/player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define HEART_LIFE (4)		//1つのUIの体力
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 12 + 50.0f * nCount, SCREEN_HEIGHT / 8, 0.0f)	//位置

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayerLifeUI::CPlayerLifeUI(int nPriority) : CScene(nPriority)
{
	memset(m_pHeartIcon, NULL, sizeof(m_pHeartIcon));		//ハートアイコンのポインタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayerLifeUI::~CPlayerLifeUI()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CPlayerLifeUI * CPlayerLifeUI::Create()
{
	//プレイヤーの体力UIポインタ
	CPlayerLifeUI * pPlayerLifeUI = nullptr;
	//プレイヤーの体力UIポインタがnullptrの場合
	if (pPlayerLifeUI == nullptr)
	{
		//プレイヤーの体力UIのメモリ確保
		pPlayerLifeUI = new CPlayerLifeUI;
		//プレイヤーの体力UIのポインタがNULLではない場合
		if (pPlayerLifeUI != nullptr)
		{
			//プレイヤーの体力UIの初期化処理関数呼び出し
			pPlayerLifeUI->Init();
		}
	}
	//プレイヤーの体力UIのポインタを返す
	return pPlayerLifeUI;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPlayerLifeUI::Init(void)
{
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしプレイヤーのポインタがnullptrではない場合
	if (pPlayer != nullptr)
	{
		//プレイヤーの体力を取得
		int nPlayerLife = pPlayer->GetLife();
		//ハートアイコンの生成数を求める
		m_nHeartIconCreateCount = nPlayerLife / HEART_LIFE;
		//ハートアイコンの生成数分回す
		for (int nCount = 0; nCount < m_nHeartIconCreateCount; nCount++)
		{
			//ハートアイコンの生成
			m_pHeartIcon[nCount] = CHeartIcon::Create(POSITION));
			//ハートアイコンのパターンアニメを設定する(絶対に1にする)
			m_pHeartIcon[nCount]->SetPatternAnime(4);
		}
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPlayerLifeUI::Uninit(void)
{
	//破棄処理関数呼び出し
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPlayerLifeUI::Update(void)
{
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしプレイヤーのポインタがnullptrではない場合
	if (pPlayer != nullptr)
	{
		//プレイヤーの体力を取得
		int nPlayerLife = pPlayer->GetLife();
		//現在の完全に表示するハートの個数を求める
		int nHeart = nPlayerLife / HEART_LIFE;
		//残りの表示するハートのライフ
		int nHeartLife = nPlayerLife % HEART_LIFE;
		//生成数分回す
		for (int nCount = 0; nCount < m_nHeartIconCreateCount; nCount++)
		{
			//ハートアイコンの色を黒にする
			m_pHeartIcon[nCount]->SetPatternAnime(0);
		}
		//ハートアイコンの生成数分回す
		for (int nCount = 0; nCount < nHeart; nCount++)
		{
			//ハートアイコンの色を赤にする
			m_pHeartIcon[nCount]->SetPatternAnime(4);
		}
		//もし商の値が生成数より小さい場合
		if (nHeart < m_nHeartIconCreateCount)
		{
			//もし余りの値が0ではない場合
			if (nHeartLife > 0)
			{
				//余りの所だけ赤くする
				m_pHeartIcon[nHeart]->SetPatternAnime(nHeartLife);
			}
		}
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPlayerLifeUI::Draw(void)
{
}
