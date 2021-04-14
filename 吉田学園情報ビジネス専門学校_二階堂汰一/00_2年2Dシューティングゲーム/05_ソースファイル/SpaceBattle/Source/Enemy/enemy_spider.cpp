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
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/sound.h"
#include "Mode/mode_game.h"
#include "Base/renderer.h"
#include "Base/scene2d.h"
#include "enemy_spider.h"
#include "Player/player.h"
#include "Bullet/bullet.h"
#include "Bullet/bullet_n-way.h"
#include "Item/item_levelup.h"
#include "Effect/explosion_death.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/spider.png")				//テクスチャ
#define MOVE (D3DXVECTOR3(0.0f,5.0f,0.0f))						//移動量
#define RATE_MOVE (0.03f)										//移動量
#define SIZE (D3DXVECTOR3(150.0f,150.0f,0.0f))					//サイズ
#define MINIMUM_LIFE (0)										//体力の最小値
#define LIFE (12)												//体力
#define RETURN_SPEED (D3DXVECTOR3(0.0f,-10.0f,0.0f))			//戻る移動量
#define STOP_MOVE (D3DXVECTOR3(GetMove().x,GetMove().y + (0.0f - GetMove().y)*RATE_MOVE,GetMove().z))	//停止
#define STAY_TIME (500)											//滞在時間
#define BULLET_SPEED (D3DXVECTOR3(cosf(D3DXToRadian(nCount * (360 / 30) + 40.0f))*5.5f, sinf(D3DXToRadian(nCount * (360 / 30) + 40.0f))*5.5f, 0.0f))	//弾の移動量
#define SHOT_TIME (50)											//発射時間
#define SHOT_INTERVAL (20)										//発射間隔
#define SCORE (100000)											//スコア
#define INITIAL_STOP_POSITION (D3DXVECTOR3(0.0f, 0.0f, 0.0f))	//停止位置の最小値
#define INITIAL_SHOT_TIME (0)									//発射最小時間
#define MINIMUM_COUNTER_ANIME (0)								//アニメーション最小カウンタ
#define MINIMUM_PATTERN_ANIME (0)								//アニメーション最小パターン
#define MINIMUM_STAY_TIME (0)									//滞在最小時間
#define STOP_POSITION (float(rand() % (FIELD_HEIGHT / 6) + 100))//停止位置
#define ANIMATION_VALUE (0.500f)								//アニメーションの値
#define MAX_COUNTER_ANIMATION (16)								//アニメーション最大カウンタ
#define MAX_BULLET (9)											//弾の最大数

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemySpider::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemySpider::CEnemySpider()
{
	m_StopPosition = INITIAL_STOP_POSITION;			//停止する位置
	m_nShotTime = INITIAL_SHOT_TIME;				//弾のカウンタ
	m_nCounterAnime = MINIMUM_COUNTER_ANIME;		//アニメカウンタ
	m_nPatternAnime = MINIMUM_PATTERN_ANIME;		//パターンアニメ
	m_nStayTime = MINIMUM_STAY_TIME;				//滞在時間
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
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
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
	//もしテクスチャがNULLじゃない場合
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャをNULLにする
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CEnemySpider * CEnemySpider::Create(D3DXVECTOR3 Position)
{
	//蜘蛛の敵のポインタ
	CEnemySpider * pEnemySpider = NULL;
	//蜘蛛の敵のポインタがNULLの場合
	if (pEnemySpider == NULL)
	{
		//蜘蛛の敵のメモリ確保
		pEnemySpider = new CEnemySpider;
		//蜘蛛の敵のポインタがNULLじゃない場合
		if (pEnemySpider != NULL)
		{
			//位置を設定する
			pEnemySpider->SetPosition(Position);
			//初期化処理関数呼び出し
			pEnemySpider->Init();
		}
	}
	//蜘蛛の敵のポインタを返す
	return pEnemySpider;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEnemySpider::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
	//敵の初期化処理関数呼び出し
	CEnemy::Init();
	//サイズの初期設定
	SetSize(SIZE);
	//体力の初期設定
	SetLife(LIFE);
	//移動量の初期設定
	SetMove(MOVE);
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	//状態を移動中
	SetState(STATE_MOVE);
	//停止場所の初期設定
	m_StopPosition.y = STOP_POSITION;
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
	//滞在処理関数呼び出し
	Stay();
	//もしライフが0になったら
	if (GetLife() <= MINIMUM_LIFE)
	{
		//死亡処理関数呼び出し
		Death();
	}
	//アニメーション処理関数呼び出し
	Animation();
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
	//もしプレイヤーがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//もしプレイヤーの状態が死亡状態以外の時
		if (pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			//初弾を発射するまでの時間
			if (m_nShotTime >= SHOT_TIME)
			{
				//発射間隔
				if (m_nShotTime % SHOT_INTERVAL == REMAINDER)
				{
					//発射する弾の最大数回す
					for (int nCount = 0; nCount < MAX_BULLET; nCount++)
					{
						//n_way弾の生成
						CBulletN_Way::Create(D3DXVECTOR3(Position.x, Position.y + Size.y / 4, 0.0f), BULLET_SPEED);
					}
				}
			}
			//弾のカウントを加算
			m_nShotTime++;
		}
	}
}

//=============================================================================
// 停止処理関数
//=============================================================================
void CEnemySpider::Stop(void)
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//現在の位置が停止位置より値が上だった場合
	if (Position.y >= m_StopPosition.y)
	{
		//移動量を設定する
		SetMove(STOP_MOVE);
		//状態を無にする
		SetState(STATE_NONE);
	}
}

//=============================================================================
// 滞在処理関数
//=============================================================================
void CEnemySpider::Stay(void)
{
	//滞在時間を加算する
	m_nStayTime++;
	//もし指定の滞在時間を過ぎたら
	if (m_nStayTime >= STAY_TIME)
	{
		//状態を移動中
		SetState(STATE_MOVE);
		//移動量を設定する
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
		CExplosionDeath::Create(GetPosition(), EXPLOSION_SIZE);
		//もしサウンドがNULLじゃない場合
		if (pSound != NULL)
		{
			//爆発音の再生
			pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
		}
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
	if (m_nCounterAnime > MAX_COUNTER_ANIMATION)
	{
		//カウントを0にする
		m_nCounterAnime = MINIMUM_COUNTER_ANIME;
		//パターンのインクリメント
		m_nPatternAnime++;
	}
	//アニメーションのカウントを進める
	m_nCounterAnime++;
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
	//テクスチャの設定
	SetTexture(aTexture);
}
