//=============================================================================
//
// マネージャー [manager.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Mode/mode_title.h"
#include "Mode/mode_tutorial.h"
#include "Mode/mode_game.h"
#include "Mode/mode_result.h"
#include "scene.h"
#include "scene2d.h"
#include "sound.h"
#include "input.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "fade.h"
#include "Character/player.h"
#include "Character/enemy.h"
#include "Effect/effect.h"
#include "UI/number.h"
#include "UI/ui.h"
#include "Button/button_continue.h"
#include "Button/button_not_continue.h"
#include "2DPolygon/continue_logo.h"
#include "Background/bg_continue.h"
#include "Background/bg_title.h"
#include "Background/bg_result.h"
#include "2DPolygon/title_logo.h"
#include "Effect/particle.h"
#include "Background/bg_tutorial.h"
#include "Map/wood.h"
#include "Map/tree.h"
#include "Map/tile.h"
#include "Item/dia.h"
#include "Item/meat.h"
#include "Map/needle.h"
#include "3DPolygon/shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CRenderer * CManager::m_pRenderer = NULL;		//レンダラーへのポインタ
CSound * CManager::m_pSound = NULL;				//サウンドへのポインタ
CKeyboard * CManager::m_pKeyboard = NULL;		//キーボードへのポインタ
CJoystick * CManager::m_pJoystick = NULL;		//マネージャーへのポインタ
CGameMode * CManager::m_pGameMode = NULL;		//ゲームモードへのポインタ
CResultMode * CManager::m_pResultMode = NULL;	//リザルトモードへのポインタ
CFade * CManager::m_pFade = NULL;				//フェードへのポインタ
CManager::MODE  CManager::m_Mode = MODE_NONE;	//モード
bool CManager::m_bUseFade = false;				//フェードしてるか

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow)
{
	//もしレンダラーのポインタがNULLの場合
	if (m_pRenderer == NULL)
	{
		//レンダラーのメモリを確保
		m_pRenderer = new  CRenderer;
	}
	//レンダラーの初期化処理関数呼び出し
	m_pRenderer->Init(hWnd, TRUE);
	//もしフェードのポインタがNULLの場合
	if (m_pFade == NULL)
	{
		//フェードの生成処理関数呼び出し
		m_pFade = CFade::Create(m_Mode);
	}
	//もしサウンドのポインタがNULLの場合
	if (m_pSound == NULL)
	{
		//サウンドのメモリ確保
		m_pSound = new CSound;
	}
	//サウンドの初期化処理関数呼び出し
	m_pSound->Init(hWnd);
	//もしキーボードのポインタがNULLの場合
	if (m_pKeyboard == NULL)
	{
		//キーボードのメモリ確保
		m_pKeyboard = new CKeyboard;
	}
	//キーボードの初期化処理関数呼び出し
	m_pKeyboard->Init(hInsitance, hWnd);
	//もしジョイスティックのポインタがNULLの場合
	if (m_pJoystick == NULL)
	{
		//ジョイスティックのメモリ確保
		m_pJoystick = new CJoystick;
	}
	//ジョイスティックの初期化処理関数呼び出し
	m_pJoystick->Init(hInsitance, hWnd);
	//全読み込み関数呼び出し
	LoadAll();
	//モードの設定
	SetMode(MODE_TITLE);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CManager::Uninit(void)
{
	//シーンの全破棄処理関数呼び出し
	CScene::ReleaseAll();
	//サウンドの停止
	m_pSound->StopSound();
	//全破棄関数呼び出し
	DeleteAll();
	//全読み込み破棄関数呼び出し
	UnloadAll();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CManager::Update(void)
{
	//もしレンダラーのポインタがNULLじゃない場合
	if (m_pRenderer != NULL)
	{
		//レンダラーの更新処理関数呼び出し
		m_pRenderer->Update();
	}
	//もしキーボードのポインタがNULLじゃない場合
	if (m_pKeyboard != NULL)
	{
		//キーボードの更新処理関数呼び出し
		m_pKeyboard->Update();
	}
	//もしジョイスティックのポインタがNULLじゃない場合
	if (m_pJoystick != NULL)
	{
		//ジョイスティックの更新処理関数呼び出し
		m_pJoystick->Update();
	}
	//もしフェードされたら
	if (m_bUseFade == true)
	{
		//もしフェードのポインタがNULLじゃない場合
		if (m_pFade != NULL)
		{
			//フェードの更新処理関数呼び出し
			m_pFade->Update();
		}
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CManager::Draw(void)
{
	//レンダラーの描画処理関数呼び出し
	m_pRenderer->Draw();
}

//=============================================================================
// フェード開始処理関数
//=============================================================================
void CManager::StartFade(MODE mode)
{
	//モードを設定する
	m_Mode = mode;
	//フェードをする
	m_bUseFade = true;
}

//=============================================================================
// フェード停止処理関数
//=============================================================================
void CManager::StopFade(void)
{
	//フェードをやめる
	m_bUseFade = false;
}

//=============================================================================
// モード設定関数
//=============================================================================
void CManager::SetMode(MODE Mode)
{
	//シーンの全破棄処理関数呼び出し
	CScene::ReleaseAll();
	//サウンドを停止する
	m_pSound->StopSound();
	//モードを設定する
	m_Mode = Mode;
	switch (m_Mode)
	{
	case MODE_TITLE:
		//タイトルモードの生成処理関数呼び出し
		CTitleMode::Create();
		break;
	case MODE_TUTORIAL:
		//チュートリアルモードの生成処理関数呼び出し
		CTutorialMode::Create();
		break;
	case MODE_GAME:
		//ゲームモードの生成処理関数呼び出し
		m_pGameMode = CGameMode::Create();
		break;
	case MODE_RESULT:
		//リザルトモードの生成処理関数呼び出し
		m_pResultMode = CResultMode::Create();
		break;
	default:
		break;
	}
}

//=============================================================================
// 全読み込み処理関数
//=============================================================================
void CManager::LoadAll(void)
{
	CPlayer::Load();
	CEnemy::Load();
	CEffect::Load();
	CParticle::Load();
	CUi::Load();
	CNumber::Load();
	CContinueButton::TextureLoad();
	CNotContinueButton::TextureLoad();
	CContinueLogo::TextureLoad();
	CContinueBG::TextureLoad();
	CTitleBG::TextureLoad();
	CResultBG::TextureLoad();
	CTitlelogo::Load();
	CTutorialBG::TextureLoad();
	CTree::Load();
	CWood::Load();
	CTile::Load();
	CDia::Load();
	CMeat::Load();
	CNeedle::Load();
	CShadow::TextureLoad();
}

//=============================================================================
// 全読み込み破棄処理関数
//=============================================================================
void CManager::UnloadAll(void)
{
	CPlayer::Unload();
	CEnemy::Unload();
	CEffect::Unload();
	CParticle::Unload();
	CUi::Unload();
	CNumber::Unload();
	CContinueButton::TextureUnload();
	CNotContinueButton::TextureUnload();
	CContinueLogo::TextureUnload();
	CContinueBG::TextureUnload();
	CTitleBG::TextureUnload();
	CResultBG::TextureUnload();
	CTitlelogo::Unload();
	CTutorialBG::TextureUnload();
	CWood::Unload();
	CTree::Unload();
	CTile::Unload();
	CDia::Unload();
	CMeat::Unload();
	CNeedle::Unload();
	CShadow::TextureUnload();
}

//=============================================================================
// 全破棄処理関数
//=============================================================================
void CManager::DeleteAll(void)
{
	//もしジョイスティックのポインタがNULLじゃない場合
	if (m_pJoystick != NULL)
	{
		//ジョイスティックの終了処理関数呼び出し
		m_pJoystick->Uninit();
		//ジョイスティックのメモリ破棄
		delete m_pJoystick;
		//ジョイスティックのポインタをNULLにする
		m_pJoystick = NULL;
	}
	//もしキーボードのポインタがNULLじゃない場合
	if (m_pKeyboard != NULL)
	{
		//キーボードの終了処理関数呼び出し
		m_pKeyboard->Uninit();
		//キーボードのメモリ破棄
		delete m_pKeyboard;
		//キーボードのポインタをNULLにする
		m_pKeyboard = NULL;
	}
	//もしサウンドのポインタがNULLじゃない場合
	if (m_pSound != NULL)
	{
		//サウンドの終了処理関数呼び出し
		m_pSound->Uninit();
		//サウンドのメモリ破棄
		delete m_pSound;
		//サウンドのポインタをNULLにする
		m_pSound = NULL;
	}
	//もしレンダラーのポインタがNULLじゃない場合
	if (m_pRenderer != NULL)
	{
		//レンダラーの終了処理関数呼び出し
		m_pRenderer->Uninit();
		//レンダラーのメモリ破棄
		delete m_pRenderer;
		//レンダラーのポインタをNULLにする
		m_pRenderer = NULL;
	}
	//もしフェードのポインタがNULLじゃない場合
	if (m_pFade != NULL)
	{
		//フェードの終了処理関数呼び出し
		m_pFade->Uninit();
		//フェードのメモリ破棄
		delete m_pFade;
		//フェードのポインタをNULLにする
		m_pFade = NULL;
	}
}
