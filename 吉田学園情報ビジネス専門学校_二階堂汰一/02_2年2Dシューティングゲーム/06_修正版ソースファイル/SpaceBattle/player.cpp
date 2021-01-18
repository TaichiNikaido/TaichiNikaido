//=============================================================================
//
// プレイヤー処理 [player.cpp]
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
#include "mode_game.h"
#include "renderer.h"
#include "scene2d.h"
#include "keyboard.h"
#include "joystick.h"
#include "sound.h"
#include "player.h"
#include "bullet_player.h"
#include "bullet_bomb.h"
#include "ui_score.h"
#include "ui_bomb.h"
#include "ui_life.h"
#include "explosion_death.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Player/BattleShip.png")
#define DEATH_TIME (100)
#define INVINCIBLE_TIME (80)
#define INITIAL_BOMB (3)
#define INITIAL_LIFE (3)
#define BOMB_COST (1000)
#define DEATH_COST (1000)
#define LEVEL1_BULLETSPEED (D3DXVECTOR3(0.0f, -10.0f, 0.0f))
#define LEVEL2_LEFTBULLETSPEED (D3DXVECTOR3(cosf(D3DXToRadian (-10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(-10.0f + 90.0f)) * -10.0f, 0.0f))
#define LEVEL2_RIGHTBULLETSPEED (D3DXVECTOR3(cosf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, 0.0f))

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority)
{
	m_pBullet = NULL;									//弾へのポインタ
	m_Move = D3DXVECTOR3(0.0f,0.0f,0.0f);				//移動量
	m_nLife = 0;										//体力
	m_nBomb = 0;										//爆弾の所持数
	m_nUseBomb = 0;										//爆弾の使用回数
	m_nDeathCount = 0;									//死亡数
	m_nContinue = 0;									//コンティニュー数
	m_nScore = 0;										//スコア
	m_nLevel = LEVEL_NONE;								//レベル
	m_nDeathTime = 0;									//死亡時間
	m_nInvincibleTime = 0;								//無敵時間
	m_nBulletinterval = 0;								//発射間隔
	m_nCount = 0;										//カウント
	m_fSpeed = 0.0f;									//速さ
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
void CPlayer::TextureUnload(void)
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
CPlayer * CPlayer::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size)
{
	CPlayer * pPlayer;
	pPlayer = new CPlayer;
	pPlayer->Init();
	pPlayer->SetPosition(Position);
	pPlayer->SetSize(Size);
	return pPlayer;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.33333f * m_nLevel, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.33333f * m_nLevel + 0.33333f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.33333f * m_nLevel, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.33333f * m_nLevel + 0.33333f, 1.0f);
	//2Dシーン管理初期化処理関数呼び出し
	CScene2d::Init();
	//オブジェタイプをプレイヤーにする
	SetObjType(CScene::OBJTYPE_PLAYER);
	//移動速度の初期設定
	m_fSpeed = PLAYER_SPEED;
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
	//ゲームモードの取得
	CGameMode * pGameMode = CManager::GetGameMode();
	//スコアのUIを取得
	CScoreUI * pScoreUI = CGameMode::GetScoreUI();
	//爆弾のUIを取得
	CBombUI * pBombUI = CGameMode::GetBombUI();
	//体力のUIを取得
	CLifeUI * pLifeUI = CGameMode::GetLifeUI();
	//2Dシーン管理更新処理関数呼び出し
	CScene2d::Update();
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.33333f * m_nLevel, 0.0f);
	aTexture[1] = D3DXVECTOR2(0.33333f * m_nLevel + 0.33333f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.33333f * m_nLevel, 1.0f);
	aTexture[3] = D3DXVECTOR2(0.33333f * m_nLevel + 0.33333f, 1.0f);
	//位置を取得
	D3DXVECTOR3 Position = GetPosition();
	//もしリプレイ状態が偽のとき
	if (pGameMode->GetbReplay() == false)
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
	Position = MovableRange(Position);
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
	//体力を減算する
	m_nLife -= nValue;
	//死亡処理関数呼び出し
	Death();
	//もし体力が0になったら
	if (m_nLife <= 0)
	{
		//コンティニュー数を加算する
		m_nContinue++;
		//ライフを初期設定する
		m_nLife = INITIAL_LIFE;
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
	if (m_nScore < 0)
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
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
		m_nBulletinterval++;
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

	if (pKeyboard->GetKeyboardTrigger(DIK_Z))
	{
		Death();
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
		case INPUT_UP:
			m_Move.y = cosf(D3DX_PI) * m_fSpeed;
			break;
		case INPUT_DOWN:
			m_Move.y = cosf(D3DX_PI) * -m_fSpeed;
			break;
		case INPUT_LEFT:
			m_Move.x = cosf(D3DX_PI) * m_fSpeed;
			break;
		case INPUT_RIGHT:
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
	//もし死亡状態じゃないとき
	if (m_State != STATE_DEATH)
	{
		switch (m_Attack)
		{
		case ATTACK_SHOT:
			//弾の発射感覚処理
			if (m_nBulletinterval % 10 == 0)
			{
				switch (m_nLevel)
				{
				case LEVEL_1:
					//弾の生成
					m_pBullet = CBulletPlayer::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y - GetSize().y / 2, GetPosition().z), LEVEL1_BULLETSPEED);
					break;
				case LEVEL_2:
					//弾の生成
					m_pBullet = CBulletPlayer::Create(D3DXVECTOR3(GetPosition().x + GetSize().x / 5, GetPosition().y - GetSize().y / 2, GetPosition().z), LEVEL1_BULLETSPEED);
					m_pBullet = CBulletPlayer::Create(D3DXVECTOR3(GetPosition().x - GetSize().x / 5, GetPosition().y - GetSize().y / 2, GetPosition().z), LEVEL1_BULLETSPEED);
					break;
				case LEVEL_3:
					//弾の生成
					m_pBullet = CBulletPlayer::Create(D3DXVECTOR3(GetPosition().x + GetSize().x / 5, GetPosition().y - GetSize().y / 2, GetPosition().z), LEVEL1_BULLETSPEED);
					m_pBullet = CBulletPlayer::Create(D3DXVECTOR3(GetPosition().x - GetSize().x / 5, GetPosition().y - GetSize().y / 2, GetPosition().z), LEVEL1_BULLETSPEED);
					m_pBullet = CBulletPlayer::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y - GetSize().y / 2, 0.0f), LEVEL2_LEFTBULLETSPEED);
					m_pBullet = CBulletPlayer::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y - GetSize().y / 2, 0.0f), LEVEL2_RIGHTBULLETSPEED);
					break;
				default:
					break;
				}
			}
			break;
		case ATTACK_BOMB:
			//もし爆弾の所持数が1個以上のとき
			if (m_nBomb > 0)
			{
				//爆弾の生成
				m_pBullet = CBulletBomb::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y - GetSize().y / 2, 0.0f), BOMB_SPEED);
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
	D3DXCOLOR Color;
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
	AddScore(1);
	//死亡数を加算する
	m_nDeathCount++;
	//色を透明にする
	Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	//全ての弾を消す
	//
	//色の設定
	SetColor(Color);
}

