//=============================================================================
//
// ゲームモード [mode_game.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "sound.h"
#include "mode_game.h"
#include "camera.h"
#include "light.h"
#include "pose_button_manager.h"
#include "floor.h"
#include "player.h"
#include "weapon_sword.h"
#include "weapon_shield.h"
#include "enemy_skeleton.h"
#include "enemy_dragon.h"
#include "village.h"
#include "sparks.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CCamera * CGameMode::m_pCamera = NULL;	//カメラのポインタ
CPlayer * CGameMode::m_pPlayer = NULL;	//プレイヤーのポインタ
CDragon * CGameMode::m_pDragon = NULL;	//ドラゴンのポインタ
CVillage * CGameMode::m_pVillage = NULL;	//村のポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CGameMode::CGameMode()
{
	m_pLight = NULL;	//ライトのポインタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameMode::~CGameMode()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CGameMode * CGameMode::Create()
{
	//ゲームモードのポインタ
	CGameMode * pGameMode = NULL;
	//もしゲームモードのポインタをNULLだった場合
	if (pGameMode == NULL)
	{
		//ゲームモードのメモリ確保
		pGameMode = new CGameMode;
		//もしゲームモードのポインタをNULLじゃない場合
		if (pGameMode != NULL)
		{
			//ゲームモードの初期化関数呼び出し
			pGameMode->Init();
		}
	}
	//ゲームモードのポインタを返す
	return pGameMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CGameMode::Init(void)
{
	//全初期生成処理関数呼び出し
	InitCreateAll();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CGameMode::Uninit(void)
{
	//もしカメラのポインタがNULLじゃない場合
	if (m_pCamera != NULL)
	{
		//カメラの初期化処理関数呼び出し
		m_pCamera->Uninit();
		//カメラのメモリ破棄
		delete m_pCamera;
		//カメラのポインタをNULLにする
		m_pCamera = NULL;
	}
	//もしライトのポインタがNULLじゃない場合
	if (m_pLight != NULL)
	{
		//ライトの初期化処理関数呼び出し
		m_pLight->Uninit();
		//ライトのメモリ破棄
		delete m_pLight;
		//ライトのポインタをNULLにする
		m_pLight = NULL;
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CGameMode::Update(void)
{
	//全更新生成処理関数呼び出し
	UpdateCreateAll();
	//もしカメラのポインタがNULLじゃない場合
	if (m_pCamera != NULL)
	{
		//カメラを設定する
		m_pCamera->SetCamera();
		//カメラの更新処理関数呼び出し
		m_pCamera->Update();
	}
	//入力処理関数呼び出し
	Input();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGameMode::Draw(void)
{
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CGameMode::Input(void)
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
	//もしESCAPEキー又はジョイスティックのスタートボタンを押されたら
	if (pKeyboard->GetKeyboardTrigger(DIK_ESCAPE) || pJoystick->GetJoystickTrigger(JS_START))
	{
		//ポーズボタンマネージャーの生成処理関数呼び出し
		CPoseButtonManager::Create();
	}
}

//=============================================================================
// 全初期生成処理関数
//=============================================================================
void CGameMode::InitCreateAll(void)
{
	////もしライトのポインタがNULLの場合
	//if (m_pLight == NULL)
	//{
	//	//ライトのメモリ確保
	//	m_pLight = new CLight;
	//}
	////もしライトのポインタがNULLじゃない場合
	//if (m_pLight != NULL)
	//{
	//	//ライトの初期化処理関数呼び出し
	//	m_pLight->Init();
	//}
	////もしプレイヤーのポインタがNULLの場合
	//if (m_pPlayer == NULL)
	//{
	//	//プレイヤーの生成
	//	m_pPlayer = CPlayer::Create();
	//}
	////もしカメラのポインタがNULLの場合
	//if (m_pCamera == NULL)
	//{
	//	//カメラのメモリ確保
	//	m_pCamera = new CCamera;
	//}
	////もしカメラのポインタがNULLじゃない場合
	//if (m_pCamera != NULL)
	//{
	//	//カメラの初期化処理関数呼び出し
	//	m_pCamera->Init();
	//}



	//CFloor::Create();
	//CSkeleton::Create();
	//m_pDragon = CDragon::Create();
	//CSparks::Create();
	//CSword::Create();
	//CShield::Create();
	//m_pStage = CStage::Create();
	//CVillageLifeUI::Create();
	//CVillageIcon::Create();
}

//=============================================================================
// 全更新生成処理関数
//=============================================================================
void CGameMode::UpdateCreateAll(void)
{
}