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
// インクルードファイル
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "Base/main.h"
#include "Base/manager.h"
#include "Mode/mode_game.h"
#include "Base/renderer.h"
#include "Base/sound.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "player.h"
#include "Base/camera.h"
#include "Effect/stan_effect.h"
#include "Mode/continue.h"
#include "Base/animation.h"
#include "Item/meat.h"
#include "Map/wood.h"
#include "3DPolygon/shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCRIPT_PASS ("Data/Script/PlayerData.txt")				//スクリプトパス
#define INITIAL_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))			//位置の初期値
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))				//サイズの初期値
#define INITIAL_COLLISIION_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//衝突判定用サイズの初期値
#define INITIAL_ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))			//回転の初期値
#define INITIAL_MOVE (D3DXVECTOR3(0.0f,0.0f,0.0f))				//移動量の初期値
#define MINIMUM_MEAT (0)										//肉の最小数
#define MINIMUM_LIFE (0)										//体力
#define MINIMUM_DIAMOND (0)										//ダイアモンドの最小数
#define MINIMUM_STAN_TIME (0)									//スタン時間の最小値
#define INITIAL_MOVE_SPEED (0.0f)								//移動速度の初期値							
#define INITIAL_JUMP_POWER (0.0f)								//ジャンプ力の初期値
#define INITIAL_GRAVITY (0.0f)									//重力の初期値
#define STANEFFECT_SIZE	(D3DXVECTOR3(30.0f,30.0f,0.0f))			//スタンエフェクトサイズ
#define STANEFFECT_ROT	(D3DXVECTOR3(0.0f,0.0f,0.0f))			//スタンエフェクト向き
#define STANEFFECT_COL	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))		//スタンエフェクトカラー
#define STANEFFECT_LENGTH	(80.0f)								//スタンエフェクト距離
#define JUMP_Z_VALUE		(6.4f)
#define STAN_POS		(D3DXVECTOR3(Position.x,Position.y + 160.0f,Position.z))

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;		
LPD3DXMESH CPlayer::m_pMesh[PARTS_MAX] = {};		
LPD3DXBUFFER CPlayer::m_pBuffMat[PARTS_MAX] = {};	
DWORD CPlayer::m_nNumMat[PARTS_MAX] = {};			

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer()
{
	m_Size = INITIAL_SIZE;						//サイズ
	m_Move = INITIAL_MOVE;						//移動量
	m_ContinuePosition = INITIAL_POSITION;		//コンティニューする位置
	m_nMeat = MINIMUM_MEAT;						//肉の所持数
	m_nMaxMeat = MINIMUM_MEAT;					//肉の最大数
	m_nDiamond = MINIMUM_DIAMOND;				//ダイアモンドの所持数
	m_nStunTime = MINIMUM_STAN_TIME;			//スタン時間
	m_nStunTimeCount = MINIMUM_STAN_TIME;		//スタン時間のカウント
	m_nLife = MINIMUM_LIFE;						//体力
	m_fAutoRunSpeed = INITIAL_MOVE_SPEED;		//移動速度
	m_fSlowSpeed = INITIAL_MOVE_SPEED;			//スロウ速度
	m_fLeftRightSpeed = INITIAL_MOVE_SPEED;		//左右移動速度
	m_fJumpPower = INITIAL_JUMP_POWER;			//ジャンプ力
	m_fGravity = INITIAL_GRAVITY;				//重力
	m_bHit = false;								//ヒットしたか
	m_bJump = false;							//ジャンプしたかどうか
	m_bContinue = false;						//コンティニューするかどうか
	m_bSlowRun = false;							//スロウにするか
	m_bStop = false;							//停止するか
	m_bContinuePositionSave = false;			//コンティニューする位置を保存するか
	m_State = STATE_NONE;						//状態
	m_Input = INPUT_NONE;						//入力情報
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// プレイヤー1
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/00_Body.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_BODY], NULL, &m_nNumMat[PARTS_BODY], &m_pMesh[PARTS_BODY]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/01_Head.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_HEAD], NULL, &m_nNumMat[PARTS_HEAD], &m_pMesh[PARTS_HEAD]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/02_RightArm.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RARM], NULL, &m_nNumMat[PARTS_RARM], &m_pMesh[PARTS_RARM]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/03_RightHand.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RHAND], NULL, &m_nNumMat[PARTS_RHAND], &m_pMesh[PARTS_RHAND]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/04_LeftArm.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LARM], NULL, &m_nNumMat[PARTS_LARM], &m_pMesh[PARTS_LARM]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/05_LeftHand.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LHAND], NULL, &m_nNumMat[PARTS_LHAND], &m_pMesh[PARTS_LHAND]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/06_RightLeg.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RLEG], NULL, &m_nNumMat[PARTS_RLEG], &m_pMesh[PARTS_RLEG]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/07_RightShoe.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_RSHOE], NULL, &m_nNumMat[PARTS_RSHOE], &m_pMesh[PARTS_RSHOE]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/08_LeftLeg.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LLEG], NULL, &m_nNumMat[PARTS_LLEG], &m_pMesh[PARTS_LLEG]);
	D3DXLoadMeshFromX(LPCSTR("./Data/model/player/09_LeftShoe.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PARTS_LSHOE], NULL, &m_nNumMat[PARTS_LSHOE], &m_pMesh[PARTS_LSHOE]);
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CPlayer::Unload(void)
{
	//もしテクスチャのポインタがNULLではない場合
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャのポインタをNULL
		m_pTexture = NULL;
	}
}
//=============================================================================
// 生成処理関数
//=============================================================================
CPlayer * CPlayer::Create(void)
{
	//プレイヤーのポインタ
	CPlayer * pPlayer = NULL;
	//プレイヤーのポインタがNULLの場合
	if (pPlayer == NULL)
	{
		//プレイヤーのメモリ確保
		pPlayer = new CPlayer;
		//プレイヤーのポインタがNULLではない場合
		if (pPlayer != NULL)
		{
			//プレイヤーの初期化処理関数呼び出し
			pPlayer->Init();
		}
	}
	//プレイヤーのポインタを返す
	return pPlayer;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	// パーツ数を設定
	SetPartNum(PARTS_MAX);
	//パーツの最大数分回す
	for (int nCount = 0; nCount < PARTS_MAX; nCount++)
	{
		//メッシュの割り当て
		BindMesh(CAnimation::TYPE_HUMAN, nCount, m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount]);
	}
	// 座標・親子関係の読み込み
	LoadModelData("./Data/text/motion.txt");
	//データ読み込み関数呼び出し
	DataLoad();
	//キャラクターの初期化処理関数呼び出し
	CCharacter::Init();
	//プレイヤーの状態を生存状態にする
	m_State = STATE_LIVE;
	//影生成
	CShadow::Create();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit()
{
	//キャラクターの終了処理関数呼び出し
	CCharacter::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update()
{
	//キャラクターの更新処理関数呼び出し
	CCharacter::Update();
	//アニメーションの取得
	CAnimation * pAnimation = GetAnimation();
	//もし生きていたら
	if (m_State == STATE_LIVE)
	{
		//もしヒットしたら
		if (m_bHit == true)
		{
			//スタン時間を加算する
			m_nStunTimeCount++;
			//もしスタン時間内だった場合
			if (m_nStunTimeCount <= m_nStunTime)
			{
				//スタンアニメーション再生
				pAnimation->SetAnimation(MOTION_STAN);
				//移動量を0にする
				m_Move = INITIAL_MOVE;
			}
			else
			{
				//ヒット状態をやめる
				m_bHit = false;
				//スタン時間を0にする
				m_nStunTimeCount = MINIMUM_STAN_TIME;
			}
		}
		else
		{
			//入力処理関数呼び出し
			Input();
			//移動処理関数呼び出し
			Move();
		}
		//もしジャンプ状態がfalseかつヒット状態がfalse
		if (m_bJump == false && m_bHit == false)
		{
			//ダッシュアニメーションの再生
			pAnimation->SetAnimation(MOTION_DUSH);
		}
	}
	//移動可能範囲処理関数
	MovableRange();
	//重力処理関数呼び出し
	Gravity();
	//もしコンティニューしたら
	if (m_bContinue == true)
	{
		//コンティニュー処理関数呼び出し
		Continue();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//キャラクターの描画処理関数呼び出し
	CCharacter::Draw();
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
	//アニメーションの取得
	CAnimation * pAnimation = GetAnimation();

	//ジョイスティックの振動取得
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//ゲームモードの取得
	CGameMode * pGameMode = CManager::GetGameMode();
	//キーが押されていない場合
	m_Input = INPUT_NONE;
	//左移動処理
	if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
	{
		//入力キー情報を左にする
		m_Input = INPUT_LEFT;
	}
	//右移動処理
	if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
	{
		//入力キー情報を右にする
		m_Input = INPUT_RIGHT;
	}
	//ジャンプ処理関数
	if (pKeyboard->GetKeyboardTrigger(DIK_SPACE) || pJoystick->GetJoystickTrigger(JS_A))
	{
		//入力キー情報をスペースにする
		m_Input = INPUT_SPACE;
	}
}

//=============================================================================
// 移動処理関数
//=============================================================================
void CPlayer::Move(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//アニメーションの取得
	CAnimation * pAnimation = GetAnimation();
	//位置を取得する
	D3DXVECTOR3 Position = GetPos();
	//もし死亡状態じゃないとき
	if (m_State != STATE_DEATH)
	{
		switch (m_Input)
		{
			//もし入力情報が左の場合
		case INPUT_LEFT:
			//移動量を設定する
			m_Move.x = m_fLeftRightSpeed;
			break;
			//もし入力情報が右の場合
		case INPUT_RIGHT:
			//移動量を設定する
			m_Move.x = -m_fLeftRightSpeed;
			break;
			//もし入力情報がスペースの場合
		case INPUT_SPACE:
			//もしジャンプ状態じゃない場合
			if (m_bJump == false)
			{
				//もしサウンドのポインタがNULLじゃない場合
				if (pSound != NULL)
				{
					//タイトルBGMの再生
					pSound->PlaySoundA(CSound::SOUND_LABEL_SE_PLAYER_JUMP);
				}
				pAnimation->SetAnimation(MOTION_JUMP);
				//移動量を設定する
				m_Move.y += m_fJumpPower;
				//ジャンプ状態にする
				m_bJump = true;
			}
			break;
		default:
			break;
		}
		//もし停止しないなら
		if (m_bStop == false)
		{
			//もしスロウ状態じゃない場合
			if (m_bSlowRun == false)
			{
				//オートランの速度にする
				m_Move.z = m_fAutoRunSpeed;
			}
			else
			{
				//オートラン(スロウ)の速度にする
				m_Move.z = m_fSlowSpeed;
			}
			if (m_bJump == true)
			{
				m_Move.z += JUMP_Z_VALUE;
			}
		}
	}
	//位置更新
	Position.x += m_Move.x;
	Position.y += m_Move.y;
	Position.z += m_Move.z;

	//もしコンティニューする位置を保存するなら
	if (m_bContinuePositionSave == true)
	{
		//コンティニューする位置を保存する
		m_ContinuePosition = Position;
	}

	CScene *pScene = CScene::GetTopScene(OBJTYPE_WOOD);
	bool bStop = false;

	while (pScene != NULL)
	{
		CScene *pNextScene = pScene->GetNextScene();

		CWood *pWood = (CWood*)pScene;
		D3DXVECTOR3 woodPos = pWood->GetPos();

		if (Position.x + COLLISION_SIZE_PLAYER.x / 2 >= woodPos.x - COLLISION_SIZE_WOOD.x / 2 &&
			Position.x - COLLISION_SIZE_PLAYER.x / 2 <= woodPos.x + COLLISION_SIZE_WOOD.x / 2 &&
			Position.z + COLLISION_SIZE_PLAYER.z / 2 >= woodPos.z - COLLISION_SIZE_WOOD.z / 2 &&
			Position.z - COLLISION_SIZE_PLAYER.z / 2 <= woodPos.z + COLLISION_SIZE_WOOD.z / 2 &&
			!m_bJump)
		{
			SetbStop(true);
			bStop = true;
			break;
		}
		else
		{
			SetbStop(false);
			pScene = pNextScene;
		}
	}
	//位置を設定する
	SetPos(Position);
}

//=============================================================================
// 重力処理関数
//=============================================================================
void CPlayer::Gravity(void)
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPos();
	//もし位置が初期位置より下にいったら
	if (Position.y <= INITIAL_POSITION.y)
	{
		m_Move = INITIAL_MOVE;
		//初期位置に戻す
		Position.y = INITIAL_POSITION.y;
		//ジャンプ状態をやめる
		m_bJump = false;
	}
	//重力をかける
	m_Move.y += m_fGravity;
	//位置更新
	Position.y += m_Move.y;
	//位置を設定する
	SetPos(Position);
}

//=============================================================================
// ヒット処理関数
//=============================================================================
void CPlayer::Hit(void)
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPos();
	//肉の所持数を減算する
	if (m_nMeat > MINIMUM_MEAT)
	{
		//肉を生成する
		CMeat::Create(Position);
		m_nMeat--;
	}
	//体力を減算する
	m_nLife--;
	//ヒットさせる
	m_bHit = true;
	//スタンエフェクトの生成
	CStan_Effect::StanEffect_Create(STAN_POS, STANEFFECT_SIZE, STANEFFECT_ROT, STANEFFECT_COL, STANEFFECT_LENGTH);
	//もし肉の所持数が0以下になったら
	if (m_nLife <= MINIMUM_MEAT)
	{
		//死亡処理関数呼び出し
		Death();
	}
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CPlayer::Death(void)
{
	//死亡状態にする
	m_State = STATE_DEATH;
	//ダイアモンドの所持数を0にする
	m_nDiamond = MINIMUM_DIAMOND;
	//コンティニュー画面の生成
	CGameMode::SetContinue(CContinue::Create());
	//ヒット状態をやめる
	m_bHit = false;
}

//=============================================================================
// コンティニュー関数
//=============================================================================
void CPlayer::Continue(void)
{
	D3DXVECTOR3 Position = GetPos();
	//コンティニューをやめる
	m_bContinue = false;
	//肉の所持数を回復させる
	m_nMeat = m_nMaxMeat;
	//体力を回復させる
	m_nLife = m_nMeat + 1;
	//チェックポイントに戻す
	Position = m_ContinuePosition;
	//位置を設定する
	SetPos(Position);
	//生存状態にする
	m_State = STATE_LIVE;
}

//=============================================================================
// 移動可能範囲処理関数
//=============================================================================
void CPlayer::MovableRange(void)
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPos();
	//もしプレイヤーが左画面外に行ったら
	if (Position.x + COLLISION_SIZE_PLAYER.x / 2 > -230)
	{
		//位置が画面外に移動しないように制御する
		Position.x = -COLLISION_SIZE_PLAYER.x / 2 - 230;
	}
	//もしプレイヤーが右画面外に行ったら
	if (Position.x + COLLISION_SIZE_PLAYER.x / 2 < -780)
	{
		//位置が画面外に移動しないように制御する
		Position.x = -COLLISION_SIZE_PLAYER.x / 2 - 780;
	}
	SetPos(Position);
}

//=============================================================================
// データ読み込み関数
//=============================================================================
void CPlayer::DataLoad(void)
{
	D3DXVECTOR3 Position = INITIAL_POSITION;	//位置
	D3DXVECTOR3 CollisionSize = INITIAL_SIZE;	//衝突判定用サイズ
	D3DXVECTOR3 Rotation = INITIAL_ROTATION;	//回転
	char aReadText[MAX_TEXT];					//読み込んだテキスト
	char aCurrentText[MAX_TEXT];				//現在のテキスト
	char aUnnecessaryText[MAX_TEXT];			//不必要なテキスト
	memset(aReadText, NULL, sizeof(aReadText));
	memset(aCurrentText, NULL, sizeof(aCurrentText));
	memset(aUnnecessaryText, NULL, sizeof(aUnnecessaryText));
	//ファイルのポインタ
	FILE *pFile = NULL;
	//もしファイルのポインタがNULLの場合
	if (pFile == NULL)
	{
		//ファイルの読み込み
		pFile = fopen(SCRIPT_PASS, "r");
		//ファイルを開くことができたら
		if (pFile != NULL)
		{
			//SCRIPTの文字を見つける
			while (strcmp(aCurrentText, "SCRIPT") != 0)
			{
				//読み込んだテキストを格納する
				fgets(aReadText, sizeof(aReadText), pFile);
				//読み込んだテキストを現在のテキストに格納
				sscanf(aReadText, "%s", &aCurrentText);
			}
			//現在のテキストがSCRIPTだったら
			if (strcmp(aCurrentText, "SCRIPT") == 0)
			{
				//END_SCRIPTの文字が見つかるまで読む
				while (strcmp(aCurrentText, "END_SCRIPT") != 0)
				{
					//読み込んだテキストを格納する
					fgets(aReadText, sizeof(aReadText), pFile);
					//読み込んだテキストを現在のテキストに格納
					sscanf(aReadText, "%s", &aCurrentText);
					//現在のテキストがPARAMETER_SETだったら
					if (strcmp(aCurrentText, "PARAMETER_SET") == 0)
					{
						//END_PARAMETER_SETの文字が見つかるまで読む
						while (strcmp(aCurrentText, "END_PARAMETER_SET") != 0)
						{
							//読み込んだテキストを格納する
							fgets(aReadText, sizeof(aReadText), pFile);
							//読み込んだテキストを現在のテキストに格納
							sscanf(aReadText, "%s", &aCurrentText);
							//現在のテキストがPOSだったら
							if (strcmp(aCurrentText, "POS") == 0)
							{
								//位置情報の読み込み
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Position.x, &Position.y, &Position.z);
								//コンティニューする位置を設定する
								m_ContinuePosition = Position;
								//位置を設定する
								SetPos(Position);
							}
							//現在のテキストがSIZEだったら
							if (strcmp(aCurrentText, "SIZE") == 0)
							{
								//サイズ情報の読み込み
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Size.x, &m_Size.y, &m_Size.z);
							}
							//現在のテキストがCOLLISION_SIZEだったら
							if (strcmp(aCurrentText, "COLLISION_SIZE") == 0)
							{
								//衝突判定用のサイズの取得
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &CollisionSize.x, &CollisionSize.y, &CollisionSize.z);
							}
							//現在のテキストがROTだったら
							if (strcmp(aCurrentText, "ROT") == 0)
							{
								//回転情報の読み込み
								sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Rotation.x, &Rotation.y, &Rotation.z);
								//回転を設定する
								SetRot(D3DXToRadian(Rotation));
							}
							//現在のテキストがMeatだったら
							if (strcmp(aCurrentText, "Meat") == 0)
							{
								//サイズの設定
								sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nMaxMeat);
								//肉の所持数を設定する
								m_nMeat = m_nMaxMeat;
								m_nLife = m_nMeat + 1;
							}
							//現在のテキストがStunTimeだったら
							if (strcmp(aCurrentText, "StunTime") == 0)
							{
								//スタン速度の設定
								sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nStunTime);
							}
							//現在のテキストがAutoRunSpeedだったら
							if (strcmp(aCurrentText, "AutoRunSpeed") == 0)
							{
								//オートラン速度の設定
								sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fAutoRunSpeed);
							}
							//現在のテキストがSlowSpeedだったら
							if (strcmp(aCurrentText, "SlowSpeed") == 0)
							{
								//スロウ速度の設定
								sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fSlowSpeed);
							}
							//現在のテキストがLeftRightSpeedだったら
							if (strcmp(aCurrentText, "LeftRightSpeed") == 0)
							{
								//サイズの設定
								sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fLeftRightSpeed);
							}
							//現在のテキストがJumpPowerだったら
							if (strcmp(aCurrentText, "JumpPower") == 0)
							{
								//サイズの設定
								sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fJumpPower);
							}
							//現在のテキストがGravityだったら
							if (strcmp(aCurrentText, "Gravity") == 0)
							{
								//サイズの設定
								sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fGravity);
							}
						}
					}
				}
			}
			//ファイルを閉じる
			fclose(pFile);
		}
	}
}