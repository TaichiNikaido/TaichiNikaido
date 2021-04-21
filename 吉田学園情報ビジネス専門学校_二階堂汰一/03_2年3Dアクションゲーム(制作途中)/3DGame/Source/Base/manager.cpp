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
#include "Mode/mode_name.h"
#include "Mode/mode_tutorial.h"
#include "Mode/mode_game.h"
#include "Mode/mode_result.h"
#include "Mode/mode_ranking.h"
#include "scene.h"
#include "scene2d.h"
#include "sound.h"
#include "input.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "Input/mouse.h"
#include "fade.h"
#include "Character/player.h"
#include "Character/enemy_dragon.h"
#include "Weapon/weapon_sword.h"
#include "Weapon/weapon_shield.h"
#include "Polygon3d/floor.h"
#include "Polygon2d/title_logo.h"
#include "Polygon2d/letter.h"
#include "Button/button_any.h"
#include "Button/button_start.h"
#include "Button/button_tutorial.h"
#include "Button/button_ranking.h"
#include "Button/button_exit.h"
#include "Button/button_quit_game.h"
#include "Button/button_controller_guid.h"
#include "Button/button_back_to_title.h"
#include "skybox.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CRenderer * CManager::m_pRenderer = nullptr;			//レンダラーのポインタ
CSound * CManager::m_pSound = nullptr;					//サウンドのポインタ
CKeyboard * CManager::m_pKeyboard = nullptr;			//キーボードのポインタ
CMouse * CManager::m_pMouse = nullptr;					//マウスのポインタ
CJoystick * CManager::m_pJoystick = nullptr;			//マネージャーのポインタ
CTutorialMode * CManager::m_pTutorialMode = nullptr;	//チュートリアルモードのポインタ
CGameMode * CManager::m_pGameMode = nullptr;			//ゲームモードのポインタ
CResultMode * CManager::m_pResultMode = nullptr;		//リザルトモードのポインタ
CRankingMode * CManager::m_pRankingMode = nullptr;		//ランキングモードのポインタ
CFade * CManager::m_pFade = nullptr;					//フェードへのポインタ
CManager::MODE  CManager::m_Mode = MODE_NONE;			//モード
bool CManager::m_bUseFade = false;						//フェードの使用状態

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
	//もしレンダラーのポインタがnullptrの場合
	if (m_pRenderer == nullptr)
	{
		//レンダラーのメモリを確保
		m_pRenderer = new  CRenderer;
		//もしレンダラーのポインタがnullptrではない場合
		if (m_pRenderer != nullptr)
		{
			//レンダラーの初期化処理関数呼び出し
			m_pRenderer->Init(hWnd, TRUE);
		}
	}
	//もしフェードのポインタがnullptrの場合
	if (m_pFade == nullptr)
	{
		//フェードの生成処理関数呼び出し
		m_pFade = CFade::Create(m_Mode);
	}
	//もしサウンドのポインタがnullptrの場合
	if (m_pSound == nullptr)
	{
		//サウンドのメモリ確保
		m_pSound = new CSound;
		//もしサウンドのポインタがnullptrではない場合
		if (m_pSound != nullptr)
		{
			//サウンドの初期化処理関数呼び出し
			m_pSound->Init(hWnd);
		}
	}
	//もしキーボードのポインタがnullptrの場合
	if (m_pKeyboard == nullptr)
	{
		//キーボードのメモリ確保
		m_pKeyboard = new CKeyboard;
		//もしキーボードのポインタがnullptrではない場合
		if (m_pKeyboard != nullptr)
		{
			//キーボードの初期化処理関数呼び出し
			m_pKeyboard->Init(hInsitance, hWnd);
		}
	}
	//もしジョイスティックのポインタがnullptrの場合
	if (m_pJoystick == nullptr)
	{
		//ジョイスティックのメモリ確保
		m_pJoystick = new CJoystick;
		//もしジョイスティックのポインタがnullptrではない場合
		if (m_pJoystick != nullptr)
		{
			//ジョイスティックの初期化処理関数呼び出し
			m_pJoystick->Init(hInsitance, hWnd);
		}
	}
	//もしマウスのポインタがnullptrの場合
	if (m_pMouse == nullptr)
	{
		//マウスのメモリ確保
		m_pMouse = new CMouse;
		//もしマウスのポインタがnullptrではない場合
		if (m_pMouse != NULL)
		{
			//マウスの初期化処理関数呼び出し
			m_pMouse->Init(hInsitance, hWnd);
		}
	}
	//全読み込み関数呼び出し
	LoadAll();
	//モードの設定
	SetMode(MODE_GAME);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CManager::Uninit(void)
{
	//シーンの全破棄処理関数呼び出し
	CScene::ReleaseAll();
	//もしサウンドのポインタがnullptrではない場合
	if (m_pSound != nullptr)
	{
		//サウンドの停止
		m_pSound->StopSound();
	}
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
	//もしレンダラーのポインタがnullptrではない場合
	if (m_pRenderer != nullptr)
	{
		//レンダラーの更新処理関数呼び出し
		m_pRenderer->Update();
	}
	//もしキーボードのポインタがnullptrではない場合
	if (m_pKeyboard != nullptr)
	{
		//キーボードの更新処理関数呼び出し
		m_pKeyboard->Update();
	}
	//もしジョイスティックのポインタがnullptrではない場合
	if (m_pJoystick != nullptr)
	{
		//ジョイスティックの更新処理関数呼び出し
		m_pJoystick->Update();
	}
	//もしマウスのポインタがnullptrではない場合
	if (m_pMouse != nullptr)
	{
		//マウスの更新処理関数呼び出し
		m_pMouse->Update();
	}
	//もしフェードされたら
	if (m_bUseFade == true)
	{
		//もしフェードのポインタがnullptrではない場合
		if (m_pFade != nullptr)
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
	//モードを設定する
	m_Mode = Mode;
	//各モードの処理
	switch (m_Mode)
	{
	case MODE_TITLE:
		//タイトルモードの生成処理関数呼び出し
		CTitleMode::Create();
		break;
	case MODE_NAME:
		//名前入力モードの生成処理関数呼び出し
		CNameMode::Create();
		break;
	case MODE_TUTORIAL:
		//チュートリアルモードの生成処理関数呼び出し
		m_pTutorialMode = CTutorialMode::Create();
		break;
	case MODE_GAME:
		//ゲームモードの生成処理関数呼び出し
		m_pGameMode = CGameMode::Create();
		break;
	case MODE_RESULT:
		//リザルトモードの生成処理関数呼び出し
		m_pResultMode = CResultMode::Create();
		break;
	case MODE_RANKING:
		//ランキングモードの生成処理関数呼び出し
		m_pRankingMode = CRankingMode::Create();
	default:
		break;
	}
}

//=============================================================================
// 全読み込み処理関数
//=============================================================================
void CManager::LoadAll(void)
{
	//プレイヤーのモデル読み込み
	CPlayer::ModelLoad();
	//剣のモデル読み込み
	CSword::ModelLoad();
	//盾のモデル読み込み
	CShield::ModelLoad();
	//ドラゴンモデル読み込み
	CDragon::ModelLoad();
	//地面のテクスチャ読み込み
	CFloor::TextureLoad();
	//何らかのボタンのテクスチャ読み込み
	CAnyButton::TextureLoad();
	//スタートボタンのテクスチャ読み込み
	CStartButton::TextureLoad();
	//チュートリアルボタンのテクスチャ読み込み
	CTutorialButton::TextureLoad();
	//ランキングボタンのテクスチャ読み込み
	CRankingButton::TextureLoad();
	//終了ボタンのテクスチャ読み込み
	CExitButton::TextureLoad();
	//ゲームに戻るボタンのテクスチャ読み込み
	CQuitGameButton::TextureLoad();
	//操作説明ボタンのテクスチャ読み込み
	CControllerGuidButton::TextureLoad();
	//タイトルに戻るボタンのテクスチャ読み込み
	CBackToTitleButton::TextureLoad();
	//タイトルロゴのテクスチャ読み込み
	CTitleLogo::TextureLoad();
	//文字のテクスチャ読み込み
	CLetter::TextureLoad();
	//スカイボックスのテクスチャ読み込み
	CSkyBox::TextureLoad();
}

//=============================================================================
// 全読み込み破棄処理関数
//=============================================================================
void CManager::UnloadAll(void)
{
	//プレイヤーのモデル破棄
	CPlayer::ModelUnload();
	//剣のモデル破棄
	CSword::ModelUnload();
	//盾のモデル破棄
	CShield::ModelUnload();
	//ドラゴンモデル破棄
	CDragon::ModelUnload();
	//地面のテクスチャ破棄
	CFloor::TextureUnload();
	//何らかのボタンのテクスチャ破棄
	CAnyButton::TextureUnload();
	//スタートボタンのテクスチャ破棄
	CStartButton::TextureUnload();
	//チュートリアルボタンのテクスチャ破棄
	CTutorialButton::TextureUnload();
	//ランキングボタンのテクスチャ破棄
	CRankingButton::TextureUnload();
	//終了ボタンのテクスチャ破棄
	CExitButton::TextureUnload();
	//ゲームに戻るボタンのテクスチャ破棄
	CQuitGameButton::TextureUnload();
	//操作説明ボタンのテクスチャ破棄
	CControllerGuidButton::TextureUnload();
	//タイトルに戻るボタンのテクスチャ破棄
	CBackToTitleButton::TextureUnload();
	//タイトルロゴのテクスチャ破棄
	CTitleLogo::TextureUnload();
	//文字のテクスチャ破棄
	CLetter::TextureUnload();
	//スカイボックスのテクスチャ破棄
	CSkyBox::TextureUnload();
}

//=============================================================================
// 全破棄処理関数
//=============================================================================
void CManager::DeleteAll(void)
{
	//もしマウスのポインタがnullptrではない場合
	if (m_pMouse != nullptr)
	{
		//マウスの終了処理関数呼び出し
		m_pMouse->Uninit();
		//マウスのメモリ破棄
		delete m_pMouse;
		//マウスのポインタをnullptrにする
		m_pMouse = nullptr;
	}
	//もしジョイスティックのポインタがnullptrではない場合
	if (m_pJoystick != nullptr)
	{
		//ジョイスティックの終了処理関数呼び出し
		m_pJoystick->Uninit();
		//ジョイスティックのメモリ破棄
		delete m_pJoystick;
		//ジョイスティックのポインタをnullptrにする
		m_pJoystick = nullptr;
	}
	//もしキーボードのポインタがnullptrではない場合
	if (m_pKeyboard != nullptr)
	{
		//キーボードの終了処理関数呼び出し
		m_pKeyboard->Uninit();
		//キーボードのメモリ破棄
		delete m_pKeyboard;
		//キーボードのポインタをnullptrにする
		m_pKeyboard = nullptr;
	}
	//もしサウンドのポインタがnullptrではない場合
	if (m_pSound != nullptr)
	{
		//サウンドの終了処理関数呼び出し
		m_pSound->Uninit();
		//サウンドのメモリ破棄
		delete m_pSound;
		//サウンドのポインタをnullptrにする
		m_pSound = nullptr;
	}
	//もしレンダラーのポインタがnullptrではない場合
	if (m_pRenderer != nullptr)
	{
		//レンダラーの終了処理関数呼び出し
		m_pRenderer->Uninit();
		//レンダラーのメモリ破棄
		delete m_pRenderer;
		//レンダラーのポインタをnullptrにする
		m_pRenderer = nullptr;
	}
	//もしフェードのポインタがnullptrではない場合
	if (m_pFade != nullptr)
	{
		//フェードの終了処理関数呼び出し
		m_pFade->Uninit();
		//フェードのメモリ破棄
		delete m_pFade;
		//フェードのポインタをnullptrにする
		m_pFade = nullptr;
	}
}