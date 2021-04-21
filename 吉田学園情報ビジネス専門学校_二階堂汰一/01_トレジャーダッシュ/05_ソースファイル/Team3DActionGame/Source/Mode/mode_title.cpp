//=============================================================================
//
// タイトルモード [mode_title.cpp]
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
#include "mode_title.h"
#include "Background/bg_title.h"
#include "2DPolygon/title_logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CTitlelogo *CTitleMode::m_pTitlelogo = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CTitleMode::CTitleMode()
{
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
	//タイトルモードのポインタ
	CTitleMode * pTitleMode = NULL;
	//もしタイトルモードのポインタがNULLの場合
	if (pTitleMode == NULL)
	{
		//タイトルモードのメモリ確保
		pTitleMode = new CTitleMode;
		//もしタイトルモードのポインタがNULLじゃない場合
		if (pTitleMode != NULL)
		{
			//初期化処理関数呼び出し
			pTitleMode->Init();
		}
	}
	//タイトルモードのポインタを返す	
	return pTitleMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CTitleMode::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//もしサウンドのポインタがNULLじゃない場合
	if (pSound != NULL)
	{
		//タイトルBGMの再生
		pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_TITLE);
	}
	//初期全生成処理関数呼び出し
	InitCreateAll();
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
	//入力処理関数呼び出し
	Input();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CTitleMode::Draw(void)
{
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CTitleMode::Input(void)
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
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL && pJoystick->GetJoystickTrigger(JS_A))
	{
		//ランキングに移動
		CManager::StartFade(CManager::MODE_GAME);
	}
}

//=============================================================================
// 初期全生成処理関数
//=============================================================================
void CTitleMode::InitCreateAll(void)
{
	//タイトル背景の生成
	CTitleBG::Create();
	//タイトルロゴの生成
	m_pTitlelogo = CTitlelogo::Create(D3DXVECTOR3(TITLE_PLESS_POS_X, TITLE_PLESS_POS_Y, 0.0f),
		D3DXVECTOR3(TITLE_PLESS_SIZE_X, TITLE_PLESS_SIZE_Y, 0.0f),
		CTitlelogo::LOGOTIPE_PRESS);
}
