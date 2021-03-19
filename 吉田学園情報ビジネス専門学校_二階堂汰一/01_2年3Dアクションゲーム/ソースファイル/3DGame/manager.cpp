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
#include "renderer.h"
#include "manager.h"
#include "mode_title.h"
#include "mode_name.h"
#include "mode_tutorial.h"
#include "mode_game.h"
#include "mode_result.h"
#include "mode_ranking.h"
#include "scene.h"
#include "scene2d.h"
#include "sound.h"
#include "input.h"
#include "keyboard.h"
#include "joystick.h"
#include "fade.h"
#include "player.h"
#include "enemy_skeleton.h"
#include "weapon_sword.h"
#include "weapon_shield.h"
#include "enemy_dragon.h"
#include "object_wood_house.h"
#include "object_stone_house.h"
#include "object_fountain.h"
#include "object_fence.h"
#include "object_corpse.h"
#include "gauge.h"
#include "floor.h"
#include "button.h"
#include "particle_texture_sparks.h"

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
CManager::MODE  CManager::m_Mode = MODE_NONE;	//モード
bool CManager::m_bUseFade = false;				//フェードしてるか

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
		//レンダラーのメモリを確保
		m_pRenderer = new  CRenderer;
	}
	//レンダラーの初期化処理関数呼び出し
	m_pRenderer->Init(hWnd, TRUE);
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
	}
	//サウンドの初期化処理関数呼び出し
	m_pSound->Init(hWnd);
	//もしキーボードのポインタがNULLの場合
	if (m_pKeyboard == NULL)
	{
		//キーボードのメモリ確保
		m_pKeyboard = new CKeyboard;
	}
	//キーボードの初期化処理関数呼び出し
	m_pKeyboard->Init(hInsitance, hWnd);
	//もしジョイスティックのポインタがNULLの場合
	if (m_pJoystick == NULL)
	{
		//ジョイスティックのメモリ確保
		m_pJoystick = new CJoystick;
	}
	//ジョイスティックの初期化処理関数呼び出し
	m_pJoystick->Init(hInsitance, hWnd);
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
	//シーンの全破棄処理関数呼び出し
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
	//もしレンダラーのポインタがNULLじゃない場合
	if (m_pRenderer != NULL)
	{
		//レンダラーの更新処理関数呼び出し
		m_pRenderer->Update();
	}
	//もしキーボードのポインタがNULLじゃない場合
	if (m_pKeyboard != NULL)
	{
		//キーボードの更新処理関数呼び出し
		m_pKeyboard->Update();
	}
	//もしジョイスティックのポインタがNULLじゃない場合
	if (m_pJoystick != NULL)
	{
		//ジョイスティックの更新処理関数呼び出し
		m_pJoystick->Update();
	}
	//もしフェードされたら
	if (m_bUseFade == true)
	{
		//もしフェードのポインタがNULLじゃない場合
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
	//レンダラーの描画処理関数呼び出し
	m_pRenderer->Draw();
}

//=============================================================================
// フェード開始処理関数
//=============================================================================
void CManager::StartFade(MODE mode)
{
	//モードを設定する
	m_Mode = mode;
	//フェードをする
	m_bUseFade = true;
}

