//=============================================================================
//
// ゲームモード [mode_game.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/sound.h"
#include "mode_game.h"
#include "Player/player.h"
#include "Enemy/enemy_eye_normal.h"
#include "Enemy/enemy_eye_hard.h"
#include "Enemy/enemy_spider.h"
#include "Enemy/enemy_flower.h"
#include "Enemy/enemy_dragon.h"
#include "Enemy/enemy_bomb_head.h"
#include "Enemy/enemy_bomb_body.h"
#include "2DPolygon/wormhole.h"
#include "Background/background_manager.h"
#include "UI/ui_score.h"
#include "UI/ui_bomb.h"
#include "UI/ui_life.h"
#include "2DPolygon/flame.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MINIMUM_FLAME_COUNT (0)	//フレームの数の最小値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CScoreUI * CGameMode::m_pScoreUI = NULL;				//スコアのUIへのポインタ
CBombUI * CGameMode::m_pBombUI = NULL;					//爆弾のUIへのポインタ
CLifeUI * CGameMode::m_pLifeUI = NULL;					//体力のUIへのポインタ
CPlayer * CGameMode::m_pPlayer = NULL;					//プレイヤーへのポインタ
CEnemyDragon * CGameMode::m_pDragon = NULL;				//ドラゴンへのポインタ
CWarning * CGameMode::m_pWarning = NULL;				//危険地帯へのポインタ
CBulletFireball * CGameMode::m_pBulletFireBall = NULL;	//火球のポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CGameMode::CGameMode()
{
	m_nFlameCount = MINIMUM_FLAME_COUNT;	//フレーム数
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
	//ゲームモードのポインタ
	CGameMode * pGameMode = NULL;
	//ゲームモードのポインタをNULLだった場合
	if (pGameMode == NULL)
	{
		//ゲームモードのメモリ確保
		pGameMode = new CGameMode;
		//ゲームモードのポインタをNULLじゃない場合
		if (pGameMode != NULL)
		{
			//ゲームモードの初期化関数呼び出し
			pGameMode->Init();
		}
	}
	//ゲームモードのポインタを返す
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
	//フレームの生成
	CFlame::Create(D3DXVECTOR3(200, SCREEN_HEIGHT / 2, 0.0f));
	CFlame::Create(D3DXVECTOR3(1720, SCREEN_HEIGHT / 2, 0.0f));
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
	//フレームカウントを進める
	m_nFlameCount++;

	if (m_nFlameCount == 50)
	{
		CEnemyEyeNormal::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(730.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(960.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1190.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1420.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 350)
	{
		CEnemyEyeHard::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f));
		CEnemyEyeHard::Create(D3DXVECTOR3(1420.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(600.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(900.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1200.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 750)
	{
		CEnemySpider::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 950)
	{
		CEnemyBombHead::Create(D3DXVECTOR3(600.0f, 200.0f, 0.0f));
	}
	if (m_nFlameCount == 1050)
	{
		CEnemyEyeNormal::Create(D3DXVECTOR3(730.0f, 0.0f, 0.0f));
		CEnemyFlower::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1190.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 1350)
	{
		CEnemyFlower::Create(D3DXVECTOR3(600.0f, 0.0f, 0.0f));
		CEnemyFlower::Create(D3DXVECTOR3(1320.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 1850)
	{
		CEnemySpider::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 2000)
	{
		CEnemyBombHead::Create(D3DXVECTOR3(600.0f, 200.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(730.0f, 0.0f, 0.0f));
		CEnemyFlower::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1190.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 2300)
	{
		CEnemyEyeNormal::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(730.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(960.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1190.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1420.0f, 0.0f, 0.0f));
		CEnemyFlower::Create(D3DXVECTOR3(600.0f, 0.0f, 0.0f));
		CEnemyFlower::Create(D3DXVECTOR3(1320.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 2800)
	{
		CWormhole::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4,0.0f));
	}
	if (m_nFlameCount == 3400)
	{
		CEnemyBombHead::Create(D3DXVECTOR3(600.0f, 200.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(730.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(960.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1190.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1420.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 3900)
	{
		CEnemyEyeHard::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(730.0f, 0.0f, 0.0f));
		CEnemyFlower::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1190.0f, 0.0f, 0.0f));
		CEnemyEyeHard::Create(D3DXVECTOR3(1420.0f, 0.0f, 0.0f));
	}
	if (m_nFlameCount == 4300)
	{
		CEnemyEyeNormal::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(730.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(960.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1190.0f, 0.0f, 0.0f));
		CEnemyEyeNormal::Create(D3DXVECTOR3(1420.0f, 0.0f, 0.0f));
	}
}