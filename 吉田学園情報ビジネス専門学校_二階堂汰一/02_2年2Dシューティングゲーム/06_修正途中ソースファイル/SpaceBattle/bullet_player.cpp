//=============================================================================
//
// プレイヤーの弾 [bullet_player.cpp]
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
#include "bullet_player.h"
#include "effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/Bullet.png")
#define SIZE (D3DXVECTOR3(10.0f,10.0f,0.0f))
#define COLOR (D3DXCOLOR(1.0f,0.0f,1.0f,1.0f))
#define LIFE (175)
#define EFFECT_LIFE (7)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletPlayer::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBulletPlayer::CBulletPlayer(int nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBulletPlayer::~CBulletPlayer()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBulletPlayer::TextureLoad(void)
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
void CBulletPlayer::TextureUnload(void)
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
CBulletPlayer * CBulletPlayer::Create(D3DXVECTOR3 Position,D3DXVECTOR3 Speed)
{
	CBulletPlayer * pBulletPlayer;
	pBulletPlayer = new CBulletPlayer;
	pBulletPlayer->Init();
	pBulletPlayer->SetPosition(Position);
	pBulletPlayer->SetMove(Speed);
	return pBulletPlayer;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBulletPlayer::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f,0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f,0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f,1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f,1.0f);
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//弾の初期化関数呼び出し
	CBullet::Init();
	//ショット音の再生
	pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
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
void CBulletPlayer::Uninit(void)
{
	//弾の終了処理関数呼び出し
	CBullet::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBulletPlayer::Update(void)
{
	//移動量の取得
	D3DXVECTOR3 Move = GetMove();
	//もしライフが0になったら
	if (GetLife() <= 0)
	{
		//初期化処理関数呼び出し
		Uninit();
		return;
	}
	//エフェクトの生成
	CEffect::Create(GetPosition(), GetSize(), GetColor(), EFFECT_LIFE);
	//移動量を設定する
	SetMove(Move);
	//衝突判定処理関数呼び出し
	Collision();
	//弾の更新処理関数呼び出し
	CBullet::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CBulletPlayer::Draw(void)
{
	//弾の描画処理関数呼び出し
	CBullet::Draw();
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CBulletPlayer::Death(void)
{
	//初期化処理関数呼び出し
	Uninit();
	return;
}

//=============================================================================
// 衝突判定処理関数
//=============================================================================
void CBulletPlayer::Collision(void)
{
	//敵の取得
	CEnemy * pEnemy = CGameMode::GetEnemy();
	if (pEnemy != NULL)
	{
		//敵との衝突
		if (GetPosition().x + GetSize().x / 2 > pEnemy->GetPosition().x - (pEnemy->GetSize().x / 2) &&
			GetPosition().x - GetSize().x / 2 < pEnemy->GetPosition().x + (pEnemy->GetSize().x / 2) &&
			GetPosition().y + GetSize().y / 2 > pEnemy->GetPosition().y - (pEnemy->GetSize().y / 2) &&
			GetPosition().y - GetSize().y / 2 < pEnemy->GetPosition().y + (pEnemy->GetSize().y / 2))
		{
			//敵のヒット処理関数呼び出し
			pEnemy->Hit();
			//死亡処理関数呼び出し
			Death();
		}
	}
}
