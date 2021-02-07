//=============================================================================
//
// ドラゴン [enemy_dragon.cpp]
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
#include "enemy_dragon.h"
#include "bullet_fireball.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/dragon.png")
#define SIZE (D3DXVECTOR3(600.0f,600.0f,0.0f))
#define LIFE (300)
#define SCALE (0.1f)
#define ADD_SCALE (0.01f)
#define SCORE (100000)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyDragon::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyDragon::CEnemyDragon(int nPriority) : CEnemy(nPriority)
{
	m_nPatternAnime = 0;	//パターンアニメ
	m_nCounterAnime = 0;	//カウンターアニメ
	m_nBulletTime = 0;		//弾の発射間隔
	m_TargetDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bCharge = false;
	m_nChargeTime = 0;
	m_pBulletFireBall = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyDragon::~CEnemyDragon()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CEnemyDragon::TextureLoad(void)
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
void CEnemyDragon::TextureUnload(void)
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
CEnemyDragon * CEnemyDragon::Create(D3DXVECTOR3 Position)
{
	CEnemyDragon * pEnemyDragon;
	pEnemyDragon = new CEnemyDragon;
	pEnemyDragon->Init();
	pEnemyDragon->SetPosition(Position);
	return pEnemyDragon;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEnemyDragon::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.1666f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.1666f * m_nPatternAnime + 0.1666f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.1666f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.1666f * m_nPatternAnime + 0.1666f, 1.0f);
	//敵の初期化処理関数呼び出し
	CEnemy::Init();
	//サイズの初期設定
	SetSize(SIZE);
	//スケールの初期設定
	SetScale(SCALE);
	//体力の初期設定
	SetLife(LIFE);
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	//BGMの再生
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_DRAGON);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CEnemyDragon::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CEnemyDragon::Update(void)
{
	if (m_bCharge == true)
	{
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		if (GetScale() >= 1.0f)
		{
			//目標距離に近づいたら目標を再設定する
			if (GetPosition().x >= m_TargetPos.x - 50 / 2 &&
				GetPosition().x < m_TargetPos.x + 50 / 2 &&
				GetPosition().y >= m_TargetPos.y - 50 / 2 &&
				GetPosition().y < m_TargetPos.y + 50 / 2)
			{
				//ランダムシード値
				int nRandSeed = rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500);
				srand((unsigned int)nRandSeed);
				m_TargetPos.x = (float)(rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500));//目標距離の決定
				m_TargetPos.y = (float)(rand() % 300 + 200);
			}
			else
			{
				m_TargetDistance = D3DXVECTOR3(m_TargetPos.x - GetPosition().x, m_TargetPos.y - GetPosition().y, 0.0f);//目標までの距離を算出
				SetRotation(D3DXVECTOR3(GetRotation().x, atan2f(m_TargetDistance.y, m_TargetDistance.x), GetRotation().z));
				SetMove(D3DXVECTOR3(cosf(GetRotation().y)*2.5f, sinf(GetRotation().y)*2.5f, 0.0f));
			}
			if (GetPosition().x > FIELD_WIDTH - 200)
			{
				//ランダムシード値
				int nRandSeed = rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500);
				srand((unsigned int)nRandSeed);
				m_TargetPos.x = (float)(rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500));//目標距離の決定
				m_TargetPos.y = (float)(rand() % 300 + 200);
				m_TargetPos.x += -600.0f;
			}
			if (GetPosition().x < FIELD_WIDTH_MIN + 200)
			{
				//ランダムシード値
				int nRandSeed = rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500);
				srand((unsigned int)nRandSeed);
				m_TargetPos.x = (float)(rand() % (FIELD_WIDTH - 500) + (FIELD_WIDTH_MIN + 500));//目標距離の決定
				m_TargetPos.y = (float)(rand() % 300 + 200);
				m_TargetPos.x += 200.0f;
			}
		}
	}
	//敵の更新処理関数呼び出し
	CEnemy::Update();
	//拡縮処理関数呼び出し
	Scale();
	//アニメーション処理関数呼び出し
	Animation();
	//もしライフが0になったら
	if (GetLife() <= 0)
	{
		//死亡処理関数呼び出し
		Death();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CEnemyDragon::Draw(void)
{
	//敵の描画処理関数呼び出し
	CEnemy::Draw();
}

//=============================================================================
// 拡縮処理関数
//=============================================================================
void CEnemyDragon::Scale(void)
{
	//拡大率を取得する
	float fScale = GetScale();
	//もし拡大率が1倍以下の場合
	if (fScale <= 1.0f)
	{
		//拡大する
		fScale += ADD_SCALE;
	}
	else
	{
		//攻撃処理関数呼び出し
		Attack();
	}
	//拡縮を設定
	SetScale(fScale);
}

//=============================================================================
// 攻撃処理関数
//=============================================================================
void CEnemyDragon::Attack(void)
{
	//位置を取得
	D3DXVECTOR3 Position = GetPosition();
	//サイズを取得
	D3DXVECTOR3 Size = GetSize();
	//プレイヤーを取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		//プレイヤーの位置を取得
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//もしプレイヤーの位置が下の場合
		if (PlayerPosition.y >= Position.y)
		{
			if (m_nBulletTime % 400 == 0)
			{
				//火球の発射
				m_pBulletFireBall = CBulletFireball::Create(D3DXVECTOR3(Position.x, Position.y + Size.y / 2, 0.0f));
				m_bCharge = true;
			}
		}
	}
	if (m_bCharge == true)
	{
		if (m_nChargeTime >= 70)
		{
			m_bCharge = false;
			m_nChargeTime = 0;
		}
		m_nChargeTime++;
	}
	//バレットの発射間隔を進める
	m_nBulletTime++;
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CEnemyDragon::Death(void)
{
	//プレイヤーを取得する
	CPlayer * pPlayer = CGameMode::GetPlayer();
	if (pPlayer != NULL)
	{
		//プレイヤーのスコアを加算する
 		pPlayer->AddScore(SCORE);
		pPlayer->Clear();
	}
	//終了処理関数呼び出し
	Uninit();
	return;
}

//=============================================================================
// アニメーション処理関数
//=============================================================================
void CEnemyDragon::Animation(void)
{
	//カウントインクリメント
	m_nCounterAnime++;
	//カウントが4以上になった場合
	if (m_nCounterAnime > 24)
	{
		//カウントを0にする
		m_nCounterAnime = 0;
		//パターンのインクリメント
		m_nPatternAnime++;
		//もしパターンアニメが4になったら
		if (m_nPatternAnime > 4)
		{
			//パターンアニメを初期化する
			m_nPatternAnime = 0;
		}
	}
	//アニメーションのカウントを進める
	m_nCounterAnime++;
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.1666f * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.1666f * m_nPatternAnime + 0.1666f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.1666f * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.1666f * m_nPatternAnime + 0.1666f, 1.0f);
	//テクスチャの設定
	SetTexture(aTexture);
}
