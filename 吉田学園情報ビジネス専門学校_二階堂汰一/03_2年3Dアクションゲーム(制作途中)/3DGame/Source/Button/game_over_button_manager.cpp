//=============================================================================
//
// ゲームオーバーボタンマネージャー [game_over_button_manager.cpp]
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
#include "game_over_button_manager.h"
#include "button_retry.h"
#include "button_back_to_title.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RETRY_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 790.0f, 0.0f))				//スタートボタンの位置
#define BACK_TO_TITLE_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 890.0f, 0.0f))		//タイトルに戻るボタンの位置
#define INPUT_INTERVAL (10)																//入力間隔

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CGameOverButtonManager::CGameOverButtonManager(int nPriority) : CScene(nPriority)
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//ボタンのポインタ
	m_nButton = BUTTON_NONE;						//ボタン
	m_nInputCount = 0;								//入力間隔
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameOverButtonManager::~CGameOverButtonManager()
{
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CGameOverButtonManager * CGameOverButtonManager::Create(void)
{
	//ゲームオーバーボタンマネージャーのポインタ
	CGameOverButtonManager * pGameOverButtonManager = nullptr;
	//ゲームオーバーボタンマネージャーがnullptrの場合
	if (pGameOverButtonManager == nullptr)
	{
		//ゲームオーバーボタンマネージャーのメモリ確保
		pGameOverButtonManager = new CGameOverButtonManager;
		//ゲームオーバーボタンマネージャーのポインタがnullptrではない場合
		if (pGameOverButtonManager != nullptr)
		{
			//ゲームオーバーボタンマネージャーの初期化処理関数呼び出し
			pGameOverButtonManager->Init();
		}
	}
	//ゲームオーバーボタンマネージャーのポインタを返す
	return pGameOverButtonManager;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CGameOverButtonManager::Init(void)
{
	//初期全性処理関数呼び出し
	InitCreateAll();
	//ボタンの初期設定
	m_nButton = BUTTON_RETRY;
	//ボタンの初期選択処理関数呼び出し
	m_apButton[m_nButton]->ChangeTranslucent(true);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CGameOverButtonManager::Uninit(void)
{
	//破棄処理関数呼び出し
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CGameOverButtonManager::Update(void)
{
	//選択処理関数呼び出し
	Select();
	//入力処理関数呼び出し
	Input();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGameOverButtonManager::Draw(void)
{
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CGameOverButtonManager::Input(void)
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
		//現在のボタンを減算する
		m_nButton--;
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
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
			m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
		}
	}
	//下矢印キーが入力された場合
	if (pKeyboard->GetKeyboardTrigger(DIK_DOWN))
	{
		//現在のボタンを減算する
		m_nButton++;
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
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
			m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
		}
	}
	//もしENTERキー又はジョイスティックのAボタンを押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pJoystick->GetJoystickTrigger(JS_A))
	{
		//ボタンのプレス処理関数呼び出し
		m_apButton[m_nButton]->Press();
	}
}

//=============================================================================
// 選択処理関数
//=============================================================================
void CGameOverButtonManager::Select(void)
{
	//もし現在のボタンがリトライボタンより下だったら
	if (m_nButton < BUTTON_RETRY)
	{
		//現在のボタンをタイトルに戻るボタンにする
		m_nButton = BUTTON_BACK_TO_TITLE;
	}
	//もし現在のボタンがタイトルに戻るボタンを越えたら
	if (m_nButton > BUTTON_BACK_TO_TITLE)
	{
		//現在のボタンをリトライボタンにする
		m_nButton = BUTTON_RETRY;
	}
	//ボタンの最大数分回す
	for (int nCount = BUTTON_RETRY; nCount < BUTTON_MAX; nCount++)
	{
		//ボタンの選択されてない時の色変更処理関数呼び出し
		m_apButton[nCount]->ChangeTranslucent(false);
	}
	//ボタンの選択時色変更処理関数呼び出し
	m_apButton[m_nButton]->ChangeTranslucent(true);
}

//=============================================================================
// キャンセル時音再生処理関数
//=============================================================================
void CGameOverButtonManager::CancelSound(void)
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
void CGameOverButtonManager::InitCreateAll(void)
{
	//スタートボタンの生成
	m_apButton[BUTTON_RETRY] = CRetryButton::Create(RETRY_BUTTON_POSITION);
	//タイトルボタンの生成
	m_apButton[BUTTON_BACK_TO_TITLE] = CBackToTitleButton::Create(BACK_TO_TITLE_BUTTON_POSITION);
}