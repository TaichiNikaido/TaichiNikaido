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
#define TEXTURE ("Data/Texture/Bullet/Bullet_flower.png")
#define LIFE (500)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletFlower::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBulletFlower::CBulletFlower(int nPriority)
{
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
void CBulletFlower::TextureUnload(void)
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
CBulletFlower * CBulletFlower::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed)
{
	CBulletFlower * pBulletFlower;
	pBulletFlower = new CBulletFlower;
	pBulletFlower->Init();
	pBulletFlower->SetPosition(Position);
	pBulletFlower->SetMove(Speed);
	return pBulletFlower;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBulletFlower::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//敵の弾の初期化処理関数呼び出し
	CBulletEnemy::Init();
	//色の初期設定
	//SetColor(COLOR);
	//体力の初期設定
	SetLife(LIFE);
	////テクスチャの設定
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
	//プレイヤーを取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//移動量を取得
	D3DXVECTOR3 Move = GetMove();
	//ターゲットの位置を取得
	D3DXVECTOR3 TartgetPosition = pPlayer->GetPosition();
	////目標までの距離を算出//今回は生成時のプレイヤーに向けての方向指定のみ
	D3DXVECTOR3 m_TargetDistance = D3DXVECTOR3(TartgetPosition.x - GetPosition().x, TartgetPosition.y - GetPosition().y, 0.0f);
	float Rotation = atan2f(m_TargetDistance.y, m_TargetDistance.x);
	Move = D3DXVECTOR3(cosf(Rotation)*5.5f, sinf(Rotation)*5.5f, 0.0f);
	//移動量の設定
	SetMove(Move);
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CBulletFlower::Draw(void)
{
	//敵の描画処理関数呼び出し
	CBulletEnemy::Draw();
}