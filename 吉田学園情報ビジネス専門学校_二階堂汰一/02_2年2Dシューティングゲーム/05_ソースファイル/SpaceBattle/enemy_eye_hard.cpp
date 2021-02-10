//=============================================================================
//
// 目玉(ハード) [enemy_eye_hard.cpp]
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
#include "enemy_eye_hard.h"
#include "bullet_homing.h"
#include "player.h"
#include "bullet.h"
#include "explosion_death.h"
#include "bullet_homing.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/eye_hard.png")					//テクスチャ
#define SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))						//サイズ
#define MOVE (D3DXVECTOR3(0.0f,5.0f,0.0f))							//移動量
#define RETURN_MOVE (D3DXVECTOR3(0.0f,-10.0f,0.0f))					//戻る時の移動量
#define INITIAL_STOP_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))			//停止する位置の初期値
#define STOP_POSITION (float(rand() % (FIELD_HEIGHT / 2) + 100))	//停止する位置
#define MINIMUM_SHOT_TIME (0)										//弾を撃つまでの最小時間
#define SHOT_TIME (100)												//撃つまでの時間
#define MINIMUM_STAY_TIME (0)										//滞在する最小時間
#define STAY_TIME (500)												//滞在時間
#define MINIMUM_TARGET_ANGLE (0.0f)									//目標の角度の最小値
#define RATE_MOVE (0.03f)											//移動量
#define STOP (D3DXVECTOR3(GetMove().x,GetMove().y + (0.0f - GetMove().y) * RATE_MOVE,GetMove().z))	//停止位置
#define MINIMUM_LIFE (0)											//体力の最小値
#define LIFE (3)													//体力
#define SCORE (10000)												//スコア								
#define BULLET_SPEED (7.0f)											//弾の速度

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyEyeHard::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyEyeHard::CEnemyEyeHard()
{
	m_StopPosition = INITIAL_STOP_POSITION;		//停止位置
	m_fTargetAngle = MINIMUM_TARGET_ANGLE;		//目標までの角度
	m_nShotTime = MINIMUM_SHOT_TIME;			//弾を発射するまでの時間
	m_nStayTime = MINIMUM_STAY_TIME;			//滞在時間
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyEyeHard::~CEnemyEyeHard()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CEnemyEyeHard::TextureLoad(void)
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
void CEnemyEyeHard::TextureUnload(void)
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
CEnemyEyeHard * CEnemyEyeHard::Create(D3DXVECTOR3 Position)
{
	//目玉の敵(ハード)のポインタ
	CEnemyEyeHard * pEnemyEyeHard = NULL;
	//もし目玉のポインタがNULLの場合
	if (pEnemyEyeHard == NULL)
	{
		//目玉の敵(ハード)のメモリ確保
		pEnemyEyeHard = new CEnemyEyeHard;
	}
	//もし目玉のポインタがNULLじゃない場合
	if (pEnemyEyeHard != NULL)
	{
		//初期化処理関数呼び出し
		pEnemyEyeHard->Init();
		//位置を設定する
		pEnemyEyeHard->SetPosition(Position);
	}
	return pEnemyEyeHard;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEnemyEyeHard::Init(void)
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
void CEnemyEyeHard::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CEnemyEyeHard::Update(void)
{
	//敵の更新処理関数呼び出し
	CEnemy::Update();
	//見つめる処理関数呼び出し
	Gaze();
	//状態が移動状態じゃないとき
	if (GetState() != STATE_MOVE)
	{
		//攻撃処理関数呼び出し
		Attack();
	}
	//停止処理関数呼び出し
	Stop();
	//停止処理関数呼び出し
	Stay();
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
void CEnemyEyeHard::Draw(void)
{
	//敵の描画処理関数呼び出し
	CEnemy::Draw();
}

//=============================================================================
// 攻撃処理関数
//=============================================================================
void CEnemyEyeHard::Attack(void)
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしプレイヤーのポインタがNULLじゃなかったら
	if (pPlayer != NULL)
	{
		//もしプレイヤーの状態が死亡状態以外の時
		if (pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			//弾を発射する時間になったら
			if (m_nShotTime % SHOT_TIME == REMAINDER)
			{
				//ホーミング弾の生成
				CBulletHoming::Create(Position);
			}
			//弾のカウントを加算
			m_nShotTime++;
		}
	}
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CEnemyEyeHard::Death(void)
{
	//プレイヤーを取得する
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//プレイヤーがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//爆発エフェクトの生成
		CExplosionDeath::Create(GetPosition());
		//爆発音の再生
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
		//プレイヤーのスコアを加算する
		pPlayer->AddScore(SCORE);
	}
	//終了処理関数呼び出し
	Uninit();
	return;
}

//=============================================================================
// 見つめる処理関数
//=============================================================================
void CEnemyEyeHard::Gaze(void)
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//プレイヤーを取得する
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//プレイヤーがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//目標の位置を取得する
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//もし状態が無又は移動状態だったら
		if (GetState() == STATE_NONE || GetState() == STATE_MOVE)
		{
			//プレイヤーまでの距離を計算
			D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(PlayerPosition.x - Position.x, PlayerPosition.y - Position.y, 0.0f);
			//プレイヤの方に向けた角度を計算
			m_fTargetAngle = atan2f(m_TargetDistance.y, m_TargetDistance.x);
			//向きを設定する
			SetRotation(D3DXVECTOR3(0.0f, 0.0f, -m_fTargetAngle));
		}
	}
}

//=============================================================================
// 停止処理関数
//=============================================================================
void CEnemyEyeHard::Stop(void)
{
	//位置を取得する
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
void CEnemyEyeHard::Stay(void)
{
	//滞在時間を加算する
	m_nStayTime++;
	//もし指定の滞在時間を過ぎたら
	if (m_nStayTime >= STAY_TIME)
	{
		//状態を移動中
		SetState(STATE_MOVE);
		//移動量を設定する
		SetMove(RETURN_MOVE);
	}
}
