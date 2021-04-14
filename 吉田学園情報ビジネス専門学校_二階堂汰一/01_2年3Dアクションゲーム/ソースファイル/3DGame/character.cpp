//=============================================================================
//
// キャラクター [character.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "character.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CCharacter::CCharacter()
{
	memset(m_apModelScriptPass, NULL, sizeof(m_apModelScriptPass));		//モデルのスクリプトパス
	memset(m_aModelData, NULL, sizeof(m_aModelData));					//モデルデータ
	memset(m_pModel,NULL,sizeof(m_pModel));								//モデルのポインタ
	m_pMotion = nullptr;												//モーションのポインタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CCharacter::~CCharacter()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CCharacter::Init(void)
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
		m_pMotion->LoadMotion(m_apModelScriptPass[0]);
		//モーション情報の読み込み
		m_pMotion->LoadModelInformation(m_apModelScriptPass[0]);
		//最大パーツ数分回す
		for (int nCount = 0; nCount < MAX_PARTS; nCount++)
		{
			//もしモデルデータのメッシュがNULLじゃない場合
			if (m_aModelData[nCount].pMesh != NULL)
			{
				//親モデルの番号受け取り
				m_aModelData[nCount].nIndexModelParent = m_pMotion->GetParents(nCount);
				//モデルの生成
				m_pModel[nCount] = CModel::Create(m_aModelData[nCount]);
				//モーションの位置を取得
				m_pMotion->GetPosition(nCount);
				//モーションの回転を取得
				m_pMotion->GetRotation(nCount);
				//モデルの割り当て
				m_pModel[nCount]->BindModel(m_aModelData[nCount]);
				// モデルのパーツごとの座標と回転を受け取る
				m_pModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), GetSize());
			}
		}
		//パーツの最大数分回す
		for (int nCount = 0; nCount < MAX_PARTS; nCount++)
		{
			//もし親のモデルが存在したら
			if (m_pModel[m_aModelData[nCount].nIndexModelParent] != NULL && m_aModelData[nCount].nIndexModelParent != -1)
			{
				//もしモデルデータのメッシュがNULLじゃない場合
				if (m_aModelData[nCount].pMesh != NULL)
				{
					//親のモデルポインタを受け取る
					m_aModelData[nCount].pParent = m_pModel[m_aModelData[nCount].nIndexModelParent];
					// モデルの割り当て
					m_pModel[nCount]->BindModel(m_aModelData[nCount]);
				}
			}
		}
		// 座標、回転、サイズのセット
		m_pModel[0]->SetModel(m_pMotion->GetPosition(0) + GetPosition(), m_pMotion->GetRotation(0) + GetRotation(), GetSize());
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CCharacter::Uninit(void)
{
	//もしモーションのポインタがNULLの場合
	if (m_pMotion != NULL)
	{
		//終了処理関数呼び出し
		m_pMotion->Uninit();
	}
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルのポインタがNULLではない場合
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
void CCharacter::Update(void)
{
	//もしモーションのポインタがNULLの場合
	if (m_pMotion != NULL)
	{
		//更新処理関数呼び出し
		m_pMotion->Update();
	}
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルのポインタがNULLではない場合	
		if (m_pModel[nCount] != NULL)
		{
			//モデルの更新処理関数呼び出し
			m_pModel[nCount]->Update();
			// モデルのパーツごとの座標と回転を受け取る
			m_pModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), GetSize());
		}
	}
	// 座標、回転、サイズのセット
	m_pModel[0]->SetModel(m_pMotion->GetPosition(0) + GetPosition(), m_pMotion->GetRotation(0) + GetRotation(), GetSize());
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CCharacter::Draw(void)
{
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルのポインタがNULLではない場合
		if (m_pModel[nCount] != NULL)
		{
			//モデルの描画処理関数呼び出し
			m_pModel[nCount]->Draw();
		}
	}
}

//=============================================================================
// モデル情報の設定処理関数
//=============================================================================
void CCharacter::SetModelData(CModel::MODEL_DATA ModelData[MAX_PARTS])
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		if (ModelData[nCount].pMesh != NULL)
		{
			m_aModelData[nCount] = ModelData[nCount];
		}
	}
}