//=============================================================================
// フェード停止処理関数
//=============================================================================
void CManager::StopFade(void)
{
	//フェードをやめる
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
	//各モードの処理
	switch (m_Mode)
	{
	case MODE_TITLE:
		//タイトルモードの生成処理関数呼び出し
		CTitleMode::Create();
		break;
	case MODE_NAME:
		//名前入力モードの生成処理関数呼び出し
		CNameMode::Create();
		break;
	case MODE_TUTORIAL:
		//チュートリアルモードの生成処理関数呼び出し
		CTutorialMode::Create();
		break;
	case MODE_GAME:
		//ゲームモードの生成処理関数呼び出し
		m_pGameMode = CGameMode::Create();
		break;
	case MODE_RESULT:
		//リザルトモードの生成処理関数呼び出し
		m_pResultMode = CResultMode::Create();
		break;
	case MODE_RANKING:
		//ランキングモードの生成処理関数呼び出し
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
	//プレイヤーのモデル読み込み
	CPlayer::ModelLoad();
	//スケルトンのモデル読み込み
	CSkeleton::ModelLoad();
	//剣のモデル読み込み
	CSword::ModelLoad();
	//盾のモデル読み込み
	CShield::ModelLoad();
	//ドラゴンモデル読み込み
	//CDragon::ModelLoad();
	//木造の家モデル読み込み
	CWoodHouse::ModelLoad();
	//石造の家モデル読み込み
	CStoneHouse::ModelLoad();
	//噴水のモデル読み込み
	CFountain::ModelLoad();
	//フェンスのモデル読み込み
	CFence::ModelLoad();
	//屍のモデル読み込み
	CCorpse::ModelLoad();
	//ゲージのテクスチャ読み込み
	CGauge::TextureLoad();
	//地面のテクスチャ読み込み
	CFloor::TextureLoad();
	//ボタンのテクスチャ読み込み
	CButton::TextureLoad();
	//火の粉のテクスチャ読み込み
	//CSparksTexture::TextureLoad();
}

//=============================================================================
// 全読み込み破棄処理関数
//=============================================================================
void CManager::UnloadAll(void)
{
	//プレイヤーのモデル破棄
	CPlayer::ModelUnload();
	//スケルトンのモデル破棄
	CSkeleton::ModelUnload();
	//剣のモデル破棄
	CSword::ModelUnload();
	//盾のモデル破棄
	CShield::ModelUnload();
	//ドラゴンモデル破棄
	//CDragon::ModelUnload();
	//木造の家モデル破棄
	CWoodHouse::ModelUnload();
	//石造の家モデル破棄
	CStoneHouse::ModelUnload();
	//噴水のモデル破棄
	CFountain::ModelUnload();
	//フェンスのモデル破棄
	CFence::ModelUnload();
	//屍のモデル破棄
	CCorpse::ModelUnload();
	//ゲージのテクスチャ破棄
	CGauge::TextureUnload();
	//地面のテクスチャ破棄
	CFloor::TextureUnload();
	//ボタンのテクスチャ破棄
	CButton::TextureUnload();
	//火の粉のテクスチャ破棄
	//CSparksTexture::TextureUnload();
}

//=============================================================================
// 全破棄処理関数
//=============================================================================
void CManager::DeleteAll(void)
{
	//もしジョイスティックのポインタがNULLじゃない場合
	if (m_pJoystick != NULL)
	{
		//ジョイスティックの終了処理関数呼び出し
		m_pJoystick->Uninit();
		//ジョイスティックのメモリ破棄
		delete m_pJoystick;
		//ジョイスティックのポインタをNULLにする
		m_pJoystick = NULL;
	}
	//もしキーボードのポインタがNULLじゃない場合
	if (m_pKeyboard != NULL)
	{
		//キーボードの終了処理関数呼び出し
		m_pKeyboard->Uninit();
		//キーボードのメモリ破棄
		delete m_pKeyboard;
		//キーボードのポインタをNULLにする
		m_pKeyboard = NULL;
	}
	//もしサウンドのポインタがNULLじゃない場合
	if (m_pSound != NULL)
	{
		//サウンドの終了処理関数呼び出し
		m_pSound->Uninit();
		//サウンドのメモリ破棄
		delete m_pSound;
		//サウンドのポインタをNULLにする
		m_pSound = NULL;
	}
	//もしレンダラーのポインタがNULLじゃない場合
	if (m_pRenderer != NULL)
	{
		//レンダラーの終了処理関数呼び出し
		m_pRenderer->Uninit();
		//レンダラーのメモリ破棄
		delete m_pRenderer;
		//レンダラーのポインタをNULLにする
		m_pRenderer = NULL;
	}
	//もしフェードのポインタがNULLじゃない場合
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
