//=============================================================================
//
// 花弾 [bullet_flower.cpp]
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
#include "renderer.h"
#include "scene2d.h"
#include "mode_game.h"
#include "bullet_flower.h"
#include "bullet.h"
#include "player.h"
#include "bullet_flower.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/bullet_flower.png")	//テクスチャ
#define SIZE (D3DXVECTOR3(40.0f,40.0f,0.0f))				//サイズ
#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))				//色
#define LIFE (1500)											//体力
#define MINIMUM_TIME (0)									//時間の最小値
#define MAX_TIME (80)										//時間の最大値
#define MINIMUM_LIFE (0)									//体力の最小値
#define ANIMATION_VALUE (0.1428f)							//アニメーションの値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletFlower::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBulletFlower::CBulletFlower()
{
	m_ColorNumber = COLOR_NUMBER_NONE;	//色の番号
	m_nTime = MINIMUM_TIME;				//時間
}

//=============================================================================
// デストラクタ
//=============================================================================
CBulletFlower::~CBulletFlower()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBulletFlower::TextureLoad(void)
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
void CBulletFlower::TextureUnload(void)
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
CBulletFlower * CBulletFlower::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed, COLOR_NUMBER nColor)
{
	//花弾のポインタ
	CBulletFlower * pBulletFlower = NULL;
	//もし花弾のポインタがNULLの場合
	if (pBulletFlower == NULL)
	{
		//花弾のメモリ確保
		pBulletFlower = new CBulletFlower;
	}
	//もし花弾のポインタがNULLじゃない場合
	if (pBulletFlower != NULL)
	{
		//位置を設定する
		pBulletFlower->SetPosition(Position);
		//移動量を設定する
		pBulletFlower->SetMove(Speed);
		//色の番号を設定する
		pBulletFlower->m_ColorNumber = nColor;
		//初期化処理関数呼び出し
		pBulletFlower->Init();
	}
	//もし花弾のポインタを返す
	return pBulletFlower;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBulletFlower::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_ColorNumber * ANIMATION_VALUE, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_ColorNumber * ANIMATION_VALUE + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_ColorNumber * ANIMATION_VALUE, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_ColorNumber * ANIMATION_VALUE + ANIMATION_VALUE, 1.0f);
	//敵の弾の初期化処理関数呼び出し
	CBulletEnemy::Init();
	//サイズの設定
	SetSize(SIZE);
	//色の初期設定
	SetColor(COLOR);
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
void CBulletFlower::Uninit(void)
{
	//敵の弾の終了処理関数呼び出し
	CBulletEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBulletFlower::Update(void)
{
	//敵の弾の更新処理関数呼び出し
	CBulletEnemy::Update();
	//移動処理関数呼び出し
	Move();
	//色選択処理関数呼び出し
	ColorSelect();
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
void CBulletFlower::Draw(void)
{
	//敵の描画処理関数呼び出し
	CBulletEnemy::Draw();
}

//=============================================================================
// 移動処理関数
//=============================================================================
void CBulletFlower::Move(void)
{
	//位置を取得
	D3DXVECTOR3 Position = GetPosition();
	//向きを取得
	D3DXVECTOR3 Rotaion = GetRotation();
	//移動量を取得
	D3DXVECTOR3 Move = GetMove();
	//プレイヤーを取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしプレイヤーがNULLじゃない場合
	if (pPlayer != NULL)
	{
		if (m_nTime == MAX_TIME)
		{
			//プレイヤーの位置を取得
			D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
			//プレイヤーまでの距離を求める
			D3DXVECTOR3 TargetDistance = D3DXVECTOR3(PlayerPosition.x - Position.x, PlayerPosition.y - Position.y, 0.0f);
			//向きを設定する
			Rotaion.y = float(atan2(TargetDistance.y, TargetDistance.x));
			//移動量を代入
			Move = D3DXVECTOR3(cosf(Rotaion.y) * 5.5f, sinf(Rotaion.y) * 5.5f, 0.0f);
		}
		//タイムを進める
		m_nTime++;
	}
	//進行方向に向きを合わせる
	Rotaion.z = atan2f((Position.x + Move.x) - Position.x, (Position.y + Move.y) - Position.y);
	//向きを合わせる
	SetRotation(Rotaion);
	//移動量を設定
	SetMove(Move);
}

//=============================================================================
// 色選択処理関数
//=============================================================================
void CBulletFlower::ColorSelect(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_ColorNumber * ANIMATION_VALUE, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_ColorNumber * ANIMATION_VALUE + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_ColorNumber * ANIMATION_VALUE, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_ColorNumber * ANIMATION_VALUE + ANIMATION_VALUE, 1.0f);
	//テクスチャの設定
	SetTexture(aTexture);
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CBulletFlower::Death(void)
{
	//終了処理関数呼び出し
	Uninit();
	return;
}
