//=============================================================================
//
// マネージャー [manager.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "mode_title.h"
#include "mode_name.h"
#include "mode_tutorial.h"
#include "mode_game.h"
#include "mode_result.h"
#include "mode_ranking.h"
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"
#include "keyboard.h"
#include "joystick.h"
#include "player.h"
#include "enemy_eye_normal.h"
#include "enemy_eye_hard.h"
#include "enemy_spider.h"
#include "enemy_flower.h"
#include "enemy_dragon.h"
#include "enemy_bomb_head.h"
#include "enemy_bomb_body.h"
#include "bullet_player.h"
#include "bullet_enemy.h"
#include "bullet_fireball.h"
#include "bullet_n-way.h"
#include "bullet_direction.h"
#include "bullet_homing.h"
#include "bullet_flower.h"
#include "bullet_bomb.h"
#include "item_bomb.h"
#include "item_life.h"
#include "item_levelup.h"
#include "ui_number_texture.h"
#include "ui_bomb_texture.h"
#include "ui_life_texture.h"
#include "background_under_layer.h"
#include "background_middle_layer.h"
#include "background_upper_layer.h"
#include "background_title.h"
#include "background_name.h"
#include "background_tutorial.h"
#include "background_result.h"
#include "background_ranking.h"
#include "fade.h"
#include "effect.h"
#include "button.h"
#include "name.h"
#include "explosion_bomb.h"
#include "explosion_death.h"
#include "explosion_fireball.h"
#include "wormhole.h"
#include "warning.h"
#include "text.h"
#include "flame.h"
#include "gameclear_logo.h"
#include "continue_logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CRenderer * CManager::m_pRenderer = NULL;		//レンダラーへのポインタ
CSound * CManager::m_pSound = NULL;				//サウンドへのポインタ
CKeyboard * CManager::m_pKeyboard = NULL;		//キーボードへのポインタ
CJoystick * CManager::m_pJoystick = NULL;		//マネージャーへのポインタ
CGameMode * CManager::m_pGameMode = NULL;		//ゲームモードへのポインタ
CResultMode * CManager::m_pResultMode = NULL;	//リザルトモードへのポインタ
CRankingMode * CManager::m_pRankingMode = NULL;	//リザルトモードへのポインタ
CFade * CManager::m_pFade = NULL;				//フェードへのポインタ
CText * CManager::m_pText = NULL;				//テキストへのポインタ
CManager::MODE  CManager::m_Mode = MODE_NONE;	//モード
bool CManager::m_bUseFade = false;				//フェードの真偽

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow)
{
	//レンダラーの生成
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new  CRenderer;
	}
	//レンダラーの初期化処理
	m_pRenderer->Init(hWnd, TRUE);
	if (m_pFade == NULL)
	{
		//フェードの生成処理関数呼び出し
		m_pFade = CFade::Create(m_Mode);
	}
	//サウンドの生成
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}
	//サウンドの初期化
	m_pSound->Init(hWnd);
	//キーボードの生成
	if (m_pKeyboard == NULL)
	{
		m_pKeyboard = new CKeyboard;
	}
	//キーボードの初期化
	m_pKeyboard->Init(hInsitance, hWnd);
	//ジョイスティックの生成
	if (m_pJoystick == NULL)
	{
		m_pJoystick = new CJoystick;
	}
	//ジョイスティックの初期化
	m_pJoystick->Init(hInsitance, hWnd);
	//テキストの生成
	m_pText = CText::Create();
	//全読み込み関数呼び出し
	LoadAll();
	//モードの設定
	SetMode(MODE_TITLE);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();
	//サウンドの停止
	m_pSound->StopSound();
	//全破棄関数呼び出し
	DeleteAll();
	//全読み込み破棄関数呼び出し
	UnloadAll();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CManager::Update(void)
{
	//描画の更新
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
	//キーボードの更新
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}
	//キーボードの更新
	if (m_pJoystick != NULL)
	{
		m_pJoystick->Update();
	}
	//フェード更新
	if (m_bUseFade == true)
	{
		if (m_pFade != NULL)
		{
			m_pFade->Update();
		}
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CManager::Draw(void)
{
	//レンダラーの描画
	m_pRenderer->Draw();
}

//=============================================================================
// フェード開始処理関数
//=============================================================================
void CManager::StartFade(MODE mode)
{
	m_Mode = mode;
	m_bUseFade = true;
	CText::IsDrawText(false);
}

//=============================================================================
// フェード停止処理関数
//=============================================================================
void CManager::StopFade(void)
{
	CText::IsDrawText(true);
	m_bUseFade = false;
}

//=============================================================================
// モード設定関数
//=============================================================================
void CManager::SetMode(MODE Mode)
{
	CScene::ReleaseAll();
	//サウンドを停止する
	m_pSound->StopSound();
	//モードを設定する
	m_Mode = Mode;
	switch (m_Mode)
	{
	case MODE_TITLE:
		CTitleMode::Create();
		break;
	case MODE_NAME:
		CNameMode::Create();
		break;
	case MODE_TUTORIAL:
		CTutorialMode::Create();
		break;
	case MODE_GAME:
		m_pGameMode = CGameMode::Create();
		break;
	case MODE_RESULT:
		m_pResultMode = CResultMode::Create();
		break;
	case MODE_RANKING:
		m_pRankingMode = CRankingMode::Create();
	default:
		break;
	}
}

//=============================================================================
// 全読み込み処理関数
//=============================================================================
void CManager::LoadAll(void)
{
	//プレイヤーのテクスチャ読み込み
	CPlayer::TextureLoad();
	//目玉(ノーマル)のテクスチャ読み込み
	CEnemyEyeNormal::TextureLoad();
	//目玉(ハード)のテクスチャ読み込み
	CEnemyEyeHard::TextureLoad();
	//蜘蛛のテクスチャ読み込み
	CEnemySpider::TextureLoad();
	//花のテクスチャ読み込み
	CEnemyFlower::TextureLoad();
	//ドラゴンのテクスチャ読み込み
	CEnemyDragon::TextureLoad();
	//爆弾敵の頭テクスチャ読み込み
	CEnemyBombHead::TextureLoad();
	//爆弾敵の体テクスチャ読み込み
	CEnemyBombBody::TextureLoad();
	//プレイヤーの弾のテクスチャ読み込み
	CBulletPlayer::TextureLoad();
	//火球のテクスチャ読み込み
	CBulletFireball::TextureLoad();
	//n-wayのテクスチャ読み込み
	CBulletN_Way::TextureLoad();
	//方向弾のテクスチャ読み込み
	CBulletDirection::TextureLoad();
	//ホーミング弾のテクスチャ
	CBulletHoming::TextureLoad();
	//花弾のテクスチャ
	CBulletFlower::TextureLoad();
	//爆弾のテクスチャ読み込み
	CBulletBomb::TextureLoad();
	//爆弾付与アイテムテクスチャ読み込み
	CItemBomb::TextureLoad();
	//体力付与アイテムテクスチャ読み込み
	CItemLife::TextureLoad();
	//レベルアップアイテムテクスチャ読み込み
	CItemLevelUP::TextureLoad();
	//UI用数字テクスチャ読み込み
	CUINumberTexture::TextureLoad();
	//UI用爆弾テクスチャ読み込み
	CUIBombTexture::TextureLoad();
	//UI用体力テクスチャ読み込み
	CUILifeTexture::TextureLoad();
	//下層背景テクスチャ読み込み
	CBackgroundUnderLayer::TextureLoad();
	//中層背景テクスチャ読み込み
	CBackgroundMiddleLayer::TextureLoad();
	//上層背景テクスチャ読み込み
	CBackgroundUpperLayer::TextureLoad();
	//タイトル背景テクスチャ読み込み
	CBackgroundTitle::TextureLoad();
	//名前入力背景テクスチャ読み込み
	CBackgroundName::TextureLoad();
	//チュートリアル背景テクスチャ読み込み
	CBackgroundTutorial::TextureLoad();
	//リザルト背景テクスチャ読み込み
	CBackgroundResult::TextureLoad();
	//ランキング背景テクスチャ読み込み
	CBackgroundRanking::TextureLoad();
	//エフェクトテクスチャ読み込み
	CEffect::TextureLoad();
	//ボタンテクスチャ読み込み
	CButton::TextureLoad();
	//名前テクスチャ読み込み
	CName::TextureLoad();
	//爆弾爆発テクスチャ読み込み
	CExplosionBomb::TextureLoad();
	//死亡時爆発テクスチャ読み込み
	CExplosionDeath::TextureLoad();
	//火球爆発テクスチャ読み込み
	CExplosionFireball::TextureLoad();
	//ワームホールテクスチャ読み込み
	CWormhole::TextureLoad();
	//ワーニングテクスチャ読み込み
	CWarning::TextureLoad();
	//フレームテクスチャ読み込み
	CFlame::TextureLoad();
	//ゲームクリアロゴのテクスチャ読み込み
	CGameClearLogo::TextureLoad();
	//コンティニューロゴのテクスチャ読み込み
	CContinueLogo::TextureLoad();
}

//=============================================================================
// 全読み込み破棄処理関数
//=============================================================================
void CManager::UnloadAll(void)
{
	//プレイヤーのテクスチャ破棄
	CPlayer::TextureUnload();
	//目玉(ノーマル)のテクスチャ破棄
	CEnemyEyeNormal::TextureUnload();
	//目玉(ハード)のテクスチャ破棄
	CEnemyEyeHard::TextureUnload();
	//蜘蛛のテクスチャ破棄
	CEnemySpider::TextureUnload();
	//花のテクスチャ破棄
	CEnemyFlower::TextureUnload();
	//ドラゴンのテクスチャ破棄
	CEnemyDragon::TextureUnload();
	//爆弾敵の頭テクスチャ破棄
	CEnemyBombHead::TextureUnload();
	//爆弾敵の体テクスチャ読み込み
	CEnemyBombBody::TextureUnload();
	//プレイヤーの弾のテクスチャ破棄
	CBulletPlayer::TextureUnload();
	//火球のテクスチャ破棄
	CBulletFireball::TextureUnload();
	//n-wayのテクスチャ破棄
	CBulletN_Way::TextureUnload();
	//方向弾のテクスチャ破棄
	CBulletDirection::TextureUnload();
	//ホーミング弾のテクスチャ破棄
	CBulletHoming::TextureUnload();
	//花弾のテクスチャ破棄
	CBulletFlower::TextureUnload();
	//爆弾のテクスチャ
	CBulletBomb::TextureUnload();
	//爆弾付与アイテムテクスチャ破棄
	CItemBomb::TextureUnload();
	//体力付与アイテムテクスチャ破棄
	CItemLife::TextureUnload();
	//レベルアップアイテムテクスチャ破棄
	CItemLevelUP::TextureUnload();
	//UI用数字テクスチャ破棄
	CUINumberTexture::TextureUnload();
	//UI用爆弾テクスチャ破棄
	CUIBombTexture::TextureUnload();
	//UI用ライフテクスチャ破棄
	CUILifeTexture::TextureUnload();
	//下層背景テクスチャ破棄
	CBackgroundUnderLayer::TextureUnload();
	//中層背景テクスチャ破棄
	CBackgroundMiddleLayer::TextureUnload();
	//上層背景テクスチャ破棄
	CBackgroundUpperLayer::TextureUnload();
	//タイトル背景テクスチャ破棄
	CBackgroundTitle::TextureUnload();
	//名前入力背景テクスチャ破棄
	CBackgroundName::TextureUnload();
	//チュートリアル背景テクスチャ破棄
	CBackgroundTutorial::TextureUnload();
	//リザルト背景テクスチャ破棄
	CBackgroundResult::TextureUnload();
	//ランキング背景テクスチャ破棄
	CBackgroundRanking::TextureUnload();
	//エフェクトテクスチャ破棄
	CEffect::TextureUnload();
	//ボタンテクスチャ破棄
	CButton::TextureUnload();
	//名前テクスチャ破棄
	CName::TextureUnload();
	//爆弾爆発テクスチャ破棄
	CExplosionBomb::TextureUnload();
	//死亡時爆発テクスチャ破棄
	CExplosionDeath::TextureUnload();
	//火球爆発テクスチャ破棄
	CExplosionFireball::TextureUnload();
	//ワームホールテクスチャ破棄
	CWormhole::TextureUnload();
	//ワーニングテクスチャ破棄
	CWarning::TextureUnload();
	//フレームテクスチャ破棄
	CFlame::TextureUnload();
	//ゲームクリアロゴのテクスチャ破棄
	CGameClearLogo::TextureUnload();
	//コンティニューロゴのテクスチャ破棄
	CContinueLogo::TextureUnload();
}

//=============================================================================
// 全破棄処理関数
//=============================================================================
void CManager::DeleteAll(void)
{
	//ジョイスティックの破棄
	if (m_pJoystick != NULL)
	{
		m_pJoystick->Uninit();
		delete m_pJoystick;
		m_pJoystick = NULL;
	}
	//キーボードの破棄
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}
	//サウンドの破棄
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	//レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	//フェードの破棄
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}
}
