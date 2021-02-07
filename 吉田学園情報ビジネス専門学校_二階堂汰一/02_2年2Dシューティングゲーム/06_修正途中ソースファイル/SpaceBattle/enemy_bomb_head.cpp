//=============================================================================
//
// 爆弾の敵の胴体 [enemy_bomb_body.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "mode_game.h"
#include "renderer.h"
#include "scene2d.h"
#include "enemy_bomb_head.h"
#include "player.h"
#include "bullet_direction.h"
#include "bullet.h"
#include "explosion_death.h"
#include "item_bomb.h"
#include "enemy_bomb_body.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/bombhead.png")
#define SIZE (D3DXVECTOR3(100.0f,150.0f,0.0f))
#define LIFE (12)
#define SPEED (D3DXVECTOR3(5.0f,0.0f,0.0f))
#define SCORE (10000)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyBombHead::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyBombHead::CEnemyBombHead(int nPriority) : CEnemy(nPriority)
{
	m_fRd = 0.0f;
	m_fRdScale = 0.1f;
	memset(m_pBombBody, NULL, sizeof(m_pBombBody));
	m_bCreateBody = true;
	m_nCreateCount = 0;
	m_nCreateBodyCount = 0;
	m_InitPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nBombLife = LIFE;
	m_bDeath = false;
	m_bDeathAll = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyBombHead::~CEnemyBombHead()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CEnemyBombHead::TextureLoad(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE,						// ファイルの名前
		&m_pTexture);					// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CEnemyBombHead::TextureUnload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CEnemyBombHead * CEnemyBombHead::Create(D3DXVECTOR3 Position)
{
	CEnemyBombHead * pEnemyBombHead;
	pEnemyBombHead = new CEnemyBombHead;
	pEnemyBombHead->SetPosition(Position);
	pEnemyBombHead->m_InitPos = Position;
	pEnemyBombHead->Init();
	return pEnemyBombHead;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEnemyBombHead::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//敵の初期化処理関数呼び出し
	CEnemy::Init();
	//サイズの初期設定
	SetSize(SIZE);
	//体力の初期設定
	SetLife(LIFE);
	//移動量の初期設定
	SetMove(SPEED);
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	//状態を移動中
	SetState(STATE_MOVE);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CEnemyBombHead::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CEnemyBombHead::Update(void)
{
	if (m_bCreateBody == true)
	{
		if (m_nCreateCount % 10 == 0)
		{
			m_pBombBody[m_nCreateBodyCount] = CEnemyBombBody::Create(m_InitPos,this);
			m_nCreateBodyCount++;

			if (m_nCreateBodyCount >= MAX_BOMB_BODY)
			{
				m_bCreateBody = false;
			}
		}
		m_nCreateCount++;
	}
	else
	{
		m_fRd += m_fRdScale;
		if (m_fRd >= 360.0f)//一周したらリセット
		{
			m_fRd = 0;
		}
		//移動量のセット
		SetMove(D3DXVECTOR3(GetMove().x, float(5 * sin(m_fRd)), GetMove().z));
		//画面端についたら逆方向に
		if (GetPosition().x < FIELD_WIDTH_MIN + 10.0f)
		{
			SetMove(D3DXVECTOR3(GetMove().x * -1.0f, GetMove().y, GetMove().z));
			m_fRdScale = m_fRdScale * -1.0f;
		}
		if (GetPosition().x > FIELD_WIDTH - 10.0f)
		{
			SetMove(D3DXVECTOR3(GetMove().x * -1.0f, GetMove().y, GetMove().z));
			m_fRdScale = m_fRdScale * -1.0f;
		}
		//進行方向に向きを合わせる
		SetRotation(D3DXVECTOR3(GetRotation().x, GetRotation().y, atan2f((GetPosition().x + GetMove().x) - GetPosition().x, (GetPosition().y + GetMove().y) - GetPosition().y)));
		//敵の更新処理関数呼び出し
		CEnemy::Update();
		//もしライフが0になったら
		if (GetLife() <= 0)
		{
			//死亡処理関数呼び出し
			Death();
		}
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CEnemyBombHead::Draw(void)
{
	//敵の描画処理関数呼び出し
	CEnemy::Draw();
}
//=============================================================================
// 死亡処理関数
//=============================================================================
void CEnemyBombHead::DeathAll(void)
{
	if (m_bDeathAll == false && m_bDeath == false)
	{
		m_bDeathAll = true;
		for (int nCount = 0; nCount < MAX_BOMB_BODY; nCount++)
		{
			if (m_pBombBody[nCount] != NULL)
			{
				//爆発エフェクトの生成
				CExplosionDeath::Create(m_pBombBody[nCount]->GetPosition());
				m_pBombBody[nCount]->Uninit();
			}
		}
		Death();
	}
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CEnemyBombHead::Death(void)
{
		//プレイヤーを取得する
		CPlayer * pPlayer = CGameMode::GetPlayer();
		//サウンドの取得
		CSound * pSound = CManager::GetSound();
		if (pPlayer != NULL)
		{
			//爆発エフェクトの生成
			CExplosionDeath::Create(GetPosition());
			//爆発音の再生
			pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
			//爆弾アイテムの生成
			CItemBomb::Create(GetPosition());
			//プレイヤーのスコアを加算する
			pPlayer->AddScore(SCORE);
			DeathAll();
			m_bDeath = true;
			m_bDeathAll = true;
		}
		//終了処理関数呼び出し
		Uninit();
}