//=============================================================================
// 無敵処理関数
//=============================================================================
void CPlayer::Invincible(void)
{
	if (m_nCount % 5 == 0)
	{
		if (m_nInvincibleTime % 2 == 0)
		{
			//透明状態
			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
			{
				D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				//色の設定
				SetColor(Color);
			}
		}
		else
		{
			//通常状態
			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
			{
				D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				//色の設定
				SetColor(Color);
			}
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
D3DXVECTOR3 CPlayer::MovableRange(D3DXVECTOR3 Position)
{
	//もしプレイヤーが上画面外に行ったら
	if (Position.y - GetSize().y / 2 < 0)
	{
		Position.y = GetSize().y / 2;
	}
	//もしプレイヤーが下画面外に行ったら
	if (Position.y + GetSize().y > FIELD_HEIGHT)
	{
		Position.y = FIELD_HEIGHT - GetSize().y;
	}
	//もしプレイヤーが左画面外に行ったら
	if (Position.x - GetSize().y / 2 < FIELD_WIDTH_MIN)
	{
		Position.x = GetSize().y / 2 + FIELD_WIDTH_MIN;
	}
	//もしプレイヤーが右画面外に行ったら
	if (Position.x + GetSize().y / 2 > FIELD_WIDTH)
	{
		Position.x = FIELD_WIDTH - GetSize().y / 2;
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
	//上キーの入力情報があるとき
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_UP] == '1')
	{
		//移動量を代入
		m_Move.y = cosf(D3DX_PI)*m_fSpeed;
		//入力キー情報を上にする
		m_Input = INPUT_UP;
		//移動処理関数呼び出し
		Move();
	}
	//下キーの入力情報があるとき
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_DOWN] == '1')
	{
		//移動量を代入
		m_Move.y = cosf(D3DX_PI)*-m_fSpeed;
		//入力キー情報を下にする
		m_Input = INPUT_DOWN;
		//移動処理関数呼び出し
		Move();
	}
	//左キーの入力情報があるとき
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_LEFT] == '1')
	{
		//移動量を代入
		m_Move.x = cosf(D3DX_PI)*m_fSpeed;
		//入力キー情報を左にする
		m_Input = INPUT_LEFT;
		//移動処理関数呼び出し
		Move();
	}
	//右キーの入力情報があるとき
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_RIGHT] == '1')
	{
		//移動量を代入
		m_Move.x = cosf(D3DX_PI)*-m_fSpeed;
		//入力キー情報を右にする
		m_Input = INPUT_RIGHT;
		//移動処理関数呼び出し
		Move();
	}
	//射撃キーの入力情報があるとき
	if (m_aInputData[pGameMode->GetFlameCount()][INPUT_SHOT] == '1')
	{
		//発射間隔のカウントを進める
		m_nBulletinterval++;
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
// タイムカウント処理関数
//=============================================================================
void CPlayer::TimeCount(void)
{
	switch (m_State)
	{
	case STATE_DEATH:
		//死亡時間を加算する
		m_nDeathTime++;
		//無敵状態に移行する
		if (m_nDeathTime >= DEATH_TIME)
		{
			//リスポーン処理関数呼び出し
			Respawn();
			//死亡時間を初期化する
			m_nDeathTime = 0;
		}
		break;
	case STATE_INVINCIBLE:
		//無敵時間を加算する
		m_nInvincibleTime++;
		//カウントを進める
		m_nCount++;
		//無状態に移行する
		if (m_nInvincibleTime >= INVINCIBLE_TIME)
		{
			//状態を無にする
			m_State = STATE_NONE;
			//無敵時間を初期化する
			m_nInvincibleTime = 0;
			//カウントを初期化する
			m_nCount = 0;
		}
		break;
	default:
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	}
}

//=============================================================================
// プレイヤー情報保存処理関数
//=============================================================================
void CPlayer::DataSave(void)
{
	FILE * pFile;

	pFile = fopen("data/TEXT/PlayerData.txt", "w"); //ファイルの書き込み

	if (pFile != NULL)
	{
		//名前を記録
		//fprintf(pFile, "%s\n", &m_aPlayerName);
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
	FILE * pFile;
	//ゲームモードの取得
	CGameMode * pGameMode = CManager::GetGameMode();

	//ファイルの書き込み
	pFile = fopen("data/TEXT/InputData.txt", "w");

	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < pGameMode->GetFlameCount(); nCount++)
		{
		//	プレイヤーの入力情報の記録
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_UP]);
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_DOWN]);
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_LEFT]);
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_RIGHT]);
			fprintf(pFile, "%d", m_aInputData[nCount][INPUT_BOMB]);
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
	FILE *pFile;

	//ファイルの読み込み
	pFile = fopen("data/TEXT/InputData.txt", "r");

	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < 15000; nCount++)
		{
			//入力情報読み込み
			fscanf(pFile, "%s", &m_aInputData[nCount][0]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}














////=============================================================================
////
//// プレイヤー処理 [player.cpp]
//// Author : 二階堂汰一
////
////=============================================================================
//#define _CRT_SECURE_NO_WARNINGS
////*****************************************************************************
//// ヘッダファイルのインクルード
////*****************************************************************************
//#include "main.h"
//#include "manager.h"
//#include "game.h"
//#include "renderer.h"
//#include "input.h"
//#include "keyboard.h"
//#include "joystick.h"
//#include "scene.h"
//#include "scene2d.h"
//#include "player.h"
//#include "sound.h"
//#include "own.h"
//#include "ownui.h"
//#include "Bomb.h"
//#include "explosion.h"
//#include "bombui.h"
//#include "fade.h"
//#include "score.h"
//#include "player.h"
//#include "title.h"
//#include <stdio.h>
//#include <stdlib.h>
//
//LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
//int CPlayer::m_nScore = 0;
//char CPlayer::m_aPlayerName[MAX_NAME] = {};
//int CPlayer::m_nNameCount = 0;
//bool CPlayer::m_bDeath = false;
//
////=============================================================================
//// コンストラクタ(メンバ変数の初期化(全て0に))
////=============================================================================
//CPlayer::CPlayer(int nPriority) :CScene2d(nPriority)
//{
//	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //位置
//	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //位置
//	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//	{
//		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //頂点座標
//		m_col[nCount] = D3DCOLOR_RGBA(0, 0, 0, 255);
//	}
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //向き
//	m_fLength = 0.0f;		//ポリゴンの対角線の長さ
//	m_fAngle = 0.0f;		//ポリゴンの角度
//	m_fScale = 0.0f;		// 拡大
//	m_fAddScale = 0.0f;		// 拡大加算値
//	m_nOwn = 0;				//自機の数
//	m_nLevel = 0;			//プレイヤーレベル
//	m_nCountBullet = 0;		//弾のカウント
//	m_nBomb = 0;			//所持してる爆弾の数
//	m_fWidth = 0.0f;		//幅
//	m_fHeight = 0.0f;		//高さ
//	m_fSpeed = 0.0f;		//速さ
//	m_bShot = false;		//発射してるかどうか
//	m_bInvincible = false;	//無敵かどうか
//	m_bHit = false;			//HITしたかどうか
//	m_nInvincibleCount = 0;
//	m_nCount = 0;			//カウント
//	m_nContinue = 0;			//コンティニュー数
//	m_nDeath = 0;			//死亡数
//	m_nUseBomb = 0;			//使用したボムの数
//	m_nDeathCount = 0;		//死亡時間
//	memset(m_aInputData, NULL, sizeof(m_aInputData));
//	m_bDeath = false;
//	//m_nInputSaveCount = 0;
//	//m_nInputLoadCount = 0;
//	m_pBullet = NULL;
//}
//
////=============================================================================
////デストラクタ
////=============================================================================
//CPlayer::~CPlayer()
//{
//}
//
////=============================================================================
//// テクスチャロード関数
////=============================================================================
//HRESULT CPlayer::TextureLoad(void)
//{
//	CRenderer *pRenderer = CManager::GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	// テクスチャの生成
//	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
//		TEXTURE_PLAYER,								// ファイルの名前
//		&m_pTexture);								// 読み込むメモリー
//	return S_OK;
//}
//
////=============================================================================
//// テクスチャアンロード関数
////=============================================================================
//void CPlayer::TextureUnload(void)
//{
//	// テクスチャの破棄
//	if (m_pTexture != NULL)
//	{
//		m_pTexture->Release();
//		m_pTexture = NULL;
//	}
//}
//
////=============================================================================
//// 生成関数
////=============================================================================
//CPlayer * CPlayer::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, int nOwn)
//{
//	CPlayer * pPlayer;
//	pPlayer = new CPlayer;
//	pPlayer->Init(pos, SizeHeight, SizeWidth, nOwn);
//	return pPlayer;
//}
//
////=============================================================================
//// 初期化関数(メンバ変数の初期設定)
////=============================================================================
//HRESULT CPlayer::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, int nOwn)
//{
//	CScene2d::Init(pos, SizeWidth, SizeHeight);
//
//	//レンダラーの取得
//	//CRenderer *pRenderer = CManager::GetRenderer();
//	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	//オブジェタイプをプレイヤーにする
//	SetObjType(CScene::OBJTYPE_PLAYER);
//
//	m_Position = pos;	//プレイヤーの位置
//	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //位置
//	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//	{
//		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //頂点座標
//		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
//	}
//
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //向き
//	m_fLength = 0.0f;			//ポリゴンの対角線の長さ
//	m_fAngle = 0.0f;			//ポリゴンの角度
//	m_fScale = 0.0f;			// 拡大
//	m_fAddScale = 0.0f;			// 拡大加算値
//	m_nOwn = nOwn;				//自機の数
//	m_nLevel = 1;				//プレイヤーレベル
//	m_nCountBullet = 0;			//弾のカウント
//	m_nBomb = 3;				//爆弾の初期化
//	m_bShot = false;			//発射してるかどうか
//	m_bInvincible = true;
//	m_fWidth = SizeWidth;		//プレイヤーの幅
//	m_fHeight = SizeHeight;		//プレイヤーの高さ
//	m_fSpeed = PLAYER_SPEED;	//プレイヤーの速度
//	m_nCount = 0;				//カウント
//	m_nDeath = 0;				//死亡数
//	m_nContinue = 0;			//コンティニュー数
//	m_nDeathCount = 0;			//死亡時間
//	m_nUseBomb = 0;				//使用したボムの数
//	m_bDeath = false;			//死んだかどうか
//	m_bHit = false;				//HITしたかどうか
//	memset(m_aInputData, NULL, sizeof(m_aInputData));
//	//m_nInputSaveCount = 0;
//	//m_nInputLoadCount = 5;
//
//	if (CTitle::GetbReplay() == true)
//	{
//		InputLoad();
//	}
//
//	// 頂点座標を設定
//	m_vpos[0] = D3DXVECTOR3(m_Position.x + (-m_fWidth / 2), m_Position.y + (-m_fHeight / 2), 0.0f);
//	m_vpos[1] = D3DXVECTOR3(m_Position.x + (m_fWidth / 2), m_Position.y + (-m_fHeight / 2), 0.0f);
//	m_vpos[2] = D3DXVECTOR3(m_Position.x + (-m_fWidth / 2), m_Position.y + (m_fHeight / 2), 0.0f);
//	m_vpos[3] = D3DXVECTOR3(m_Position.x + (m_fWidth / 2), m_Position.y + (m_fHeight / 2), 0.0f);
//
//	//テクスチャのセット
//	SetTex(
//		(m_nLevel - 1) * 0.33333f,
//		0.0f,
//		(m_nLevel - 1) * 0.33333f + 0.33333f,
//		1.0f);
//	SetVertexPosition(m_vpos);	//頂点座標の設定
//	BindTexture(m_pTexture);	//テクスチャの割り当て
//
//								//ボムのUI取得
//	CBombUI * pBombUI = CGame::GetBombUI();
//
//	pBombUI->AddBombUI(3);
//	Save();
//	return S_OK;
//}
//
////=============================================================================
//// 終了関数
////=============================================================================
//void CPlayer::Uninit(void)
//{
//	CScene2d::Uninit();
//}
//
////=============================================================================
//// 更新関数
////=============================================================================
//void CPlayer::Update(void)
//{
//	CScene2d::Update();
//	//位置の取得
//	m_Position = GetPosition();
//	//サウンドの取得
//	CSound * pSound = CManager::GetSound();
//	//キーボードの取得
//	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
//	//ジョイスティックの取得
//	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
//	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
//	DIJOYSTATE js;
//	//ジョイスティックの振動取得
//	LPDIRECTINPUTEFFECT pDIEffect = CInputJoystick::GetEffect();
//
//	if (lpDIDevice != NULL)
//	{
//		lpDIDevice->Poll();
//		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
//	}
//
//	//もし自機が生きてたら
//	if (m_bDeath == false)
//	{
//		//プレイヤーが移動していないとき
//		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		if (CTitle::GetbReplay() == false)
//		{
//			//プレイヤーの左移動
//			if (pInputKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
//			{
//				m_move.x = cosf(D3DX_PI)*m_fSpeed;
//				m_aInputData[CGame::GetbInputSaveCount()][INPUT_LEFT] = 1;
//			}
//
//			//プレイヤーの右移動
//			if (pInputKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
//			{
//				m_move.x = cosf(D3DX_PI)*-m_fSpeed;
//				m_aInputData[CGame::GetbInputSaveCount()][INPUT_RIGHT] = 1;
//			}
//
//			//プレイヤーの上移動
//			if (pInputKeyboard->GetKeyboardPress(DIK_W) || lpDIDevice != NULL &&js.lY == -1000)
//			{
//				m_move.y = cosf(D3DX_PI)*m_fSpeed;
//				m_aInputData[CGame::GetbInputSaveCount()][INPUT_UP] = 1;
//			}
//
//			//プレイヤーの下移動
//			if (pInputKeyboard->GetKeyboardPress(DIK_S) || lpDIDevice != NULL &&js.lY == 1000)
//			{
//				m_move.y = cosf(D3DX_PI)*-m_fSpeed;
//				m_aInputData[CGame::GetbInputSaveCount()][INPUT_DOWN] = 1;
//			}
//
//			//プレイヤーの爆弾発射
//			if (pInputKeyboard->GetKeyboardTrigger(DIK_B) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_B))
//			{
//				//もし爆弾を1個以上持っていたら
//				if (m_nBomb >= PLAYER_BOMB_COST)
//				{
//					//爆弾の生成
//					m_pBomb = CBomb::Create(D3DXVECTOR3(m_Position.x, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BOMB_SIZE, BOMB_SIZE, PLAYER_BOMB_LIFE, PLAYER_BOMB_DAMAGE);
//					//所持爆弾数の減算
//					SubBomb(PLAYER_SUB_BOMB);
//				}
//				m_aInputData[CGame::GetbInputSaveCount()][INPUT_BOMB] = 1;
//			}
//
//			//プレイヤーのビーム
//			if (pInputKeyboard->GetKeyboardPress(DIK_Q))
//			{
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x + PLAYER_SIZE / 5, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BEAM_SIZE, BEAM_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NONE, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
//			}
//
//			//プレイヤーの弾発射
//			if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) || lpDIDevice != NULL &&pInputJoystick->GetJoystickPress(JS_A))
//			{
//				//射撃状態をtrueにする
//				m_bShot = true;
//				m_aInputData[CGame::GetbInputSaveCount()][INPUT_SHOT] = 1;
//			}
//			else
//			{
//				//射撃状態をfalseにする
//				m_bShot = false;
//				//弾のカウントを
//				m_nCountBullet = 9;
//				//pDIEffect->Stop();
//			}
//		}
//		else
//		{
//			if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_UP] == '1')
//			{
//				m_move.y = cosf(D3DX_PI)*m_fSpeed;
//			}
//			if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_DOWN] == '1')
//			{
//				m_move.y = cosf(D3DX_PI)*-m_fSpeed;
//			}
//			if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_LEFT] == '1')
//			{
//				m_move.x = cosf(D3DX_PI)*m_fSpeed;
//			}
//			if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_RIGHT] == '1')
//			{
//				m_move.x = cosf(D3DX_PI)*-m_fSpeed;
//			}
//			if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_SHOT] == '1')
//			{
//				//射撃状態をtrueにする
//				m_bShot = true;
//			}
//			else
//			{
//				//射撃状態をfalseにする
//				m_bShot = false;
//				//弾のカウントを
//				m_nCountBullet = 9;
//				//pDIEffect->Stop();
//			}
//			if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_BOMB] == '1')
//			{
//				//もし爆弾を1個以上持っていたら
//				if (m_nBomb >= PLAYER_BOMB_COST)
//				{
//					//爆弾の生成
//					m_pBomb = CBomb::Create(D3DXVECTOR3(m_Position.x, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BOMB_SIZE, BOMB_SIZE, PLAYER_BOMB_LIFE, PLAYER_BOMB_DAMAGE);
//					//所持爆弾数の減算
//					SubBomb(PLAYER_SUB_BOMB);
//				}
//			}
//		}
//
//		//もし弾を撃っているとき
//		if (m_bShot == true)
//		{
//
//			//弾のカウントを進める
//			m_nCountBullet++;
//		}
//
//		//弾の発射感覚処理
//		if (m_nCountBullet % 10 == 0)
//		{
//			//プレイヤーのレベルによる弾の生成
//			switch (m_nLevel)
//			{
//			case 1:
//				//弾の生成
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
//				break;
//			case 2:
//				//弾の生成
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x + PLAYER_SIZE / 5, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x - PLAYER_SIZE / 5, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
//				break;
//			case 3:
//				//弾の生成
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x + PLAYER_SIZE / 5, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x - PLAYER_SIZE / 5, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(cosf(D3DXToRadian(-10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(-10.0f + 90.0f)) * -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK * 2);
//				m_pBullet = CBullet::Create(D3DXVECTOR3(m_Position.x, m_Position.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(cosf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK * 2);
//				break;
//			default:
//				break;
//			}
//			//ショット音の生成
//			pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
//
//			if (pDIEffect != NULL)
//			{
//				//ジョイスティックの振動発生
//				pDIEffect->Start(1, 0);
//			}
//		}
//
//		//もしプレイヤーが上画面外に行ったら
//		if (m_Position.y - PLAYER_SIZE / 2 < 0)
//		{
//			m_Position.y = PLAYER_SIZE / 2;
//		}
//
//		//もしプレイヤーが下画面外に行ったら
//		if (m_Position.y + PLAYER_SIZE > FIELD_HEIGHT)
//		{
//			m_Position.y = FIELD_HEIGHT - PLAYER_SIZE;
//		}
//
//		//もしプレイヤーが左画面外に行ったら
//		if (m_Position.x - PLAYER_SIZE / 2 < FIELD_WIDTH_MIN)
//		{
//			m_Position.x = PLAYER_SIZE / 2 + FIELD_WIDTH_MIN;
//		}
//
//		//もしプレイヤーが右画面外に行ったら
//		if (m_Position.x + PLAYER_SIZE / 2 > FIELD_WIDTH)
//		{
//			m_Position.x = FIELD_WIDTH - PLAYER_SIZE / 2;
//		}
//	}
//	//もしプレイヤーが無敵の時
//	if (m_bInvincible == true)
//	{
//		//無敵中
//		if (m_nCount <= PLAYER_INVINCIBLE_TIME)
//		{
//			if (m_nCount % 5 == 0)
//			{
//				//無敵時間のカウントを進める
//				m_nInvincibleCount++;
//
//				if (m_nInvincibleCount % 2 == 0)
//				{
//					//透明状態
//					for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//					{
//						m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 0);
//					}
//				}
//				else
//				{
//					//通常状態
//					for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//					{
//						m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
//					}
//				}
//			}
//		}
//		else
//		{
//			//無敵をやめる
//			m_bInvincible = false;
//			//カウントを戻す
//			m_nInvincibleCount = 0;
//			//カウントを戻す
//			m_nCount = 0;
//			//通常状態に戻す
//			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//			{
//				m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
//			}
//		}
//		//カウントを進める
//		m_nCount++;
//	}
//
//	//もし自機が死んだとき
//	if (m_bDeath == true)
//	{
//		if (m_bHit == true)
//		{
//			m_bHit = false;
//		}
//		for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
//		{
//			CScene * pScene = GetScene(4, nCountScene);
//			if (pScene != NULL)
//			{
//				//オブジェタイプの取得
//				OBJTYPE objType;
//				objType = pScene->GetObjType();
//				//シーンオブジェクトの位置を取得
//				D3DXVECTOR3 Scene_pos;
//				Scene_pos = pScene->GetPosition();
//				//もしオブジェタイプが弾の場合
//				if (objType == OBJTYPE_BULLET)
//				{
//					pScene->Uninit();
//				}
//			}
//		}
//		//透明状態
//		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//		{
//			m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 0);
//		}
//		//もしカウントが死亡時間以下の場合
//		if (m_nDeathCount >= PLAYER_DEATH_TIME)
//		{
//			//自機を初期位置に配置
//			m_Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 180, 0.0f);
//			//死亡状態解除
//			m_bDeath = false;
//			//無敵状態にする
//			m_bInvincible = true;
//			//カウントを0に戻す
//			m_nDeathCount = 0;
//		}
//		//死亡時間を進める
//		m_nDeathCount++;
//	}
//
//	//位置更新
//	m_Position.x += m_move.x;
//	m_Position.y += m_move.y;
//
//	// 頂点座標を設定
//	m_vpos[0] = D3DXVECTOR3(m_Position.x + (-m_fWidth / 2), m_Position.y + (-m_fHeight / 2), 0.0f);
//	m_vpos[1] = D3DXVECTOR3(m_Position.x + (m_fWidth / 2), m_Position.y + (-m_fHeight / 2), 0.0f);
//	m_vpos[2] = D3DXVECTOR3(m_Position.x + (-m_fWidth / 2), m_Position.y + (m_fHeight / 2), 0.0f);
//	m_vpos[3] = D3DXVECTOR3(m_Position.x + (m_fWidth / 2), m_Position.y + (m_fHeight / 2), 0.0f);
//
//	//m_nInputSaveCount++;
//	//m_nInputLoadCount++;
//
//	if (CTitle::GetbReplay() == false)
//	{
//		if (CDragon::GetDeath() == true)
//		{
//			CPlayer::Save();
//			CPlayer::InputSave();
//			CDragon::SetDeath(false);
//			CManager::StartFade(CManager::MODE_RESULT);
//		}
//	}
//
//	SetTex(
//		(m_nLevel - 1) * 0.33333f,
//		0.0f,
//		(m_nLevel - 1) * 0.33333f + 0.33333f,
//		1.0f);
//	//色のセット
//	SetColor(m_col);
//	//頂点情報のセット
//	SetVertexPosition(m_vpos);
//	//位置の情報のセット
//	SetPosition(m_Position);
//}
//
////=============================================================================
//// 描画関数
////=============================================================================
//void CPlayer::Draw(void)
//{
//	CScene2d::Draw();
//}
//
////=============================================================================
//// HIT関数
////=============================================================================
//void CPlayer::Hit(void)
//{
//	//体力の減算
//	SubOwn(PLAYER_SUB_OWN);
//	//HIT状態をtrueにする
//	m_bHit = true;
//}
//
////=============================================================================
//// 自機加算関数
////=============================================================================
//void CPlayer::AddOwn(int nValue)
//{
//	//自機のUIの取得
//	COwnUI * pOwnUI = CGame::GetOwnUI();
//	if (m_nOwn < MAX_OWN)
//	{
//		//自機の加算処理
//		m_nOwn += nValue;
//		//プレイヤーの自機のUIを加算
//		pOwnUI->AddOwnUI(PLAYER_ADD_OWN);
//	}
//}
//
////=============================================================================
//// 自機減算関数
////=============================================================================
//void CPlayer::SubOwn(int nValue)
//{
//	//ジョイスティックの振動取得
//	LPDIRECTINPUTEFFECT pDIEffect = CInputJoystick::GetEffect();
//	//スコア取得
//	CScore * pScore = CGame::GetScore();
//	//自機のUI取得
//	COwnUI * pOwnUI = CGame::GetOwnUI();
//	//サウンドの取得
//	CSound * pSound = CManager::GetSound();
//
//	//もし自機が無敵じゃないとき
//	if (m_bDeath == false)
//	{
//		if (m_bInvincible == false)
//		{
//			//カラーの指定
//			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//			{
//				m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
//			}
//			//爆発の発生
//			CExplosion::Create(m_Position, PLAYER_EXPLOSION_SIZE, PLAYER_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
//			//爆発音の生成
//			pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
//			//自機の減算処理
//			m_nOwn -= nValue;
//			//死亡数を加算
//			m_nDeath++;
//			//自機UIの減算
//			pOwnUI->SubOwnUI(PLAYER_SUB_OWN);
//			if (pDIEffect != NULL)
//			{
//				//ジョイスティックの振動開始
//				pDIEffect->Start(1, 0);
//			}
//			//死亡状態にする
//			m_bDeath = true;
//		}
//
//		//プレイヤーの自機ががPLAYER_MIN_OWN以下になったとき(プレイヤーが死んだとき)
//		if (m_nOwn <= PLAYER_MIN_OWN)
//		{
//			//自機の加算処理
//			m_nOwn = PLAYER_INIT_OWN;
//			//自機UIの加算処理
//			pOwnUI->AddOwnUI(PLAYER_INIT_OWN);
//			//スコアの加算関数呼び出し
//			pScore->AddScore(1);
//			//スコアの減算
//			pScore->SubScore(1000);
//			//リザルト数を加算
//			m_nContinue++;
//			//死亡状態にする
//			m_bDeath = true;
//			//モードリザルトへ
//			//CManager::StartFade(CManager::MODE_RESULT);
//		}
//	}
//}
//
////=============================================================================
//// レベル加算関数
////=============================================================================
//void CPlayer::AddLevel(int nValue)
//{
//	//サウンドの取得
//	CSound * pSound = CManager::GetSound();
//	pSound->PlaySound(CSound::SOUND_LABEL_LVUP);
//	//引数の値を加算
//	m_nLevel += nValue;
//}
//
////=============================================================================
//// 爆弾加算関数
////=============================================================================
//void CPlayer::AddBomb(int nValue)
//{
//	//ボムのUI取得
//	CBombUI * pBombUI = CGame::GetBombUI();
//	//引数の値を加算
//	m_nBomb += nValue;
//	pBombUI->AddBombUI(PLAYER_ADD_BOMB);
//}
//
////=============================================================================
//// 爆弾減算関数
////=============================================================================
//void CPlayer::SubBomb(int nValue)
//{
//	//スコア取得
//	CScore * pScore = CGame::GetScore();
//	//ボムのUI取得
//	CBombUI * pBombUI = CGame::GetBombUI();
//	//引数の値を減算
//	m_nBomb -= nValue;
//	//ボムの使用回数を加算
//	m_nUseBomb++;
//	//スコアの減算
//	pScore->SubScore(1000);
//	//ボムのUIセット
//	pBombUI->SubBombUI(PLAYER_SUB_BOMB);
//}
//
////=============================================================================
//// スコア取得関数
////=============================================================================
//void CPlayer::SetPlayerScpre(int nValue)
//{
//	m_nScore = nValue;
//}
//
////=============================================================================
//// 名前取得関数
////=============================================================================
//void CPlayer::SetPlayerName(int nCount, char aName)
//{
//	m_aPlayerName[nCount] = aName;
//	/*m_nNameCount++;*/
//}
//
////=============================================================================
//// セーブ関数
////=============================================================================
//void CPlayer::Save(void)
//{
//	FILE *pFile;
//
//	pFile = fopen("data/TEXT/PlayerData.txt", "w"); //ファイルの書き込み
//
//	if (pFile != NULL)
//	{
//		//名前を記録
//		fprintf(pFile, "%s\n", &m_aPlayerName);
//		//死亡数を記録
//		fprintf(pFile, "%d\n", m_nDeath);
//		//コンティニュー数を記録
//		fprintf(pFile, "%d\n", m_nContinue);
//		//ボムの使用回数を記録
//		fprintf(pFile, "%d\n", m_nUseBomb);
//		//スコアを記録
//		fprintf(pFile, "%d\n", m_nScore);
//
//		//for (int nCount = 0; nCount < CGame::GetbInputSaveCount(); nCount++)
//		//{
//		//	//プレイヤーの入力情報の記録
//		//	fprintf(pFile, "%d", m_aInputData[nCount][0]);
//		//	fprintf(pFile, "%d", m_aInputData[nCount][1]);
//		//	fprintf(pFile, "%d", m_aInputData[nCount][2]);
//		//	fprintf(pFile, "%d", m_aInputData[nCount][3]);
//		//	fprintf(pFile, "%d", m_aInputData[nCount][4]);
//		//	fprintf(pFile, "%d\n", m_aInputData[nCount][5]);
//		//}
//
//		//ファイルを閉じる
//		fclose(pFile);
//	}
//}
//
//void CPlayer::InputSave(void)
//{
//	FILE *pFile;
//
//	pFile = fopen("data/TEXT/InputData.txt", "w"); //ファイルの書き込み
//
//	if (pFile != NULL)
//	{
//		for (int nCount = 0; nCount < CGame::GetbInputSaveCount(); nCount++)
//		{
//			//プレイヤーの入力情報の記録
//			fprintf(pFile, "%d", m_aInputData[nCount][0]);
//			fprintf(pFile, "%d", m_aInputData[nCount][1]);
//			fprintf(pFile, "%d", m_aInputData[nCount][2]);
//			fprintf(pFile, "%d", m_aInputData[nCount][3]);
//			fprintf(pFile, "%d", m_aInputData[nCount][4]);
//			fprintf(pFile, "%d\n", m_aInputData[nCount][5]);
//		}
//
//		//ファイルを閉じる
//		fclose(pFile);
//	}
//}
//
//void CPlayer::InputLoad(void)
//{
//	FILE *pFile;
//
//	pFile = fopen("data/TEXT/InputData.txt", "r"); //ファイルの読み込み
//
//	if (pFile != NULL)
//	{
//		for (int nCount = 0; nCount < 15000; nCount++)
//		{
//			//プレイヤーの入力情報読み込み
//			fscanf(pFile, "%s", &m_aInputData[nCount][0]);
//		}
//
//		fclose(pFile); //ファイルを閉じる
//	}
//}
