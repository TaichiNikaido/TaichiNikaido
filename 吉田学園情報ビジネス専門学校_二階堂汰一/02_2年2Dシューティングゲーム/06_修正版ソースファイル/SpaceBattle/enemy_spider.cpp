//=============================================================================
//
// 蜘蛛 [enemy_spider.cpp]
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
#include "mode_game.h"
#include "renderer.h"
#include "scene2d.h"
#include "enemy_spider.h"
#include "player.h"
#include "bullet.h"
#include "bullet_n-way.h"
#include "item_levelup.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/spider.png")
#define SPEED (D3DXVECTOR3(0.0f,5.0f,0.0f))
#define RATE_MOVE (0.03f)
#define SIZE (D3DXVECTOR3(150.0f,150.0f,0.0f))
#define LIFE (12)
#define SHOT_SPEED (D3DXVECTOR3(cosf(D3DXToRadian(nCnt * (360 / 30) + 40.0f))*5.5f, sinf(D3DXToRadian(nCnt * (360 / 30) + 40.0f))*5.5f, 0.0f))
#define SHOT_TIME (50)
#define SHOT_INTERVAL (20)
#define TARGET_POINT (float(rand() % (FIELD_HEIGHT / 6) + 100))
#define STAY_TIME (500)
#define RETURN_SPEED ((D3DXVECTOR3(0.0f,-7.0f,0.0f)))
#define SCORE (100000)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemySpider::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemySpider::CEnemySpider(int nPriority)
{
	m_nCountBullet = 0;	//弾のカウンタ
	m_nStayTime = 0;	//待機時間
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemySpider::~CEnemySpider()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CEnemySpider::TextureLoad(void)
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
void CEnemySpider::TextureUnload(void)
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
CEnemySpider * CEnemySpider::Create(D3DXVECTOR3 Position)
{
	CEnemySpider * pEnemySpider;
	pEnemySpider = new CEnemySpider;
	pEnemySpider->Init();
	pEnemySpider->SetPosition(Position);
	return pEnemySpider;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEnemySpider::Init(void)
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
	//待機時間の設定
	m_nStayTime = STAY_TIME;
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CEnemySpider::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CEnemySpider::Update(void)
{
	//敵の更新処理関数呼び出し
	CEnemy::Update();
	//もしライフが0になったら
	if (GetLife() <= 0)
	{
		//死亡処理関数呼び出し
		Death();
	}
	//移動処理関数呼び出し
	Move();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CEnemySpider::Draw(void)
{
	//敵の描画処理関数呼び出し
	CEnemy::Draw();
}

//=============================================================================
// 移動量設定処理関数
//=============================================================================
void CEnemySpider::Move(void)
{
	//位置を取得
	D3DXVECTOR3 m_Move = GetMove();
	//カウント
	int nCount = 0;
	//もし目標の位置に達していなかったら
	if (GetPosition().y <= TARGET_POINT)
	{
		//移動量を設定する
		SetMove(SPEED);
	}
	else
	{
		//もし待機時間を越えたら
		if (nCount >= m_nStayTime)
		{
			//移動量を設定する
			SetMove(RETURN_SPEED);
		}
		else
		{
			//慣性
			m_Move.y += (0.0f - m_Move.y) * RATE_MOVE;
			//攻撃処理関数呼び出し
			Attack();
		}
	}
	//カウントを進める
	nCount++;
}

//=============================================================================
// 攻撃処理関数
//=============================================================================
void CEnemySpider::Attack(void)
{
	//プレイヤーを取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//初弾を発射するまでの時間
	if (m_nCountBullet >= SHOT_TIME)
	{
		//プレイヤーが死んでないとき
		//if (CPlayer::GetbDeath() == false)
		//{
			//発射間隔
			if (m_nCountBullet % SHOT_INTERVAL == 0)
			{
				//発射する弾数
				for (int nCnt = 0; nCnt < 9; nCnt++)
				{
					//プレイヤーが死んでいないとき
					if (pPlayer->GetState() != CPlayer::STATE_DEATH)
					{
						CBulletN_Way::Create(GetPosition(), SHOT_SPEED);
					}
				}
			}
		//}
	}
	//弾のカウントを加算
	m_nCountBullet++;
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CEnemySpider::Death(void)
{
	//プレイヤーを取得する
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		//プレイヤーのスコアを加算する
		pPlayer->AddScore(SCORE);
	}
	//ドロップ処理関数呼び出し
	Drop();
	//終了処理関数呼び出し
	Uninit();
	return;
}

//=============================================================================
// ドロップ処理関数
//=============================================================================
void CEnemySpider::Drop(void)
{
	//アイテムを落とす
	CItemLevelUP::Create(GetPosition());
}
