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
#include "main.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "input.h"
#include "keyboard.h"
#include "joystick.h"
#include "scene.h"
#include "scene2d.h"
#include "player.h"
#include "sound.h"
#include "own.h"
#include "ownui.h"
#include "Bomb.h"
#include "explosion.h"
#include "bombui.h"
#include "fade.h"
#include "score.h"
#include "player.h"
#include "title.h"
#include <stdio.h>
#include <stdlib.h>

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;	//テクスチャへのポインタ
int CPlayer::m_nScore = 0;						//スコア
char CPlayer::m_aPlayerName[MAX_NAME] = {};		//名前
int CPlayer::m_nNameCount = 0;					//名前の文字数
bool CPlayer::m_bDeath = false;					//死んだかどうか

//=============================================================================
// コンストラクタ(メンバ変数の初期化(全て0に))
//=============================================================================
CPlayer::CPlayer(int nPriority):CScene2d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //位置
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //頂点座標
		m_col[nCount] = D3DCOLOR_RGBA(0, 0, 0, 255);	//頂点カラー	
	}
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //向き
	m_fLength = 0.0f;		//ポリゴンの対角線の長さ
	m_fAngle = 0.0f;		//ポリゴンの角度
	m_fScale = 0.0f;		//拡大
	m_fAddScale = 0.0f;		//拡大加算値
	m_nOwn = 0;				//自機の数
	m_nLevel = 0;			//プレイヤーレベル
	m_nCountBullet = 0;		//弾のカウント
	m_nBomb = 0;			//所持してる爆弾の数
	m_fWidth = 0.0f;		//幅
	m_fHeight = 0.0f;		//高さ
	m_fSpeed = 0.0f;		//速さ
	m_bShot = false;		//発射してるかどうか
	m_bInvincible = false;	//無敵かどうか
	m_bHit = false;			//HITしたかどうか
	m_nInvincibleCount = 0;	//無敵時間カウント
	m_nCount = 0;			//カウント
	m_nContinue = 0;		//コンティニュー数
	m_nDeath = 0;			//死亡数
	m_nUseBomb = 0;			//使用したボムの数
	m_nDeathCount = 0;		//死亡時間
	memset(m_aInputData, NULL, sizeof(m_aInputData));	//入力情報
	m_bDeath = false;		//死亡したかどうか
	m_pBullet = NULL;		//弾へのポインタ
}

//=============================================================================
//デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// テクスチャロード関数
//=============================================================================
HRESULT CPlayer::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_PLAYER,								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャアンロード関数
//=============================================================================
void CPlayer::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成関数
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,int nOwn)
{
	CPlayer * pPlayer;
	pPlayer = new CPlayer;
	pPlayer->Init(pos, SizeHeight, SizeWidth, nOwn);
	return pPlayer;
}

