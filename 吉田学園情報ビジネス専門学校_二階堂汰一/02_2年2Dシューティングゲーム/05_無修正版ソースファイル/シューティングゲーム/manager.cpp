//=============================================================================
//
// manager処理 [manager.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "keyboard.h"
#include "player.h"
#include "wormhole.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
#include "background.h"
#include "enemy.h"
#include "dragon.h"
#include "number.h"
#include "score.h"
#include "item.h"
#include "own.h"
#include "ownui.h"
#include "bomb.h"
#include "effect.h"
#include "joystick.h"
#include "title.h"
#include "name.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "bombtexture.h"
#include "fade.h"
#include "text.h"
#include "warning.h"
#include "flame.h"
#include "tutorial.h"

CRenderer * CManager::m_pRenderer = NULL;
CInputKeyboard * CManager::m_pInputKeyboard = NULL;
CInputJoystick * CManager::m_pInputJoystick = NULL;
CSound * CManager::m_pSound = NULL;
CTitle * CManager::m_pTitle = NULL;
CTutorial * CManager::m_pTutorial = NULL;
CName * CManager::m_pName = NULL;
CGame * CManager::m_pGame = NULL;
CResult * CManager::m_pResult = NULL;
CRanking * CManager::m_pRanking = NULL;
CFade * CManager::m_pFade = NULL;
CText * CManager::m_pText = NULL;
CManager::MODE CManager::m_mode = MODE_NONE;
bool CManager::m_bUseFade = false;
bool CManager::m_bPause = false;
//*****************************************************************************
// グローバル変数:
//*****************************************************************************

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
// 初期化関数
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow)
{
	CEnemy::TYPE type;
	type = CEnemy::TYPE_NONE;

	//レンダラーの生成
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new  CRenderer;
	}
	//初期化処理
	m_pRenderer->Init(hWnd, TRUE);

	//入力の生成
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyboard;
	}

	//キーボードの初期化
	m_pInputKeyboard->InitInput(hInsitance, hWnd);

	//ジョイスティックの生成
	if (m_pInputJoystick == NULL)
	{
		m_pInputJoystick = new CInputJoystick;
	}

	//ジョイスティックの初期化
	m_pInputJoystick->InitInput(hInsitance, hWnd);

	//サウンドの生成
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}

	//サウンドの初期化
	m_pSound->Init(hWnd);

	//テキストを生成
	m_pText = CText::Create(D3DXVECTOR3(FIELD_WIDTH, FIELD_HEIGHT, 0.0f), FIELD_WIDTH, FIELD_HEIGHT);

	//プレイヤーのテクスチャロード
	CPlayer::Load();

	//敵のロード
	CEnemy::Load();

	//ドラゴンのロード
	CDragon::Load();

	//弾のテクスチャロード
	CBullet::Load();

	//爆発のテクスチャロード
	CExplosion::Load();

	//背景のロード
	CBg::Load();

	//アイテムのロード
	CItem::Load();

	//番号のロード
	CNumber::Load();

	//自機のロード
	COwn::Load();

	//ワームホールのロード
	CWormhole::Load();

	//爆弾のロード
	CBomb::Load();

	//エフェクトのロード
	CEffect::Load();

	//タイトルのロード
	CTitle::Load();

	//名前入力画面のロード
	CName::Load();

	//リザルトのロード
	CResult::Load();

	//ランキングのロード
	CRanking::Load();

	//爆弾のテクスチャロード
	CBombTexture::Load();

	//危険地帯のテクスチャのロード
	CWarning::Load();

	CFlame::Load();

	CTutorial::Load();
	
	SetMode(MODE_TITLE);

	//フェードの生成
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, m_mode);

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();

	//ワームホールのアンロード
	CWormhole::Unload();

	//自機のアンロード
	COwn::Unload();

	//番号のアンロード
	CNumber::Unload();

	//名前入力画面のアンロード
	CName::Unload();

	//アイテムのアンロード
	CItem::Unload();

	//背景のテクスチャアンロード
	CBg::Unload();

	//爆発のテクスチャアンロード
	CExplosion::Unload();

	//弾のテクスチャアンロード
	CBullet::Unload();

	//敵のアンロード
	CEnemy::Unload();

	//ドラゴンのアンロード
	CDragon::Unload();

	//プレイヤーのテクスチャアンロード
	CPlayer::Unload();

	//爆弾のアンロード
	CBomb::Unload();

	//エフェクトのアンロード
	CEffect::Unload();

	//タイトルのアンロード
	CTitle::Unload();

	//リザルトのアンロード
	CResult::Unload();

	//ランキングのアンロード
	CRanking::Unload();

	//爆弾のテクスチャアンロード
	CBombTexture::Unload();

	//危険地帯のテクスチャのアンロード
	CWarning::Unload();

	CFlame::Unload();

	CTutorial::Unload();

	//キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->UninitInput();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	//ジョイスティックの破棄
	if (m_pInputJoystick != NULL)
	{
		m_pInputJoystick->UninitInput();
		delete m_pInputJoystick;
		m_pInputJoystick = NULL;
	}
	//レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	//サウンドの停止
	m_pSound->StopSound();

	//サウンドの破棄
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	//フェードの破棄
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}

	//テキストの破棄
	if (m_pText != NULL)
	{
		m_pText->Uninit();
		delete m_pText;
		m_pText = NULL;
	}
}

//=============================================================================
// 更新関数
//=============================================================================
void CManager::Update(void)
{
	//キーボードの更新
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->UpdateInput();
	}

	//キーボードの更新
	if (m_pInputJoystick != NULL)
	{
		m_pInputJoystick->UpdateInput();
	}

	//描画の更新
	if (m_pRenderer != NULL)
	{
 		m_pRenderer->Update();
	}

	//フェード更新
	if (m_bUseFade == true)
	{
		if (m_pFade != NULL)
		{
			m_pFade->Update();
		}
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw(); // 描画処理
}

void CManager::SetMode(MODE mode)
{
	CScene::ReleaseAll();
	m_mode = mode;
	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = CTitle::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 ,0.0f), SCREEN_HEIGHT, SCREEN_WIDTH);
		break;
	case MODE_TUTORIAL:
		m_pTutorial = CTutorial::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH);
		break;
	case MODE_NAME:
		m_pName = CName::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH);
		break;
	case MODE_GAME:
		m_pGame = CGame::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH);
		break;
	case MODE_RESULT:
		m_pResult = CResult::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH);
		break;
	case MODE_RANKING:
		m_pRanking = CRanking::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH);
		break;
	default:
		break;
	}
	m_pInputKeyboard->UpdateInput();
	m_pInputJoystick->UpdateInput();
}

CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

CInputKeyboard * CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

CInputJoystick * CManager::GetInputJoystick(void)
{
	return m_pInputJoystick;
}

CSound * CManager::GetSound(void)
{
	return m_pSound;
}

CFade * CManager::GetFade(void)
{
	return m_pFade;
}

//----------------------------------------------------
//フェードの開始
//----------------------------------------------------
void CManager::StartFade(MODE mode)
{
	m_mode = mode;
	m_bUseFade = true;
	CText::IsDrawText(false);
}
//----------------------------------------------------
//フェードの更新終了
//----------------------------------------------------
void CManager::StopFade(void)
{
	m_bUseFade = false;
	CText::IsDrawText(true);
}
CScene2d * CManager::GetScene2d(void)
{
	return m_pScene2d;
}
