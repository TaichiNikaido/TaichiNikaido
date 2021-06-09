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
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/sound.h"
#include "Base/camera.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "Mode/mode_game.h"
#include "player.h"
#include "enemy_dragon.h"
#include "Weapon/weapon_sword.h"
#include "Weapon/weapon_shield.h"
#include "Polygon3d/shadow.h"
#include "Polygon3d/round_shadow.h"
#include "Polygon2d/game_over_logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PASS ("Data/Script/Player/PlayerModel.txt")		//モデルスクリプトのパス
#define SCRIPT_PASS ("Data/Script/Player/PlayerData.txt")		//プレイヤーデータのスクリプトのパス
#define MINIMUM_LIFE (0)										//体力の最小値
#define MINIMUM_ATTACK (0)										//攻撃力の最小値
#define MINIMUM_ATTACK_COMBO (0)								//攻撃コンボ数の最小値
#define MINIMUM_COOL_TIME (0)									//クールタイム
#define MINIMUM_SPEED (0.0f)									//初期速さ
#define MINIMUM_WALK_SPEED (0.0f)								//初期歩行速度
#define MINIMUM_DASH_SPEED (0.0f)								//初期ダッシュ速度
#define MINIMUM_ADD_DIRECTION_VALUE (D3DXToRadian(0.75f))		//向きの加算値の初期値
#define MINIMUM_CAMERA_DISTANCE (0.0f)							//カメラとの距離
#define ATTACK1_COOL_TIME (1)									//攻撃(1)のクールタイム
#define ATTACK2_COOL_TIME (2)									//攻撃(2)のクールタイム
#define ATTACK3_COOL_TIME (3)									//攻撃(3)のクールタイム
#define BURNING_MINIMUM_TIME (0)								//燃焼時間の最小値
#define BURNING_SUB_LIFE (1)									//燃焼時の体力減算量
#define ROUND_SHADOW_SIZE (D3DXVECTOR3(50.0f,50.0f,50.0f))		//丸影のサイズ
#define ROUND_SHADOW_COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))		//丸影の色

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODEL_DATA CPlayer::m_aPlayerModelData[MAX_PARTS] = {};	//モデル情報

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer()
{
	m_DirectionDest = INITIAL_D3DXVECTOR3;				//目的の向き
	m_Move = INITIAL_D3DXVECTOR3;						//移動量
	m_nMaxLife = MINIMUM_LIFE;							//最大体力
	m_nLife = MINIMUM_LIFE;								//体力
	m_nAttack = MINIMUM_ATTACK;							//攻撃力
	m_nAttackCombo = MINIMUM_ATTACK_COMBO;				//攻撃コンボ
	m_nCoolTime = MINIMUM_COOL_TIME;					//クールタイム
	m_nCoolTimeCount = MINIMUM_COOL_TIME;				//クールタイムカウント
	m_nBurningTime = BURNING_MINIMUM_TIME;				//燃焼タイム
	m_nBurningTiming = BURNING_MINIMUM_TIME;			//燃焼タイミング
	m_nBurningTimeCount = BURNING_MINIMUM_TIME;			//燃焼カウント
	m_fSpeed = MINIMUM_SPEED;							//速さ
	m_fWalkSpeed = MINIMUM_WALK_SPEED;					//歩行速度
	m_fDashSpeed = MINIMUM_DASH_SPEED;					//ダッシュ速度
	m_fDirectionValue = MINIMUM_ADD_DIRECTION_VALUE;	//向きの値
	m_fCameraDistance = MINIMUM_CAMERA_DISTANCE;		//カメラとの距離
	m_bWeapon = false;									//武器を使用してるか
	m_bBurning = false;									//燃えてるか
	m_State = STATE_NONE;								//状態
	m_Input = INPUT_NONE;								//入力情報
	m_pRoundShadow = nullptr;							//丸影のポインタ
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
HRESULT CPlayer::ModelLoad(void)
{
	//マテリアルのポインタ
	D3DXMATERIAL * pMaterial;
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//パスのポインタ
	char * pPass = nullptr;
	//もしパスのポインタがnullptrの場合
	if (pPass == nullptr)
	{
		//パスを取得
		pPass = CModel::LoadModelText(MODEL_PASS);
	}
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしパスのポインタがnullptrじゃない場合
		if (pPass != nullptr)
		{
			//モデル読み込み
			D3DXLoadMeshFromX(pPass,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_aPlayerModelData[nCount].pBuffMat,
				NULL,
				&m_aPlayerModelData[nCount].nNumMat,
				&m_aPlayerModelData[nCount].pMesh);
			//もしモデルのマテリアル情報がNULLじゃない場合
			if (m_aPlayerModelData[nCount].pBuffMat != NULL)
			{
				//マテリアルのポインタを取得
				pMaterial = (D3DXMATERIAL *)m_aPlayerModelData[nCount].pBuffMat->GetBufferPointer();
				//モデルデータ数分回す
				for (int nCountMat = 0; nCountMat < (int)m_aPlayerModelData[nCount].nNumMat; nCountMat++)
				{
					//もしファイルネームがNULLじゃない場合
					if (pMaterial[nCountMat].pTextureFilename != NULL)
					{
						//テクスチャを読み込む
						D3DXCreateTextureFromFile(pDevice, pMaterial[nCountMat].pTextureFilename, &m_aPlayerModelData[nCount].pTexture[nCountMat]);
					}
				}
			}
			//ポインタを捨てる
			pPass += MAX_TEXT;
		}
	}
	return S_OK;
}

