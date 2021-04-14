//=============================================================================
//
// プレイヤーの弾 [bullet_player.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Mode/mode_game.h"
#include "Base/renderer.h"
#include "Base/sound.h"
#include "Player/player.h"
#include "Enemy/enemy.h"
#include "bullet_player.h"
#include "Effect/effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/Bullet.png")	//テクスチャ
#define SIZE (D3DXVECTOR3(10.0f,10.0f,0.0f))		//サイズ
#define COLOR (D3DXCOLOR(1.0f,0.0f,1.0f,1.0f))		//色
#define MINIMUM_LIFE (0)							//体力の最小値
#define LIFE (175)									//体力
#define EFFECT_LIFE (7)								//エフェクトの体力

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletPlayer::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBulletPlayer::CBulletPlayer()
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
void CBulletPlayer::TextureUnload(void)
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
CBulletPlayer * CBulletPlayer::Create(D3DXVECTOR3 Position,D3DXVECTOR3 Speed)
{
	//プレイヤーの弾のポインタ
	CBulletPlayer * pBulletPlayer = NULL;
	//もしプレイヤーの弾がNULLの場合
	if (pBulletPlayer == NULL)
	{
		//プレイヤーの弾のメモリ確保
		pBulletPlayer = new CBulletPlayer;
		//もしプレイヤーの弾がNULLじゃない場合
		if (pBulletPlayer != NULL)
		{
			//初期化処理関数呼び出し
			pBulletPlayer->Init();
			//位置を設定する
			pBulletPlayer->SetPosition(Position);
			//移動量を設定する
			pBulletPlayer->SetMove(Speed);
		}
	}
	//プレイヤーのポインタの弾を返す
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
	//もしサウンドがNULLじゃない場合
	if (pSound != NULL)
	{
		//ショット音の再生
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
	}
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
	//エフェクトの生成
	CEffect::Create(GetPosition(), GetSize(), GetColor(), EFFECT_LIFE);
	//移動量を設定する
	SetMove(Move);
	//弾の更新処理関数呼び出し
	CBullet::Update();
	//衝突判定処理関数呼び出し
	Collision();
	//もしライフが0になったら
	if (GetLife() <= MINIMUM_LIFE)
	{
		//初期化処理関数呼び出し
		Uninit();
		return;
	}
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
	//敵のプライオリティ分回す
	for (int nCountPriority = PRIORITY_BULLET; nCountPriority <= PRIORITY_ENEMY; nCountPriority++)
	{
		//シーンの総数分回す
		for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
		{
			//シーンの取得
			CScene * pScene = GetScene(nCountPriority, nCountScene);
			//もしシーンがNULLじゃない場合
			if (pScene != NULL)
			{
				//オブジェタイプの取得
				OBJECT_TYPE ObjType = pScene->GetObjectType();
				//もしオブジェクトタイプが敵だったら
				if (ObjType == OBJECT_TYPE_ENEMY)
				{
					//敵のポインタ取得
					CEnemy * pEnemy = dynamic_cast<CEnemy*> (pScene);
					//もし敵のポインタがNULLじゃない場合
					if (pEnemy != NULL)
					{
						//敵の位置を取得
						D3DXVECTOR3 EnemyPosition = pEnemy->GetPosition();
						//敵のサイズを取得
						D3DXVECTOR3 EnemySize = pEnemy->GetSize();
						//敵との衝突判定
						if (GetPosition().x + GetSize().x / 2 > EnemyPosition.x - (EnemySize.x / 2) &&
							GetPosition().x - GetSize().x / 2 < EnemyPosition.x + (EnemySize.x / 2) &&
							GetPosition().y + GetSize().y / 2 > EnemyPosition.y - (EnemySize.y / 2) &&
							GetPosition().y - GetSize().y / 2 < EnemyPosition.y + (EnemySize.y / 2))
						{
							//敵のヒット処理関数呼び出し
							pEnemy->Hit();
							//ライフを0にする
							SetLife(MINIMUM_LIFE);
							return;
						}
					}
				}
			}
		}
	}
}
