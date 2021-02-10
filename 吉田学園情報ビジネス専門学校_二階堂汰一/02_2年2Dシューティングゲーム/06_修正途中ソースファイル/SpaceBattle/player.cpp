//=============================================================================
//
// プレイヤー [player.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// 警告制御
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "keyboard.h"
#include "joystick.h"
#include "scene2d.h"
#include "mode_game.h"
#include "ui_score.h"
#include "ui_bomb.h"
#include "ui_life.h"
#include "explosion_death.h"
#include "bullet_player.h"
#include "bullet_bomb.h"
#include "player.h"
#include "enemy_dragon.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Player/BattleShip.png")			//テクスチャパス
#define SPEED (5.0f)											//移動速度
#define DEATH_TIME (100)										//死亡時間
#define INVINCIBLE_TIME (80)									//無敵時間
#define INVINCIBLE_COLOR_CHANGE (2)								//色変更
#define INITIAL_BOMB (3)										//初期ボム数
#define INITIAL_LIFE (3)										//初期自機数
#define MINIMUM_LIFE (0)											//体力の最小値
#define MINIMUM_SPEED (0.0f)										//移動速度の最小値
#define MINIMUM_BOMB (0)											//ボムの最小値
#define MINIMUM_SCORE (0)											//スコアの最小値
#define MINIMUM_DEATH_COUNT (0)									//死亡数の最小値
#define MINIMUM_DEATH_TIME (0)										//死亡時間の最小値
#define MINIMUM_INVINCIBLE_TIME (0)								//無敵時間の最小値
#define MINIMUM_BULLET_INTERVAL (0)								//弾の発射間隔の最小値
#define MINIMUM_CONTINUE_COUNT (0)									//コンティニューの最小値
#define BOMB_COST (1000)										//ボム使用時のスコア減算値
#define DEATH_COST (1000)										//死亡時のスコア減算値
#define DEATH_ADD_SCORE (1)										//死亡時のスコア加算地							
#define ANIMATION_VALUE (0.33333f)								//アニメーションの値
#define BULLET_INTERVAL (10)									//弾の発射間隔
#define INVICIBLE_TITME_REMAINDER (0)							//無敵時間の余り
#define BULLET_INTERVAL_REMAINDER (0)							//弾の発射間隔の余り
#define COLOR_TRANSPARENT (D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))	//透明色
#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))					//色
#define BULLET_DAMAGE (0)										//弾へのダメージ
#define LEVEL1_BULLETSPEED (D3DXVECTOR3(0.0f, -10.0f, 0.0f))	//レベル1の弾の速度
#define LEVEL2_LEFTBULLETSPEED (D3DXVECTOR3(cosf(D3DXToRadian (-10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(-10.0f + 90.0f)) * -10.0f, 0.0f))	//レベル2の弾の速度
#define LEVEL2_RIGHTBULLETSPEED (D3DXVECTOR3(cosf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, 0.0f))		//レベル3の弾の速度

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;	//テクスチャへのポインタ
char CPlayer::m_aPlayerName[MAX_NAME] = {};		//プレイヤーネーム
bool CPlayer::m_bReplay = false;				//リプレイの真偽

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene2d(nPriority)
{
	m_Move = INITIAL_MOVE;								//移動量
	m_nLife = MINIMUM_LIFE;								//体力
	m_nBomb = MINIMUM_BOMB;								//爆弾の所持数
	m_nUseBomb = MINIMUM_BOMB;								//爆弾の使用回数
	m_nDeathCount = MINIMUM_DEATH_COUNT;					//死亡数
	m_nContinue = MINIMUM_CONTINUE_COUNT;					//コンティニュー数
	m_nScore = MINIMUM_SCORE;								//スコア
	m_nLevel = LEVEL_NONE;								//レベル
	m_nDeathTime = MINIMUM_DEATH_TIME;						//死亡時間
	m_nInvincibleTime = MINIMUM_INVINCIBLE_TIME;			//無敵時間
	m_nBulletInterval = MINIMUM_BULLET_INTERVAL;			//発射間隔
	m_fSpeed = MINIMUM_SPEED;								//速さ
	memset(m_aInputData, NULL, sizeof(m_aInputData));	//入力情報
	m_State = STATE_NONE;								//状態
	m_Input = INPUT_NONE;								//入力キー情報
	m_Attack = ATTACK_NONE;								//攻撃情報
}	

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CPlayer::TextureLoad(void)
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
void CPlayer::TextureUnload(void)
{
	// テクスチャの破棄
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
CPlayer * CPlayer::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size)
{
	//プレイヤーのポインタ
	CPlayer * pPlayer = NULL;
	//プレイヤーがNULLの場合
	if (pPlayer == NULL)
	{
		//プレイヤーのメモリ確保
		pPlayer = new CPlayer;
	}
	//プレイヤーがNULLではない場合
	if (pPlayer != NULL)
	{
		//プレイヤーの初期化処理関数呼び出し
		pPlayer->Init();
		//プレイヤーの位置を設定する
		pPlayer->SetPosition(Position);
		//プレイヤーのサイズを設定する
		pPlayer->SetSize(Size);
	}
	return pPlayer;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel + ANIMATION_VALUE, 1.0f);
	//2Dシーン管理初期化処理関数呼び出し
	CScene2d::Init();
	//移動速度の初期設定
	m_fSpeed = SPEED;
	//体力の初期設定
	m_nLife = INITIAL_LIFE;
	//初期保持ボム数の初期設定
	m_nBomb = INITIAL_BOMB;
	//レベルの初期設定
	m_nLevel = LEVEL_1;
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	//もしリプレイが真のとき
	if (m_bReplay == true)
	{
		//入力情報読み込み
		InputDataLoad();
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPlayer::Uninit(void)
{
	//2Dシーン管理終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPlayer::Update(void)
{
	//スコアのUIを取得
	CScoreUI * pScoreUI = CGameMode::GetScoreUI();
	//爆弾のUIを取得
	CBombUI * pBombUI = CGameMode::GetBombUI();
	//体力のUIを取得
	CLifeUI * pLifeUI = CGameMode::GetLifeUI();
	//ドラゴンの取得
	CEnemyDragon * pEnemyDragon = CGameMode::GetDragon();
	//2Dシーン管理更新処理関数呼び出し
	CScene2d::Update();
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nLevel + ANIMATION_VALUE, 1.0f);
	//位置を取得
	D3DXVECTOR3 Position = GetPosition();
	//もしリプレイ状態が偽のとき
	if (m_bReplay == false)
	{
		//入力処理関数呼び出し
		Input();
	}
	//もしリプレイ状態が真で死んでいないとき
	else
	{
		//リプレイ関数呼び出し
		Replay();
	}
	//もし状態が無敵状態の時
	if (m_State == STATE_INVINCIBLE)
	{
		//無敵処理関数呼び出し
		Invincible();
	}
	//移動可能範囲処理関数呼び出し
	Position = MovableRange();
	//位置更新
	Position += m_Move;
	//位置の設定
	SetPosition(Position);
	//テクスチャの設定
	SetTexture(aTexture);
	//スコアのUIを更新する
	pScoreUI->SetScore(m_nScore);
	//爆弾のUIを更新する
	pBombUI->SetBomb(m_nBomb);
	//体力のUIを更新する
	pLifeUI->SetLife(m_nLife);
	//タイムカウント処理関数呼び出し
	TimeCount();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPlayer::Draw(void)
{
	//2Dシーン管理描画処理関数呼び出し
	CScene2d::Draw();
}

//=============================================================================
// 体力加算処理関数
//=============================================================================
void CPlayer::AddLife(void)
{
	//体力が最大値に達していないとき
	if (m_nLife < PLAYER_MAX_LIFE)
	{
		//体力を加算する
		m_nLife++;
	}
}

//=============================================================================
// 体力減算処理関数
//=============================================================================
void CPlayer::SubLife(int nValue)
{
	//もし状態が無敵かつ死亡じゃないとき
	if (m_State != STATE_INVINCIBLE && m_State != STATE_DEATH)
	{
		//体力を減算する
		m_nLife -= nValue;
		//死亡処理関数呼び出し
		Death();
		//もし体力が0になったら
		if (m_nLife <= MINIMUM_LIFE)
		{
			//コンティニュー数を加算する
			m_nContinue++;
			//ライフを初期設定する
			m_nLife = INITIAL_LIFE;
		}
	}
}

//=============================================================================
// レベルアップ処理関数
//=============================================================================
void CPlayer::LevelUp(void)
{
	//もしレベルが上限に達していないとき
	if (m_nLevel <= LEVEL_3)
	{
		//レベルを加算する
		m_nLevel++;
	}
}

//=============================================================================
// 爆弾加算処理関数
//=============================================================================
void CPlayer::AddBomb(void)
{
	//もし所持爆弾数が最大量じゃなかったら
	if (m_nBomb <= PLAYER_MAX_BOMB)
	{
		//所持爆弾数を加算する
		m_nBomb++;
	}
}

//=============================================================================
// 爆弾減算処理関数
//=============================================================================
void CPlayer::SubBomb(void)
{
	//爆弾の所持数を1個減らす
	m_nBomb--;
	//爆弾の使用数を加算する
	m_nUseBomb++;
	//スコアを減産する
	SubScore(BOMB_COST);
}

//=============================================================================
// スコア加算処理関数
//=============================================================================
void CPlayer::AddScore(int nValue)
{
	//スコアを加算する
	m_nScore += nValue;
}

//=============================================================================
// スコア減算処理関数
//=============================================================================
void CPlayer::SubScore(int nValue)
{
	//スコアが0より下の場合
	if (m_nScore < MINIMUM_SCORE)
	{
		//スコアを減算する
		m_nScore -= nValue;
	}
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CPlayer::Input(void)
{
	//キーボードの取得
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	//ジョイスティックの取得
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//ジョイスティックの振動取得
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//ゲームモードの取得
	CGameMode * pGameMode = CManager::GetGameMode();
	//プレイヤーが移動していないとき
	m_Move = INITIAL_MOVE;
	//上移動処理
	if (pKeyboard->GetKeyboardPress(DIK_W) || lpDIDevice != NULL &&js.lY == -1000)
	{
		//入力キー情報を上にする
		m_Input = INPUT_UP;
		//入力情報を保存にする
		m_aInputData[pGameMode->GetFlameCount()][INPUT_UP] = 1;
		//移動処理関数呼び出し
		Move();
	}
	//下移動処理
	if (pKeyboard->GetKeyboardPress(DIK_S) || lpDIDevice != NULL &&js.lY == 1000)
	{
		//入力キー情報を下にする
		m_Input = INPUT_DOWN;
		//入力情報を保存する
		m_aInputData[pGameMode->GetFlameCount()][INPUT_DOWN] = 1;
		//移動処理関数呼び出し
		Move();
	}
	//左移動処理
	if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
	{
		//入力キー情報を左にする
		m_Input = INPUT_LEFT;
		//入力情報を保存する
		m_aInputData[pGameMode->GetFlameCount()][INPUT_LEFT] = 1;
		//移動処理関数呼び出し
		Move();
	}
	//右移動処理
	if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
	{
		//入力キー情報を右にする
		m_Input = INPUT_RIGHT;
		//入力情報を保存する
		m_aInputData[pGameMode->GetFlameCount()][INPUT_RIGHT] = 1;
		//移動処理関数呼び出し
		Move();
	}
	//弾発射キー入力処理
	if (pKeyboard->GetKeyboardPress(DIK_SPACE) || lpDIDevice != NULL &&lpDIDevice != NULL && pJoystick->GetJoystickPress(JS_A))
	{
		//発射間隔のカウントを進める
		m_nBulletInterval++;
		//入力情報を保存する
		m_aInputData[pGameMode->GetFlameCount()][INPUT_SHOT] = 1;
		//攻撃情報を弾発射にする
		m_Attack = ATTACK_SHOT;
		//攻撃処理関数呼び出し
		Attack();
	}
	//爆弾発射キー入力処理
	if (pKeyboard->GetKeyboardTrigger(DIK_B) || lpDIDevice != NULL &&pJoystick->GetJoystickTrigger(JS_B))
	{
		//入力情報を保存する
		m_aInputData[pGameMode->GetFlameCount()][INPUT_BOMB] = 1;
		//攻撃情報を爆弾発射にする
		m_Attack = ATTACK_BOMB;
		//攻撃処理関数呼び出し
		Attack();
	}
}

//=============================================================================
// 移動処理関数
//=============================================================================
void CPlayer::Move(void)
{
	//もし死亡状態じゃないとき
	if (m_State != STATE_DEATH)
	{
		switch (m_Input)
		{
			//もし入力情報が上の時
		case INPUT_UP:
			//Y軸の上方向に移動量を加算
			m_Move.y = cosf(D3DX_PI) * m_fSpeed;
			break;
			//もし入力情報が下の時
		case INPUT_DOWN:
			//Y軸の下方向に移動量を加算
			m_Move.y = cosf(D3DX_PI) * -m_fSpeed;
			break;
			//もし入力情報が左の時
		case INPUT_LEFT:
			//X軸の左方向に移動量を加算
			m_Move.x = cosf(D3DX_PI) * m_fSpeed;
			break;
			//もし入力情報が右の時
		case INPUT_RIGHT:
			//X軸の右方向に移動量を加算
			m_Move.x = cosf(D3DX_PI) * -m_fSpeed;
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// 攻撃処理関数
//=============================================================================
void CPlayer::Attack(void)
{
	//移動量を取得
	D3DXVECTOR3 Position = GetPosition();
	//サイズを所得
	D3DXVECTOR3 Size = GetSize();
	//もし死亡状態じゃないとき
	if (m_State != STATE_DEATH)
	{
		switch (m_Attack)
		{
			//攻撃情報がショットの時
		case ATTACK_SHOT:
			//弾の発射感覚処理
			if (m_nBulletInterval % BULLET_INTERVAL == BULLET_INTERVAL_REMAINDER)
			{
				switch (m_nLevel)
				{
					//レベル1の時
				case LEVEL_1:
					//弾の生成
					CBulletPlayer::Create(D3DXVECTOR3(Position.x, Position.y - Size.y / 2, Position.z), LEVEL1_BULLETSPEED);
					break;		
					//レベル2の時
				case LEVEL_2:	
					//弾の生成	
					CBulletPlayer::Create(D3DXVECTOR3(Position.x + Size.x / 5, Position.y - Size.y / 2, Position.z), LEVEL1_BULLETSPEED);
					CBulletPlayer::Create(D3DXVECTOR3(Position.x - Size.x / 5, Position.y - Size.y / 2, Position.z), LEVEL1_BULLETSPEED);
					break;	
					//レベル3の時
				case LEVEL_3:	
					//弾の生成
					CBulletPlayer::Create(D3DXVECTOR3(Position.x + Size.x / 5, Position.y - Size.y / 2, Position.z), LEVEL1_BULLETSPEED);
					CBulletPlayer::Create(D3DXVECTOR3(Position.x - Size.x / 5, Position.y - Size.y / 2, Position.z), LEVEL1_BULLETSPEED);
					CBulletPlayer::Create(D3DXVECTOR3(Position.x, Position.y - Size.y / 2, 0.0f), LEVEL2_LEFTBULLETSPEED);
					CBulletPlayer::Create(D3DXVECTOR3(Position.x, Position.y - Size.y / 2, 0.0f), LEVEL2_RIGHTBULLETSPEED);
					break;
				default:
					break;
				}
			}
			break;
			//攻撃情報がボムの時
		case ATTACK_BOMB:
			//もし爆弾の所持数が1個以上のとき
			if (m_nBomb > MINIMUM_BOMB)
			{
				//爆弾の生成
				CBulletBomb::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y - GetSize().y / 2, 0.0f), BOMB_SPEED);
				//爆弾減算関数呼び出し
				SubBomb();
			}
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CPlayer::Death(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//死亡状態にする
	m_State = STATE_DEATH;
	//爆発エフェクトの生成
	CExplosionDeath::Create(GetPosition());
	//爆発音の再生
	pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
	//スコアを減算する
	SubScore(DEATH_COST);
	//スコアを加算する
	AddScore(DEATH_ADD_SCORE);
	//死亡数を加算する
	m_nDeathCount++;
	//色を透明にする
	D3DXCOLOR Color = COLOR_TRANSPARENT;
	//全ての弾を消す
	DeleteAllBullet();
	//色の設定
	SetColor(Color);
}

//=============================================================================
// 無敵処理関数
//=============================================================================
void CPlayer::Invincible(void)
{
	//色を切り替える
	if (m_nInvincibleTime % INVINCIBLE_COLOR_CHANGE == INVICIBLE_TITME_REMAINDER)
	{
		//頂点数分回す
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			//透明にする
			D3DXCOLOR Color = COLOR_TRANSPARENT;
			//色の設定
			SetColor(Color);
		}
	}
	else
	{
		//頂点数分回す
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			//通常職にする
			D3DXCOLOR Color = COLOR;
			//色の設定
			SetColor(Color);
		}
	}
}

//=============================================================================
// リスポーン処理関数
//=============================================================================
void CPlayer::Respawn(void)
{
	//自機を初期位置に配置
	SetPosition(PLAYER_POS);
	//無敵状態にする
	m_State = STATE_INVINCIBLE;
}

//=============================================================================
// 移動可能範囲処理関数
//=============================================================================
D3DXVECTOR3 CPlayer::MovableRange()
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//サイズを取得する
	D3DXVECTOR3 Size = GetSize();
	//もしプレイヤーが上画面外に行ったら
	if (Position.y - Size.y / 2 < FIELD_HEIGHT_MIN)
	{
		//位置が画面外に移動しないように制御する
		Position.y = Size.y / 2;
	}
	//もしプレイヤーが下画面外に行ったら
	if (Position.y + Size.y > FIELD_HEIGHT)
	{
		//位置が画面外に移動しないように制御する
		Position.y = FIELD_HEIGHT - Size.y;
	}
	//もしプレイヤーが左画面外に行ったら
	if (Position.x - Size.y / 2 < FIELD_WIDTH_MIN)
	{
		//位置が画面外に移動しないように制御する
		Position.x = Size.y / 2 + FIELD_WIDTH_MIN;
	}
	//もしプレイヤーが右画面外に行ったら
	if (Position.x + Size.y / 2 > FIELD_WIDTH)
	{
		//位置が画面外に移動しないように制御する
		Position.x = FIELD_WIDTH - Size.y / 2;
	}
	return Position;
}

//=============================================================================
// リプレイ処理関数
//=============================================================================
void CPlayer::Replay(void)
{
	//ゲームモードの取得
	CGameMode * pGameMode = CManager::GetGameMode();
	//プレイヤーが移動していないとき
	m_Move = INITIAL_MOVE;
	//上キーの入力情報があるとき
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_UP] == '1')
	{
		//入力キー情報を上にする
		m_Input = INPUT_UP;
		//移動処理関数呼び出し
		Move();
	}
	//下キーの入力情報があるとき
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_DOWN] == '1')
	{
		//入力キー情報を下にする
		m_Input = INPUT_DOWN;
		//移動処理関数呼び出し
		Move();
	}
	//左キーの入力情報があるとき
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_LEFT] == '1')
	{
		//入力キー情報を左にする
		m_Input = INPUT_LEFT;
		//移動処理関数呼び出し
		Move();
	}
	//右キーの入力情報があるとき
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_RIGHT] == '1')
	{
		//入力キー情報を右にする
		m_Input = INPUT_RIGHT;
		//移動処理関数呼び出し
		Move();
	}
	//射撃キーの入力情報があるとき
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_SHOT] == '1')
	{
		//発射間隔のカウントを進める
		m_nBulletInterval++;
		//攻撃情報を弾発射にする
		m_Attack = ATTACK_SHOT;
		//攻撃処理関数呼び出し
		Attack();
	}
	//爆弾発射キーの入力情報があるとき
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_BOMB] == '1')
	{
		//攻撃情報を爆弾発射にする
		m_Attack = ATTACK_BOMB;
		//攻撃処理関数呼び出し
		Attack();
	}
}

