//=============================================================================
//
// ゲームモード [mode_game.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/sound.h"
#include "Base/light.h"
#include "Base/camera.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "mode_game.h"
#include "Character/player.h"
#include "Character/enemy_dragon.h"
#include "Polygon3d/floor.h"
#include "Button/pose_button_manager.h"
#include "skybox.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CGameMode::CGameMode()
{
	m_pPlayer = nullptr;	//プレイヤーのポインタ
	m_pCamera = nullptr;	//カメラのポインタ
	m_pDragon = nullptr;	//ドラゴンのポインタ
	m_pLight = nullptr;		//ライトのポインタ
	m_bPouse = false;		//ポーズを使用してるか
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
	CGameMode * pGameMode = nullptr;
	//もしゲームモードのポインタをnullptrだった場合
	if (pGameMode == nullptr)
	{
		//ゲームモードのメモリ確保
		pGameMode = new CGameMode;
		//もしゲームモードのポインタをnullptrではない場合
		if (pGameMode != nullptr)
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
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//もしサウンドのポインタがnullptrではない場合
	if (pSound != nullptr)
	{
		//名前入力のBGM停止 
		pSound->StopSound(CSound::SOUND_LABEL_BGM_NAME);
	}
	//初期生成処理関数呼び出し
	InitCreate();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CGameMode::Uninit(void)
{
	//もしカメラのポインタがnullptrではない場合
	if (m_pCamera != nullptr)
	{
		//カメラの終了処理関数呼び出し
		m_pCamera->Uninit();
		//カメラのメモリ破棄
		delete m_pCamera;
		//カメラのポインタをnullptrにする
		m_pCamera = nullptr;
	}
	//もしライトのポインタがnullptrではない場合
	if (m_pLight != nullptr)
	{
		//ライトの終了処理関数呼び出し
		m_pLight->Uninit();
		//ライトのメモリ破棄
		delete m_pLight;
		//ライトのポインタをnullptrにする
		m_pLight = nullptr;
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CGameMode::Update(void)
{
	//更新生成処理関数呼び出し
	UpdateCreate();
	//もしカメラのポインタがnullptrではない場合
	if (m_pCamera != nullptr)
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
		//もしポーズを使用していない場合
		if (m_bPouse == false)
		{
			//ポーズボタンマネージャーの生成処理関数呼び出し
			CPoseButtonManager::Create();
		}
	}
}

//=============================================================================
// 初期生成処理関数
//=============================================================================
void CGameMode::InitCreate(void)
{
	//全基本生成処理関数呼び出し
	BaseCreateAll();
	//全UI生成処理関数呼び出し
	UICreateAll();
	//全マップオブジェクト生成処理関数呼び出し
	MapObjectCreateAll();
	//全キャラクター生成処理関数呼び出し
	CharacterCreateAll();
}

//=============================================================================
// 更新生成処理関数
//=============================================================================
void CGameMode::UpdateCreate(void)
{
}

//=============================================================================
// 全基本生成処理関数
//=============================================================================
void CGameMode::BaseCreateAll(void)
{
	//もしライトのポインタがnullptrの場合
	if (m_pLight == nullptr)
	{
		//ライトのメモリ確保
		m_pLight = new CLight;
		//もしライトのポインタがnullptrではない場合
		if (m_pLight != nullptr)
		{
			//ライトの初期化処理関数呼び出し
			m_pLight->Init();
		}
	}
	//もしカメラのポインタがnullptrの場合
	if (m_pCamera == nullptr)
	{
		//カメラのメモリ確保
		m_pCamera = new CCamera;
		//もしカメラのポインタがnullptrではない場合
		if (m_pCamera != nullptr)
		{
			//カメラの初期化処理関数呼び出し
			m_pCamera->Init();
		}
	}
}

//=============================================================================
// 全マップオブジェクト生成処理関数
//=============================================================================
void CGameMode::MapObjectCreateAll(void)
{
	//スカイボックスの生成
	CSkyBox::Create();
	//床の生成
	//CFloor::Create();
}

//=============================================================================
// 全キャラクター生成処理関数
//=============================================================================
void CGameMode::CharacterCreateAll(void)
{
	//もしプレイヤーのポインタがnullptrの場合
	if (m_pPlayer == nullptr)
	{
		//プレイヤーの生成
		m_pPlayer = CPlayer::Create();
	}
	//もしドラゴンのポインタがnullptrの場合
	if (m_pDragon == nullptr)
	{
		//ドラゴンの生成
		m_pDragon = CDragon::Create();
	}
}

//=============================================================================
// 全UI生成処理関数
//=============================================================================
void CGameMode::UICreateAll(void)
{
}