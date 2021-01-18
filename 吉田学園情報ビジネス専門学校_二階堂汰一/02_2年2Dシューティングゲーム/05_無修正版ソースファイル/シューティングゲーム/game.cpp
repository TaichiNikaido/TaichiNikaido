//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "game.h"
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
#include "result.h"
#include "boss.h"
#include "bombui.h"
#include "flame.h"

CScore * CGame::m_pScore = NULL;
COwnUI * CGame::m_pOwnUI = NULL;
CBombUI * CGame::m_pBombUI = NULL;
CPlayer * CGame::m_pPlayer = NULL;
CDragon * CGame::m_pDragon = NULL;
int CGame::m_nInputSaveCount = 0;
int CGame::m_nInputLoadCount = 0;
//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame(int nPriority) : CScene(nPriority)
{
	m_pPlayer = NULL;
	m_pScene2d = NULL;
	m_pEnemy = NULL;
	m_pWormhole = NULL;
	memset(m_Location, 0, sizeof(m_Location));
	m_nCount = 0;
	m_nInputSaveCount = 0;
	m_nInputLoadCount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{
}

CGame * CGame::Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	CGame * pGame;
	pGame = new CGame;
	pGame->Init(pos, SizeHeight, SizeWidth);
	return pGame;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	CEnemy::TYPE type;
	type = CEnemy::TYPE_NONE;
	//サウンドの取得
	CSound * pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL_BGM01);

	//背景の生成
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);

	CFlame::Create(D3DXVECTOR3(400 / 2, SCREEN_HEIGHT / 2, 0.0f), 400, SCREEN_HEIGHT);
	CFlame::Create(D3DXVECTOR3(SCREEN_WIDTH - (400 / 2), SCREEN_HEIGHT / 2, 0.0f), 400, SCREEN_HEIGHT);

	//ワームホールの生成
	//m_pWormhole = CWormhole::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f), WORMHOLEEFFECT_TEXTURE_SIZE, WORMHOLEEFFECT_TEXTURE_SIZE, CWormhole::TYPE_DRAGON,CWormhole::TEX_EFFECT, D3DXCOLOR(255.0f, 0.0f, 0.0f, 1.0f));
	//m_pWormhole = CWormhole::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0.0f), WORMHOLE_TEXTURE_SIZE, WORMHOLE_TEXTURE_SIZE, CWormhole::TYPE_DRAGON, CWormhole::TEX_HOLE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	

	//ドラゴンの生成
	//CDragon::Create(D3DXVECTOR3(FIELD_WIDTH/2,FIELD_HEIGHT / 2,0.0f), DRAGON_SIZE_WIDTH, DRAGON_SIZE_HEIGHT, DRAGON_MAX_HP);

	//敵の生成
	//CEnemy::Create(D3DXVECTOR3(300.0f, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_ENEMY_MAX_HP);
	//CEnemy::Create(D3DXVECTOR3(400.0f, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_ENEMY_MAX_HP);
	//CEnemy::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_ENEMY_MAX_HP);

	//CEnemy::Create(D3DXVECTOR3(600.0f, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_ENEMY_MAX_HP);
	//CEnemy::Create(D3DXVECTOR3(700.0f, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_ENEMY_MAX_HP);
	//CEnemy::Create(D3DXVECTOR3(800.0f, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_ENEMY_MAX_HP);

	//CEnemy::Create(D3DXVECTOR3(600.0f, 0.0f, 0.0f), EYE_SIZE + 40, EYE_SIZE + 40, CEnemy::TYPE_FLOWER, EASY_ENEMY_MAX_HP);
	//CEnemy::Create(D3DXVECTOR3(700.0f, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_MIDDLE, EASY_ENEMY_MAX_HP);
	//CEnemy::Create(D3DXVECTOR3(FIELD_HEIGHT / 2, 0.0f, 0.0f), EYE_SIZE * 2, EYE_SIZE * 2, CEnemy::TYPE_FLOWER, NORMAL_ENEMY_MAX_HP);

	//ボスの生成
	//CBoss::Create(D3DXVECTOR3(FIELD_WIDTH / 2, FIELD_HEIGHT / 2, 0.0f), 0, 0);

	//アイテムの生成
	//CItem::Create(D3DXVECTOR3(200, -100, 0.0f), ITEM_SIZE, ITEM_SIZE, CItem::TYPE_LEVEL);
	//CItem::Create(D3DXVECTOR3(200, 0, 0.0f), ITEM_SIZE, ITEM_SIZE, CItem::TYPE_OWN);
	//CItem::Create(D3DXVECTOR3(200, 100, 0.0f), ITEM_SIZE, ITEM_SIZE, CItem::TYPE_BOMB);
	//CItem::Create(D3DXVECTOR3(200, 200, 0.0f), ITEM_SIZE, ITEM_SIZE, CItem::TYPE_LEVEL);

	//スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(FIELD_WIDTH - SCORE_SIZE_WIDTH, SCORE_SIZE_HEIGHT, 0.0f), SCORE_SIZE_WIDTH * 1.5f, SCORE_SIZE_HEIGHT * 1.5f);
	m_pScore->SetScore(0);

	//自機のUIの生成
	m_pOwnUI = COwnUI::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 50.0f, OWNUI_SIZE_HEIGHT, 0.0f), OWNUI_SIZE_WIDTH * 1.5f, OWNUI_SIZE_HEIGHT * 1.5f);
	m_pOwnUI->SetOwnUI(PLAYER_INIT_OWN);

	//爆弾のUIの生成
	m_pBombUI = CBombUI::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 50.0f, BOMBUI_SIZE_HEIGHT + 50.0f, 0.0f), BOMBUI_SIZE_WIDTH * 1.5f, BOMBUI_SIZE_HEIGHT * 1.5f);
	m_pBombUI->SetBombUI(PLAYER_MIN_BOMB);

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 180, 0.0f), PLAYER_SIZE, PLAYER_SIZE, PLAYER_INIT_OWN);

	m_nCount = 0;
	m_nInputSaveCount = 0;
	m_nInputLoadCount = 0;

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CGame::Uninit(void)
{
	CScene::Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CGame::Update(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//ジョイスティックの取得
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
	DIJOYSTATE js;

	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	//もしPKEYかJOYSTICKのSTARTが押されたとき
	if (pInputKeyboard->GetKeyboardTrigger(DIK_P) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(11))
	{
		CManager::SetbPause(true);
	}

	//目
	if (m_nCount == 50)
	{
		for (int nCount = 0; nCount < 4; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 1.5f + 200.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		}
	}

	//目
	if (m_nCount == 350)
	{
		for (int nCount = 0; nCount < 5; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 1.5f + 150.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		}
	}

	//蜘蛛
	if (m_nCount == 750)
	{
		//CItem::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 1.5f + float(FIELD_WIDTH / 4), 0.0f, 0.0f), ITEM_SIZE, ITEM_SIZE, CItem::TYPE_BOMB);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f), SPIDER_SIZE, SPIDER_SIZE, CEnemy::TYPE_SPIDER, EASY_SPIDER_MAX_HP);
	}

	if (m_nCount == 950)
	{
		CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 10.0f, 100.0f, 0.0f), EYE_SIZE * 2, EYE_SIZE * 3, CEnemy::TYPE_BOMBHEAD, EASY_SPIDER_MAX_HP);
	}

	if (m_nCount % 10 == 0 && m_nCount > 958 && m_nCount < 1100)
	{
		CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 10.0f, 100.0f, 0.0f), EYE_SIZE * 2, EYE_SIZE * 3, CEnemy::TYPE_BOMBBODY, EASY_SPIDER_MAX_HP);
	}

	//花
	if (m_nCount == 1050)
	{
		for (int nCount = 0; nCount <2; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 1.5f +100.0f + 400.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE2, EASY_EYE_MAX_HP);
		}
			//CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH / 2, 0.0f, 0.0f), FLOWER_SIZE, FLOWER_SIZE, CEnemy::TYPE_FLOWER, EASY_FLOWER_MAX_HP);
	}

	//目
	if (m_nCount == 1350)
	{
		for (int nCount = 0; nCount < 4; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		}
	}

	//目
	if (m_nCount == 1550)
	{
		//CItem::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 700.0f, 0.0f, 0.0f), ITEM_SIZE, ITEM_SIZE, CItem::TYPE_BOMB);
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(100.0f + 200.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		}
	}

	//花
	if (m_nCount == 1900)
	{
		for (int nCount = 0; nCount < 3; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 700.0f + 200.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		}
		CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 2.0f + FIELD_WIDTH / 2, 0.0f, 0.0f), FLOWER_SIZE, FLOWER_SIZE, CEnemy::TYPE_FLOWER, EASY_FLOWER_MAX_HP);
	}

	//花
	if (m_nCount == 2200)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		}
		CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN* 2.0f + 700, 0.0f, 0.0f), FLOWER_SIZE, FLOWER_SIZE, CEnemy::TYPE_FLOWER, EASY_FLOWER_MAX_HP);
	}

	//蜘蛛
	if (m_nCount == 2500)
	{
		//CItem::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 300.0f, 0.0f, 0.0f), ITEM_SIZE, ITEM_SIZE, CItem::TYPE_BOMB);
		//for (int nCount = 0; nCount < 6; nCount++)
		//{
		//	CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		//}
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f), SPIDER_SIZE, SPIDER_SIZE, CEnemy::TYPE_SPIDER, EASY_SPIDER_MAX_HP + 100);
	}

	if (m_nCount == 2700)
	{
		CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 10.0f, 100.0f, 0.0f), EYE_SIZE * 2, EYE_SIZE * 3, CEnemy::TYPE_BOMBHEAD, EASY_SPIDER_MAX_HP);
	}

	if (m_nCount % 10 == 0 && m_nCount > 2708 && m_nCount < 2800)
	{
		CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 10.0f, 100.0f, 0.0f), EYE_SIZE * 2, EYE_SIZE * 3, CEnemy::TYPE_BOMBBODY, EASY_SPIDER_MAX_HP);
	}

	//目
	if (m_nCount == 2900)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		}
	}

	//花
	if (m_nCount == 3200)
	{
		for (int nCount = 0; nCount < 3; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN* 2.0f + 100.0f + 200.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		}
		CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN+ 2.0f + FIELD_WIDTH / 4, 0.0f, 0.0f), FLOWER_SIZE, FLOWER_SIZE, CEnemy::TYPE_FLOWER, EASY_FLOWER_MAX_HP);
	}

	//目
	if (m_nCount == 3450)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		}
	}
	//花
	if (m_nCount == 3700)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		}
		for (int nCount = 0; nCount <2; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN * 1.5f + 100.0f + 400.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE2, EASY_EYE_MAX_HP);
		}
	}

	//ワームホール
	if (m_nCount == 4200)
	{
		pSound->StopSound();
		//ワームホールの生成
		CWormhole::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, FIELD_HEIGHT / 4, 0.0f), WORMHOLEEFFECT_TEXTURE_SIZE, WORMHOLEEFFECT_TEXTURE_SIZE, CWormhole::TYPE_DRAGON, CWormhole::TEX_EFFECT, D3DXCOLOR(255.0f, 0.0f, 0.0f, 1.0f));
		CWormhole::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, FIELD_HEIGHT / 4, 0.0f), WORMHOLE_TEXTURE_SIZE, WORMHOLE_TEXTURE_SIZE, CWormhole::TYPE_DRAGON, CWormhole::TEX_HOLE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}

	//目
	if (m_nCount == 4600)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		}
	}

	//目
	if (m_nCount == 4800)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		}
	}

	if (m_nCount == 5000)
	{
		CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 10.0f, 100.0f, 0.0f), EYE_SIZE * 2, EYE_SIZE * 3, CEnemy::TYPE_BOMBHEAD, EASY_SPIDER_MAX_HP);
	}

	if (m_nCount % 10 == 0 && m_nCount > 5008 && m_nCount < 5100)
	{
		CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 10.0f, 100.0f, 0.0f), EYE_SIZE * 2, EYE_SIZE * 3, CEnemy::TYPE_BOMBBODY, EASY_SPIDER_MAX_HP);
	}

	//目
	if (m_nCount == 5200)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		}
	}

	//目
	if (m_nCount == 5500)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		}
	}

	//目
	if (m_nCount == 6000)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			CEnemy::Create(D3DXVECTOR3(FIELD_WIDTH_MIN + 100.0f + 200.0f * nCount, 0.0f, 0.0f), EYE_SIZE, EYE_SIZE, CEnemy::TYPE_EYE, EASY_EYE_MAX_HP);
		}
	}
		m_nCount++;
		m_nInputSaveCount++;
		m_nInputLoadCount++;
}

//=============================================================================
// 描画関数
//=============================================================================
void CGame::Draw(void)
{
}

CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}

CEnemy * CGame::GetEnemy(void)
{
	return m_pEnemy;
}

CWormhole * CGame::GetWormhole(void)
{
	return m_pWormhole;
}

CScene2d * CGame::GetScene2d(void)
{
	return m_pScene2d;
}