//=============================================================================
// 全弾破棄処理関数
//=============================================================================
void CPlayer::DeleteAllBullet(void)
{
	//シーンの総数分回す
	for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
	{
		//シーンの取得
		CScene * pScene = GetScene(PRIORITY_BULLET, nCountScene);
		//もしシーンがNULLじゃない場合
		if (pScene != NULL)
		{
			//弾のポインタ
			CBullet * pBullet = dynamic_cast<CBullet*> (pScene);
			//弾のポインタがNULLじゃない場合
			if (pBullet != NULL)
			{
				//弾のライフを0にする
				pBullet->SetLife(BULLET_DAMAGE);
			}
		}
	}
}

//=============================================================================
// タイムカウント処理関数
//=============================================================================
void CPlayer::TimeCount(void)
{
	switch (m_State)
	{
		//状態が死亡状態の時
	case STATE_DEATH:
		//死亡時間を加算する
		m_nDeathTime++;
		//弾全消去
		DeleteAllBullet();
		//無敵状態に移行する
		if (m_nDeathTime >= DEATH_TIME)
		{
			//リスポーン処理関数呼び出し
			Respawn();
			//死亡時間を初期化する
			m_nDeathTime = MINIMUM_DEATH_TIME;
		}
		break;
		//状態が無敵状態の時
	case STATE_INVINCIBLE:
		//無敵時間を加算する
		m_nInvincibleTime++;
		//弾全消去
		DeleteAllBullet();
		//無状態に移行する
		if (m_nInvincibleTime >= INVINCIBLE_TIME)
		{
			//状態を無にする
			m_State = STATE_NONE;
			//無敵時間を初期化する
			m_nInvincibleTime = MINIMUM_INVINCIBLE_TIME;
		}
		break;
	default:
		//色を設定する
		SetColor(COLOR);
		break;
	}
}

