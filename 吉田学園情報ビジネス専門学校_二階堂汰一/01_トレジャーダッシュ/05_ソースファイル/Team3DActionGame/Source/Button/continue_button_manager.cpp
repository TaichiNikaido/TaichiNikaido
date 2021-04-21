//=============================================================================
//
// コンティニューボタンマネージャー [continue_button_manager.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "Base/main.h"
#include "Base/manager.h"
#include "Mode/mode_game.h"
#include "Base/renderer.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "continue_button_manager.h"
#include "button_continue.h"
#include "button_not_continue.h"
#include "Character/player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define START_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 740.0f, 0.0f))		//スタートボタンの位置
#define TUTORIAL_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 820.0f, 0.0f))	//チュートリアルボタンの位置
#define RANKING_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 900.0f, 0.0f))	//ランキングボタンの位置
#define EXIT_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 980.0f, 0.0f))		//終了ボタンの位置
#define MINIMUM_INPUT_COUNT (0)													//入力間隔の最小値
#define INPUT_INTERVAL (10)														//入力間隔

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CContinueButtonManager::CContinueButtonManager()
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//ボタンのポインタ
	m_nButton = BUTTON_NONE;						//ボタン
	m_nInputCount = MINIMUM_INPUT_COUNT;
}

//=============================================================================
// デストラクタ
//=============================================================================
CContinueButtonManager::~CContinueButtonManager()
{
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CContinueButtonManager * CContinueButtonManager::Create(void)
{
	//タイトルボタンマネージャーのポインタ
	CContinueButtonManager * pTitleButtonManager = NULL;
	//タイトルボタンマネージャーポインタがNULLの場合
	if (pTitleButtonManager == NULL)
	{
		//タイトルボタンマネージャーのメモリ確保
		pTitleButtonManager = new CContinueButtonManager;
		//タイトルボタンマネージャーのポインタがNULLではない場合
		if (pTitleButtonManager != NULL)
		{
			//タイトルボタンマネージャーの初期化処理関数呼び出し
			pTitleButtonManager->Init();
		}
	}
	//タイトルボタンマネージャーのポインタを返す
	return pTitleButtonManager;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CContinueButtonManager::Init(void)
{
	//初期全性処理関数呼び出し
	InitCreateAll();
	//ボタンの初期設定
	m_nButton = BUTTON_CONTINUE;
	//ボタンの初期選択処理関数呼び出し
	m_apButton[m_nButton]->SelectColor();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CContinueButtonManager::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CContinueButtonManager::Update(void)
{
	//ボタンの最大数分回す
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
	{
		//ボタンの選択されてない時の色変更処理関数呼び出し
		m_apButton[nCount]->NotSelectColor();
	}
	//ボタンの選択時色変更処理関数呼び出し
	m_apButton[m_nButton]->SelectColor();
	//入力処理関数呼び出し
	Input();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CContinueButtonManager::Draw(void)
{
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CContinueButtonManager::Input(void)
{
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
		//もし現在のボタンがスタートボタンより下だったら
		if (m_nButton < BUTTON_CONTINUE)
		{
			//現在のボタンを終了ボタンにする
			m_nButton = BUTTON_NOT_CONTINUE;
		}
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->SelectSound();
	}
	//上スティックが入力された場合
	if (lpDIDevice != NULL &&js.rgdwPOV[0] == 0)
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
		//もし現在のボタンがスタートボタンより下だったら
		if (m_nButton < BUTTON_CONTINUE)
		{
			//現在のボタンを終了ボタンにする
			m_nButton = BUTTON_NOT_CONTINUE;
		}
	}
	//下キーが入力された場合
	if (pKeyboard->GetKeyboardTrigger(DIK_DOWN))
	{
		//現在のボタンを減算する
		m_nButton++;
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->SelectSound();
		//もし現在のボタンが終了ボタンを越えたら
		if (m_nButton > BUTTON_NOT_CONTINUE)
		{
			//現在のボタンをスタートボタンにする
			m_nButton = BUTTON_CONTINUE;
		}
	}
	//下スティックが入力された場合
	if (lpDIDevice != NULL &&js.rgdwPOV[0] == 18000)
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
		//もし現在のボタンが終了ボタンを越えたら
		if (m_nButton > BUTTON_NOT_CONTINUE)
		{
			//現在のボタンをスタートボタンにする
			m_nButton = BUTTON_CONTINUE;
		}
	}
	//もしENTERキー又はジョイスティックのAボタンを押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pJoystick->GetJoystickTrigger(JS_A))
	{
		//ボタンのプレス処理関数呼び出し
		m_apButton[m_nButton]->Press();
		//ボタンの総数分回す
		for (int nCount = BUTTON_CONTINUE; nCount < BUTTON_MAX; nCount++)
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
// 初期生成処理関数
//=============================================================================
void CContinueButtonManager::InitCreateAll(void)
{
	//スタートボタンの生成
	m_apButton[BUTTON_CONTINUE] = CContinueButton::Create(START_BUTTON_POSITION);
	//チュートリアルボタンの生成
	m_apButton[BUTTON_NOT_CONTINUE] = CNotContinueButton::Create(TUTORIAL_BUTTON_POSITION);
}