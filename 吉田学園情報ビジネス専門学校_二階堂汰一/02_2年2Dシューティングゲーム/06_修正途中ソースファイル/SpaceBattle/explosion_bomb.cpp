//=============================================================================
//
// 爆弾の爆発 [explosion_bomb.cpp]
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
#include "explosion_bomb.h"
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/explosion.png")
#define SIZE (D3DXVECTOR3(500.0f,500.0f,0.0f))

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosionBomb::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosionBomb::CExplosionBomb(int nPriority)
{
	m_nCounterAnime = 0;					//アニメカウンタ
	m_nPatternAnime = 0;					//アニメパターン
}

//=============================================================================
// デストラクタ
//=============================================================================
CExplosionBomb::~CExplosionBomb()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CExplosionBomb::TextureLoad(void)
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
// テクスチャ破棄
//=============================================================================
void CExplosionBomb::TextureUnload(void)
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
CExplosionBomb * CExplosionBomb::Create(D3DXVECTOR3 Position)
{
	CExplosionBomb * pExolosionBomb;
	pExolosionBomb = new CExplosionBomb;
	pExolosionBomb->Init();
	pExolosionBomb->SetPosition(Position);
	return pExolosionBomb;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CExplosionBomb::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.125f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.125f * m_nPatternAnime + 0.125f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.125f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.125f * m_nPatternAnime + 0.125f, 1.0f);
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
void CExplosionBomb::Uninit(void)
{
	//爆発の終了処理関数呼び出し
	CExplosion::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CExplosionBomb::Update(void)
{
	//爆発の更新処理関数呼び出し
	CExplosion::Update();
	//アニメーション処理関数呼び出し
	Animation();

}

//=============================================================================
// 描画処理関数
//=============================================================================
void CExplosionBomb::Draw(void)
{
	//爆発の描画処理関数呼び出し
	CExplosion::Draw();
}

//=============================================================================
// アニメーション処理関数
//=============================================================================
void CExplosionBomb::Animation(void)
{
	//カウントインクリメント
	m_nCounterAnime++;
	//カウントが4以上になった場合
	if (m_nCounterAnime > 4)
	{
		//カウントを0にする
		m_nCounterAnime = 0;

		//パターンのインクリメント
		m_nPatternAnime++;
		//パターンが8になった場合
		if (m_nPatternAnime > 8)
		{
			//終了
			Uninit();
			return;
		}
	}
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.125f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.125f * m_nPatternAnime + 0.125f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.125f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.125f * m_nPatternAnime + 0.125f, 1.0f);
	//テクスチャの設定
	SetTexture(aTexture);
}

//=============================================================================
// 衝突判定処理
//=============================================================================
void CExplosionBomb::Collisio(void)
{
}
