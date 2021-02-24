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
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/explosion.png")	//テクスチャ
#define SIZE (D3DXVECTOR3(500.0f,500.0f,0.0f))	//サイズ
#define MINIMUM_COUNTER__ANIME (0)				//アニメーション最小カウンタ
#define MINIMUM_PATTERN_ANIME (0)				//アニメーション最小パターン
#define ANIMATION_VALUE (0.125f)				//アニメーションの値
#define MAX_COUNTER_ANIME (4)					//アニメーション最大カウンタ
#define MAX_PATTERN_ANIME (8)					//アニメーション最大パターン

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosionBomb::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosionBomb::CExplosionBomb()
{
	m_nCounterAnime = MINIMUM_COUNTER__ANIME;	//アニメカウンタ
	m_nPatternAnime = MINIMUM_PATTERN_ANIME;	//アニメパターン
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
void CExplosionBomb::TextureUnload(void)
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
CExplosionBomb * CExplosionBomb::Create(D3DXVECTOR3 Position)
{
	//爆弾の爆破のポインタ
	CExplosionBomb * pExplosionBomb = NULL;
	//もし爆弾の爆発のポインタがNULLの場合
	if (pExplosionBomb == NULL)
	{
		//爆弾の爆発のメモリ確保
		pExplosionBomb = new CExplosionBomb;
		//もし爆弾の爆発のポインタがNULLじゃない場合
		if (pExplosionBomb != NULL)
		{
			//初期化処理関数呼び出し
			pExplosionBomb->Init();
			//位置を設定する
			pExplosionBomb->SetPosition(Position);
		}
	}
	//爆弾の爆破のポインタを返す
	return pExplosionBomb;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CExplosionBomb::Init(void)
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
	//当たり判定
	Collision();
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
// 衝突判定処理
//=============================================================================
void CExplosionBomb::Collision(void)
{
	//弾のプライオリティから敵のプライオリティまで回す
	for (int nCountPriority = 0; nCountPriority <= PRIORITY_ENEMY + 1; nCountPriority++)
	{
		//シーンの総数分回す
		for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
		{
			//シーンの取得
			CScene * pScene = GetScene(nCountPriority, nCountScene);
			//もしシーンがNULLじゃない場合
			if (pScene != NULL)
			{
				//もしオブジェクトタイプが火球じゃないとき
				if (pScene->GetObjType() != CScene::OBJTYPE_FIRE_BALL)
				{
					//敵のポインタ
					CEnemy * pEnemy = dynamic_cast<CEnemy*> (pScene);
					//もし敵のポインタがNULLじゃない場合
					if (pEnemy != NULL)
					{
						//敵の位置を取得する
						D3DXVECTOR3 EnemyPosition = pEnemy->GetPosition();
						//敵のサイズを取得する
						D3DXVECTOR3 EnemySize = pEnemy->GetSize();
						//敵との衝突判定
						if (GetPosition().x + GetSize().x / 2 > EnemyPosition.x - (EnemySize.x / 2) &&
							GetPosition().x - GetSize().x / 2 < EnemyPosition.x + (EnemySize.x / 2) &&
							GetPosition().y + GetSize().y / 2 > EnemyPosition.y - (EnemySize.y / 2) &&
							GetPosition().y - GetSize().y / 2 < EnemyPosition.y + (EnemySize.y / 2))
						{
							//敵のヒット処理関数呼び出し
							pEnemy->Hit();
						}
					}
					//弾のポインタ
					CBullet * pBullet = dynamic_cast<CBullet*> (pScene);
					//もし弾のポインタがNULLじゃない場合
					if (pBullet != NULL)
					{
						//弾の位置を取得する
						D3DXVECTOR3 BulletPosition = pBullet->GetPosition();
						//弾のサイズを取得する
						D3DXVECTOR3 BulletSize = pBullet->GetSize();
						//敵との衝突
						if (GetPosition().x + GetSize().x / 2 > BulletPosition.x - (BulletSize.x / 2) &&
							GetPosition().x - GetSize().x / 2 < BulletPosition.x + (BulletSize.x / 2) &&
							GetPosition().y + GetSize().y / 2 > BulletPosition.y - (BulletSize.y / 2) &&
							GetPosition().y - GetSize().y / 2 < BulletPosition.y + (BulletSize.y / 2))
						{
							//弾の初期化処理関数呼び出し
							pBullet->Uninit();
						}
					}
				}
			}
		}
	}
}
