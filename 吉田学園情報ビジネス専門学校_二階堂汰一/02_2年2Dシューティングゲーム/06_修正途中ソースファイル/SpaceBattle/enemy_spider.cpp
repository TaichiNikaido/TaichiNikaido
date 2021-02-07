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
#include "sound.h"
#include "mode_game.h"
#include "renderer.h"
#include "scene2d.h"
#include "enemy_spider.h"
#include "player.h"
#include "bullet.h"
#include "bullet_n-way.h"
#include "item_levelup.h"
#include "explosion_death.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/spider.png")
#define SPEED (D3DXVECTOR3(0.0f,5.0f,0.0f))
#define RATE_MOVE (0.03f)
#define SIZE (D3DXVECTOR3(150.0f,150.0f,0.0f))
#define LIFE (12)
#define RETURN_SPEED (D3DXVECTOR3(0.0f,-10.0f,0.0f))
#define RETURN_SPEED ((D3DXVECTOR3(0.0f,-7.0f,0.0f)))
#define STOP (D3DXVECTOR3(GetMove().x,GetMove().y + (0.0f - GetMove().y)*RATE_MOVE,GetMove().z))
#define STAY_TIME (500)
#define SHOT_SPEED (D3DXVECTOR3(cosf(D3DXToRadian(nCnt * (360 / 30) + 40.0f))*5.5f, sinf(D3DXToRadian(nCnt * (360 / 30) + 40.0f))*5.5f, 0.0f))
#define SHOT_TIME (50)
#define SHOT_INTERVAL (20)
#define SCORE (100000)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemySpider::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemySpider::CEnemySpider(int nPriority) : CEnemy(nPriority)
{
	m_StopPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCountBullet = 0;		//弾のカウンタ
	m_nCounterAnime = 0;	//アニメカウンタ
	m_nPatternAnime = 0;	//パターンアニメ
	m_nStayTime = 0;
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
	pEnemySpider->SetPosition(Position);
	pEnemySpider->Init();
	return pEnemySpider;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEnemySpider::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.500f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.500f * m_nPatternAnime + 0.500f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.500f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.500f * m_nPatternAnime + 0.500f, 1.0f);
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
	m_StopPosition.y = float(rand() % (FIELD_HEIGHT / 6) + 100);
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
	//状態が移動状態じゃないとき
	if (GetState() != STATE_MOVE)
	{
		//攻撃処理関数呼び出し
		Attack();
	}
	//停止処理関数呼び出し
	Stop();
	Stay();
	//もしライフが0になったら
	if (GetLife() <= 0)
	{
		//死亡処理関数呼び出し
		Death();
	}
	//アニメーション処理関数呼び出し
	Animation();
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

}

//=============================================================================
// 攻撃処理関数
//=============================================================================
void CEnemySpider::Attack(void)
{
	//プレイヤーを取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//位置を取得
	D3DXVECTOR3 Position = GetPosition();
	//サイズを取得
	D3DXVECTOR3 Size = GetSize();
	if (pPlayer != NULL)
	{
		//もしプレイヤーの状態が死亡状態以外の時
		if (pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			//初弾を発射するまでの時間
			if (m_nCountBullet >= SHOT_TIME)
			{
				//発射間隔
				if (m_nCountBullet % SHOT_INTERVAL == 0)
				{
					//発射する弾数
					for (int nCnt = 0; nCnt < 9; nCnt++)
					{
						//n_way弾の生成
						CBulletN_Way::Create(D3DXVECTOR3(Position.x, Position.y + Size.y / 4, 0.0f), SHOT_SPEED);
					}
				}
			}
			//弾のカウントを加算
			m_nCountBullet++;
		}
	}
}

//=============================================================================
// 停止処理関数
//=============================================================================
void CEnemySpider::Stop(void)
{
	D3DXVECTOR3 Position = GetPosition();

	if (Position.y >= m_StopPosition.y)
	{
		SetMove(STOP);
		SetState(STATE_NONE);
	}
}

void CEnemySpider::Stay(void)
{
	m_nStayTime++;
	if (m_nStayTime == STAY_TIME)
	{
		//状態を移動中
		SetState(STATE_MOVE);
		SetMove(RETURN_SPEED);
	}
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CEnemySpider::Death(void)
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

//=============================================================================
// アニメーション処理関数
//=============================================================================
void CEnemySpider::Animation(void)
{
	//カウントインクリメント
	m_nCounterAnime++;
	//カウントが16以上になった場合
	if (m_nCounterAnime > 16)
	{
		//カウントを0にする
		m_nCounterAnime = 0;

		//パターンのインクリメント
		m_nPatternAnime++;
	}
	//アニメーションのカウントを進める
	m_nCounterAnime++;
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.500f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.500f * m_nPatternAnime + 0.500f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.500f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.500f * m_nPatternAnime + 0.500f, 1.0f);
	//テクスチャの設定
	SetTexture(aTexture);
}
