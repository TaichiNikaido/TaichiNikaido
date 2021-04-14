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
#include "weapon_sword.h"
#include "weapon_shield.h"
#include "enemy_dragon.h"
#include "floor.h"
#include "button_any.h"
#include "button_start.h"
#include "button_tutorial.h"
#include "button_ranking.h"
#include "button_exit.h"
#include "button_quit_game.h"
#include "button_controller_guid.h"
#include "button_back_to_title.h"
#include "title_logo.h"
#include "letter.h"
#include "skybox.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CRenderer * CManager::m_pRenderer = NULL;			//レンダラーのポインタ
CSound * CManager::m_pSound = NULL;					//サウンドのポインタ
CKeyboard * CManager::m_pKeyboard = NULL;			//キーボードのポインタ
CJoystick * CManager::m_pJoystick = NULL;			//マネージャーのポインタ
CTutorialMode * CManager::m_pTutorialMode = NULL;	//チュートリアルモードのポインタ
CGameMode * CManager::m_pGameMode = NULL;			//ゲームモードのポインタ
CResultMode * CManager::m_pResultMode = NULL;		//リザルトモードのポインタ
CRankingMode * CManager::m_pRankingMode = NULL;		//ランキングモードのポインタ
CFade * CManager::m_pFade = NULL;					//フェードへのポインタ
CManager::MODE  CManager::m_Mode = MODE_NONE;		//モード
bool CManager::m_bUseFade = false;					//フェードの使用状態

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
	//全読み込み関数呼び出し
	LoadAll();
	//モードの設定
	SetMode(MODE_GAME);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CManager::Uninit(void)
{
	//シーンの全破棄処理関数呼び出し
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
	//もしキーボードのポインタがNULLではない場合
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
	//もしフェードされたら
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
		m_pTutorialMode = CTutorialMode::Create();
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
	//剣のモデル読み込み
	CSword::ModelLoad();
	//盾のモデル読み込み
	CShield::ModelLoad();
	//ドラゴンモデル読み込み
	CDragon::ModelLoad();
	//地面のテクスチャ読み込み
	CFloor::TextureLoad();
	//何らかのボタンのテクスチャ読み込み
	CAnyButton::TextureLoad();
	//スタートボタンのテクスチャ読み込み
	CStartButton::TextureLoad();
	//チュートリアルボタンのテクスチャ読み込み
	CTutorialButton::TextureLoad();
	//ランキングボタンのテクスチャ読み込み
	CRankingButton::TextureLoad();
	//終了ボタンのテクスチャ読み込み
	CExitButton::TextureLoad();
	//ゲームに戻るボタンのテクスチャ読み込み
	CQuitGameButton::TextureLoad();
	//操作説明ボタンのテクスチャ読み込み
	CControllerGuidButton::TextureLoad();
	//タイトルに戻るボタンのテクスチャ読み込み
	CBackToTitleButton::TextureLoad();
	//タイトルロゴのテクスチャ読み込み
	CTitleLogo::TextureLoad();
	//文字のテクスチャ読み込み
	CLetter::TextureLoad();
	//スカイボックスのテクスチャ読み込み
	CSkyBox::TextureLoad();
	CShadow::ModelLoad();
}

//=============================================================================
// 全読み込み破棄処理関数
//=============================================================================
void CManager::UnloadAll(void)
{
	//プレイヤーのモデル破棄
	CPlayer::ModelUnload();
	//剣のモデル破棄
	CSword::ModelUnload();
	//盾のモデル破棄
	CShield::ModelUnload();
	//ドラゴンモデル破棄
	CDragon::ModelUnload();
	//地面のテクスチャ破棄
	CFloor::TextureUnload();
	//何らかのボタンのテクスチャ破棄
	CAnyButton::TextureUnload();
	//スタートボタンのテクスチャ破棄
	CStartButton::TextureUnload();
	//チュートリアルボタンのテクスチャ破棄
	CTutorialButton::TextureUnload();
	//ランキングボタンのテクスチャ破棄
	CRankingButton::TextureUnload();
	//終了ボタンのテクスチャ破棄
	CExitButton::TextureUnload();
	//ゲームに戻るボタンのテクスチャ破棄
	CQuitGameButton::TextureUnload();
	//操作説明ボタンのテクスチャ破棄
	CControllerGuidButton::TextureUnload();
	//タイトルに戻るボタンのテクスチャ破棄
	CBackToTitleButton::TextureUnload();
	//タイトルロゴのテクスチャ破棄
	CTitleLogo::TextureUnload();
	//文字のテクスチャ破棄
	CLetter::TextureUnload();
	//スカイボックスのテクスチャ破棄
	CSkyBox::TextureUnload();
	CShadow::ModelUnload();
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
		//サウンドの終了処理関数呼び出し
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