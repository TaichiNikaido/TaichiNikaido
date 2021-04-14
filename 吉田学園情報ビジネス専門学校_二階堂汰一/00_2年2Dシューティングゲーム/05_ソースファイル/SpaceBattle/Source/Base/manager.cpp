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
#include "Mode/mode_title.h"
#include "Mode/mode_name.h"
#include "Mode/mode_tutorial.h"
#include "Mode/mode_game.h"
#include "Mode/mode_result.h"
#include "Mode/mode_ranking.h"
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "Player/player.h"
#include "Enemy/enemy_eye_normal.h"
#include "Enemy/enemy_eye_hard.h"
#include "Enemy/enemy_spider.h"
#include "Enemy/enemy_flower.h"
#include "Enemy/enemy_dragon.h"
#include "Enemy/enemy_bomb_head.h"
#include "Enemy/enemy_bomb_body.h"
#include "Bullet/bullet_player.h"
#include "Bullet/bullet_enemy.h"
#include "Bullet/bullet_fireball.h"
#include "Bullet/bullet_n-way.h"
#include "Bullet/bullet_direction.h"
#include "Bullet/bullet_homing.h"
#include "Bullet/bullet_flower.h"
#include "Bullet/bullet_bomb.h"
#include "Item/item_bomb.h"
#include "Item/item_life.h"
#include "Item/item_levelup.h"
#include "UI/ui_number_texture.h"
#include "UI/ui_bomb_texture.h"
#include "UI/ui_life_texture.h"
#include "Background/background_under_layer.h"
#include "Background/background_middle_layer.h"
#include "Background/background_upper_layer.h"
#include "Background/background_title.h"
#include "Background/background_name.h"
#include "Background/background_tutorial.h"
#include "Background/background_result.h"
#include "Background/background_ranking.h"
#include "fade.h"
#include "Effect/effect.h"
#include "2DPolygon/button.h"
#include "System/name.h"
#include "Effect/explosion_bomb.h"
#include "Effect/explosion_death.h"
#include "Effect/explosion_fireball.h"
#include "2DPolygon/wormhole.h"
#include "2DPolygon/warning.h"
#include "text.h"
#include "2DPolygon/flame.h"
#include "2DPolygon/gameclear_logo.h"
#include "2DPolygon/continue_logo.h"

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
bool CManager::m_bUseFade = false;				//フェードの使用状態

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
	//もしレンダラーのポインタがNULLの場合
	if (m_pRenderer == NULL)
	{
		//レンダラーのメモリ確保
		m_pRenderer = new  CRenderer;
		//もしレンダラーのポインタがNULLではない場合
		if (m_pRenderer != NULL)
		{
			//レンダラーの初期化処理関数呼び出し
			m_pRenderer->Init(hWnd, TRUE);
		}
	}
	//もしフェードのポインタがNULLの場合
	if (m_pFade == NULL)
	{
		//フェードの生成処理関数呼び出し
		m_pFade = CFade::Create(m_Mode);
	}
	//もしサウンドのポインタがNULLの場合
	if (m_pSound == NULL)
	{
		//サウンドのメモリ確保
		m_pSound = new CSound;
		//もしサウンドのポインタがNULLではない場合
		if (m_pSound != NULL)
		{
			//サウンドの初期化処理関数呼び出し
			m_pSound->Init(hWnd);
		}
	}
	//もしキーボードのポインタがNULLの場合
	if (m_pKeyboard == NULL)
	{
		//キーボードのメモリ確保
		m_pKeyboard = new CKeyboard;
		//もしキーボードのポインタがNULLではない場合
		if (m_pKeyboard != NULL)
		{
			//キーボードの初期化処理関数呼び出し
			m_pKeyboard->Init(hInsitance, hWnd);
		}
	}
	//もしジョイスティックのポインタがNULLの場合
	if (m_pJoystick == NULL)
	{
		//ジョイスティックのメモリ確保
		m_pJoystick = new CJoystick;
		//もしジョイスティックのポインタがNULLではない場合
		if (m_pJoystick != NULL)
		{
			//ジョイスティックの初期化処理関数呼び出し
			m_pJoystick->Init(hInsitance, hWnd);
		}
	}
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
	//シーンの全生成処理関数呼び出し
	CScene::ReleaseAll();
	//もしサウンドのポインタがNULLではない場合
	if (m_pSound != NULL)
	{
		//サウンドの停止
		m_pSound->StopSound();
	}
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
	//もしレンダラーのポインタがNULLではない場合
	if (m_pRenderer != NULL)
	{
		//レンダラーの更新処理関数呼び出し
		m_pRenderer->Update();
	}
	//もしキーボードのポインタはNULLではない場合
	if (m_pKeyboard != NULL)
	{
		//キーボードの更新処理関数呼び出し
		m_pKeyboard->Update();
	}
	//もしジョイスティックのポインタがNULLではない場合
	if (m_pJoystick != NULL)
	{
		//ジョイスティックの更新処理関数呼び出し
		m_pJoystick->Update();
	}
	//もしフェードの使用状態がtrueの場合
	if (m_bUseFade == true)
	{
		//もしフェードのポインタがNULLではない場合
		if (m_pFade != NULL)
		{
			//フェードの更新処理関数呼び出し
			m_pFade->Update();
		}
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CManager::Draw(void)
{
	//もしレンダラーのポインタがNULLではない場合
	if (m_pRenderer != NULL)
	{
		//レンダラーの描画処理関数呼び出し
		m_pRenderer->Draw();
	}
}

//=============================================================================
// フェード開始処理関数
//=============================================================================
void CManager::StartFade(MODE mode)
{
	//モードを設定する
	m_Mode = mode;
	//フェードの使用状態をtrueにする
	m_bUseFade = true;
	//テキストの描画状態をfalseにする
	CText::IsDrawText(false);
}

//=============================================================================
// フェード停止処理関数
//=============================================================================
void CManager::StopFade(void)
{
	//テキストの描画状態をtrueにする
	CText::IsDrawText(true);
	//フェードの使用状態をfalseにする
	m_bUseFade = false;
}

//=============================================================================
// モード設定関数
//=============================================================================
void CManager::SetMode(MODE Mode)
{
	//シーンの全破棄処理関数呼び出し
	CScene::ReleaseAll();
	//サウンドを停止する
	m_pSound->StopSound();
	//モードを設定する
	m_Mode = Mode;
	switch (m_Mode)
	{
	case MODE_TITLE:
		//タイトルモードの生成
		CTitleMode::Create();
		break;
	case MODE_NAME:
		//名前入力モードの生成
		CNameMode::Create();
		break;
	case MODE_TUTORIAL:
		//チュートリアルモードの生成
		CTutorialMode::Create();
		break;
	case MODE_GAME:
		//もしゲームモードのポインタがNULLの場合
		if (m_pGameMode == NULL)
		{
			//ゲームモードの生成
			m_pGameMode = CGameMode::Create();
		}
		break;
	case MODE_RESULT:
		//もしリザルトモードのポインタがNULLの場合
		if (m_pResultMode == NULL)
		{
			//リザルトモードの生成
			m_pResultMode = CResultMode::Create();
		}
		break;
	case MODE_RANKING:
		//もしランキングモードのポインタがNULLの場合
		if (m_pRankingMode == NULL)
		{
			//ランキングモードの生成
			m_pRankingMode = CRankingMode::Create();
		}
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
	//もしジョイスティックのポインタがNULLではない場合
	if (m_pJoystick != NULL)
	{
		//ジョイスティックの終了処理関数呼び出し
		m_pJoystick->Uninit();
		//ジョイスティックのメモリ破棄
		delete m_pJoystick;
		//ジョイスティックのポインタをNULLにする
		m_pJoystick = NULL;
	}
	//もしキーボードのポインタがNULLではない場合
	if (m_pKeyboard != NULL)
	{
		//キーボードの終了処理関数呼び出し
		m_pKeyboard->Uninit();
		//キーボードのメモリ破棄
		delete m_pKeyboard;
		//キーボードのポインタをNULLにする
		m_pKeyboard = NULL;
	}
	//もしサウンドのポインタがNULLではない場合
	if (m_pSound != NULL)
	{
		//サウンドの終了処理関数呼ぼだし
		m_pSound->Uninit();
		//サウンドのメモリ破棄
		delete m_pSound;
		//サウンドのポインタをNULLにする
		m_pSound = NULL;
	}
	//もしレンダラーのポインタがNULLではない場合
	if (m_pRenderer != NULL)
	{
		//レンダラーの終了処理関数呼び出し
		m_pRenderer->Uninit();
		//レンダラーのメモリ破棄
		delete m_pRenderer;
		//レンダラーのポインタをNULLにする
		m_pRenderer = NULL;
	}
	//もしフェードのポインタがNULLではない場合
	if (m_pFade != NULL)
	{
		//フェードの終了処理関数呼び出し
		m_pFade->Uninit();
		//フェードのメモリ破棄
		delete m_pFade;
		//フェードのポインタをNULLにする
		m_pFade = NULL;
	}
}
