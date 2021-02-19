//=============================================================================
//
// 敵 [enemy.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INITIAL_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))			//位置の初期値
#define INITIAL_MOVE (D3DXVECTOR3(0.0f,0.0f,0.0f))				//移動量の初期値
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))				//サイズの初期値
#define INITIAL_COLLISION_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//衝突判定用サイズの初期値
#define INITIAL_ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))			//回転の初期値
#define MINIMUM_LIFE (0)										//体力の最小値
#define MINIMUM_ATTACK (0)										//攻撃力の最小値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy()
{
	m_Position = INITIAL_POSITION;						//位置
	m_Move = INITIAL_MOVE;								//移動量
	m_Size = INITIAL_SIZE;								//サイズ
	m_CollisionSize = INITIAL_COLLISION_SIZE;			//衝突判定用サイズ
	m_Rotation = INITIAL_ROTATION;						//回転
	m_nLife = MINIMUM_LIFE;								//体力
	m_nAttack = MINIMUM_ATTACK;							//攻撃力
	memset(m_apMotionPass,NULL,sizeof(m_apMotionPass));	//モーションデータのパス
	memset(m_apModel, 0, sizeof(m_apModel));				//モデルのポインタ
	memset(m_aModelData,NULL,sizeof(m_aModelData));		//モデルデータのポインタ
	m_pMotion = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEnemy::Init(void)
{
	//モーション処理関数呼び出し
	Motion();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CEnemy::Uninit(void)
{
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルのポインタがNULLじゃない場合
		if (m_apModel[nCount] != NULL)
		{
			//モデルの終了処理関数呼び出し
			m_apModel[nCount]->Uninit();
		}
	}
	//破棄処理関数呼び出し
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CEnemy::Update(void)
{
	//位置更新
	m_Position += m_Move;
	//もしモーションのポインタがNULLの場合
	if (m_pMotion != NULL)
	{
		//更新処理関数呼び出し
		m_pMotion->Update();
	}
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルのポインタがNULLじゃない場合
		if (m_apModel[nCount] != NULL)
		{
			//モデルの描画処理関数呼び出し
			m_apModel[nCount]->Update();
			// モデルのパーツごとの座標と回転を受け取る
			m_apModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), m_Size);
		}
	}
	// 座標、回転、サイズのセット
	m_apModel[0]->SetModel(m_pMotion->GetPosition(0) + m_Position, m_pMotion->GetRotation(0) + m_Rotation, m_Size);
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CEnemy::Draw(void)
{
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルのポインタがNULLじゃない場合
		if (m_apModel[nCount] != NULL)
		{
			//モデルの描画処理関数呼び出し
			m_apModel[nCount]->Draw();
		}
	}
}

//=============================================================================
// モデルデータセット処理関数
//=============================================================================
void CEnemy::SetModelData(CModel::MODEL_DATA ModelData[MAX_PARTS])
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		if (ModelData[nCount].pMesh != NULL)
		{
			m_aModelData[nCount] = ModelData[nCount];
		}
	}
}

//=============================================================================
// ヒット処理関数
//=============================================================================
void CEnemy::Hit(void)
{
}

//=============================================================================
// 体力減算処理関数
//=============================================================================
void CEnemy::SubLife(void)
{
}

//=============================================================================
// モーション処理関数
//=============================================================================
void CEnemy::Motion(void)
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
		m_pMotion->LoadMotion(m_apMotionPass[0]);
		//モーション情報の読み込み
		m_pMotion->LoadModelInformation(m_apMotionPass[0]);
		//最大パーツ数分回す
		for (int nCount = 0; nCount < MAX_PARTS; nCount++)
		{
			//もしモデルデータのメッシュがNULLじゃない場合
			if (m_aModelData[nCount].pMesh != NULL)
			{
				//親モデルの番号受け取り
				m_aModelData[nCount].nIndexModelParent = m_pMotion->GetParents(nCount);
				//モデルの生成
				m_apModel[nCount] = CModel::Create(m_aModelData[nCount]);
				//モーションの位置を取得
				m_pMotion->GetPosition(nCount);
				//モーションの回転を取得
				m_pMotion->GetRotation(nCount);
				//モデルの割り当て
				m_apModel[nCount]->BindModel(m_aModelData[nCount]);
				// モデルのパーツごとの座標と回転を受け取る
				m_apModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), m_Size);
			}
		}
		//パーツの最大数分回す
		for (int nCount = 0; nCount < MAX_PARTS; nCount++)
		{
			//もし親のモデルが存在したら
			if (m_apModel[m_aModelData[nCount].nIndexModelParent] != NULL && m_aModelData[nCount].nIndexModelParent != -1)
			{
				//もしモデルデータのメッシュがNULLじゃない場合
				if (m_aModelData[nCount].pMesh != NULL)
				{
					//親のモデルポインタを受け取る
					m_aModelData[nCount].pParent = m_apModel[m_aModelData[nCount].nIndexModelParent];
					// モデルの割り当て
					m_apModel[nCount]->BindModel(m_aModelData[nCount]);
				}
			}
		}
		// 座標、回転、サイズのセット
		m_apModel[0]->SetModel(m_pMotion->GetPosition(0) + m_Position, m_pMotion->GetRotation(0) + m_Rotation, m_Size);
	}
}