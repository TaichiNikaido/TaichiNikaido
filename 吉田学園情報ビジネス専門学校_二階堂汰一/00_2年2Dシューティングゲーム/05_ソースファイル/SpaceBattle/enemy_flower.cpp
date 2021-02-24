//=============================================================================
//
// 花 [enemy_flower.cpp]
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
#include "enemy_flower.h"
#include "player.h"
#include "bullet.h"
#include "item_life.h"
#include "explosion_death.h"
#include "bullet_flower.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/flower.png")	//テクスチャ
#define SIZE (D3DXVECTOR3(100.0f,100.0f,0.0f))		//サイズ
#define MINIMUM_LIFE (0)							//体力の最小値
#define LIFE (13)									//体力
#define SCORE (50000)								//スコア
#define MOVE (D3DXVECTOR3(0.0f,5.0f,0.0f))			//移動量		
#define RETURN_MOVE (D3DXVECTOR3(0.0f,-10.0f,0.0f))	//戻る移動量
#define STOP (D3DXVECTOR3(GetMove().x,GetMove().y + (0.0f - GetMove().y)*RATE_MOVE,GetMove().z))	//停止位置
#define STAY_TIME (500)								//滞在時間
#define BULLET_MOVE (D3DXVECTOR3(cosf(D3DXToRadian(nCount * (360 / 20)))*3.5f, sinf(D3DXToRadian(nCount * (360 / 20)))*3.5f, 0.0f))	//弾の移動量
#define RATE_MOVE (0.03f)							//移動量
#define INITIAL_STOP_POSITION (D3DXVECTOR3(0.0f, 0.0f, 0.0f))	//停止位置の最小値
#define MINIMUM_COUNTER_ANIME (0)					//カウンターアニメの最小値
#define MINIMUM_PATTERN_ANIME (0)					//パターンアニメの最小値
#define MINIMUM_SHOT_TIME (0)						//発射時間の最小値
#define MINIMUM_COLOR_COUNT (0)						//色の最小カウント
#define MINIMUM_STAY_TIME (0)						//滞在最小時間
#define ANIMATION_VALUE (0.250f)					//アニメーションの値
#define STOP_POSITION (float(rand() % (FIELD_HEIGHT / 8)))	//停止位置
#define SHOT_TIME (50)								//停止時間
#define SHOT_COOL_TIME (100)						//弾の色の時間
#define INTERVAL_BULLET (20)						//弾の間隔
#define MINIMUM_ANIMATION (0)						//アニメーションの最小値
#define MAX_ANIMATION (16)							//アニメーションの最大値
#define SHOT_VALUE (20)								//発射回数

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyFlower::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyFlower::CEnemyFlower()
{
	m_StopPosition = INITIAL_STOP_POSITION;		//停止位置
	m_nCounterAnime = MINIMUM_COUNTER_ANIME;	//アニメカウンタ
	m_nPatternAnime = MINIMUM_PATTERN_ANIME;	//アニメパターン
	m_nShotTime = MINIMUM_SHOT_TIME;			//弾を発射するまでの時間
	m_nColorCount = MINIMUM_COLOR_COUNT;		//色カウント
	m_nStayTime = MINIMUM_STAY_TIME;			//滞在時間
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyFlower::~CEnemyFlower()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CEnemyFlower::TextureLoad(void)
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
void CEnemyFlower::TextureUnload(void)
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
CEnemyFlower * CEnemyFlower::Create(D3DXVECTOR3 Position)
{
	//花の敵のポインタ
	CEnemyFlower * pEnemyFlower = NULL;
	//もし花の敵のポインタがNULLの場合
	if (pEnemyFlower == NULL)
	{
		//花の敵のメモリ確保
		pEnemyFlower = new CEnemyFlower;
		//もし花の敵のポインタがNULLじゃない場合
		if (pEnemyFlower != NULL)
		{
			//位置を設定する
			pEnemyFlower->SetPosition(Position);
			//初期化処理関数呼び出し
			pEnemyFlower->Init();
		}
	}
	//花の敵のポインタを返す
	return pEnemyFlower;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEnemyFlower::Init(void)
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
	//敵の止まる位置を指定する
	m_StopPosition.y = STOP_POSITION;
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CEnemyFlower::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CEnemyFlower::Update(void)
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
	//アニメーション処理関数呼び出し
	Animation();
	//もしライフが0になったら
	if (GetLife() <= MINIMUM_LIFE)
	{
		//死亡処理関数呼び出し
		Death();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CEnemyFlower::Draw(void)
{
	//敵の描画処理関数呼び出し
	CEnemy::Draw();
}

//=============================================================================
// 攻撃処理関数
//=============================================================================
void CEnemyFlower::Attack(void)
{
	//プレイヤーを取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//位置を取得
	D3DXVECTOR3 Position = GetPosition();
	//もしプレイヤーがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//もしプレイヤーの状態が死亡状態じゃないとき
		if (pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			//弾を発射するまでの時間
			if (m_nShotTime >= SHOT_TIME)
			{
				//間隔ごとに発射する
				if (m_nShotTime % INTERVAL_BULLET == REMAINDER)
				{
					//色カウントが最大以下の場合
					if (m_nColorCount < CBulletFlower::COLOR_NUMBER_MAX)
					{
						//発射弾数分回す
						for (int nCount = 0; nCount < SHOT_VALUE; nCount++)
						{
							//花弾の生成
							CBulletFlower::Create(Position, BULLET_MOVE, (CBulletFlower::COLOR_NUMBER)m_nColorCount);
						}
					}
					//色のカウントを加算
					m_nColorCount++;
				}
				//色カウントが最大数を越えたの場合
				if (m_nColorCount > CBulletFlower::COLOR_NUMBER_MAX)
				{
					//もし弾の発射時間がクールタイムを越えたら
					if (m_nShotTime % SHOT_COOL_TIME == REMAINDER)
					{
						//色のカウントを0にする
						m_nColorCount = MINIMUM_COLOR_COUNT;
					}
				}
			}
		}
		//弾を発射するまでの時間を加算する
		m_nShotTime++;
	}
}

//=============================================================================
// 停止処理関数
//=============================================================================
void CEnemyFlower::Stop(void)
{
	//位置を取得
	D3DXVECTOR3 Position = GetPosition();
	//現在の位置が停止位置より値が上だった場合
	if (Position.y >= m_StopPosition.y)
	{
		//移動量を設定する
		SetMove(STOP);
		//状態を無にする
		SetState(STATE_NONE);
	}
}

//=============================================================================
// 滞在処理関数
//=============================================================================
void CEnemyFlower::Stay(void)
{
	//滞在時間を加算する
	m_nStayTime++;
	//もし指定の滞在時間を過ぎたら
	if (m_nStayTime == STAY_TIME)
	{
		//状態を移動にする
		SetState(STATE_MOVE);
		//移動量を設定する
		SetMove(RETURN_MOVE);
	}
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CEnemyFlower::Death(void)
{
	//プレイヤーを取得する
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//プレイヤーがNULLじゃない場合
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
void CEnemyFlower::Drop(void)
{
	//体力回復アイテムを落とす
	CItemLife::Create(GetPosition());
}

//=============================================================================
// アニメーション処理関数
//=============================================================================
void CEnemyFlower::Animation(void)
{
	//カウントインクリメント
	m_nCounterAnime++;
	//カウントが16以上になった場合
	if (m_nCounterAnime > MAX_ANIMATION)
	{
		//カウントを0にする
		m_nCounterAnime = MINIMUM_ANIMATION;
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