//=============================================================================
// 初期化関数(メンバ変数の初期設定)
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,int nOwn)
{
	CScene2d::Init(pos, SizeWidth, SizeHeight);

	//オブジェタイプをプレイヤーにする
	SetObjType(CScene::OBJTYPE_PLAYER);
	//プレイヤーの位置を設定する
	m_pos = pos;
	//位置を設定する
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//頂点座標
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);	//頂点カラー
	}
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //向き
	m_fLength = 0.0f;			//ポリゴンの対角線の長さ
	m_fAngle = 0.0f;			//ポリゴンの角度
	m_fScale = 0.0f;			//拡大
	m_fAddScale = 0.0f;			//拡大加算値
	m_nOwn = nOwn;				//自機の数
	m_nLevel = 1;				//プレイヤーレベル
	m_nCountBullet = 0;			//弾のカウント
	m_nBomb = 3;				//爆弾の初期化
	m_bShot = false;			//発射してるかどうか
	m_bInvincible = true;		//無敵かどうか
	m_fWidth = SizeWidth;		//プレイヤーの幅
	m_fHeight = SizeHeight;		//プレイヤーの高さ
	m_fSpeed = PLAYER_SPEED;	//プレイヤーの速度
	m_nCount = 0;				//カウント
	m_nDeath = 0;				//死亡数
	m_nContinue = 0;			//コンティニュー数
	m_nDeathCount = 0;			//死亡時間
	m_nUseBomb = 0;				//使用したボムの数
	m_bDeath = false;			//死んだかどうか
	m_bHit = false;				//HITしたかどうか
	memset(m_aInputData, NULL, sizeof(m_aInputData));	//入力情報
	//もしリプレイモードなら
	if (CTitle::GetbReplay() == true)
	{
		//入力情報を読み込む
		InputLoad();
	}
	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	//テクスチャのセット
	SetTex(
		(m_nLevel - 1) * 0.33333f,
		0.0f,
		(m_nLevel - 1) * 0.33333f + 0.33333f,
		1.0f);
	SetVertexPosition(m_vpos);	//頂点座標の設定
	BindTexture(m_pTexture);	//テクスチャの割り当て
	//ボムのUI取得
	CBombUI * pBombUI = CGame::GetBombUI();
	//ボムの初期設定
	pBombUI->AddBombUI(3);
	//セーブ関数呼び出し
	Save();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CPlayer::Update(void)
{
	CScene2d::Update();
	//位置の取得
	m_pos = GetPosition();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//ジョイスティックの取得
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
	DIJOYSTATE js;
	//ジョイスティックの振動取得
	LPDIRECTINPUTEFFECT pDIEffect = CInputJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//もし自機が生きてたら
	if (m_bDeath == false)
	{
		//プレイヤーが移動していないとき
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//入力処理関数呼び出し
		Input();
		//攻撃処理関数
		Attack();
		//移動可能範囲制御処理関数呼び出し
		MovableRange();
	}
	//もしプレイヤーが無敵の時
	if (m_bInvincible == true)
	{
		//無敵処理関数呼び出し
		Invincible();
	}
	//もし自機が死んだとき
	if (m_bDeath == true)
	{
		//死亡処理関数呼び出し
		Death();
	}
	//位置更新
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	//もしリプレイモードじゃないとき
	if (CTitle::GetbReplay() == false)
	{
		//もしドラゴンが死亡したら
		if (CDragon::GetDeath() == true)
		{
			CPlayer::Save();
			CPlayer::InputSave();
			CDragon::SetDeath(false);
			CManager::StartFade(CManager::MODE_RESULT);
		}
	}
	//テクスチャの設定
	SetTex(
		(m_nLevel - 1) * 0.33333f,
		0.0f,
		(m_nLevel - 1) * 0.33333f + 0.33333f,
		1.0f);
	//色のセット
	SetColor(m_col);
	//頂点情報のセット
	SetVertexPosition(m_vpos);
	//位置の情報のセット
	SetPosition(m_pos);
}

//=============================================================================
// 描画関数
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// HIT関数
//=============================================================================
void CPlayer::Hit(void)
{
	//体力の減算
	SubOwn(PLAYER_SUB_OWN);
	//HIT状態をtrueにする
	m_bHit = true;
}

//=============================================================================
// 自機加算関数
//=============================================================================
void CPlayer::AddOwn(int nValue)
{
	//自機のUIの取得
	COwnUI * pOwnUI = CGame::GetOwnUI();						
	if (m_nOwn < MAX_OWN)
	{
		//自機の加算処理
		m_nOwn += nValue;
		//プレイヤーの自機のUIを加算
		pOwnUI->AddOwnUI(PLAYER_ADD_OWN);
	}
}

//=============================================================================
// 自機減算関数
//=============================================================================
void CPlayer::SubOwn(int nValue)
{
	//ジョイスティックの振動取得
	LPDIRECTINPUTEFFECT pDIEffect = CInputJoystick::GetEffect();
	//スコア取得
	CScore * pScore = CGame::GetScore();
	//自機のUI取得
	COwnUI * pOwnUI = CGame::GetOwnUI();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();

	//もし自機が無敵じゃないとき
	if (m_bDeath == false)
	{
		if (m_bInvincible == false)
		{
			//カラーの指定
			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
			{
				m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			//爆発の発生
			CExplosion::Create(m_pos, PLAYER_EXPLOSION_SIZE, PLAYER_EXPLOSION_SIZE, CExplosion::TYPE_BULLET);
			//爆発音の生成
			pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
			//自機の減算処理
			m_nOwn -= nValue;
			//死亡数を加算
			m_nDeath++;
			//自機UIの減算
			pOwnUI->SubOwnUI(PLAYER_SUB_OWN);
			if (pDIEffect != NULL)
			{
				//ジョイスティックの振動開始
				pDIEffect->Start(1, 0);
			}
			//死亡状態にする
			m_bDeath = true;
		}
		//プレイヤーの自機ががPLAYER_MIN_OWN以下になったとき(プレイヤーが死んだとき)
		if (m_nOwn <= PLAYER_MIN_OWN)
		{
			//自機の加算処理
			m_nOwn = PLAYER_INIT_OWN;
			//自機UIの加算処理
			pOwnUI->AddOwnUI(PLAYER_INIT_OWN);
			//スコアの加算関数呼び出し
			pScore->AddScore(1);
			//スコアの減算
			pScore->SubScore(1000);
			//リザルト数を加算
			m_nContinue++;
			//死亡状態にする
			m_bDeath = true;
		}
	}
}

//=============================================================================
// レベル加算関数
//=============================================================================
void CPlayer::AddLevel(int nValue)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_LVUP);
	//引数の値を加算
	m_nLevel += nValue;
}

