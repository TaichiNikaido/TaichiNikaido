//=============================================================================
//
// ドラゴン [enemy_dragon.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Mode/mode_game.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/scene2d.h"
#include "Base/sound.h"
#include "enemy_dragon.h"
#include "Bullet/bullet_fireball.h"
#include "Player/player.h"
#include "Effect/explosion_dragon.h"
#include "2DPolygon/gameclear_logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Enemy/dragon.png")				//テクスチャ
#define SIZE (D3DXVECTOR3(600.0f,600.0f,0.0f))					//サイズ
#define INITIAL_TARGET_DISTANCE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//目標までの距離
#define MINIMUM_LIFE (0)										//体力の最少値
#define LIFE (450)												//体力
#define MINIMUM_SCALE (0.1f)									//最小の拡大値
#define MAX_SCALE (1.0f)										//最大の拡大値
#define ADD_SCALE (0.01f)										//加算する拡大量
#define SCORE (100000)											//スコア
#define INITIAL_PATTERN_ANIME (0)								//パターンアニメの初期値
#define MAX_PATTERN_ANIME (4)									//パターンアニメの最大値
#define INITIAL_COUNTER_ANIME (0)								//カウンターアニメの初期値
#define MAX_COUNTER_ANIME (24)									//カウンターアニメの最大値
#define MINIMUM_BULLET_TIME (0)									//弾の発射最小時間
#define MINIMUM_CHARGE_TIME (0)									//チャージの最小時間
#define SHOT_TIME (400)											//弾を発射するまでの時間
#define ANIMATION_VALUE (0.1666f)								//アニメーションの値
#define RANDSEED_VALUE (500)									//シード値
#define MOVE_SPEED (2.5f)										//移動量
#define RANDMOVE_MAX_X (600.0f)									//ランダム最大移動量
#define RANDMOVE_MIN_X (200.0f)									//ランダム最小移動量
#define RANDMOVE_MAX_Y (300)									//ランダム最大移動量

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemyDragon::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyDragon::CEnemyDragon()
{
	m_nPatternAnime = INITIAL_PATTERN_ANIME;		//パターンアニメ
	m_nCounterAnime = INITIAL_COUNTER_ANIME;		//カウンターアニメ
	m_nBulletTime = MINIMUM_BULLET_TIME;			//弾の発射までの時間
	m_TargetDistance = INITIAL_TARGET_DISTANCE;		//目標までの距離
	m_TargetPosition = INITIAL_TARGET_DISTANCE;			//目標までの距離
	m_bCharge = false;								//チャージしてるか
	m_bDeath = false;								//死亡したかどうか
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
void CEnemyDragon::TextureUnload(void)
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
CEnemyDragon * CEnemyDragon::Create(D3DXVECTOR3 Position)
{
	//ドラゴンのポインタ
	CEnemyDragon * pEnemyDragon = NULL;
	//もしドラゴンのポインタがNULLの場合
	if (pEnemyDragon == NULL)
	{
		//ドラゴンのメモリ確保
		pEnemyDragon = new CEnemyDragon;
		//もしドラゴンのポインタがNULLじゃない場合
		if (pEnemyDragon != NULL)
		{
			//初期化処理関数呼び出し
			pEnemyDragon->Init();
			//位置設定関数呼び出し
			pEnemyDragon->SetPosition(Position);
		}
	}
	//ドラゴンのポインタを返す
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
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
	//敵の初期化処理関数呼び出し
	CEnemy::Init();
	//サイズの初期設定
	SetSize(SIZE);
	//スケールの初期設定
	SetScale(MINIMUM_SCALE);
	//体力の初期設定
	SetLife(LIFE);
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	//もしサウンドのポインタがNULLではない場合
	if (pSound != NULL)
	{
		//BGMの再生
		pSound->PlaySound(CSound::SOUND_LABEL_BGM_DRAGON);
	}
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
	//敵の更新処理関数呼び出し
	CEnemy::Update();
	//拡縮処理関数呼び出し
	Scale();
	//AI処理関数呼び出し
	AI();
	//アニメーション処理関数呼び出し
	Animation();
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
	if (fScale <= MAX_SCALE)
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
	//衝突サイズの初期設定
	SetCollisionSize(D3DXVECTOR3(SIZE.x - 200.0f,SIZE.y - 200.0f,SIZE.z) * fScale);
}

//=============================================================================
// AI処理関数
//=============================================================================
void CEnemyDragon::AI(void)
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//プレイヤーを取得する
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしプレイヤーのポインタがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//プレイヤーの位置を取得する
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//プレイヤーのサイズを取得する
		D3DXVECTOR3 PlayerSize = GetSize();
		//もしチャージが完了したら
		if (m_bCharge == true)
		{
			//移動量を設定する
			SetMove(INITIAL_D3DXVECTOR3);
		}
		else
		{
			//もしスケールが最大値以上になったら
			if (GetScale() >= MAX_SCALE)
			{
				//目標距離に近づいたら目標を再設定する
				if (Position.x >= m_TargetPosition.x - PlayerSize.x / 2 &&
					Position.x < m_TargetPosition.x + PlayerSize.x / 2 &&
					Position.y >= m_TargetPosition.y - PlayerSize.y / 2 &&
					Position.y < m_TargetPosition.y + PlayerSize.y / 2)
				{
					//ランダムシード値
					int nRandSeed = rand() % (FIELD_WIDTH - RANDSEED_VALUE) + (FIELD_WIDTH_MIN + RANDSEED_VALUE);
					srand((unsigned int)nRandSeed);
					m_TargetPosition.x = (float)(rand() % (FIELD_WIDTH - RANDSEED_VALUE) + (FIELD_WIDTH_MIN + RANDSEED_VALUE));//目標距離の決定
					m_TargetPosition.y = (float)(rand() % RANDMOVE_MAX_Y);
				}
				else
				{
					m_TargetDistance = D3DXVECTOR3(m_TargetPosition.x - Position.x, m_TargetPosition.y - Position.y, 0.0f);//目標までの距離を算出
					SetRotation(D3DXVECTOR3(Position.x, atan2f(m_TargetDistance.y, m_TargetDistance.x), Position.z));
					SetMove(D3DXVECTOR3(cosf(GetRotation().y)*MOVE_SPEED, sinf(GetRotation().y)*MOVE_SPEED, 0.0f));
				}
				if (Position.x > FIELD_WIDTH - RANDMOVE_MIN_X)
				{
					//ランダムシード値
					int nRandSeed = rand() % (FIELD_WIDTH - RANDSEED_VALUE) + (FIELD_WIDTH_MIN + RANDSEED_VALUE);
					srand((unsigned int)nRandSeed);
					m_TargetPosition.x = (float)(rand() % (FIELD_WIDTH - RANDSEED_VALUE) + (FIELD_WIDTH_MIN + RANDSEED_VALUE));//目標距離の決定
					m_TargetPosition.y = (float)(rand() % RANDMOVE_MAX_Y);
					m_TargetPosition.x += -RANDMOVE_MAX_X;
				}
				if (Position.x < FIELD_WIDTH_MIN + RANDMOVE_MIN_X)
				{
					//ランダムシード値
					int nRandSeed = rand() % (FIELD_WIDTH - RANDSEED_VALUE) + (FIELD_WIDTH_MIN + RANDSEED_VALUE);
					srand((unsigned int)nRandSeed);
					m_TargetPosition.x = (float)(rand() % (FIELD_WIDTH - RANDSEED_VALUE) + (FIELD_WIDTH_MIN + RANDSEED_VALUE));//目標距離の決定
					m_TargetPosition.y = (float)(rand() % RANDMOVE_MAX_Y);
					m_TargetPosition.x += RANDMOVE_MIN_X;
				}
			}
		}
	}
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
			//もし発射までの時間
			if (m_nBulletTime % SHOT_TIME == REMAINDER)
			{
				//火球の発射
				CGameMode::SetFireBall(CBulletFireball::Create(D3DXVECTOR3(Position.x, Position.y + Size.y / 2, 0.0f)));
			}
		}
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
	//火球を取得する
	CBulletFireball * pBulletFireBall = CGameMode::GetBulletFireBall();
	//もしプレイヤーのポインタがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//プレイヤーのスコアを加算する
 		pPlayer->AddScore(SCORE);
	}
	//死亡状態にする
	m_bDeath = true;
	//ゲームクリアロゴの生成
	CGameClearLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	//ドラゴンの爆発生成
	CExplosionDragon::Create();
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
	//アニメカウントが最大になった場合
	if (m_nCounterAnime > MAX_COUNTER_ANIME)
	{
		//カウントを0にする
		m_nCounterAnime = INITIAL_COUNTER_ANIME;
		//パターンのインクリメント
		m_nPatternAnime++;
		//もしパターンアニメが4になったら
		if (m_nPatternAnime > MAX_PATTERN_ANIME)
		{
			//パターンアニメを初期化する
			m_nPatternAnime = INITIAL_PATTERN_ANIME;
		}
	}
	//アニメーションのカウントを進める
	m_nCounterAnime++;
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
	//テクスチャの設定
	SetTexture(aTexture);
}