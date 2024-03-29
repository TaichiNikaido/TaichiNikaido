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
#include "renderer.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "Mode/mode_game.h"
#include "camera.h"
#include "Character/player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INITIAL_DISTANCE (0.0f)																	//距離の初期値
#define VECTOR (D3DXVECTOR3(0.0f, 1.0f, 0.0f))													//上方向ベクトル
#define ROTATION (D3DXVECTOR3(D3DXToRadian(0.0f), D3DXToRadian(90.0f), D3DXToRadian(80.0f)))	//回転

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
	m_PositionV = INITIAL_D3DXVECTOR3;	//視点の位置
	m_PositionR = INITIAL_D3DXVECTOR3;	//注視点の位置
	m_VectorU = INITIAL_D3DXVECTOR3;	//上方向ベクトル
	m_Rotation = INITIAL_ROTATION;		//回転
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
	//上方向ベクトルの初期設定
	m_VectorU = VECTOR;
	//回転方向の初期設定
	m_Rotation = ROTATION;
	//ウィンドウがアクティブの場合
	if (CManager::GetIsActiveWindow() == true)
	{
		//マウスカーソルの位置を画面の中心に設定する
		SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
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
	//プレイヤーを取得する
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしプレイヤーのポインタがnullptrではない場合
	if (pPlayer != nullptr)
	{
		//プレイヤーの位置を取得
		D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(pPlayer->GetModel(3)->GetModelData().mtxWorld._41, pPlayer->GetModel(3)->GetModelData().mtxWorld._42, pPlayer->GetModel(3)->GetModelData().mtxWorld._43);
		//プレイヤーまでの距離を取得
		float PlayerDistance = pPlayer->GetCameraDistance();
		//視点を設定する
		m_PositionV = D3DXVECTOR3(PlayerPosition.x, PlayerPosition.y, PlayerPosition.z + PlayerDistance);
		//注視点の設定
		m_PositionR = D3DXVECTOR3(PlayerPosition.x, PlayerPosition.y, PlayerPosition.z);
		//視点と注視点の距離を設定
		m_fDistance = sqrtf(powf(m_PositionV.z - m_PositionR.z, 2) + powf(m_PositionV.y - m_PositionR.y, 2));
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
	//プレイヤーを取得する
	CPlayer * pPlayer = CGameMode::GetPlayer();
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
	//マウスカーソルの位置格納用変数
	POINT Point;
	//マウスカーソルの位置を取得する
	GetCursorPos(&Point);
	//もしプレイヤーの状態が死亡状態ではない場合
	if (pPlayer->GetState() != CPlayer::STATE_DEATH)
	{
		//ウィンドウがアクティブの場合
		if (CManager::GetIsActiveWindow() == true)
		{
			//マウスカーソルの位置を画面の中心に設定する
			SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			//マウスでのカメラ操作
			m_Rotation.z += (Point.y - (SCREEN_HEIGHT / 2)) * (0.01f * 1.0f);
			m_Rotation.y -= (Point.x - (SCREEN_WIDTH / 2)) * (0.01f * 1.0f);
		}
		//スティックが上入力されたら
		if (lpDIDevice != NULL &&js.lRz == -1000)
		{
			if (m_Rotation.z > D3DXToRadian(5.0f))
			{
				m_Rotation.z -= D3DXToRadian(1.75f);
			}
		}
		//スティックが下入力されたら
		if (lpDIDevice != NULL &&js.lRz == 1000)
		{
			if (m_Rotation.z < D3DXToRadian(115.0f))
			{
				m_Rotation.z += D3DXToRadian(1.75f);
			}
		}
		//スティックが左入力されたら
		if (lpDIDevice != NULL &&js.lZ == -1000)
		{
			m_Rotation.y += D3DXToRadian(1.75f);
		}
		//スティックが右入力されたら
		if (lpDIDevice != NULL &&js.lZ == 1000)
		{
			m_Rotation.y -= D3DXToRadian(1.75f);
		}
		if (m_Rotation.z < D3DXToRadian(5.0f))
		{
			m_Rotation.z = D3DXToRadian(5.0f);
		}
		if (m_Rotation.z > D3DXToRadian(115.0f))
		{
			m_Rotation.z = D3DXToRadian(115.0f);
		}
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