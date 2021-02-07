//=============================================================================
//
// 火球の爆発 [explosion_fireball.cpp]
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
#include "explosion_fireball.h"
#include "enemy.h"
#include "warning.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/explosion.png")
#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define ATTACK (1)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosionFireball::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosionFireball::CExplosionFireball(int nPriority) : CExplosion(nPriority)
{
	m_nCounterAnime = 0;	//アニメカウンタ
	m_nPatternAnime = 0;	//アニメパターン
}

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosionFireball::~CExplosionFireball()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CExplosionFireball::TextureLoad(void)
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
void CExplosionFireball::TextureUnload(void)
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
CExplosionFireball * CExplosionFireball::Create(D3DXVECTOR3 Position)
{
	CExplosionFireball * pExolosionFireball;
	pExolosionFireball = new CExplosionFireball;
	pExolosionFireball->Init();
	pExolosionFireball->SetPosition(Position);
	return pExolosionFireball;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CExplosionFireball::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//危険地帯を取得
	CWarning * pWarning = CGameMode::GetWarning();
	//サイズの初期設定
	D3DXVECTOR3 Size = pWarning->GetSize();
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.125f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.125f * m_nPatternAnime + 0.125f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.125f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.125f * m_nPatternAnime + 0.125f, 1.0f);
	//爆発の初期化処理関数呼び出し
	CExplosion::Init();
	//サイズの初期設定
	SetSize(Size);
	//色の初期設定
	SetColor(COLOR);
	//爆発音の再生
	pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CExplosionFireball::Uninit(void)
{
	//爆発の終了処理関数呼び出し
	CExplosion::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CExplosionFireball::Update(void)
{
	//爆発の更新処理関数呼び出し
	CExplosion::Update();
	//アニメーション処理関数呼び出し
	Animation();
	//衝突判定処理関数呼び出し
	Collision();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CExplosionFireball::Draw(void)
{
	//爆発の描画処理関数呼び出し
	CExplosion::Draw();
}

//=============================================================================
// アニメーション処理関数
//=============================================================================
void CExplosionFireball::Animation(void)
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
			//終了処理関数呼び出し
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
// アニメーション処理関数
//=============================================================================
void CExplosionFireball::Collision(void)
{
	//プレイヤーを取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//位置を取得
	D3DXVECTOR3 Position = GetPosition();
	//サイズを取得
	D3DXVECTOR3 Size = GetSize();
	//目標の位置を取得
	if (pPlayer != NULL)
	{
		//目標の位置を取得
		D3DXVECTOR3 TargetPosition = pPlayer->GetPosition();
		//目標のサイズを取得
		D3DXVECTOR3 TargetSize = pPlayer->GetSize();
		if (Position.x + Size.x / 2 > TargetPosition.x - TargetSize.x / 2 &&
			Position.x - Size.x / 2 < TargetPosition.x + TargetSize.x / 2 &&
			Position.y + Size.y / 2 > TargetPosition.y - TargetSize.y / 2 &&
			Position.y - Size.y / 2 < TargetPosition.y + TargetSize.y / 2)
		{
			pPlayer->SubLife(ATTACK);
		}
	}
}
