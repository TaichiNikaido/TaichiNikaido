//=============================================================================
//
// リザルトモード [mode_result.cpp]
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
#include "mode_result.h"
#include "Background/bg_result.h"
#include "UI/score.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CScore *CResultMode::m_pScore = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CResultMode::CResultMode()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CResultMode::~CResultMode()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CResultMode * CResultMode::Create()
{
	//リザルトモードのポインタ
	CResultMode * pResultMode = NULL;
	//もしリザルトモードがNULLの場合
	if (pResultMode == NULL)
	{
		//リザルトモードのメモリ確保
		pResultMode = new CResultMode;
		//もしリザルトモードがNULLじゃない場合
		if (pResultMode != NULL)
		{
			//初期化処理関数呼び出し
			pResultMode->Init();
		}
	}
	//リザルトモードのポインタ
	return pResultMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CResultMode::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//もしサウンドのポインタがNULLじゃない場合
	if (pSound != NULL)
	{
		//タイトルBGMの再生
		pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_RESULT);
	}
	//全生成処理関数呼び出し
	CreateAll();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CResultMode::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CResultMode::Update(void)
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
		CManager::StartFade(CManager::MODE_TITLE);
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CResultMode::Draw(void)
{
}

//=============================================================================
// 全生成処理関数
//=============================================================================
void CResultMode::CreateAll(void)
{
	//リザルト背景の生成
	CResultBG::Create();
	//スコアの生成
	m_pScore = CScore::Create();
}
