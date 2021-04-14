//=============================================================================
//
// ポーズボタンマネージャー [pose_button_manager.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "mode_tutorial.h"
#include "mode_game.h"
#include "keyboard.h"
#include "joystick.h"
#include "pose_button_manager.h"
#include "button_back_to_title.h"
#include "button_controller_guid.h"
#include "button_quit_game.h"
#include "button_exit.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define START_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 740.0f, 0.0f))		//スタートボタンの位置
#define TUTORIAL_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 820.0f, 0.0f))	//チュートリアルボタンの位置
#define RANKING_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 900.0f, 0.0f))	//ランキングボタンの位置
#define EXIT_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 980.0f, 0.0f))		//終了ボタンの位置
#define INPUT_INTERVAL (10)														//入力間隔

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CPoseButtonManager::CPoseButtonManager()
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//ボタンのポインタ
	m_nButton = BUTTON_NONE;						//ボタン
	m_nInputCount = 0;								//入力間隔
}

//=============================================================================
// デストラクタ
//=============================================================================
CPoseButtonManager::~CPoseButtonManager()
{
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CPoseButtonManager * CPoseButtonManager::Create(void)
{
	//ポーズボタンマネージャーのポインタ
	CPoseButtonManager * pPoseButtonManager = NULL;
	//ポーズボタンマネージャーポインタがNULLの場合
	if (pPoseButtonManager == NULL)
	{
		//ポーズボタンマネージャーのメモリ確保
		pPoseButtonManager = new CPoseButtonManager;
		//ポーズボタンマネージャーのポインタがNULLではない場合
		if (pPoseButtonManager != NULL)
		{
			//ポーズボタンマネージャーの初期化処理関数呼び出し
			pPoseButtonManager->Init();
		}
	}
	//ポーズボタンマネージャーのポインタを返す
	return pPoseButtonManager;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPoseButtonManager::Init(void)
{
	//チュートリアルモードの取得
	CTutorialMode * pTutorialMode = CManager::GetTutorialMode();
	//ゲームモードの取得
	CGameMode * pGameMode = CManager::GetGameMode();
	//初期全性処理関数呼び出し
	InitCreateAll();
	//ボタンの初期設定
	m_nButton = BUTTON_QUIT_GAME;
	//ボタンの初期選択処理関数呼び出し
	m_apButton[m_nButton]->SelectColor();
	//もしチュートリアルモードのポインタがNULLじゃない場合
	if (pTutorialMode != NULL)
	{
		//ポーズ使用状態にする
		pTutorialMode->SetbPouse(true);
	}
	//もしゲームモードのポインタがNULLじゃない場合
	if (pGameMode != NULL)
	{
		//ポーズ使用状態にする
		pGameMode->SetbPouse(true);
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPoseButtonManager::Uninit(void)
{
	//破棄処理関数呼び出し
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPoseButtonManager::Update(void)
{
	//選択処理関数呼び出し
	Select();
	//入力処理関数呼び出し
	Input();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPoseButtonManager::Draw(void)
{
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CPoseButtonManager::Input(void)
{
	//チュートリアルモードの取得
	CTutorialMode * pTutorialMode = CManager::GetTutorialMode();
	//ゲームモードの取得
	CGameMode * pGameMode = CManager::GetGameMode();
	//キーボードの取得
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	//ジョイスティックの取得
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//ジョイスティックの振動取得
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//上矢印キーが入力された場合
	if (pKeyboard->GetKeyboardTrigger(DIK_UP))
	{
		//現在のボタンを加算する
		m_nButton--;
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->SelectSound();
	}
	//上矢印ボタンか上スティックが入力された場合
	if (lpDIDevice != NULL &&js.rgdwPOV[0] == 0 || lpDIDevice != NULL &&js.lY == -1000)
	{
		//入力間隔を加算する
		m_nInputCount++;
		if (m_nInputCount % INPUT_INTERVAL == 0)
		{
			//現在のボタンを加算する
			m_nButton--;
			//ボタンの選択時音再生処理関数呼び出し
			m_apButton[m_nButton]->SelectSound();
		}
	}
	//下矢印キーが入力された場合
	if (pKeyboard->GetKeyboardTrigger(DIK_DOWN))
	{
		//現在のボタンを減算する
		m_nButton++;
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->SelectSound();
	}
	//下矢印ボタンか下スティックが入力された場合
	if (lpDIDevice != NULL &&js.rgdwPOV[0] == 18000 || lpDIDevice != NULL &&js.lY == 1000)
	{
		//入力間隔を加算する
		m_nInputCount++;
		if (m_nInputCount % INPUT_INTERVAL == 0)
		{
			//現在のボタンを減算する
			m_nButton++;
			//ボタンの選択時音再生処理関数呼び出し
			m_apButton[m_nButton]->SelectSound();
		}
	}
	//もしENTERキー又はジョイスティックのAボタンを押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pJoystick->GetJoystickTrigger(JS_A))
	{
		//ボタンのプレス処理関数呼び出し
		m_apButton[m_nButton]->Press();
		//ボタンの総数分回す
		for (int nCount = BUTTON_QUIT_GAME; nCount < BUTTON_MAX; nCount++)
		{
			//各ボタンの終了処理関数呼び出し
			m_apButton[nCount]->Uninit();
		}
		//終了処理関数呼び出し
		Uninit();
		return;
	}
}

//=============================================================================
// 選択処理関数
//=============================================================================
void CPoseButtonManager::Select(void)
{
	//もし現在のボタンが終了ボタンより下だったら
	if (m_nButton < BUTTON_QUIT_GAME)
	{
		//現在のボタンをタイトルに戻るボタンにする
		m_nButton = BUTTON_EXIT;
	}
	//もし現在のボタンが終了ボタンを越えたら
	if (m_nButton > BUTTON_EXIT)
	{
		//現在のボタンをゲームに戻るボタンにする
		m_nButton = BUTTON_QUIT_GAME;
	}
	//ボタンの最大数分回す
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
	{
		//ボタンの選択されてない時の色変更処理関数呼び出し
		m_apButton[nCount]->NotSelectColor();
	}
	//ボタンの選択時色変更処理関数呼び出し
	m_apButton[m_nButton]->SelectColor();
}

//=============================================================================
// 初期生成処理関数
//=============================================================================
void CPoseButtonManager::InitCreateAll(void)
{
	//ゲームに戻るボタンの生成
	m_apButton[BUTTON_QUIT_GAME] = CQuitGameButton::Create(START_BUTTON_POSITION);
	//操作説明ボタンの生成
	m_apButton[BUTTON_CONTROLLER_GUIDE] = CControllerGuidButton::Create(TUTORIAL_BUTTON_POSITION);
	//タイトルボタンの生成
	m_apButton[BUTTON_BACK_TO_TITLE] = CBackToTitleButton::Create(RANKING_BUTTON_POSITION);
	//終了ボタンの生成
	m_apButton[BUTTON_EXIT] = CExitButton::Create(EXIT_BUTTON_POSITION, CExitButton::TEXTURE_JAPANESE);
}