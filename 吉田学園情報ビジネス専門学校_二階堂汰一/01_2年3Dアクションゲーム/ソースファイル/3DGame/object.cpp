//=============================================================================
//
// オブジェクト [object.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "renderer.h"
#include "object.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INITIAL_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))				//位置の初期値
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))					//サイズの初期値
#define INITIAL_COLLISION_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))		//衝突判定用サイズの初期値
#define INITIAL_ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))				//回転の初期値
#define INITIAL_ALL_LIFE (0)										//全体の体力の初期値
#define INITIAL_LIFE (0)											//体力の初期値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CObject::CObject()
{
	m_Position = INITIAL_POSITION;				//位置
	m_Size = INITIAL_SIZE;						//サイズ
	m_CollisionSize = INITIAL_COLLISION_SIZE;	//衝突判定用サイズ
	m_Rotation = INITIAL_ROTATION;				//回転
	m_nLife = INITIAL_LIFE;						//体力
	m_pModel = NULL;							//モデルのポインタ
	m_ModelData = {};							//モデルデータ
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CObject::Init(void)
{
	//もしモデルのポインタがNULLの場合
	if (m_pModel == NULL)
	{
		//モデルの生成
		m_pModel = CModel::Create(m_ModelData);
	}
	//もしモデルのポインタがNULLじゃない場合
	if (m_pModel != NULL)
	{
		//モデルの初期化処理関数呼び出し
		m_pModel->Init();
		//モデルに位置を設定する
		m_pModel->SetPosition(m_Position);
		//モデルにサイズを設定する
		m_pModel->SetSize(m_Size);
		//モデルに回転を設定する
		m_pModel->SetRotation(m_Rotation);
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CObject::Uninit(void)
{
	//もしモデルのポインタがNULLじゃない場合
	if (m_pModel != NULL)
	{
		//モデルの終了処理関数呼び出し
		m_pModel->Uninit();
	}
	//破棄処理関数呼び出し
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CObject::Update(void)
{
	//もしモデルのポインタがNULLじゃない場合
	if (m_pModel != NULL)
	{
		//モデルの更新処理関数呼び出し
		m_pModel->Update();
	}
	//衝突判定の家
	Collision();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CObject::Draw(void)
{
	//もしモデルのポインタがNULLじゃない場合
	if (m_pModel != NULL)
	{
		//モデルの描画処理関数呼び出し
		m_pModel->Draw();
	}
}

//=============================================================================
// 体力減算処理関数
//=============================================================================
void CObject::SubLife(void)
{
}

//=============================================================================
// 衝突処理関数
//=============================================================================
void CObject::Collision(void)
{
	//プレイヤーを取得する
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしプレイヤーのポインタがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//プレイヤーの位置を取得する
		//D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(pPlayer->GetModel(0)->GetModelData().mtxWorld._41, pPlayer->GetModel(0)->GetModelData().mtxWorld._42 - 20.0f, pPlayer->GetModel(0)->GetModelData().mtxWorld._43);
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//プレイヤーの前の位置を取得する
		D3DXVECTOR3 PlayerPositionOld = pPlayer->GetPositionOld();
		//プレイヤーの移動量を設定する
		D3DXVECTOR3 PlayerMove = pPlayer->GetMove();
		//プレイヤーの衝突判定用サイズの取得
		D3DXVECTOR3 PlayerCollisionSize = pPlayer->GetCollisionSize();
		D3DXVECTOR3 PlayerCollisionMAX = D3DXVECTOR3(PlayerCollisionSize.x / 2, PlayerCollisionSize.y / 2, PlayerCollisionSize.z / 2) + PlayerPosition;
		D3DXVECTOR3 PlayerCollisionMIN = D3DXVECTOR3(-PlayerCollisionSize.x / 2, -PlayerCollisionSize.y / 2, -PlayerCollisionSize.z / 2) + PlayerPosition;
		D3DXVECTOR3 ObjectCollisionMAX = D3DXVECTOR3(m_CollisionSize.x / 2, m_CollisionSize.y / 2, m_CollisionSize.z / 2) + m_Position;
		D3DXVECTOR3 ObjectCollisionMIN = D3DXVECTOR3(-m_CollisionSize.x / 2, -m_CollisionSize.y / 2, -m_CollisionSize.z / 2) + m_Position;
		if (PlayerCollisionMAX.y > ObjectCollisionMIN.y &&
			PlayerCollisionMIN.y < ObjectCollisionMAX.y &&
			PlayerCollisionMAX.x > ObjectCollisionMIN.x &&
			PlayerCollisionMIN.x < ObjectCollisionMAX.x &&
			PlayerCollisionMAX.z > ObjectCollisionMIN.z &&
			PlayerCollisionMIN.z < ObjectCollisionMAX.z)
		{
			if (PlayerCollisionMAX.y > ObjectCollisionMIN.y && PlayerPositionOld.y <= ObjectCollisionMIN.y)
			{
				pPlayer->SetMove(D3DXVECTOR3(PlayerMove.x,0.0f, PlayerMove.z));
				pPlayer->SetPosition(D3DXVECTOR3(pPlayer->GetPosition().x,ObjectCollisionMIN.y - PlayerCollisionSize.y / 2,PlayerPosition.z));
			}
			else if (PlayerCollisionMIN.y < ObjectCollisionMAX.y && PlayerPositionOld.y >= ObjectCollisionMAX.y)
			{
				pPlayer->SetMove(D3DXVECTOR3(PlayerMove.x, 0.0f, PlayerMove.z));
				pPlayer->SetPosition(D3DXVECTOR3(pPlayer->GetPosition().x,ObjectCollisionMAX.y + PlayerCollisionSize.y / 2,PlayerPosition.z));
			}
			else if (PlayerCollisionMAX.x > ObjectCollisionMIN.x && PlayerPositionOld.x <= ObjectCollisionMIN.x)
			{
				pPlayer->SetMove(D3DXVECTOR3(0.0f, PlayerMove.y, PlayerMove.z));
				pPlayer->SetPosition(D3DXVECTOR3(ObjectCollisionMIN.x - PlayerCollisionSize.x / 2,PlayerPosition.y,PlayerPosition.z));
			}
			else if (PlayerCollisionMIN.x < ObjectCollisionMAX.x && PlayerPositionOld.x >= ObjectCollisionMAX.x)
			{
				pPlayer->SetMove(D3DXVECTOR3(0.0f, PlayerMove.y, PlayerMove.z));
				pPlayer->SetPosition(D3DXVECTOR3(ObjectCollisionMAX.x + PlayerCollisionSize.x / 2,PlayerPosition.y,PlayerPosition.z));
			}
			else if (PlayerCollisionMAX.z > ObjectCollisionMIN.z && PlayerPositionOld.z <= ObjectCollisionMIN.z)
			{
				pPlayer->SetMove(D3DXVECTOR3(PlayerMove.x, PlayerMove.y, 0.0f));
				pPlayer->SetPosition(D3DXVECTOR3(PlayerPosition.x,PlayerPosition.y,ObjectCollisionMIN.z - PlayerCollisionSize.z / 2));
			}
			else if (PlayerCollisionMIN.z < ObjectCollisionMAX.z && PlayerPositionOld.z >= ObjectCollisionMAX.z)
			{
				pPlayer->SetMove(D3DXVECTOR3(PlayerMove.x, PlayerMove.y, 0.0f));
				pPlayer->SetPosition(D3DXVECTOR3(PlayerPosition.x, PlayerPosition.y,ObjectCollisionMAX.z + PlayerCollisionSize.z / 2));
			}
		}
	}
}
