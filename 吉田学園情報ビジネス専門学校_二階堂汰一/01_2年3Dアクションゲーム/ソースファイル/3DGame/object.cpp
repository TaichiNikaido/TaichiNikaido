//=============================================================================
//
// オブジェクト [object.cpp]
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
	m_pScriptPass = NULL;						//スクリプトのパス
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
	//スクリプト読み込み関数呼び出し
	ScriptLoad();
	//もしモデルのポインタがNULLの場合
	if (m_pModel == NULL)
	{
		//モデルの生成
		m_pModel = CModel::Create(m_ModelData);
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
	//衝突処理関数呼び出し
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

//=============================================================================
// スクリプト読み込み関数
//=============================================================================
void CObject::ScriptLoad(void)
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
		pFile = fopen(m_pScriptPass, "r");
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
						//現在のテキストがSIZEだったら
						if (strcmp(aCurrentText, "SIZE") == 0)
						{
							//サイズ情報の読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_Size.x, &m_Size.y, &m_Size.z);
						}
						//現在のテキストがCOLLISION_SIZEだったら
						if (strcmp(aCurrentText, "COLLISION_SIZE") == 0)
						{
							//衝突判定用サイズ情報の読み込み
							sscanf(aReadText, "%s %s %f %f %f", &aUnnecessaryText, &aUnnecessaryText, &m_CollisionSize.x, &m_CollisionSize.y, &m_CollisionSize.z);
						}
						//現在のテキストがLIFEだったら
						if (strcmp(aCurrentText, "LIFE") == 0)
						{
							//体力情報の読み込み
							sscanf(aReadText, "%s %s %d", &aUnnecessaryText, &aUnnecessaryText, &m_nLife);
						}
					}
				}
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}