//=============================================================================
// 爆弾加算関数
//=============================================================================
void CPlayer::AddBomb(int nValue)
{
	//ボムのUI取得
	CBombUI * pBombUI = CGame::GetBombUI();
	//引数の値を加算
	if (m_nBomb <= 5)
	{
		m_nBomb += nValue;
		pBombUI->AddBombUI(PLAYER_ADD_BOMB);
	}
}

//=============================================================================
// 爆弾減算関数
//=============================================================================
void CPlayer::SubBomb(int nValue)
{
	//スコア取得
	CScore * pScore = CGame::GetScore();
	//ボムのUI取得
	CBombUI * pBombUI = CGame::GetBombUI();
	//引数の値を減算
	m_nBomb -= nValue;
	//ボムの使用回数を加算
	m_nUseBomb++;
	//スコアの減算
	pScore->SubScore(1000);
	//ボムのUIセット
	pBombUI->SubBombUI(PLAYER_SUB_BOMB);
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CPlayer::Input(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//ジョイスティックの取得
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
	DIJOYSTATE js;
	//ジョイスティックの振動取得
	LPDIRECTINPUTEFFECT pDIEffect = CInputJoystick::GetEffect();

	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	if (CTitle::GetbReplay() == false)
	{
		//プレイヤーの左移動
		if (pInputKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
		{
			m_move.x = cosf(D3DX_PI)*m_fSpeed;
			m_aInputData[CGame::GetbInputSaveCount()][INPUT_LEFT] = 1;
		}

		//プレイヤーの右移動
		if (pInputKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
		{
			m_move.x = cosf(D3DX_PI)*-m_fSpeed;
			m_aInputData[CGame::GetbInputSaveCount()][INPUT_RIGHT] = 1;
		}

		//プレイヤーの上移動
		if (pInputKeyboard->GetKeyboardPress(DIK_W) || lpDIDevice != NULL &&js.lY == -1000)
		{
			m_move.y = cosf(D3DX_PI)*m_fSpeed;
			m_aInputData[CGame::GetbInputSaveCount()][INPUT_UP] = 1;
		}

		//プレイヤーの下移動
		if (pInputKeyboard->GetKeyboardPress(DIK_S) || lpDIDevice != NULL &&js.lY == 1000)
		{
			m_move.y = cosf(D3DX_PI)*-m_fSpeed;
			m_aInputData[CGame::GetbInputSaveCount()][INPUT_DOWN] = 1;
		}

		//プレイヤーの爆弾発射
		if (pInputKeyboard->GetKeyboardTrigger(DIK_B) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_B))
		{
			//もし爆弾を1個以上持っていたら
			if (m_nBomb >= PLAYER_BOMB_COST)
			{
				//爆弾の生成
				m_pBomb = CBomb::Create(D3DXVECTOR3(m_pos.x, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BOMB_SIZE, BOMB_SIZE, PLAYER_BOMB_LIFE, PLAYER_BOMB_DAMAGE);
				//所持爆弾数の減算
				SubBomb(PLAYER_SUB_BOMB);
			}
			m_aInputData[CGame::GetbInputSaveCount()][INPUT_BOMB] = 1;
		}

		//プレイヤーのビーム
		if (pInputKeyboard->GetKeyboardPress(DIK_Q))
		{
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x + PLAYER_SIZE / 5, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BEAM_SIZE, BEAM_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NONE, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
		}

		//プレイヤーの弾発射
		if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) || lpDIDevice != NULL &&pInputJoystick->GetJoystickPress(JS_A))
		{
			//射撃状態をtrueにする
			m_bShot = true;
			m_aInputData[CGame::GetbInputSaveCount()][INPUT_SHOT] = 1;
		}
		else
		{
			//射撃状態をfalseにする
			m_bShot = false;
			//弾のカウントを
			m_nCountBullet = 9;
			//pDIEffect->Stop();
		}
	}
	else
	{
		if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_UP] == '1')
		{
			m_move.y = cosf(D3DX_PI)*m_fSpeed;
		}
		if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_DOWN] == '1')
		{
			m_move.y = cosf(D3DX_PI)*-m_fSpeed;
		}
		if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_LEFT] == '1')
		{
			m_move.x = cosf(D3DX_PI)*m_fSpeed;
		}
		if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_RIGHT] == '1')
		{
			m_move.x = cosf(D3DX_PI)*-m_fSpeed;
		}
		if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_SHOT] == '1')
		{
			//射撃状態をtrueにする
			m_bShot = true;
		}
		else
		{
			//射撃状態をfalseにする
			m_bShot = false;
			//弾のカウントを
			m_nCountBullet = 9;
		}
		if (m_aInputData[CGame::GetbInputSaveCount()][INPUT_BOMB] == '1')
		{
			//もし爆弾を1個以上持っていたら
			if (m_nBomb >= PLAYER_BOMB_COST)
			{
				//爆弾の生成
				m_pBomb = CBomb::Create(D3DXVECTOR3(m_pos.x, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BOMB_SIZE, BOMB_SIZE, PLAYER_BOMB_LIFE, PLAYER_BOMB_DAMAGE);
				//所持爆弾数の減算
				SubBomb(PLAYER_SUB_BOMB);
			}
		}
	}
}

