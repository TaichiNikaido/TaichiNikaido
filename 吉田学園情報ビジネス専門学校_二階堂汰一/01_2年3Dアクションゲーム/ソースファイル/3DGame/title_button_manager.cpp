//=============================================================================
//
// タイトルボタンマネージャー [title_button_manager.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "renderer.h"
#include "keyboard.h"
#include "joystick.h"
#include "title_button_manager.h"
#include "button_start.h"
#include "button_tutorial.h"
#include "button_ranking.h"
#include "button_exit.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define START_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 740.0f, 0.0f))		//スタートボタンの位置
#define TUTORIAL_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 820.0f, 0.0f))	//チュートリアルボタンの位置
#define RANKING_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 900.0f, 0.0f))	//ランキングボタンの位置
#define EXIT_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 980.0f, 0.0f))		//終了ボタンの位置

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CTitleButtonManager::CTitleButtonManager()
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//ボタンのポインタ
	m_nButton = CButton::BUTTON_NONE;				//ボタン
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitleButtonManager::~CTitleButtonManager()
{
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CTitleButtonManager * CTitleButtonManager::Create(void)
{
	//タイトルボタンマネージャーのポインタ
	CTitleButtonManager * pTitleButtonManager = NULL;
	//タイトルボタンマネージャーポインタがNULLの場合
	if (pTitleButtonManager == NULL)
	{
		//タイトルボタンマネージャーのメモリ確保
		pTitleButtonManager = new CTitleButtonManager;
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
HRESULT CTitleButtonManager::Init(void)
{
	//初期全性処理関数呼び出し
	InitCreateAll();
	//ボタンの初期設定
	m_nButton = CButton::BUTTON_START;
	//ボタンの初期選択処理関数呼び出し
	m_apButton[m_nButton]->SelectColor();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CTitleButtonManager::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CTitleButtonManager::Update(void)
{
	//入力処理関数呼び出し
	Input();
	//ボタンの最大数分回す
	for (int nCount = 0; nCount < CButton::BUTTON_MAX; nCount++)
	{
		//ボタンの選択されてない時の色変更処理関数呼び出し
		m_apButton[nCount]->NotSelectColor();
	}
	//ボタンの選択時色変更処理関数呼び出し
	m_apButton[m_nButton]->SelectColor();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CTitleButtonManager::Draw(void)
{
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CTitleButtonManager::Input(void)
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
	if (pKeyboard->GetKeyboardTrigger(DIK_UP) || lpDIDevice != NULL &&js.rgdwPOV[0] == 0)
	{
		//現在のボタンを加算する
		m_nButton--;
		//もし現在のボタンがスタートボタンより下だったら
		if (m_nButton < CButton::BUTTON_START)
		{
			//現在のボタンを終了ボタンにする
			m_nButton = CButton::BUTTON_EXIT;
		}
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->SelectSound();
	}
	//下矢印キーが入力された場合
	if (pKeyboard->GetKeyboardTrigger(DIK_DOWN) || lpDIDevice != NULL &&js.rgdwPOV[0] == 18000)
	{
		//現在のボタンを減算する
		m_nButton++;
		//もし現在のボタンが終了ボタンを越えたら
		if (m_nButton > CButton::BUTTON_EXIT)
		{
			//現在のボタンをスタートボタンにする
			m_nButton = CButton::BUTTON_START;
		}
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->SelectSound();
	}
	//もしENTERキー又はジョイスティックのAボタンを押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pJoystick->GetJoystickTrigger(JS_A))
	{
		//ボタンのプレス処理関数呼び出し
		m_apButton[m_nButton]->Press();
	}
}

//=============================================================================
// 初期生成処理関数
//=============================================================================
void CTitleButtonManager::InitCreateAll(void)
{
	//スタートボタンの生成
	m_apButton[CButton::BUTTON_START] = CStartButton::Create(START_BUTTON_POSITION);
	//チュートリアルボタンの生成
	m_apButton[CButton::BUTTON_TUTORIAL] = CTutorialButton::Create(TUTORIAL_BUTTON_POSITION);
	//ランキングボタンの生成
	m_apButton[CButton::BUTTON_RANKING] = CRankingButton::Create(RANKING_BUTTON_POSITION);
	//終了ボタンの生成
	m_apButton[CButton::BUTTON_EXIT] = CExitButton::Create(EXIT_BUTTON_POSITION);
}