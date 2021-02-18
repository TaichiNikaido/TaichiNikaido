//=============================================================================
//
// 火球 [bullet_fireball.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "mode_game.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "sound.h"
#include "bullet.h"
#include "bullet_fireball.h"
#include "player.h"
#include "warning.h"
#include "explosion_fireball.h"
#include "effect.h"
#include "enemy_dragon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/bullet_fireball.png")	//テクスチャ
#define SIZE (D3DXVECTOR3(35.0f,35.0f,0.0f))				//サイズ
#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))				//色
#define MOVE (D3DXVECTOR3(0.0f,3.0f,0.0f))					//移動量
#define EFFECT_LIFE (7)										//エフェクトの体力
#define ADD_SCALE (0.1f)									//加算する加算量
#define MAX_SCALE (4.0f)									//最大の加算量

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletFireball::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBulletFireball::CBulletFireball()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBulletFireball::~CBulletFireball()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBulletFireball::TextureLoad(void)
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
void CBulletFireball::TextureUnload(void)
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
CBulletFireball * CBulletFireball::Create(D3DXVECTOR3 Position)
{
	//火球のポインタ
	CBulletFireball * pFireBall = NULL;
	//もし火球のポインタがNULLの場合
	if (pFireBall == NULL)
	{
		//火球のメモリ確保
		pFireBall = new CBulletFireball;
	}
	//もし火球のポインタがNULLじゃない場合
	if (pFireBall != NULL)
	{
		//初期化処理関数呼び出し
		pFireBall->Init();
		//位置を設定する
		pFireBall->SetPosition(Position);
	}
	//火球のポインタを返す
	return pFireBall;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBulletFireball::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//敵の弾の初期化処理関数呼び出し
	CBulletEnemy::Init();
	//サイズの初期設定
	SetSize(SIZE);
	//色の初期設定
	SetColor(COLOR);
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	//危険地帯の生成
	CGameMode::SetWarning(CWarning::Create());
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CBulletFireball::Uninit(void)
{
	//敵の弾の終了処理関数呼び出し
	CBulletEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBulletFireball::Update(void)
{
	//敵の弾の更新処理関数呼び出し
	CBulletEnemy::Update();
	//チャージ処理関数呼び出し
	Charge();
	//死亡処理関数呼び出し
	Death();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CBulletFireball::Draw(void)
{
	//敵の弾の描画処理関数呼び出し
	CBulletEnemy::Draw();
}

//=============================================================================
// チャージ処理関数
//=============================================================================
void CBulletFireball::Charge(void)
{
	//スケールを取得
	float fScale = GetScale();
	//ドラゴンを取得
	CEnemyDragon * pEnemyDragon = CGameMode::GetDragon();
	//もしドラゴンのポインタがNULLじゃない場合
	if (pEnemyDragon != NULL)
	{
		//スケールが最大になったら
		if (fScale < MAX_SCALE)
		{
			//ドラゴンのチャージを完了にする
			pEnemyDragon->SetbCharge(true);
			//拡大していく
			fScale += ADD_SCALE;
			//拡縮を設定する
			SetScale(fScale);
		}
		else
		{
			//ドラゴンのチャージを完了にする
			pEnemyDragon->SetbCharge(false);
			//移動量を設定
			SetMove(MOVE);
		}
	}
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CBulletFireball::Death(void)
{
	//位置を取得
	D3DXVECTOR3 Position = GetPosition();
	//プレイヤーを取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//危険地帯を取得
	CWarning * pWarning = CGameMode::GetWarning();
	//もし危険地帯がNULLじゃない場合
	if (pPlayer != NULL)
	{
		//目標の位置を取得
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//もし位置のY座標が目標のY座標を越えたら
		if (Position.y >= PlayerPosition.y)
		{
			//爆発エフェクトの生成
			CExplosionFireball::Create(Position);
			//危険地帯の終了処理関数呼び出し
			pWarning->Uninit();
			//終了処理関数呼び出し
			Uninit();
			return;
		}
	}
}