//=============================================================================
//
// 爆弾 [bullet_bomb.cpp]
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
#include "sound.h"
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "bullet_bomb.h"
#include "explosion_bomb.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/bullet_bomb.png")	//テクスチャ
#define SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))			//サイズ
#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))			//色
#define MINIMUM_LIFE (0)								//体力の最小値
#define LIFE (50)										//体力

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletBomb::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBulletBomb::CBulletBomb()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBulletBomb::~CBulletBomb()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBulletBomb::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスを取得
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
void CBulletBomb::TextureUnload(void)
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
CBulletBomb * CBulletBomb::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed)
{
	//爆弾のポインタ
	CBulletBomb * pBulletBomb = NULL;
	//もし爆弾のポインタがNULLの場合
	if (pBulletBomb == NULL)
	{
		//爆弾のメモリ確保
		pBulletBomb = new CBulletBomb;
		//もし爆弾のポインタがNULLじゃない場合
		if (pBulletBomb != NULL)
		{
			//初期化処理関数呼び出し
			pBulletBomb->Init();
			//位置を設定する
			pBulletBomb->SetPosition(Position);
			//移動量を設定する
			pBulletBomb->SetMove(Speed);
		}
	}
	//爆弾のポインタを返す
	return pBulletBomb;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBulletBomb::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//弾の初期化関数呼び出し
	CBullet::Init();
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
void CBulletBomb::Uninit(void)
{
	//弾の終了処理関数呼び出し
	CBullet::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBulletBomb::Update(void)
{
	//移動量の取得
	D3DXVECTOR3 Move = GetMove();
	//移動量を設定する
	SetMove(Move);
	//弾の更新処理関数呼び出し
	CBullet::Update();
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
void CBulletBomb::Draw(void)
{
	//弾の描画処理関数呼び出し
	CBullet::Draw();
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CBulletBomb::Death(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//爆発の生成
	CExplosionBomb::Create(GetPosition());
	//もしサウンドがNULLじゃない場合
	if (pSound != NULL)
	{
		//爆発音の再生
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
	}
	//終了処理関数呼び出し
	Uninit();
	return;
}