//=============================================================================
// クリア処理関数
//=============================================================================
void CPlayer::Clear(void)
{
	//もしリプレイモードでは無い場合
	if (m_bReplay == false)
	{
		//入力情報保存処理関数呼び出し
		InputDataSave();
	}
	else
	{
		//リプレイを偽にする
		m_bReplay = false;
	}
	//データ保存処理関数呼び出し
	DataSave();
	//リザルトへ遷移
	CManager::StartFade(CManager::MODE_RESULT);
}

//=============================================================================
// データ保存処理関数
//=============================================================================
void CPlayer::DataSave(void)
{
	//ファイルのポインタ
	FILE * pFile;
	//ファイルの書き込み
	pFile = fopen("data/Text/PlayerData.txt", "w");
	//ファイルのNULLチェック
	if (pFile != NULL)
	{
		//名前を記録
		fprintf(pFile, "%s\n", &m_aPlayerName);
		//死亡数を記録
		fprintf(pFile, "%d\n", m_nDeathCount);
		//コンティニュー数を記録
		fprintf(pFile, "%d\n", m_nContinue);
		//ボムの使用回数を記録
		fprintf(pFile, "%d\n", m_nUseBomb);
		//スコアを記録
		fprintf(pFile, "%d\n", m_nScore);
		//ファイルを閉じる
		fclose(pFile);
	}
}

