//=============================================================================
//
// ドラゴン [enemy_dragon.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/model.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "Mode/mode_game.h"
#include "enemy_dragon.h"
#include "Character/player.h"
#include "Polygon2d/game_clear_logo.h"
#include "AttackPattern/attack_pattern_meteor.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PASS ("Data/Script/Dragon/DragonModel.txt")		//モデルスクリプトのパス
#define SCRIPT_PASS ("Data/Script/Dragon/DragonData.txt")		//スケルトンのスクリプトのパス
#define MINIMUM_LIFE (0)										//体力の最小値
#define ATTACK_AREA (1200.0f)									//攻撃開始範囲
#define BITING_AREA (300.0f)									//噛みつき範囲

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODEL_DATA CDragon::m_aModelData[MAX_PARTS] = {};		//モデルデータのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CDragon::CDragon()
{
	m_bGameClearLogoCreate = false;		//ゲームクリアロゴを生成したか
	m_AttackPattern = ATTACK_NONE;		//攻撃パターン
}

//=============================================================================
// デストラクタ
//=============================================================================
CDragon::~CDragon()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CDragon::ModelLoad(void)
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
					&m_aModelData[nCount].pBuffMat,
					NULL,
					&m_aModelData[nCount].nNumMat,
					&m_aModelData[nCount].pMesh);
				//もしモデルのマテリアル情報がNULLじゃない場合
				if (m_aModelData[nCount].pBuffMat != nullptr)
				{
					//マテリアルのポインタを取得
					pMaterial = (D3DXMATERIAL *)m_aModelData[nCount].pBuffMat->GetBufferPointer();
					//モデルデータ数分回す
					for (int nCountMat = 0; nCountMat < (int)m_aModelData[nCount].nNumMat; nCountMat++)
					{
						//もしファイルネームがNULLじゃない場合
						if (pMaterial[nCountMat].pTextureFilename != NULL)
						{
							//テクスチャを読み込む
							D3DXCreateTextureFromFile(pDevice, pMaterial[nCountMat].pTextureFilename, &m_aModelData[nCount].pTexture[nCountMat]);
						}
					}
				}
				//ポインタを捨てる
				pPass += MAX_TEXT;
			}
		}
	}
	return S_OK;
}

