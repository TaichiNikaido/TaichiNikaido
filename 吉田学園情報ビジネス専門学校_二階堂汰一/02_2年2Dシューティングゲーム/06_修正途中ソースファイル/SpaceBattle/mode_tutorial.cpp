//=============================================================================
//
// チュートリアルモード [mode_tutorial.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "mode_tutorial.h"
#include "background_tutorial.h"
#include "keyboard.h"
#include "joystick.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorialMode::CTutorialMode()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorialMode::~CTutorialMode()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CTutorialMode * CTutorialMode::Create()
{
	CTutorialMode * pTutorialMode;
	pTutorialMode = new CTutorialMode;
	pTutorialMode->Init();
	return pTutorialMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CTutorialMode::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//BGMの再生
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);
	//全生成処理関数呼び出し
	CreateAll();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CTutorialMode::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CTutorialMode::Update(void)
{
	//キーボードの取得
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
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
	//もしENTERかAボタンを押したとき
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pJoystick->GetJoystickTrigger(JS_A))
	{
		//サウンドの停止
		pSound->StopSound();
		//ランキングに移動
		CManager::StartFade(CManager::MODE_GAME);
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CTutorialMode::Draw(void)
{
}

//=============================================================================
// 全生成処理関数
//=============================================================================
void CTutorialMode::CreateAll(void)
{
	//チュートリアル背景生成
	CBackgroundTutorial::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
}
