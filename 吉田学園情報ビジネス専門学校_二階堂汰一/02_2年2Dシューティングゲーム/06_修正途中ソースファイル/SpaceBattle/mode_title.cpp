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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COUNT_TRIGGER_PAUSE (5)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CTitleMode::CTitleMode()
{
	m_IsTrigger.Down.bTrigger = false;//押されてるかどうか
	m_IsTrigger.Up.bTrigger = false;
	m_IsTrigger.Left.bTrigger = false;
	m_IsTrigger.Right.bTrigger = false;
	m_IsTrigger.Down.nCount = 0;//押されてるかどうか
	m_IsTrigger.Up.nCount = 0;
	m_IsTrigger.Left.nCount = 0;
	m_IsTrigger.Right.nCount = 0;
	m_nButtonPosition = 0;
	memset(m_apButton,NULL,sizeof(m_apButton));
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
	Input();
	
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
// 処理関数
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
// 入力関数
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

	if (lpDIDevice != NULL &&js.lY == -1000 || pKeyboard->GetKeyboardPress(DIK_W))//上
	{
		m_IsTrigger.Up.nCount++;
	}
	if (lpDIDevice != NULL &&js.lY == 1000 || pKeyboard->GetKeyboardPress(DIK_S))//下
	{
		m_IsTrigger.Down.nCount++;
	}

	if (m_IsTrigger.Up.nCount > COUNT_TRIGGER_PAUSE)
	{
		m_IsTrigger.Up.bTrigger = true;
		m_IsTrigger.Up.nCount = COUNT_TRIGGER_PAUSE - 5;
	}
	if (m_IsTrigger.Down.nCount > COUNT_TRIGGER_PAUSE)
	{
		m_IsTrigger.Down.bTrigger = true;
		m_IsTrigger.Down.nCount = COUNT_TRIGGER_PAUSE - 5;
	}
	if (m_IsTrigger.Down.bTrigger == true)
	{
		m_IsTrigger.Down.bTrigger = false;
		if (m_nButtonPosition < 2)
		{
			m_nButtonPosition++;
		}
	}
	if (m_IsTrigger.Up.bTrigger == true)
	{
		m_IsTrigger.Up.bTrigger = false;
		if (m_nButtonPosition > 0)
		{
			m_nButtonPosition--;
		}
	}

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
	//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_ENTER);
	switch (m_nButtonPosition)
	{
	case CButton::BUTTON_PLAY://スタート
		 //名前入力に移動
		 //pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
		CManager::StartFade(CManager::MODE_NAME);
		//pSound->StopSound();
		break;
	case CButton::BUTTON_REPLAY://リプレイボタン
		//pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
		//pSound->StopSound();
		//m_bReplay = true;
		//名前入力に移動
		CManager::StartFade(CManager::MODE_GAME);
		break;
	case CButton::BUTTON_EXIT://終了
		//pSound->PlaySound(CSound::SOUND_LABEL_ENTER);
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
		m_apButton[nCount] = CButton::Create(D3DXVECTOR3(600.0f, 300.0f + 100.0f * nCount, 0.0f),(CButton::BUTTON)nCount);
	}
}
