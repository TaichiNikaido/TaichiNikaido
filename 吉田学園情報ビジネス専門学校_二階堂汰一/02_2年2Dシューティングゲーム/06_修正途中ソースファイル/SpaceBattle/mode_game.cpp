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
CEnemy * CGameMode::m_pEnemy = NULL;		//敵へのポインタ
CEnemyDragon * CGameMode::m_pDragon = NULL;	//ドラゴンへのポインタ
CWarning * CGameMode::m_pWarning = NULL;	//危険地帯へのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CGameMode::CGameMode()
{
	m_nFlameCount = 0;	//フレーム数
	m_bReplay = false;	//リプレイの真偽
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
	//全生成処理関数呼び出し
	CreateAll();
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
	//フレームカウントを進める
	m_nFlameCount++;
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGameMode::Draw(void)
{
}

//=============================================================================
// リプレイの真偽設定関数
//=============================================================================
void CGameMode::SetbReplay(bool bReplay)
{
	//リプレイの真偽を設定する
	m_bReplay = bReplay;
}

//=============================================================================
// 全生成処理関数
//=============================================================================
void CGameMode::CreateAll(void)
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
	m_pPlayer = CPlayer::Create(PLAYER_POS,PLAYER_SIZE);

	//CEnemyEyeNormal::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0.0f));

	//CEnemyEyeHard::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	//CEnemySpider::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	CEnemyFlower::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	//CWormhole::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	//m_pDragon = CEnemyDragon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f));
}