//=============================================================================
// 攻撃処理関数
//=============================================================================
void CPlayer::Attack(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//ジョイスティックの取得
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
	DIJOYSTATE js;
	//ジョイスティックの振動取得
	LPDIRECTINPUTEFFECT pDIEffect = CInputJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//もし弾を撃っているとき
	if (m_bShot == true)
	{
		//弾のカウントを進める
		m_nCountBullet++;
	}
	//弾の発射感覚処理
	if (m_nCountBullet % 10 == 0)
	{
		//プレイヤーのレベルによる弾の生成
		switch (m_nLevel)
		{
		case 1:
			//弾の生成
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
			break;
		case 2:
			//弾の生成
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x + PLAYER_SIZE / 5, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x - PLAYER_SIZE / 5, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
			break;
		case 3:
			//弾の生成
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x + PLAYER_SIZE / 5, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x - PLAYER_SIZE / 5, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK);
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(cosf(D3DXToRadian(-10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(-10.0f + 90.0f)) * -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK * 2);
			m_pBullet = CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - PLAYER_SIZE / 2, 0.0f), D3DXVECTOR3(cosf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, sinf(D3DXToRadian(10.0f + 90.0f)) * -10.0f, 0.0f), BULLET_SIZE, BULLET_SIZE, CBullet::USER_PLAYER, CBullet::TYPE_NORMAL, CBullet::COLOR_PURPLE, CBullet::BULLET_TEXTURE, PLAYER_BULLET_ATTACK * 2);
			break;
		default:
			break;
		}
		//ショット音の生成
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

		if (pDIEffect != NULL)
		{
			//ジョイスティックの振動発生
			pDIEffect->Start(1, 0);
		}
	}
}

//=============================================================================
// 移動可能範囲制御処理関数
//=============================================================================
void CPlayer::MovableRange(void)
{
	//もしプレイヤーが上画面外に行ったら
	if (m_pos.y - PLAYER_SIZE / 2 < 0)
	{
		m_pos.y = PLAYER_SIZE / 2;
	}

	//もしプレイヤーが下画面外に行ったら
	if (m_pos.y + PLAYER_SIZE > FIELD_HEIGHT)
	{
		m_pos.y = FIELD_HEIGHT - PLAYER_SIZE;
	}

	//もしプレイヤーが左画面外に行ったら
	if (m_pos.x - PLAYER_SIZE / 2 < FIELD_WIDTH_MIN)
	{
		m_pos.x = PLAYER_SIZE / 2 + FIELD_WIDTH_MIN;
	}

	//もしプレイヤーが右画面外に行ったら
	if (m_pos.x + PLAYER_SIZE / 2 > FIELD_WIDTH)
	{
		m_pos.x = FIELD_WIDTH - PLAYER_SIZE / 2;
	}
}

