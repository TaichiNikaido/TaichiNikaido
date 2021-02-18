//=============================================================================
//
// 方向弾 [bullet_direction.cpp]
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
#include "bullet_direction.h"
#include "bullet.h"
#include "effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/bullet.png")	//テクスチャ
#define SIZE (D3DXVECTOR3(10.0f,10.0f,0.0f))		//サイズ
#define COLOR (D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))		//色
#define MINIMUM_LIFE (0)							//体力の最小値
#define LIFE (1000)									//体力
#define EFFECT_LIFE (7)								//エフェクトの体力

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletDirection::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBulletDirection::CBulletDirection()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBulletDirection::~CBulletDirection()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBulletDirection::TextureLoad(void)
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
void CBulletDirection::TextureUnload(void)
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
CBulletDirection * CBulletDirection::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed)
{
	//方向弾のポインタ
	CBulletDirection * pBulletDirection = NULL;
	//もし方向弾のポインタがNULLの場合
	if (pBulletDirection == NULL)
	{
		//方向弾のメモリ確保
		pBulletDirection = new CBulletDirection;
	}
	//もし方向弾のポインタがNULLじゃない場合
	if (pBulletDirection != NULL)
	{
		//初期化処理関数呼び出し
		pBulletDirection->Init();
		//位置を設定する
		pBulletDirection->SetPosition(Position);
		//移動量を設定する
		pBulletDirection->SetMove(Speed);
	}
	//方向弾のポインタを返す
	return pBulletDirection;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBulletDirection::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//敵の初期化処理関数呼び出し
	CBulletEnemy::Init();
	//サイズの初期設定
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
void CBulletDirection::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CBulletEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBulletDirection::Update(void)
{
	//敵の弾更新処理関数呼び出し
	CBulletEnemy::Update();
	//エフェクトの生成
	CEffect::Create(GetPosition(), GetSize(), GetColor(), EFFECT_LIFE);
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
void CBulletDirection::Draw(void)
{
	//敵の描画処理関数呼び出し
	CBulletEnemy::Draw();
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CBulletDirection::Death(void)
{
	//終了処理関数呼び出し
	Uninit();
	return;
}
