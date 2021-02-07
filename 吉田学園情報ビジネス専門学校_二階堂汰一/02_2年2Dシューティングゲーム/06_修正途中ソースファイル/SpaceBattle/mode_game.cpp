//=============================================================================
//
// ゲームモード [mode_game.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "mode_game.h"
#include "player.h"
#include "enemy_eye_normal.h"
#include "enemy_eye_hard.h"
#include "enemy_spider.h"
#include "enemy_flower.h"
#include "enemy_dragon.h"
#include "enemy_bomb_head.h"
#include "enemy_bomb_body.h"
#include "wormhole.h"
#include "background_manager.h"
#include "ui_score.h"
#include "ui_bomb.h"
#include "ui_life.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CScoreUI * CGameMode::m_pScoreUI = NULL;	//スコアのUIへのポインタ
CBombUI * CGameMode::m_pBombUI = NULL;		//爆弾のUIへのポインタ
CLifeUI * CGameMode::m_pLifeUI = NULL;		//体力のUIへのポインタ
CPlayer * CGameMode::m_pPlayer = NULL;		//プレイヤーへのポインタ
CEnemyDragon * CGameMode::m_pDragon = NULL;	//ドラゴンへのポインタ
CWarning * CGameMode::m_pWarning = NULL;	//危険地帯へのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CGameMode::CGameMode()
{
	m_nFlameCount = 0;	//フレーム数
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameMode::~CGameMode()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CGameMode * CGameMode::Create()
{
	CGameMode * pGameMode;
	pGameMode = new CGameMode;
	pGameMode->Init();
	return pGameMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CGameMode::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//BGMの再生
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);
	//全初期生成処理関数呼び出し
	InitCreateAll();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CGameMode::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CGameMode::Update(void)
{
	//全更新生成処理関数呼び出し
	UpdateCreateAll();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGameMode::Draw(void)
{
}

//=============================================================================
// 全初期生成処理関数
//=============================================================================
void CGameMode::InitCreateAll(void)
{
	//背景管理の生成
	CBackgroundManager::Create();
	//スコアのUIの生成
	m_pScoreUI = CScoreUI::Create();
	//体力のUIの生成
	m_pLifeUI = CLifeUI::Create();
	//爆弾のUIの生成
	m_pBombUI = CBombUI::Create();
	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(PLAYER_POS, PLAYER_SIZE);
}

//=============================================================================
// 全更新生成処理関数
//=============================================================================
void CGameMode::UpdateCreateAll(void)
{
	if (m_nFlameCount == 50)
	{
		for (int nCount = 0; nCount < 4; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 1.5f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 350)
	{
		for (int nCount = 0; nCount < 5; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 1.5f + 150.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 750)
	{
		CEnemySpider::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 950)
	{
		CEnemyBombHead::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}
	if (m_nFlameCount == 1050)
	{
		for (int nCount = 0; nCount < 2; nCount++)
		{
			CEnemyEyeHard::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 1.5f + 100.0f + 400.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 1350)
	{
		for (int nCount = 0; nCount < 4; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 1550)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 1900)
	{
		for (int nCount = 0; nCount < 3; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 700.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
		CEnemyFlower::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 2.0f + FIELD_WIDTH / 2, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 2200)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
		CEnemyFlower::Create(D3DXVECTOR3(FIELD_WIDTH_MIN* 2.0f + 700, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 2500)
	{
		CEnemySpider::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 2700)
	{
		CEnemyBombHead::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}
	if (m_nFlameCount == 2900)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 3200)
	{
		for (int nCount = 0; nCount < 3; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN* 2.0f + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
		CEnemyFlower::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 2.0f + FIELD_WIDTH / 4, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 3450)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 3700)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
		for (int nCount = 0; nCount < 2; nCount++)
		{
			CEnemyEyeHard::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 1.5f + 100.0f + 400.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 4200)
	{
		CWormhole::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, FIELD_HEIGHT / 4, 0.0f));
	}
	if (m_nFlameCount == 4600)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 4800)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 5000)
	{
		CEnemyBombHead::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}
	if (m_nFlameCount % 10 == 0 && m_nFlameCount > 5008 && m_nFlameCount < 5100)
	{
	}
	if (m_nFlameCount == 5200)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 5500)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	if (m_nFlameCount == 6000)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemyEyeNormal::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f));
		}
	}
	//フレームカウントを進める
	m_nFlameCount++;
}