//=============================================================================
// 無敵処理関数
//=============================================================================
void CPlayer::Invincible(void)
{
	//無敵中
	if (m_nCount <= PLAYER_INVINCIBLE_TIME)
	{
		if (m_nCount % 5 == 0)
		{
			//無敵時間のカウントを進める
			m_nInvincibleCount++;

			if (m_nInvincibleCount % 2 == 0)
			{
				//透明状態
				for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
				{
					m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 0);
				}
			}
			else
			{
				//通常状態
				for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
				{
					m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
			}
		}
	}
	else
	{
		//無敵をやめる
		m_bInvincible = false;
		//カウントを戻す
		m_nInvincibleCount = 0;
		//カウントを戻す
		m_nCount = 0;
		//通常状態に戻す
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
	}
	//カウントを進める
	m_nCount++;
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CPlayer::Death(void)
{
	if (m_bHit == true)
	{
		m_bHit = false;
	}
	for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
	{
		CScene * pScene = GetScene(4, nCountScene);
		if (pScene != NULL)
		{
			//オブジェタイプの取得
			OBJTYPE objType;
			objType = pScene->GetObjType();
			//シーンオブジェクトの位置を取得
			D3DXVECTOR3 Scene_pos;
			Scene_pos = pScene->GetPosition();
			//もしオブジェタイプが弾の場合
			if (objType == OBJTYPE_BULLET)
			{
				pScene->Uninit();
			}
		}
	}
	//透明状態
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_col[nCount] = m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 0);
	}
	//もしカウントが死亡時間以下の場合
	if (m_nDeathCount >= PLAYER_DEATH_TIME)
	{
		//自機を初期位置に配置
		m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 180, 0.0f);
		//死亡状態解除
		m_bDeath = false;
		//無敵状態にする
		m_bInvincible = true;
		//カウントを0に戻す
		m_nDeathCount = 0;
	}
	//死亡時間を進める
	m_nDeathCount++;
}

//=============================================================================
// スコア取得関数
//=============================================================================
void CPlayer::SetPlayerScpre(int nValue)
{
	m_nScore = nValue;
}

//=============================================================================
// 名前取得関数
//=============================================================================
void CPlayer::SetPlayerName(int nCount,char aName)
{
	m_aPlayerName[nCount] = aName;
}

//=============================================================================
// セーブ関数
//=============================================================================
void CPlayer::Save(void)
{
	FILE *pFile;

	pFile = fopen("data/TEXT/PlayerData.txt", "w"); //ファイルの書き込み

	if (pFile != NULL)
	{
		//名前を記録
		fprintf(pFile, "%s\n", &m_aPlayerName);
		//死亡数を記録
		fprintf(pFile, "%d\n", m_nDeath);
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
// 入力情報セーブ関数
//=============================================================================
void CPlayer::InputSave(void)
{
	FILE *pFile;

	pFile = fopen("data/TEXT/InputData.txt", "w"); //ファイルの書き込み

	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < CGame::GetbInputSaveCount(); nCount++)
		{
			//プレイヤーの入力情報の記録
			fprintf(pFile, "%d", m_aInputData[nCount][0]);
			fprintf(pFile, "%d", m_aInputData[nCount][1]);
			fprintf(pFile, "%d", m_aInputData[nCount][2]);
			fprintf(pFile, "%d", m_aInputData[nCount][3]);
			fprintf(pFile, "%d", m_aInputData[nCount][4]);
			fprintf(pFile, "%d\n", m_aInputData[nCount][5]);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}

//=============================================================================
// 入力情報読み込み関数
//=============================================================================
void CPlayer::InputLoad(void)
{
	FILE *pFile;
	pFile = fopen("data/TEXT/InputData.txt", "r"); //ファイルの読み込み
	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < 15000; nCount++)
		{
			//プレイヤーの入力情報読み込み
			fscanf(pFile, "%s", &m_aInputData[nCount][0]);
		}
		fclose(pFile); //ファイルを閉じる
	}
}
