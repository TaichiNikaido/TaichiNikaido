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
#include "mode_game.h"
#include "Base/camera.h"
#include "Base/light.h"
#include "Character/player.h"
#include "Character/enemy.h"
#include "UI/ui_meat.h"
#include "UI/ui_daiya.h"
#include "UI/ui.h"
#include "Effect/byte_effect.h"
#include "Background/bg_tutorial.h"
#include "Effect/dust_particle.h"
#include "Map/field.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CCamera * CGameMode::m_pCamera = NULL;			//カメラのポインタ
CPlayer * CGameMode::m_pPlayer = NULL;			//プレイヤーのポインタ
CEnemy * CGameMode::m_pEnemy = NULL;			//敵のポインタ
CUi * CGameMode::m_pUi = NULL;					//UIのポインタ
CContinue * CGameMode::m_pContinue = NULL;		//コンティニューのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CGameMode::CGameMode()
{
	m_pUi		= NULL;
	m_pLight	= NULL;	//ライトのポインタ
	m_pTutorial = NULL;
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
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//もしサウンドのポインタがNULLじゃない場合
	if (pSound != NULL)
	{
		//タイトルBGMの再生
		pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_GAME);
	}
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
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGameMode::Draw(void)
{
}

//=============================================================================
// 全初期生成処理関数
//=============================================================================
void CGameMode::InitCreateAll(void)
{
	if (m_pUi == NULL)
	{
		// ダイヤUI
		m_pUi = CUi::Create(D3DXVECTOR3(DAIYA_POS_X, DAIYA_POS_Y, 0.0f),
			D3DXVECTOR3(DAIYA_SIZE, DAIYA_SIZE, 0.0f),
			CUi::UITYPE_DAIYA);

		// お肉UI
		m_pUi = CUi::Create(D3DXVECTOR3(MEAT_POS_X, MEAT_POS_Y, 0.0f),
			D3DXVECTOR3(MEAT_SIZE, MEAT_SIZE, 0.0f),
			CUi::UITYPE_MEAT);
	}
	CMeatUI::Create();
	CDaiyaUI::Create();
	//もしライトのポインタがNULLの場合
	if (m_pLight == NULL)
	{
		//ライトのメモリ確保
		m_pLight = new CLight;
	}
	//もしライトのポインタがNULLじゃない場合
	if (m_pLight != NULL)
	{
		//ライトの初期化処理関数呼び出し
		m_pLight->Init();
	}
	m_pPlayer = CPlayer::Create();
	m_pEnemy = CEnemy::Create();
	//もしカメラのポインタがNULLの場合
	if (m_pCamera == NULL)
	{
		//カメラのメモリ確保
		m_pCamera = new CCamera;
	}
	//もしカメラのポインタがNULLじゃない場合
	if (m_pCamera != NULL)
	{
		//カメラの初期化処理関数呼び出し
		m_pCamera->Init();
	}
	CField::Create();
	m_pTutorial = CTutorialBG::Create();
}

//=============================================================================
// 全更新生成処理関数
//=============================================================================
void CGameMode::UpdateCreateAll(void)
{
}