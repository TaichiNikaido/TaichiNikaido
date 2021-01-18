//=============================================================================
//
// 目玉(ノーマル) [enemy_eye_normal.cpp]
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
#include "enemy_eye_normal.h"
#include "player.h"
#include "bullet_direction.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/eye_normal.png")
#define SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))
#define LIFE (3)
#define SCORE (10000)
#define BULLET_SPEED (7.0f)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyEyeNormal::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyEyeNormal::CEnemyEyeNormal(int nPriority)
{
	m_fAngleRot = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyEyeNormal::~CEnemyEyeNormal()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CEnemyEyeNormal::TextureLoad(void)
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
void CEnemyEyeNormal::TextureUnload(void)
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
CEnemyEyeNormal * CEnemyEyeNormal::Create(D3DXVECTOR3 Position)
{
	CEnemyEyeNormal * pEnemyEyeNormal;
	pEnemyEyeNormal = new CEnemyEyeNormal;
	pEnemyEyeNormal->Init();
	pEnemyEyeNormal->SetPosition(Position);
	return pEnemyEyeNormal;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEnemyEyeNormal::Init(void)
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
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CEnemyEyeNormal::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CEnemyEyeNormal::Update(void)
{
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//目標までの距離
	D3DXVECTOR3 TargetDistance = D3DXVECTOR3(pPlayer->GetPosition().x - GetPosition().x,pPlayer->GetPosition().y - GetPosition().y,0.0f);
	//敵の更新処理関数呼び出し
	CEnemy::Update();
	//攻撃処理関数呼び出し
	Attack();
	//プレイヤ-の方に向けた角度を計算
	m_fAngleRot = atan2f(TargetDistance.y, TargetDistance.x);
	m_fAngleRot = m_fAngleRot * -1.0f;
	//もしライフが0になったら
	if (GetLife() <= 0)
	{
		//死亡処理関数呼び出し
		Death();
	}
	//向きを設定する
	//SetRotation(m_fAngleRot);
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CEnemyEyeNormal::Draw(void)
{
	//敵の描画処理関数呼び出し
	CEnemy::Draw();
}

//=============================================================================
// 攻撃処理関数
//=============================================================================
void CEnemyEyeNormal::Attack(void)
{
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//目標の位置
	D3DXVECTOR3 TargetPosisiton = pPlayer->GetPosition();
	//目標までの距離を計算
	D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(TargetPosisiton.x - GetPosition().x, TargetPosisiton.y - GetPosition().y, 0.0f);
	//向けた角度を計算
	float fBulletAngle = atan2f(m_TargetDistance.y, m_TargetDistance.x);
	//プレイヤーが死んでいないとき
	if (pPlayer->GetState() != CPlayer::STATE_DEATH)
	{
		//弾の生成
		CBulletDirection::Create(GetPosition(), D3DXVECTOR3(cosf(fBulletAngle) * BULLET_SPEED, sinf(fBulletAngle) * BULLET_SPEED, 0.0f));
	}
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CEnemyEyeNormal::Death(void)
{
	//プレイヤーを取得する
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		//プレイヤーのスコアを加算する
		pPlayer->AddScore(SCORE);
	}
	//終了処理関数呼び出し
	Uninit();
	return;
}
