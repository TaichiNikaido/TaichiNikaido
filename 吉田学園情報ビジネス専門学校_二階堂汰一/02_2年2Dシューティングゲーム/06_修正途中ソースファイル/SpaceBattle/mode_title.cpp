//=============================================================================
//
// タイトルモード [mode_title.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "mode_title.h"
#include "background_title.h"
#include "keyboard.h"
#include "joystick.h"
#include "button.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INPUT_TIME (5)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CTitleMode::CTitleMode()
{
	m_InputStick.Up.bTrigger = false;			//スティックを上に倒しているかどうか
	m_InputStick.Down.bTrigger = false;			//スティックを下に倒しているかどうか
	m_InputStick.Up.nCount = 0;					//スティックの上入力の遊び
	m_InputStick.Down.nCount = 0;				//スティックの下入力の遊び
	m_nButtonPosition = 0;						//選択中のボタンの位置
	memset(m_apButton,NULL,sizeof(m_apButton));	//ボタンへのポインタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitleMode::~CTitleMode()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CTitleMode * CTitleMode::Create()
{
	CTitleMode * pTitleMode;
	pTitleMode = new CTitleMode;
	pTitleMode->Init();
	return pTitleMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CTitleMode::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//BGMの再生
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
	//全生成処理関数呼び出し
	CreateAll();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CTitleMode::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CTitleMode::Update(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//入力処理関数呼び出し
	Input();
	//ボタン設定処理関数呼び出し
	SetButtonUI();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CTitleMode::Draw(void)
{
	for (int nCount = 0; nCount < CButton::BUTTON_MAX; nCount++)
	{
		m_apButton[nCount]->Draw();
	}
}

//=============================================================================
// ボタン設定処理関数
//=============================================================================
void CTitleMode::SetButtonUI(void)
{
	for (int nCount = 0; nCount < CButton::BUTTON_MAX; nCount++)
	{
		m_apButton[nCount]->SelectButton(false);
	}

	m_apButton[m_nButtonPosition]->SelectButton(true);
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CTitleMode::Input(void)
{
	//キーボードの取得
	CKeyboard *pKeyboard = CManager::GetKeyboard();
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
	//スティックの上が入力されたとき
	if (lpDIDevice != NULL &&js.lY == -1000)
	{
		//スティックの上入力の遊びを加算する
		m_InputStick.Up.nCount++;
	}
	//Wキーが入力されたとき
	if (pKeyboard->GetKeyboardTrigger(DIK_W))
	{
		//もしボタンの位置がプレイボタンより上だったら
		if (m_nButtonPosition > CButton::BUTTON_PLAY)
		{
			//選択中のボタンの位置を下げる
			m_nButtonPosition--;
		}
	}
	//スティックの下が入力されたとき
	if (lpDIDevice != NULL &&js.lY == 1000)
	{
		//スティックの下入力の遊びを加算する
		m_InputStick.Down.nCount++;
	}
	//Sキーが入力されたとき
	if (pKeyboard->GetKeyboardTrigger(DIK_S))
	{
		//もしボタンの位置がEXITボタンより上だったら
		if (m_nButtonPosition < CButton::BUTTON_EXIT)
		{
			//選択中のボタンの位置を上げる
			m_nButtonPosition++;
		}

	}
	//スティックの上入力の遊びが指定の時間になったら
	if (m_InputStick.Up.nCount > INPUT_TIME)
	{
		//スティックの上入力を真にする
		m_InputStick.Up.bTrigger = true;
		//入力の遊びを0にする
		m_InputStick.Up.nCount = 0;
	}
	//スティックの下入力の遊びが指定の時間になったら
	if (m_InputStick.Down.nCount > INPUT_TIME)
	{
		//スティックの下入力を真にする
		m_InputStick.Down.bTrigger = true;
		//入力の遊びを0にする
		m_InputStick.Down.nCount = 0;
	}
	//もしスティックの上入力が真になったら
	if (m_InputStick.Up.bTrigger == true)
	{
		//もしスティックの上入力を偽にする
		m_InputStick.Up.bTrigger = false;
		//もしボタンの位置がプレイボタンより上だったら
		if (m_nButtonPosition > CButton::BUTTON_PLAY)
		{
			//選択中のボタンの位置を下げる
			m_nButtonPosition--;
		}
	}
	//もしスティックの下入力が真になったら
	if (m_InputStick.Down.bTrigger == true)
	{
		//もしスティックの下入力を偽にする
		m_InputStick.Down.bTrigger = false;
		//もしボタンの位置がEXITボタンより上だったら
		if (m_nButtonPosition < CButton::BUTTON_EXIT)
		{
			//選択中のボタンの位置を上げる
			m_nButtonPosition++;
		}
	}
	//もしキーボードのエンターキー又はジョイスティックのAボタンがおされたら
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pJoystick->GetJoystickTrigger(JS_A))
	{
		//選択処理関数呼び出し
		Select();
	}
}

//=============================================================================
// 選択処理関数
//=============================================================================
void CTitleMode::Select(void)
{
	switch (m_nButtonPosition)
	{
	case CButton::BUTTON_PLAY:
		 //名前入力モードに遷移
		CManager::StartFade(CManager::MODE_NAME);
		break;
	case CButton::BUTTON_REPLAY:
		CPlayer::SetbReplay(true);
		//ゲームモードに遷移
		CManager::StartFade(CManager::MODE_GAME);
		break;
	case CButton::BUTTON_EXIT:
		//終了処理
		exit(0);
		return;
		break;
	default:
		break;
	}
}

//=============================================================================
// 全生成処理関数
//=============================================================================
void CTitleMode::CreateAll(void)
{
	//タイトル背景生成
	CBackgroundTitle::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	//プレイボタンの生成
	for (int nCount = 0; nCount < CButton::BUTTON_MAX; nCount++)
	{
		m_apButton[nCount] = CButton::Create(D3DXVECTOR3(float(SCREEN_WIDTH * 0.75), float(SCREEN_HEIGHT * 0.6 + 100.0f * nCount), 0.0f),(CButton::BUTTON)nCount);
	}
}
