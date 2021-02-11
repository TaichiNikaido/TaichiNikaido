//=============================================================================
//
// 死亡時の爆発 [explosion_death.cpp]
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
#include "sound.h"
#include "explosion_death.h"
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/explosion.png")	  //テクスチャ
#define SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))	  //サイズ
#define MINIMUM_COUNTER__ANIME (0)				  //アニメーション最小カウンタ
#define MINIMUM_PATTERN_ANIME (0)				  //アニメーション最小パターン
#define ANIMATION_VALUE (0.125f)				  //アニメーションの値
#define MAX_COUNTER_ANIME (4)					  //アニメーション最大カウンタ
#define MAX_PATTERN_ANIME (8)					  //アニメーション最大パターン

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosionDeath::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosionDeath::CExplosionDeath()
{
	m_nCounterAnime = MINIMUM_COUNTER__ANIME;	//アニメカウンタ
	m_nPatternAnime = MINIMUM_PATTERN_ANIME;	//アニメパターン
}

//=============================================================================
// デストラクタ
//=============================================================================
CExplosionDeath::~CExplosionDeath()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CExplosionDeath::TextureLoad(void)
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
// テクスチャ破棄
//=============================================================================
void CExplosionDeath::TextureUnload(void)
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
CExplosionDeath * CExplosionDeath::Create(D3DXVECTOR3 Position)
{
	//死亡時の爆発のポインタ
	CExplosionDeath * pExplosionDeath = NULL;
	//もし死亡時の爆発のポインタがNULLの場合
	if (pExplosionDeath == NULL)
	{
		//死亡時の爆発のメモリ確保
		pExplosionDeath = new CExplosionDeath;
	}
	//もし死亡時の爆発のポインタがNULLじゃない場合
	if (pExplosionDeath != NULL)
	{
		//初期化処理関数呼び出し
		pExplosionDeath->Init();
		//位置を設定する
		pExplosionDeath->SetPosition(Position);
	}
	//死亡時の爆発のポインタを返す
	return pExplosionDeath;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CExplosionDeath::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
	//爆発の初期化処理関数呼び出し
	CExplosion::Init();
	//サイズの初期設定
	SetSize(SIZE);
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CExplosionDeath::Uninit(void)
{
	//爆発の終了処理関数呼び出し
	CExplosion::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CExplosionDeath::Update(void)
{
	//爆発の更新処理関数呼び出し
	CExplosion::Update();
	//カウントインクリメント
	m_nCounterAnime++;
	//カウントが4以上になった場合
	if (m_nCounterAnime > MAX_COUNTER_ANIME)
	{
		//カウントを0にする
		m_nCounterAnime = MINIMUM_COUNTER__ANIME;
		//パターンのインクリメント
		m_nPatternAnime++;
		//パターンが8になった場合
		if (m_nPatternAnime > MAX_PATTERN_ANIME)
		{
			//終了処理関数呼び出し
			Uninit();
			return;
		}
	}
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
	//テクスチャの設定
	SetTexture(aTexture);
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CExplosionDeath::Draw(void)
{
	//爆発の描画処理関数呼び出し
	CExplosion::Draw();
}
