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
#include "mode_game.h"
#include "renderer.h"
#include "sound.h"
#include "keyboard.h"
#include "joystick.h"
#include "player.h"
#include "camera.h"
#include "weapon_sword.h"
#include "weapon_shield.h"
#include "enemy_dragon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PASS ("Data/Script/Player/Model.txt")															//モデルスクリプトのパス
#define SCRIPT_PASS ("Data/Script/Player/Data.txt")															//プレイヤーデータのスクリプトのパス
#define INITIAL_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))														//初期位置
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))															//初期サイズ
#define INITIAL_COLLISIION_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))												//初期当たり判定用サイズ
#define INITIAL_ROTATION (D3DXVECTOR3(D3DXToRadian(0.0f),D3DXToRadian(0.0f),D3DXToRadian(0.0f)))			//初期回転
#define INITIAL_DIRECTION_DEST (D3DXVECTOR3(D3DXToRadian(0.0f),D3DXToRadian(0.0f),D3DXToRadian(0.0f)))		//目標の向きの初期値
#define INITIAL_MOVE (D3DXVECTOR3(0.0f,0.0f,0.0f))															//初期移動量
#define INITIAL_LIFE (0)																					//初期体力
#define MINIMUM_LIFE (0)																					//体力の最小値
#define INITIAL_ATTACK (0)																					//初期攻撃力
#define INITIAL_COOL_TIME (0)																				//クールタイム
#define INITIAL_SPEED (0.0f)																				//初期速さ
#define INITIAL_WALK_SPEED (0.0f)																			//初期歩行速度
#define INITIAL_DASH_SPEED (0.0f)																			//初期ダッシュ速度
#define INITIAL_ADD_DIRECTION_VALUE (D3DXToRadian(0.75f))													//向きの加算値の初期値
#define INITIAL_CAMERA_DISTANCE (0.0f)																		//カメラとの距離

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODEL_DATA CPlayer::m_ModelData[MAX_PARTS] = {};	//モデルデータ
D3DXMATERIAL * CPlayer::m_pMaterial = NULL;					//マテリアル

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer()
{
	m_Position = INITIAL_POSITION;									//位置
	m_PositionOld = INITIAL_POSITION;								//前の位置
	m_Size = INITIAL_SIZE;											//サイズ
	m_CollisionSize = INITIAL_COLLISIION_SIZE;						//当たり判定用サイズ
	m_Rotation = INITIAL_ROTATION;									//回転
	m_DirectionDest = INITIAL_DIRECTION_DEST;						//目的の向き
	m_Move = INITIAL_MOVE;											//移動量
	m_nLife = INITIAL_LIFE;											//体力
	memset(m_nAttack, INITIAL_ATTACK, sizeof(m_nAttack));			//攻撃力
	memset(m_nCoolTime, INITIAL_COOL_TIME, sizeof(m_nCoolTime));	//クールタイム
	m_nCoolTimeCount = INITIAL_COOL_TIME;							//クールタイムカウント
	m_fSpeed = INITIAL_SPEED;										//速さ
	m_fWalkSpeed = INITIAL_WALK_SPEED;								//歩行速度
	m_fDashSpeed = INITIAL_DASH_SPEED;								//ダッシュ速度
	m_fDirectionValue = INITIAL_ADD_DIRECTION_VALUE;				//向きの値
	m_fCameraDistance = INITIAL_CAMERA_DISTANCE;					//カメラとの距離
	m_bDash = false;												//ダッシュしてるか
	m_State = STATE_NONE;											//状態
	m_Input = INPUT_NONE;											//入力情報
	m_Attack = ATTACK_NONE;											//攻撃情報
	m_Direction = DIRECTION_FRONT;									//向き
	memset(m_pModel, NULL, sizeof(m_pModel));						//モデルのポインタ
	m_pMotion = NULL;												//モーションのポインタ
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
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//パスのポインタ
	char * pPass = NULL;
	//もしパスのポインタがNULLの場合
	if (pPass == NULL)
	{
		//パスを取得
		pPass = CModel::LoadModelText(MODEL_PASS);
	}
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしパスのポインタがNULLじゃない場合
		if (pPass != NULL)
		{
			//モデル読み込み
			D3DXLoadMeshFromX(pPass,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_ModelData[nCount].pBuffMat,
				NULL,
				&m_ModelData[nCount].nNumMat,
				&m_ModelData[nCount].pMesh);
			//もしモデルのマテリアル情報がNULLじゃない場合
 			if (m_ModelData[nCount].pBuffMat != NULL)
			{
				//マテリアルのポインタを取得
				m_pMaterial = (D3DXMATERIAL *)m_ModelData[nCount].pBuffMat->GetBufferPointer();
				//モデルデータ数分回す
				for (int nCountMat = 0; nCountMat < (int)m_ModelData[nCount].nNumMat; nCountMat++)
				{
					//もしファイルネームがNULLじゃない場合
					if (m_pMaterial[nCountMat].pTextureFilename != NULL)
					{
						//テクスチャを読み込む
						D3DXCreateTextureFromFile(pDevice, m_pMaterial[nCountMat].pTextureFilename, &m_ModelData[nCount].pTexture[nCountMat]);
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
		//もしモデルデータのワールド変換行列がNULLじゃな場合
		if (m_ModelData[nCount].mtxWorld != NULL)
		{
			//もしモデルデータのマテリアル情報がNULLじゃな場合
			if (m_ModelData[nCount].pBuffMat != NULL)
			{
				//モデルデータのマテリアル情報を破棄
				m_ModelData[nCount].pBuffMat->Release();
			}
			//もしモデルデータのメッシュ情報がNULLじゃな場合
			if (m_ModelData[nCount].pMesh != NULL)
			{
				//モデルデータのメッシュ情報を破棄
				m_ModelData[nCount].pMesh->Release();
			}
			//マテリアルの最大数分回す
			for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
			{
				//もしモデルデータのテクスチャのポインタがNULLじゃな場合
				if (m_ModelData[nCount].pTexture[nCountTexture] != NULL)
				{
					//モデルデータのテクスチャのポインタを破棄
					m_ModelData[nCount].pTexture[nCountTexture]->Release();
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
// 初期化処理関数
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//データ読み込み関数呼び出し
	DataLoad();
	//モーション処理関数呼び出し
	Motion();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPlayer::Uninit(void)
{
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルのポインタがNULLじゃない場合
		if (m_pModel[nCount] != NULL)
		{
			//モデルの終了処理関数呼び出し
			m_pModel[nCount]->Uninit();
		}
	}
	//破棄処理関数呼び出し
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPlayer::Update(void)
{
	//過去の位置を保存する
	m_PositionOld = m_Position;
	//もしモーションのポインタがNULLの場合
	if (m_pMotion != NULL)
	{
		//更新処理関数呼び出し
		m_pMotion->Update();
	}
	//もし移動量が初期値の場合
	if (m_Move == INITIAL_MOVE)
	{
		//モーションを設定する
		m_pMotion->SetMotion(CMotion::MOTION_PLAYER_IDLE);
	}
	//入力処理関数呼び出し
	Input();
	//向き変更処理関数
	Direction();
	//位置更新
	m_Position += m_Move;
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルのポインタがNULLじゃない場合	
		if (m_pModel[nCount] != NULL)
		{
			//モデルの更新処理関数呼び出し
			m_pModel[nCount]->Update();
			// モデルのパーツごとの座標と回転を受け取る
			m_pModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), m_Size);
		}
	}
	// 座標、回転、サイズのセット
	m_pModel[0]->SetModel(m_pMotion->GetPosition(0) + m_Position, m_pMotion->GetRotation(0) + m_Rotation, m_Size);
	//もし体力が最小値以下になったら
	if (m_nLife <= MINIMUM_LIFE)
	{
		//死亡処理関数呼び出し
		Death();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPlayer::Draw(void)
{
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルのポインタがNULLじゃない場合
		if (m_pModel[nCount] != NULL)
		{
			//モデルの描画処理関数呼び出し
			m_pModel[nCount]->Draw();
		}
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
	//もしダッシュキーが押されていたら
	if (pKeyboard->GetKeyboardPress(DIK_LSHIFT) || pJoystick->GetJoystickPress(JS_RB))
	{
		//ダッシュする
		m_bDash = true;
	}
	else
	{
		//ダッシュを止める
		m_bDash = false;
	}
	//上移動処理
	if (pKeyboard->GetKeyboardPress(DIK_W) || lpDIDevice != NULL &&js.lY == -1000)
	{
		//入力キー情報を上にする
		m_Input = INPUT_UP;
		//向きを前方にする
		m_Direction = DIRECTION_FRONT;
		//移動処理関数呼び出し
		Move();
	}
	//下移動処理
	if (pKeyboard->GetKeyboardPress(DIK_S) || lpDIDevice != NULL &&js.lY == 1000)
	{
		//入力キー情報を下にする
		m_Input = INPUT_DOWN;
		//向きを後方にする
		m_Direction = DIRECTION_BACK;
		//移動処理関数呼び出し
		Move();
	}
	//左移動処理
	if (pKeyboard->GetKeyboardPress(DIK_A) || lpDIDevice != NULL &&js.lX == -1000)
	{
		//入力キー情報を左にする
		m_Input = INPUT_LEFT;
		//向きを左にする
		m_Direction = DIRECTION_LEFT;
		//移動処理関数呼び出し
		Move();
	}
	//右移動処理
	if (pKeyboard->GetKeyboardPress(DIK_D) || lpDIDevice != NULL &&js.lX == 1000)
	{
		//入力キー情報を右にする
		m_Input = INPUT_RIGHT;
		//向きを右にする
		m_Direction = DIRECTION_RIGHT;
		//移動処理関数呼び出し
		Move();
	}
}

//=============================================================================
// 移動処理関数
//=============================================================================
void CPlayer::Move(void)
{
	//もしダッシュしていたら
	if (m_bDash == true)
	{
		//速度をダッシュ速度にする
		m_fSpeed = m_fDashSpeed;
		//モーションを設定する
		m_pMotion->SetMotion(CMotion::MOTION_PLAYER_DASH);
	}
	else
	{
		//速度を歩行速度にする
		m_fSpeed = m_fWalkSpeed;
		//モーションを設定する
		m_pMotion->SetMotion(CMotion::MOTION_PLAYER_WALK);
	}
	//カメラの取得
	CCamera * pCamera = CGameMode::GetCamera();
	//もしカメラのポインタがNULLじゃない場合
	if (pCamera != NULL)
	{
		//カメラの回転を取得
		D3DXVECTOR3 CameraRotation = pCamera->GetRotation();
		//もし死亡状態じゃないとき
		if (m_State != STATE_DEATH)
		{
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
		}
	}
}

//=============================================================================
// 向き変更処理関数
//=============================================================================
void CPlayer::Direction(void)
{
	//各向きの処理
	switch (m_Direction)
	{
	case DIRECTION_FRONT:
		m_DirectionDest = D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f));
		break;
	case DIRECTION_BACK:
		m_DirectionDest = D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(180.0f), D3DXToRadian(0.0f));
		break;
	case DIRECTION_LEFT:
		m_DirectionDest = D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(-90.0f), D3DXToRadian(0.0f));
		break;
	case DIRECTION_RIGHT:
		m_DirectionDest = D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(90.0f), D3DXToRadian(0.0f));
		break;
	}
	//プレイヤーの向きを更新する
	m_Rotation += (m_DirectionDest - m_Rotation) * 0.1f;
}

//=============================================================================
// 攻撃処理関数
//=============================================================================
void CPlayer::Attack(void)
{
	switch (m_Attack)
	{
	case ATTACK_1:
		break;
	case ATTACK_2:
		break;
	case ATTACK_3:
		break;
	default:
		break;
	}
}

//=============================================================================
// ヒット処理関数
//=============================================================================
void CPlayer::Hit(void)
{
	//体力減算処理関数呼び出し
	SubLife();
}

//=============================================================================
// 体力減算処理関数
//=============================================================================
void CPlayer::SubLife(void)
{
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CPlayer::Death(void)
{
}

//=============================================================================
// 衝突判定処理関数
//=============================================================================
void CPlayer::Collision(void)
{
	//ドラゴンの取得
	CDragon * pDragon = CGameMode::GetDragon();
	//もしドラゴンのポインタがNULLじゃない場合
	if (pDragon != NULL)
	{
		//ドラゴンの位置を取得
		D3DXVECTOR3 DragonPosition = pDragon->GetPosition();
		//ドラゴンの衝突判定用サイズの取得
		D3DXVECTOR3 DragonCollisionSize = pDragon->GetCollisionSize();
	}
}

//=============================================================================
// モーション処理関数
//=============================================================================
void CPlayer::Motion(void)
{
	//もしモーションのポインタがNULLの場合
	if (m_pMotion == NULL)
	{
		//モーションの生成
		m_pMotion = CMotion::Create();
	}
	//もしモーションのポインタがNULLじゃない場合
	if (m_pMotion != NULL)
	{
		//モーションの読み込み
		m_pMotion->LoadMotion(MODEL_PASS);
		//モーション情報の読み込み
		m_pMotion->LoadModelInformation(MODEL_PASS);
		//最大パーツ数分回す
		for (int nCount = 0; nCount < MAX_PARTS; nCount++)
		{
			//もしモデルデータのメッシュがNULLじゃない場合
			if (m_ModelData[nCount].pMesh != NULL)
			{
				//親モデルの番号受け取り
				m_ModelData[nCount].nIndexModelParent = m_pMotion->GetParents(nCount);
				//モデルの生成
				m_pModel[nCount] = CModel::Create(m_ModelData[nCount]);
				//モーションの位置を取得
				m_pMotion->GetPosition(nCount);
				//モーションの回転を取得
				m_pMotion->GetRotation(nCount);
				//モデルの割り当て
				m_pModel[nCount]->BindModel(m_ModelData[nCount]);
				// モデルのパーツごとの座標と回転を受け取る
				m_pModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), m_Size);
			}
		}
		//パーツの最大数分回す
		for (int nCount = 0; nCount < MAX_PARTS; nCount++)
		{
			//もし親のモデルが存在したら
			if (m_pModel[m_ModelData[nCount].nIndexModelParent] != NULL && m_ModelData[nCount].nIndexModelParent != -1)
			{
				//もしモデルデータのメッシュがNULLじゃない場合
				if (m_ModelData[nCount].pMesh != NULL)
				{
					//親のモデルポインタを受け取る
					m_ModelData[nCount].pParent = m_pModel[m_ModelData[nCount].nIndexModelParent];
					// モデルの割り当て
					m_pModel[nCount]->BindModel(m_ModelData[nCount]);
				}
			}
		}
		// 座標、回転、サイズのセット
		m_pModel[0]->SetModel(m_pMotion->GetPosition(0) + m_Position, m_pMotion->GetRotation(0) + m_Rotation, m_Size);
	}
}

//=============================================================================
// データ読み込み関数
//=============================================================================
void CPlayer::DataLoad(void)
{
	char aReadText[MAX_TEXT];			//読み込んだテキスト
	char aCurrentText[MAX_TEXT];		//現在のテキスト
	char aUnnecessaryText[MAX_TEXT];	//不必要なテキスト
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
	}
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
							//位置の設定
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Position.x, &m_Position.y, &m_Position.z);
						}
						//現在のテキストがSIZEだったら
						if (strcmp(aCurrentText, "SIZE") == 0)
						{
							//サイズの設定
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Size.x, &m_Size.y, &m_Size.z);
						}
						//現在のテキストがCOLLISION_SIZEだったら
						if (strcmp(aCurrentText, "COLLISION_SIZE") == 0)
						{
							//サイズの設定
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_CollisionSize.x, &m_CollisionSize.y, &m_CollisionSize.z);
						}
						//現在のテキストがROTだったら
						if (strcmp(aCurrentText, "ROT") == 0)
						{
							//回転情報の読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
						}
						//現在のテキストがMOVEだったら
						if (strcmp(aCurrentText, "MOVE") == 0)
						{
							//サイズの設定
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Move.x, &m_Move.y, &m_Move.z);
						}
						//現在のテキストがLIFEだったら
						if (strcmp(aCurrentText, "LIFE") == 0)
						{
							//体力の設定
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nLife);
						}
						//現在のテキストがSpeedだったら
						if (strcmp(aCurrentText, "Speed") == 0)
						{
							//速度の設定の設定
							sscanf(aReadText, "%s %s %f", &aUnnecessaryText, &aUnnecessaryText, &m_fSpeed);
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
}