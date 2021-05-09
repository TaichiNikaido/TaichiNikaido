//=============================================================================
//
// タイトルボタンマネージャー [title_button_manager.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/sound.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "title_button_manager.h"
#include "button_start.h"
#include "button_tutorial.h"
#include "button_ranking.h"
#include "button_exit.h"
#include "button_any.h"

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
CTitleButtonManager::CTitleButtonManager(int nPriority) : CScene(nPriority)
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//ボタンのポインタ
	m_nButton = BUTTON_NONE;						//ボタン
	m_nInputCount = 0;								//入力間隔
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
	CTitleButtonManager * pTitleButtonManager = nullptr;
	//タイトルボタンマネージャーポインタがnullptrの場合
	if (pTitleButtonManager == nullptr)
	{
		//タイトルボタンマネージャーのメモリ確保
		pTitleButtonManager = new CTitleButtonManager;
		//タイトルボタンマネージャーのポインタがnullptrではない場合
		if (pTitleButtonManager != nullptr)
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
	m_nButton = BUTTON_START;
	//ボタンの初期選択処理関数呼び出し
	m_apButton[m_nButton]->SelectColor();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CTitleButtonManager::Uninit(void)
{
	//破棄処理関数呼び出し
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CTitleButtonManager::Update(void)
{
	//選択処理関数呼び出し
	Select();
	//入力処理関数呼び出し
	Input();
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
	}
	//もしESCAPEキー又はジョイスティックのBボタンを押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_ESCAPE) || pJoystick->GetJoystickTrigger(JS_B))
	{
		//キャンセル時音再生処理関数呼び出し
		CancelSound();
		//何らかのボタン生成処理関数呼び出し
		CAnyButton::Create();
		//ボタンの最大数分回す
		for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
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
void CTitleButtonManager::Select(void)
{
	//もし現在のボタンがスタートボタンより下だったら
	if (m_nButton < BUTTON_START)
	{
		//現在のボタンを終了ボタンにする
		m_nButton = BUTTON_EXIT;
	}
	//もし現在のボタンが終了ボタンを越えたら
	if (m_nButton > BUTTON_EXIT)
	{
		//現在のボタンをスタートボタンにする
		m_nButton = BUTTON_START;
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
// キャンセル時音再生処理関数
//=============================================================================
void CTitleButtonManager::CancelSound(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//もしサウンドのポインタがnullptrではない場合
	if (pSound != nullptr)
	{
		//キャンセル音の再生
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_CANCEL);
	}
}

//=============================================================================
// 初期生成処理関数
//=============================================================================
void CTitleButtonManager::InitCreateAll(void)
{
	//スタートボタンの生成
	m_apButton[BUTTON_START] = CStartButton::Create(START_BUTTON_POSITION);
	//チュートリアルボタンの生成
	m_apButton[BUTTON_TUTORIAL] = CTutorialButton::Create(TUTORIAL_BUTTON_POSITION);
	//ランキングボタンの生成
	m_apButton[BUTTON_RANKING] = CRankingButton::Create(RANKING_BUTTON_POSITION);
	//終了ボタンの生成
	m_apButton[BUTTON_EXIT] = CExitButton::Create(EXIT_BUTTON_POSITION,CExitButton::TEXTURE_ENGLISH);
}