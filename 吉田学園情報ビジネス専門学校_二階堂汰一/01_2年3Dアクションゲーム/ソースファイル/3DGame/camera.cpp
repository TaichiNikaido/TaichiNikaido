//=============================================================================
//
// カメラ [camera.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "renderer.h"
#include "keyboard.h"
#include "joystick.h"
#include "camera.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCRIPT_PASS ("Data/Script/Camera/Data.txt")			//プレイヤーデータのスクリプトのパス
#define INITIAL_POSITION_V (D3DXVECTOR3(0.0f, 0.0f, 0.0f))	//視点の初期値
#define INITIAL_POSITION_R (D3DXVECTOR3(0.0f,0.0f,0.0f))	//注視点の初期値
#define INITIAL_VECTOR_U (D3DXVECTOR3(0.0f,0.0f,0.0f))		//上方向ベクトル
#define INITIAL_ROTAION (D3DXVECTOR3(0.0f,0.0f,0.0f))		//回転の初期値
#define INITIAL_DISTANCE (0.0f)								//距離の初期値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
	m_PositionV = INITIAL_POSITION_V;	//視点の位置
	m_PositionR = INITIAL_POSITION_R;	//注視点の位置
	m_VectorU = INITIAL_VECTOR_U;		//上方向ベクトル
	m_Rotation = INITIAL_ROTAION;		//回転
	m_fDistance = INITIAL_DISTANCE;		//視点と注視点の距離
}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CCamera::Init(void)
{
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしプレイヤーのポインタがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//プレイヤーの位置を取得
		D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(pPlayer->GetModel(3)->GetModelData().mtxWorld._41, pPlayer->GetModel(3)->GetModelData().mtxWorld._42, pPlayer->GetModel(3)->GetModelData().mtxWorld._43);
		//プレイヤーまでの距離を取得
		float PlayerDistance = pPlayer->GetCameraDistance();
		//視点を設定する
		m_PositionV = D3DXVECTOR3(PlayerPosition.x, PlayerPosition.y, PlayerPosition.z + PlayerDistance);
		//注視点の設定
		m_PositionR = D3DXVECTOR3(PlayerPosition.x, PlayerPosition.y, PlayerPosition.z);
	}
	//上方向ベクトルの初期設定
	m_VectorU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//回転方向の初期設定
	m_Rotation = D3DXVECTOR3(0.0f, D3DXToRadian(80.0f), D3DXToRadian(80.0f));
	//視点と注視点の距離を設定
	m_fDistance = sqrtf(powf(m_PositionV.z - m_PositionR.z, 2) + powf(m_PositionV.y - m_PositionR.y, 2));
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CCamera::Update(void)
{
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしプレイヤーのポインタがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//プレイヤーの位置を取得
		D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(pPlayer->GetModel(3)->GetModelData().mtxWorld._41, pPlayer->GetModel(3)->GetModelData().mtxWorld._42, pPlayer->GetModel(3)->GetModelData().mtxWorld._43);
		//各カメラ座標の設定
		m_PositionV.x = PlayerPosition.x + m_fDistance * sinf(m_Rotation.z) * cosf(m_Rotation.y);
		m_PositionV.y = PlayerPosition.y + m_fDistance * cosf(m_Rotation.z);
		m_PositionV.z = PlayerPosition.z + m_fDistance * sinf(m_Rotation.z) * sinf(m_Rotation.y);
		//注視点の設定
		m_PositionR = D3DXVECTOR3(PlayerPosition.x, PlayerPosition.y, PlayerPosition.z);
	}
	//入力処理関数呼び出し
	Input();
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CCamera::Input(void)
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
	//上
	if (lpDIDevice != NULL &&js.lRz == -1000)
	{
		if (m_Rotation.z > D3DXToRadian(5.0f))
		{
			//回転のZを減算する
			m_Rotation.z -= D3DXToRadian(1.75f);
		}
	}
	//下
	if (lpDIDevice != NULL &&js.lRz == 1000)
	{
		if (m_Rotation.z < D3DXToRadian(175.0f))
		{
			m_Rotation.z += D3DXToRadian(1.75f);
		}
	}
	//左
	if (lpDIDevice != NULL &&js.lZ == -1000)
	{
		m_Rotation.y += D3DXToRadian(1.75f);
	}
	//右
	if (lpDIDevice != NULL &&js.lZ == 1000)
	{
		m_Rotation.y -= D3DXToRadian(1.75f);
	}
	if (pJoystick->GetJoystickPress(JS_Y))
	{
		DataLoad();
	}
}

//=============================================================================
// カメラ設定関数
//=============================================================================
void CCamera::SetCamera(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_MtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_MtxView, &m_PositionV, &m_PositionR, &m_VectorU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_MtxView);
	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_MtxProjection);
	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_MtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 10000.0f);
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_MtxProjection);
}

//=============================================================================
// データ読み込み関数
//=============================================================================
void CCamera::DataLoad()
{
}