//=============================================================================
// 入力情報保存処理関数
//=============================================================================
void CPlayer::InputDataSave(void)
{
	//ファイルのポインタ
	FILE * pFile;
	//ゲームモードの取得
	CGameMode * pGameMode = CManager::GetGameMode();
	//ファイルの書き込み
	pFile = fopen("data/Text/InputData.txt", "w");
	//ファイルのNULLチェック
	if (pFile != NULL)
	{
		//ゲームのフレーム数だけ回す
		for (int nCount = 0; nCount < pGameMode->GetFlameCount(); nCount++)
		{
			//上方向の入力情報を保存する
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_UP]);
			//下方向の入力情報を保存する
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_DOWN]);
			//左方向の入力情報を保存する
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_LEFT]);
			//右方向の入力情報を保存する
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_RIGHT]);
			//爆弾発射の入力情報を保存する
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_BOMB]);
			//弾発射の入力情報を保存する
			fprintf(pFile, "%d\n", m_aInputData[nCount][INPUT_SHOT]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}

//=============================================================================
// 入力情報読み込み処理関数
//=============================================================================
void CPlayer::InputDataLoad(void)
{
	//ファイルのポインタ
	FILE *pFile;
	//ファイルの読み込み
	pFile = fopen("data/TEXT/InputData.txt", "r");
	//ファイルのNULLチェック
	if (pFile != NULL)
	{
		//フレームの最大値分回す
		for (int nCount = 0; nCount < MAX_FLAME; nCount++)
		{
			//入力情報読み込み
			fscanf(pFile, "%s", &m_aInputData[nCount][INPUT_UP]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}
//=============================================================================
// 名前取得関数
//=============================================================================
void CPlayer::SetPlayerName(int nCount, char aName)
{
	//名前を取得する
	m_aPlayerName[nCount] = aName;
}