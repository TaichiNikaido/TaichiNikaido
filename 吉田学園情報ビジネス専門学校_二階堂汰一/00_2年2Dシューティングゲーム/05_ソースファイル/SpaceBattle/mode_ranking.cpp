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
#include "mode_ranking.h"
#include "background_ranking.h"
#include "keyboard.h"
#include "joystick.h"
#include "ranking.h"

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
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//BGMの再生
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_RANKING);
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
void CRankingMode::Draw(void)
{
}

//=============================================================================
// 全生成処理関数
//=============================================================================
void CRankingMode::CreateAll(void)
{
	//ランキング背景生成
	CBackgroundRanking::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pRanking = CRanking::Create();
}