//=============================================================================
// モデル破棄関数
//=============================================================================
void CDragon::ModelUnload(void)
{
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルデータのワールド変換行列がNULLではない場合
		if (m_aModelData[nCount].mtxWorld != NULL)
		{
			//もしモデルデータのマテリアル情報がNULLではない場合
			if (m_aModelData[nCount].pBuffMat != NULL)
			{
				//モデルデータのマテリアル情報を破棄
				m_aModelData[nCount].pBuffMat->Release();
			}
			//もしモデルデータのメッシュ情報がNULLではない場合
			if (m_aModelData[nCount].pMesh != NULL)
			{
				//モデルデータのメッシュ情報を破棄
				m_aModelData[nCount].pMesh->Release();
			}
			//マテリアルの最大数分回す
			for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
			{
				//もしモデルデータのテクスチャのポインタがNULLではない場合
				if (m_aModelData[nCount].pTexture[nCountTexture] != NULL)
				{
					//モデルデータのテクスチャのポインタを破棄
					m_aModelData[nCount].pTexture[nCountTexture]->Release();
				}
			}
		}
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CDragon * CDragon::Create()
{
	//ドラゴンのポインタ
	CDragon * pDragon = nullptr;
	//ドラゴンのポインタがnullptrの場合
	if (pDragon == nullptr)
	{
		//ドラゴンのメモリ確保
		pDragon = new CDragon;
		//ドラゴンのポインタがnullptrではない場合
		if (pDragon != nullptr)
		{
			//ドラゴンの初期化処理関数呼び出し
			pDragon->Init();
		}
	}
	//ドラゴンのポインタを返す
	return pDragon;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CDragon::Init(void)
{
	//スクリプトのパスを設定
	SetScriptPass(SCRIPT_PASS);
	//モデルのパスを設定
	SetModelScriptPass(MODEL_PASS);
	//モデルデータの設定
	SetModelData(m_aModelData);
	//敵の初期化処理関数呼び出し
	CEnemy::Init();
	CAttackPatternMeteor::Create();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CDragon::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CDragon::Update(void)
{
	//キーボードの取得
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	int nLife = GetLife();
	if (pKeyboard->GetKeyboardTrigger(DIK_H))
	{
		nLife -= 20;
		SetLife(nLife);
	}
	//敵の更新処理関数呼び出し
	CEnemy::Update();
	//AI処理関数呼び出し
	AI();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CDragon::Draw(void)
{
	//敵の描画処理関数呼び出し
	CEnemy::Draw();
}

//=============================================================================
// AI処理関数
//=============================================================================
void CDragon::AI(void)
{
	//位置の取得
	D3DXVECTOR3 Position = GetPosition();
	//回転の取得
	D3DXVECTOR3 Rotation = GetRotation();
	//体力の取得
	int nLife = GetLife();
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしプレイヤーのポインタがnullptrではない場合
	if (pPlayer != nullptr)
	{
		//プレイヤーの位置を取得する
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//プレイヤーの衝突判定用のサイズを取得する
		D3DXVECTOR3 PlayerCollisionSize = pPlayer->GetCollisionSize();
		//プレイヤーまでの距離を求める
		D3DXVECTOR3 PlayerDistance = D3DXVECTOR3(PlayerPosition.x - Position.x, PlayerPosition.y - Position.y, PlayerPosition.z - Position.z);
		//ベクトルの長さを求める
		float Vector_length = sqrtf((PlayerDistance.x * PlayerDistance.x) * (PlayerDistance.y * PlayerDistance.y));
		//敵とプレイヤーの距離がそれぞれの半径の和より小さかったら衝突
		if (powf(PlayerDistance.x, 2) + powf(PlayerDistance.z, 2)
			<= pow(((ATTACK_AREA / 2) + (PlayerCollisionSize.x / 2)), 2))
		{
			//もし視界の中にプレイヤーがいる場合
			if (Visibility() == true)
			{
				//敵とプレイヤーの距離がそれぞれの半径の和より小さかったら衝突
				if (powf(PlayerDistance.x, 2) + powf(PlayerDistance.z, 2)
					<= pow(((BITING_AREA / 2) + (PlayerCollisionSize.x / 2)), 2))
				{
					//攻撃パターンを噛みつきにする
					m_AttackPattern = ATTACK_BITING;
				}
			}
		}
	}
	//各攻撃パターンによる処理
	switch (m_AttackPattern)
	{
	case ATTACK_BITING:
		break;
	}
	//もし体力が3割り以下になった場合
	if (nLife <= nLife * 0.3)
	{
	}
	//もし体力が0になった場合
	if (nLife <= MINIMUM_LIFE)
	{
		//死亡処理関数呼び出し
		Death();
	}
}

//=============================================================================
// 噛みつき処理関数
//=============================================================================
bool CDragon::Biting(void)
{
	//位置の取得
	D3DXVECTOR3 Position = GetPosition();
	//回転の取得
	D3DXVECTOR3 Rotation = GetRotation();
	//体力の取得
	int nLife = GetLife();
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしプレイヤーのポインタがnullptrではない場合
	if (pPlayer != nullptr)
	{
		//プレイヤーの位置を取得する
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//プレイヤーの衝突判定用のサイズを取得する
		D3DXVECTOR3 PlayerCollisionSize = pPlayer->GetCollisionSize();
		//プレイヤーとドラゴンのベクトルを求める
		D3DXVECTOR3 PlayerDistance = D3DXVECTOR3(PlayerPosition.x - Position.x, PlayerPosition.y - Position.y, PlayerPosition.z - Position.z);
		////プレイヤーとドラゴンのベクトルの長さを求める
		float Vector_length = sqrtf((PlayerDistance.x * PlayerDistance.x) + (PlayerDistance.z * PlayerDistance.z));
		//ベクトルと扇の長さの比較
		if (ATTACK_AREA < Vector_length)
		{
			return false;
		}
		D3DXVECTOR3 fan_dir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		D3DXVECTOR3 rotate_fan_dir = D3DXVECTOR3(
			fan_dir.x * cosf(D3DXToRadian(Rotation.y - 90.0f)) + fan_dir.z * -sinf(D3DXToRadian(Rotation.y - 90.0f)),
			0.0f,
			fan_dir.x * 1.0f * sinf(D3DXToRadian(Rotation.y - 90.0f)) + fan_dir.z * cosf(D3DXToRadian(Rotation.y - 90.0f)));
		// 扇と点のベクトルを単位ベクトルにする
		D3DXVECTOR3 normal_fan_to_point = D3DXVECTOR3(
			PlayerDistance.x / Vector_length,
			0.0f,
			PlayerDistance.z / Vector_length);
		// 内積計算
		float dot = normal_fan_to_point.x* rotate_fan_dir.x + normal_fan_to_point.z * rotate_fan_dir.z;
		// 扇の範囲をcosにする
		float fan_cos = cosf(D3DXToRadian(120.0f / 2.0f));
		// 点が扇の範囲内にあるかを比較する
		if (fan_cos > dot)
		{
			// 当たってない
			return false;
		}
	}
	return true;
}

//=============================================================================
// 視界処理関数
//=============================================================================
bool CDragon::Visibility(void)
{
	//位置の取得
	D3DXVECTOR3 Position = GetPosition();
	//回転の取得
	D3DXVECTOR3 Rotation = GetRotation();
	//体力の取得
	int nLife = GetLife();
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしプレイヤーのポインタがnullptrではない場合
	if (pPlayer != nullptr)
	{
		//プレイヤーの位置を取得する
		D3DXVECTOR3 PlayerPosition = pPlayer->GetPosition();
		//プレイヤーの衝突判定用のサイズを取得する
		D3DXVECTOR3 PlayerCollisionSize = pPlayer->GetCollisionSize();
		//プレイヤーとドラゴンのベクトルを求める
		D3DXVECTOR3 PlayerDistance = D3DXVECTOR3(PlayerPosition.x - Position.x, PlayerPosition.y - Position.y, PlayerPosition.z - Position.z);
		////プレイヤーとドラゴンのベクトルの長さを求める
		float Vector_length = sqrtf((PlayerDistance.x * PlayerDistance.x) + (PlayerDistance.z * PlayerDistance.z));
		//ベクトルと扇の長さの比較
		if (ATTACK_AREA < Vector_length)
		{
			return false;
		}
		D3DXVECTOR3 fan_dir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		D3DXVECTOR3 rotate_fan_dir = D3DXVECTOR3(
			fan_dir.x * cosf(D3DXToRadian(Rotation.y - 90.0f)) + fan_dir.z * -sinf(D3DXToRadian(Rotation.y - 90.0f)),
			0.0f,
			fan_dir.x * 1.0f * sinf(D3DXToRadian(Rotation.y - 90.0f)) + fan_dir.z * cosf(D3DXToRadian(Rotation.y - 90.0f)));
		//扇と点のベクトルを単位ベクトルにする
		D3DXVECTOR3 normal_fan_to_point = D3DXVECTOR3(
			PlayerDistance.x / Vector_length,
			0.0f,
			PlayerDistance.z / Vector_length);
		//内積計算
		float dot = normal_fan_to_point.x* rotate_fan_dir.x + normal_fan_to_point.z * rotate_fan_dir.z;
		//扇の範囲をcosにする
		float fan_cos = cosf(D3DXToRadian(120.0f / 2.0f));
		//点が扇の範囲内にあるかを比較する
		if (fan_cos > dot)
		{
			// 当たってない
			return false;
		}
	}
	return true;
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CDragon::Death(void)
{
	//もしゲームクリアロゴが生成していない場合
	if (m_bGameClearLogoCreate == false)
	{
		//ゲームクリアロゴの生成
		CGameClearLogo::Create();
		//ゲームクリアロゴを生成した状態にする
		m_bGameClearLogoCreate = true;
	}

}
