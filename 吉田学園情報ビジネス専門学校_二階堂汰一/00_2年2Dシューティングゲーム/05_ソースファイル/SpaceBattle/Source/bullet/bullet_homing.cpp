//=============================================================================
//
// ホーミング弾 [bullet_horming.cpp]
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
#include "bullet_homing.h"
#include "Player/player.h"
#include "Effect/effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/bullet.png")	//テクスチャ
#define SIZE (D3DXVECTOR3(10.0f,10.0f,0.0f))		//サイズ
#define COLOR (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))		//色
#define MINIMUM_LIFE (0)							//体力の最小値
#define LIFE (150)									//体力
#define MINIMUM_MOVE (0)							//移動量の最小値
#define MOVE (5.0f)									//移動量
#define EFFECT_LIFE (7)								//エフェクトライフ

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBulletHoming::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBulletHoming::CBulletHoming()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBulletHoming::~CBulletHoming()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBulletHoming::TextureLoad(void)
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
void CBulletHoming::TextureUnload(void)
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
CBulletHoming * CBulletHoming::Create(D3DXVECTOR3 Position)
{
	//ホーミング弾のポインタ
	CBulletHoming * pBulletHoming = NULL;
	//もしホーミング弾がNULLの場合
	if (pBulletHoming == NULL)
	{
		//ホーミング弾のメモリ確保
		pBulletHoming = new CBulletHoming;
		//もしホーミング弾がNULLじゃない場合
		if (pBulletHoming != NULL)
		{
			//初期化処理関数呼び出し
			pBulletHoming->Init();
			//位置を設定する
			pBulletHoming->SetPosition(Position);
		}
	}
	//ホーミング弾のポインタを返す
	return pBulletHoming;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBulletHoming::Init(void)
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
	//体力の設定
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
void CBulletHoming::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CBulletEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBulletHoming::Update(void)
{
	//敵の更新処理関数呼び出し
	CBulletEnemy::Update();
	//追尾処理関数呼び出し
	Homing();
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
void CBulletHoming::Draw(void)
{
	//敵の描画処理関数呼び出し
	CBulletEnemy::Draw();
}

//=============================================================================
// 追尾処理関数
//=============================================================================
void CBulletHoming::Homing(void)
{
	//位置を取得
	D3DXVECTOR3 Position = GetPosition();
	//移動量を取得
	D3DXVECTOR3 Move = GetMove();
	//プレイヤー取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしプレイヤーがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//目標の位置を取得
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//目標との距離
		float m_fDistance = float(sqrt((PlayerPosition.x - Position.x) * (PlayerPosition.x - Position.x) + (PlayerPosition.y - Position.y) * (PlayerPosition.y - Position.y)));
		//もし目標の距離なら
		if (m_fDistance)
		{
			//移動量を設定する
			Move.x = ((PlayerPosition.x - GetPosition().x) / m_fDistance * MOVE);
			Move.y = ((PlayerPosition.y - GetPosition().y) / m_fDistance * MOVE);
		}
		else
		{
			//移動量を代入する
			Move.x = MINIMUM_MOVE;
			Move.y = MOVE;
		}
		//移動量を設定する
		SetMove(Move);
	}
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CBulletHoming::Death(void)
{
	//終了処理関数呼び出し
	Uninit();
	return;
}
