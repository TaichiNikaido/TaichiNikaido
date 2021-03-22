//=============================================================================
//
// ランキングモード [mode_ranking.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "keyboard.h"
#include "joystick.h"
#include "mode_ranking.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CRankingMode::CRankingMode()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CRankingMode::~CRankingMode()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CRankingMode * CRankingMode::Create()
{
	//ランキングモードのポインタ
	CRankingMode * pRankingMode = NULL;
	//もしランキングモードのポインタがNULLの場合
	if (pRankingMode == NULL)
	{
		//ランキングモードのメモリ確保
		pRankingMode = new CRankingMode;
		//もしランキングモードのポインタがNULLじゃない場合
		if (pRankingMode != NULL)
		{
			//ランキングモードの初期化処理関数呼び出し
			pRankingMode->Init();
		}
	}
	//ランキングモードのポインタを返す
	return pRankingMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CRankingMode::Init(void)
{
	//全生成処理関数呼び出し
	CreateAll();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CRankingMode::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CRankingMode::Update(void)
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
	//入力処理関数呼び出し
	Input();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CRankingMode::Draw(void)
{
}

//=============================================================================
// 入力処理関数呼び出し
//=============================================================================
void CRankingMode::Input(void)
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
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//もしESCAPEキー又はジョイスティックのBボタンを押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_ESCAPE) || pJoystick->GetJoystickTrigger(JS_B))
	{
		//もしサウンドのポインタがNULLじゃない場合
		if (pSound != NULL)
		{
			//キャンセル音の再生
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_CANCEL);
		}
		//タイトルモードに遷移する
		CManager::StartFade(CManager::MODE_TITLE);
	}
}

//=============================================================================
// 全生成処理関数
//=============================================================================
void CRankingMode::CreateAll(void)
{
}