//=============================================================================
// モデル破棄関数
//=============================================================================
void CPlayer::ModelUnload(void)
{
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルデータのワールド変換行列がNULLではない場合
		if (m_aPlayerModelData[nCount].mtxWorld != NULL)
		{
			//もしモデルデータのマテリアル情報がNULLではない場合
			if (m_aPlayerModelData[nCount].pBuffMat != NULL)
			{
				//モデルデータのマテリアル情報を破棄
				m_aPlayerModelData[nCount].pBuffMat->Release();
			}
			//もしモデルデータのメッシュ情報がNULLではない場合
			if (m_aPlayerModelData[nCount].pMesh != NULL)
			{
				//モデルデータのメッシュ情報を破棄
				m_aPlayerModelData[nCount].pMesh->Release();
			}
			//マテリアルの最大数分回す
			for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
			{
				//もしモデルデータのテクスチャのポインタがNULLではない場合
				if (m_aPlayerModelData[nCount].pTexture[nCountTexture] != NULL)
				{
					//モデルデータのテクスチャのポインタを破棄
					m_aPlayerModelData[nCount].pTexture[nCountTexture]->Release();
				}
			}
		}
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CPlayer * CPlayer::Create()
{
	//プレイヤーのポインタ
	CPlayer * pPlayer = nullptr;
	//プレイヤーのポインタがnullptrの場合
	if (pPlayer == nullptr)
	{
		//プレイヤーのメモリ確保
		pPlayer = new CPlayer;
		//プレイヤーのポインタがnullptrではない場合
		if (pPlayer != nullptr)
		{
			//プレイヤーの初期化処理関数呼び出し
			pPlayer->Init();
		}
	}
	//プレイヤーのポインタを返す
	return pPlayer;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//データ読み込み関数呼び出し
	DataLoad();
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//モデル情報の設定
	SetModelData(m_aPlayerModelData);
	//キャラクターの初期化処理関数呼び出し
	CCharacter::Init();
	//もし丸影のポインタがnullptrの場合
	if (m_pRoundShadow == nullptr)
	{
		//丸影の生成
		m_pRoundShadow = CRoundShadow::Create(D3DXVECTOR3(Position.x,Position.y + 0.5f, Position.z), ROUND_SHADOW_SIZE, ROUND_SHADOW_COLOR);
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPlayer::Uninit(void)
{
	//キャラクターの終了処理関数呼び出し
	CCharacter::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPlayer::Update(void)
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//キャラクターの更新処理関数呼び出し
	CCharacter::Update();
	//もし状態が死亡状態ではない場合
	if (m_State != STATE_DEATH)
	{
		//入力処理関数呼び出し
		Input();
	}
	//位置更新
	Position += m_Move;
	//もし丸影のポインタがnullptrではない場合
	if (m_pRoundShadow != nullptr)
	{
		//丸影に位置を設定する
		m_pRoundShadow->SetPosition(D3DXVECTOR3(Position.x, Position.y + 0.5f, Position.z));
	}
	//位置を設定する
	SetPosition(Position);
	//モーション処理関数呼び出し
	Motion();
	//もし燃焼した場合
	if (m_bBurning == true)
	{
		//燃焼処理関数呼び出し
		Burning();
	}
	//もし体力が最小値以下になったら
	if (m_nLife <= MINIMUM_LIFE)
	{
		//もし状態が死亡状態ではない場合
		if (m_State != STATE_DEATH)
		{
			//死亡処理関数呼び出し
			Death();
		}
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPlayer::Draw(void)
{
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
	//ジョイスティックの振動取得
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//モーションのポインタを取得する
	CMotion * pMotion = GetpMotion();
	//移動量を0にする
	m_Move = INITIAL_D3DXVECTOR3;
	//もしダッシュキーが押されていたら
	if (pKeyboard->GetKeyboardPress(DIK_LSHIFT) || pJoystick->GetJoystickPress(JS_RB))
	{
		//状態をダッシュ状態にする
		m_State = STATE_DASH;
	}
	else
	{
		//状態を無にする
		m_State = STATE_NONE;
	}
	//上移動処理
	if (pKeyboard->GetKeyboardPress(DIK_W) || lpDIDevice != NULL &&js.lY == -1000)
	{
		//もしダッシュ状態ではない場合
		if (m_State != STATE_DASH)
		{
			//状態を歩行状態にする
			m_State = STATE_WALK;
		}
		//入力キー情報を上にする
		m_Input = INPUT_UP;
		//移動処理関数呼び出し
		Move();
	}
	//下移動処理
	if (pKeyboard->GetKeyboardPress(DIK_S) || lpDIDevice != NULL &&js.lY == 1000)
	{
		//もしダッシュ状態ではない場合
		if (m_State != STATE_DASH)
		{
			//状態を歩行状態にする
			m_State = STATE_WALK;
		}
		//入力キー情報を下にする
		m_Input = INPUT_DOWN;
		//移動処理関数呼び出し
		Move();
	}
	//左移動処理
	if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
	{
		//もしダッシュ状態ではない場合
		if (m_State != STATE_DASH)
		{
			//状態を歩行状態にする
			m_State = STATE_WALK;
		}
		//入力キー情報を左にする
		m_Input = INPUT_LEFT;
		//移動処理関数呼び出し
		Move();
	}
	//右移動処理
	if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
	{
		//もしダッシュ状態ではない場合
		if (m_State != STATE_DASH)
		{
			//状態を歩行状態にする
			m_State = STATE_WALK;
		}
		//入力キー情報を右にする
		m_Input = INPUT_RIGHT;
		//移動処理関数呼び出し
		Move();
	}
	//攻撃処理
	if (pKeyboard->GetKeyboardTrigger(DIK_L) || pJoystick->GetJoystickTrigger(JS_Y))
	{
		//もし武器を使用していたら
		if (m_bWeapon == true)
		{
			//攻撃処理関数呼び出し
			Attack();
		}
		else
		{
			//武器を使用する
			m_bWeapon = true;
		}
	}
	//納刀処理
	if (pKeyboard->GetKeyboardTrigger(DIK_I) || pJoystick->GetJoystickTrigger(JS_X))
	{
		//武器の使用を止める
		m_bWeapon = false;
	}
	//ガード処理
	if (pKeyboard->GetKeyboardPress(DIK_G) || pJoystick->GetJoystickPress(JS_RT))
	{
		//ガード処理関数呼び出し
		Guard();
	}
	else
	{
		//状態を無にする
		STATE_NONE;
	}
	if (pKeyboard->GetKeyboardTrigger(DIK_O))
	{
		m_nLife = 0;
	}
	if (pKeyboard->GetKeyboardTrigger(DIK_L))
	{
		m_bBurning = true;
	}
}

//=============================================================================
// 移動処理関数
//=============================================================================
void CPlayer::Move(void)
{
	//回転を取得
	D3DXVECTOR3 Rotation = GetRotation();
	switch (m_State)
	{
	case STATE_WALK:
		//速度を歩行速度にする
		m_fSpeed = m_fWalkSpeed;
		break;
	case STATE_DASH:
		//速度をダッシュ速度にする
		m_fSpeed = m_fDashSpeed;
		break;
	default:
		break;
	}
	//カメラの取得
	CCamera * pCamera = CManager::GetGameMode()->GetCamera();
	//もしカメラのポインタがNULLではない場合
	if (pCamera != nullptr)
	{
		//カメラの回転を取得
		D3DXVECTOR3 CameraRotation = pCamera->GetRotation();
		switch (m_Input)
		{
			//もし入力情報が上の場合
		case INPUT_UP:
			m_Move.x = sinf(-(CameraRotation.y + D3DXToRadian(90.0f))) * m_fSpeed;
			m_Move.z = cosf(-(CameraRotation.y + D3DXToRadian(90.0f))) * m_fSpeed;
			break;
			//もし入力情報が下の場合
		case INPUT_DOWN:
			m_Move.x = sinf(-(CameraRotation.y + D3DXToRadian(90.0f))) * -m_fSpeed;
			m_Move.z = cosf(-(CameraRotation.y + D3DXToRadian(90.0f))) * -m_fSpeed;
			break;
			//もし入力情報が左の場合
		case INPUT_LEFT:
			m_Move.x = sinf(-(CameraRotation.y + D3DXToRadian(180.0f))) * m_fSpeed;
			m_Move.z = cosf(-(CameraRotation.y + D3DXToRadian(180.0f))) * m_fSpeed;
			break;
			//もし入力情報が右の場合
		case INPUT_RIGHT:
			m_Move.x = sinf(-(CameraRotation.y + D3DXToRadian(0.0f))) * m_fSpeed;
			m_Move.z = cosf(-(CameraRotation.y + D3DXToRadian(0.0f))) * m_fSpeed;
			break;
		default:
			break;
		}
		//目的の向きを設定する
		m_DirectionDest = D3DXVECTOR3(D3DXToRadian(0.0f), atan2f(m_Move.x, m_Move.z) + D3DXToRadian(180.0f), D3DXToRadian(0.0f));
		while (m_DirectionDest.y - Rotation.y < D3DXToRadian(-180))
		{
			m_DirectionDest.y += D3DXToRadian(360);
		}
		while (m_DirectionDest.y - Rotation.y > D3DXToRadian(180))
		{
			m_DirectionDest.y -= D3DXToRadian(360);
		}
		//プレイヤーの向きを更新する
		Rotation += (m_DirectionDest - Rotation) * 0.1f;
		//回転を設定
		SetRotation(Rotation);
	}
}

//=============================================================================
// 攻撃処理関数
//=============================================================================
void CPlayer::Attack(void)
{
	//もし攻撃状態がfalseの場合
	if (m_State != STATE_ATTACK)
	{
		//もし攻撃コンボが最大数より下の場合
		if (m_nAttackCombo < ATTACK_3)
		{
			//攻撃コンボを加算する
			m_nAttackCombo++;
			//状態を攻撃状態にする
			m_State = STATE_ATTACK;
		}
		else
		{
			//攻撃コンボを初期化する
			m_nAttackCombo = ATTACK_NONE;
		}
	}
	//各攻撃コンボの処理
	switch (m_nAttackCombo)
	{
	case ATTACK_1:
		//クールタイムの設定
		m_nCoolTime = ATTACK1_COOL_TIME;
		break;
	case ATTACK_2:
		//クールタイムの設定
		m_nCoolTime = ATTACK2_COOL_TIME;
		break;
	case ATTACK_3:
		//クールタイムの設定
		m_nCoolTime = ATTACK3_COOL_TIME;
		break;
	default:
		break;
	}
	//クールタイムを加算する
	m_nCoolTimeCount++;
	//もし現在のクールタイムが指定の時間を越えたら
	if (m_nCoolTimeCount >= m_nCoolTime)
	{
	}
}

//=============================================================================
// ガード処理関数
//=============================================================================
void CPlayer::Guard(void)
{
}

//=============================================================================
// 燃焼処理関数
//=============================================================================
void CPlayer::Burning(void)
{
	//体力を一定時間ごとに減少させる
	if (m_nBurningTimeCount <= m_nBurningTime)
	{
		//燃焼カウントを加算する
		m_nBurningTimeCount++;
		//もし燃焼タイミングになった場合
		if (m_nBurningTimeCount % m_nBurningTiming == BURNING_MINIMUM_TIME)
		{
			//体力を減算する
			m_nLife -= BURNING_SUB_LIFE;
		}
	}
	else
	{
		//燃焼状態を止める
		m_bBurning = false;
		//燃焼カウントを初期化する
		m_nBurningTimeCount = BURNING_MINIMUM_TIME;
	}
}

//=============================================================================
// ヒット処理関数
//=============================================================================
void CPlayer::Hit(void)
{
}

//=============================================================================
// 体力加算処理関数
//=============================================================================
void CPlayer::AddLife(int nValue)
{
	//もし体力が最大値以下の場合
	if (m_nLife < m_nMaxLife)
	{
		//体力を加算する
		m_nLife += nValue;
		//もし体力が最大値を越えた場合
		if (m_nLife > m_nMaxLife)
		{
			//体力を最大値にする
			m_nLife = m_nMaxLife;
		}
	}
}

//=============================================================================
// 体力減算処理関数
//=============================================================================
void CPlayer::SubLife(int nValue)
{
	//もし体力が0より多いの場合
	if (m_nLife > MINIMUM_LIFE)
	{
		//体力を加算する
		m_nLife -= nValue;
		//もし体力が最大値を越えた場合
		if (m_nLife <= MINIMUM_LIFE)
		{
			//体力を0にする
			m_nLife = MINIMUM_LIFE;
		}
	}
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CPlayer::Death(void)
{
	//状態を死亡状態にする
	m_State = STATE_DEATH;
	//ゲームオーバーロゴの生成
	CGameOverLogo::Create();
}

//=============================================================================
// 衝突判定処理関数
//=============================================================================
void CPlayer::Collision(void)
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//過去の位置を取得する
	D3DXVECTOR3 PositionOld = GetPositionOld();
	//サイズを取得する
	D3DXVECTOR3 CollisionSize = GetCollisionSize();
	//衝突判定用の箱の設定
	D3DXVECTOR3 PlayerBoxMax = D3DXVECTOR3(CollisionSize.x / 2, CollisionSize.y / 2, CollisionSize.z / 2) + Position;
	D3DXVECTOR3 PlayerBoxMin = D3DXVECTOR3(-CollisionSize.x / 2, -CollisionSize.y / 2, -CollisionSize.z / 2) + Position;
	//ドラゴンの取得
	CDragon * pDragon = CManager::GetGameMode()->GetDragon();
	//もしドラゴンのポインタがnullptrではない場合
	if (pDragon != nullptr)
	{
		//ドラゴンの位置を取得
		D3DXVECTOR3 DragonPosition = pDragon->GetPosition();
		//ドラゴンの衝突判定用サイズの取得
		D3DXVECTOR3 DragonCollisionSize = pDragon->GetCollisionSize();
		//衝突判定用の箱の設定
		D3DXVECTOR3 DragonBoxMax = D3DXVECTOR3(DragonCollisionSize.x / 2, DragonCollisionSize.y / 2, DragonCollisionSize.z / 2) + DragonPosition;
		D3DXVECTOR3 DragonBoxMin = D3DXVECTOR3(-DragonCollisionSize.x / 2, -DragonCollisionSize.y / 2, -DragonCollisionSize.z / 2) + DragonPosition;
	}
}

//=============================================================================
// モーション処理関数
//=============================================================================
void CPlayer::Motion(void)
{
	//モーションのポインタを取得する
	CMotion * pMotion = GetpMotion();
	//もしモーションのポインタがnullptrではない場合
	if (pMotion != nullptr)
	{
		switch (m_State)
		{
		case STATE_NONE:
			//もし武器を使用していない場合
			if (m_bWeapon == false)
			{
				//アイドルモーションを設定する
				pMotion->SetMotion(MOTION_IDLE);
			}
			else
			{
				//武器所持アイドルモーションの再生
				pMotion->SetMotion(MOTION_IDLE_WEAPON);
			}
			break;
		case STATE_WALK:
			//もし武器を使用していない場合
			if (m_bWeapon == false)
			{
				//歩行モーションを設定する
				pMotion->SetMotion(MOTION_WALK);
			}
			else
			{
				//武器所持歩行モーションを設定する
				pMotion->SetMotion(MOTION_WALK_WEAPON);
			}
			break;
		case STATE_DASH:
			//もし武器を使用していない場合
			if (m_bWeapon == false)
			{

			}
			else
			{

			}
			break;
		case STATE_DEATH:
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// データ読み込み関数
//=============================================================================
void CPlayer::DataLoad(void)
{
	D3DXVECTOR3 Position = INITIAL_D3DXVECTOR3;			//位置
	D3DXVECTOR3 Size = INITIAL_D3DXVECTOR3;				//サイズ
	D3DXVECTOR3 CollisionSize = INITIAL_D3DXVECTOR3;	//衝突判定用サイズ
	D3DXVECTOR3 Rotation = INITIAL_D3DXVECTOR3;			//回転
	char aReadText[MAX_TEXT];							//読み込んだテキスト
	char aCurrentText[MAX_TEXT];						//現在のテキスト
	char aUnnecessaryText[MAX_TEXT];					//不必要なテキスト
	memset(aReadText, NULL, sizeof(aReadText));
	memset(aCurrentText, NULL, sizeof(aCurrentText));
	memset(aUnnecessaryText, NULL, sizeof(aUnnecessaryText));
	//ファイルのポインタ
	FILE *pFile = nullptr;
	//もしファイルのポインタがnullptrの場合
	if (pFile == nullptr)
	{
		//ファイルの読み込み
		pFile = fopen(SCRIPT_PASS, "r");
	}
	//ファイルを開くことができたら
	if (pFile != nullptr)
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
						//現在のテキストがPositionだったら
						if (strcmp(aCurrentText, "Position") == 0)
						{
							//位置情報読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Position.x, &Position.y, &Position.z);
							//位置を設定する
							SetPosition(Position);
						}
						//現在のテキストがSizeだったら
						if (strcmp(aCurrentText, "Size") == 0)
						{
							//サイズ情報読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Size.x, &Size.y, &Size.z);
							//サイズを設定する
							SetSize(Size);
						}
						//現在のテキストがCollisionSizeだったら
						if (strcmp(aCurrentText, "CollisionSize") == 0)
						{
							//衝突判定用サイズの取得
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &CollisionSize.x, &CollisionSize.y, &CollisionSize.z);
							//衝突判定用サイズの設定
							SetCollisionSize(CollisionSize);
						}
						//現在のテキストがRotationだったら
						if (strcmp(aCurrentText, "Rotation") == 0)
						{
							//回転情報の読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &Rotation.x, &Rotation.y, &Rotation.z);
							//回転の設定
							SetRotation(Rotation);
						}
						//現在のテキストがMoveだったら
						if (strcmp(aCurrentText, "Move") == 0)
						{
							//サイズの設定
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Move.x, &m_Move.y, &m_Move.z);
						}
						//現在のテキストがLifeだったら
						if (strcmp(aCurrentText, "Life") == 0)
						{
							//最大体力の設定
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nMaxLife);
							//体力の設定
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nLife);
						}
						//現在のテキストがBurningTimeだったら
						if (strcmp(aCurrentText, "BurningTime") == 0)
						{
							//燃焼時間の設定
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nBurningTime);
						}
						//現在のテキストがBurningTimingだったら
						if (strcmp(aCurrentText, "BurningTiming") == 0)
						{
							//燃焼タイミングの設定
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nBurningTiming);
						}
						//現在のテキストがWalkSpeedだったら
						if (strcmp(aCurrentText, "WalkSpeed") == 0)
						{
							//歩行速度の設定の設定
							sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fWalkSpeed);
						}
						//現在のテキストがDashSpeedだったら
						if (strcmp(aCurrentText, "DashSpeed") == 0)
						{
							//ダッシュ速度の設定
							sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fDashSpeed);
						}
						//現在のテキストがCameraDistanceだったら
						if (strcmp(aCurrentText, "CameraDistance") == 0)
						{
							//カメラとの距離の設定
							sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fCameraDistance);
						}
					}
				}
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	//モデルのスクリプトパスを設定
	SetModelScriptPass(MODEL_PASS);
}