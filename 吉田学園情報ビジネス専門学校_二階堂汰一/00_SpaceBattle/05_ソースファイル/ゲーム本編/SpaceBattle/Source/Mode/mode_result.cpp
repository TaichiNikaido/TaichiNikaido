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
#include "mode_result.h"
#include "Background/background_result.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "System/result.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

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
	//もしリザルトモードのポインタがNULLの場合
	if (pResultMode == NULL)
	{
		//リザルトモードのメモリ確保
		pResultMode = new CResultMode;
		//もしリザルトモードのポインタがNULLじゃない場合
		if (pResultMode != NULL)
		{
			//リザルトモードの初期化処理関数呼び出し
			pResultMode->Init();
		}
	}
	//リザルトモードのポインタを返す
	return pResultMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CResultMode::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//BGMの再生
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);
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
		CManager::StartFade(CManager::MODE_RANKING);
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
	CBackgroundResult::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pResult = CResult::Create();
}
