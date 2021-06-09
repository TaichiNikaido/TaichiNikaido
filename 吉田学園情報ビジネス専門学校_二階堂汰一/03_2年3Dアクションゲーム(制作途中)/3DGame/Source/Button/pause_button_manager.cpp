//=============================================================================
//
// ポーズボタンマネージャー [pause_button_manager.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Mode/mode_tutorial.h"
#include "Mode/mode_game.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "pause_button_manager.h"
#include "button_back_to_title.h"
#include "button_controller_guid.h"
#include "button_quit_game.h"
#include "button_exit.h"
#include "polygon2d/pause_bg.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define QUIT_GAME_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 740.0f, 0.0f))				//ゲームに戻るボタンの位置
#define CONTROLLER_GUIDE_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 820.0f, 0.0f))		//操作説明ボタンの位置
#define BACK_TO_TITLE_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 900.0f, 0.0f))			//タイトルに戻るボタンの位置
#define EXIT_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 980.0f, 0.0f))					//終了ボタンの位置
#define INPUT_INTERVAL (10)																	//入力間隔

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CPauseButtonManager::CPauseButtonManager(int nPriority) : CScene(nPriority)
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//ボタンのポインタ
	m_nButton = BUTTON_NONE;						//ボタン
	m_nInputCount = 0;								//入力間隔
	m_pPouseBG = nullptr;							//ポーズ背景のポインタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CPauseButtonManager::~CPauseButtonManager()
{
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CPauseButtonManager * CPauseButtonManager::Create(void)
{
	//ポーズボタンマネージャーのポインタ
	CPauseButtonManager * pPoseButtonManager = nullptr;
	//ポーズボタンマネージャーポインタがnullptrの場合
	if (pPoseButtonManager == nullptr)
	{
		//ポーズボタンマネージャーのメモリ確保
		pPoseButtonManager = new CPauseButtonManager;
		//ポーズボタンマネージャーのポインタがnullptrではない場合
		if (pPoseButtonManager != nullptr)
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
HRESULT CPauseButtonManager::Init(void)
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
	//もしチュートリアルモードのポインタがnullptrじゃない場合
	if (pTutorialMode != nullptr)
	{
		//ポーズ使用状態にする
		pTutorialMode->SetbCreatePause(true);
	}
	//もしゲームモードのポインタがnullptrじゃない場合
	if (pGameMode != nullptr)
	{
		//ポーズ使用状態にする
		pGameMode->SetbCreatePause(true);
	}
	//もしポーズ背景のポインタがnullptrの場合
	if (m_pPouseBG == nullptr)
	{
		//ポーズ背景の生成
		m_pPouseBG = CPauseBG::Create();
	}
	//ポーズの使用状態を設定する
	SetbPause(true);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPauseButtonManager::Uninit(void)
{
	//チュートリアルモードの取得
	CTutorialMode * pTutorialMode = CManager::GetTutorialMode();
	//ゲームモードの取得
	CGameMode * pGameMode = CManager::GetGameMode();
	//もしチュートリアルモードのポインタがnullptrじゃない場合
	if (pTutorialMode != nullptr)
	{
		//ポーズ未生成状態にする
		pTutorialMode->SetbCreatePause(false);
	}
	//もしゲームモードのポインタがnullptrじゃない場合
	if (pGameMode != nullptr)
	{
		//ポーズ未生成状態にする
		pGameMode->SetbCreatePause(false);
	}
	//破棄処理関数呼び出し
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPauseButtonManager::Update(void)
{
	//選択処理関数呼び出し
	Select();
	//入力処理関数呼び出し
	Input();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPauseButtonManager::Draw(void)
{
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CPauseButtonManager::Input(void)
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
	//キーボードの更新処理関数呼び出し
	pKeyboard->Update();
	//ジョイスティックの更新処理関数呼び出し
	pJoystick->Update();
	//ウィンドウがアクティブの場合
	if (CManager::GetIsActiveWindow() == true)
	{
		//マウスカーソルの位置を画面の中心に設定する
		SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	//上矢印キーが入力された場合
	if (pKeyboard->GetKeyboardTrigger(DIK_UP))
	{
		//現在のボタンを減算する
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
			//現在のボタンを減算する
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
		//もしポーズ背景のポインタがnullptrではない場合
		if (m_pPouseBG != nullptr)
		{
			//ポーズ背景の終了処理関数呼び出し
			m_pPouseBG->Uninit();
		}
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
	//もしESCAPEキー又はジョイスティックのSTARTボタンを押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_ESCAPE) || pJoystick->GetJoystickTrigger(JS_START))
	{
		//もしポーズ背景のポインタがnullptrではない場合
		if (m_pPouseBG != nullptr)
		{
			//ポーズ背景の終了処理関数呼び出し
			m_pPouseBG->Uninit();
		}
		//ボタンの総数分回す
		for (int nCount = BUTTON_QUIT_GAME; nCount < BUTTON_MAX; nCount++)
		{
			//各ボタンの終了処理関数呼び出し
			m_apButton[nCount]->Uninit();
		}
		//ポーズを未使用状態にする
		SetbPause(false);
		//終了処理関数呼び出し
		Uninit();
		return;
	}
	if (lpDIDevice != NULL &&js.lY == 0)
	{
		m_nInputCount = 0;
	}

}

//=============================================================================
// 選択処理関数
//=============================================================================
void CPauseButtonManager::Select(void)
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
void CPauseButtonManager::InitCreateAll(void)
{
	//ゲームに戻るボタンの生成
	m_apButton[BUTTON_QUIT_GAME] = CQuitGameButton::Create(QUIT_GAME_BUTTON_POSITION);
	//操作説明ボタンの生成
	m_apButton[BUTTON_CONTROLLER_GUIDE] = CControllerGuidButton::Create(CONTROLLER_GUIDE_BUTTON_POSITION);
	//タイトルボタンの生成
	m_apButton[BUTTON_BACK_TO_TITLE] = CBackToTitleButton::Create(BACK_TO_TITLE_BUTTON_POSITION);
	//終了ボタンの生成
	m_apButton[BUTTON_EXIT] = CExitButton::Create(EXIT_BUTTON_POSITION, CExitButton::TEXTURE_JAPANESE);
}