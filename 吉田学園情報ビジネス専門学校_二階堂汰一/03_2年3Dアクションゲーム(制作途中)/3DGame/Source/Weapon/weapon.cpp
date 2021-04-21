//=============================================================================
//
// 武器 [weapon.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "weapon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CWeapon::CWeapon()
{
	m_Position = INITIAL_D3DXVECTOR3;			//位置
	m_Size = INITIAL_D3DXVECTOR3;				//サイズ
	m_CollisionSize = INITIAL_D3DXVECTOR3;		//衝突判定用サイズ
	m_Rotation = INITIAL_ROTATION;				//回転
	m_pModel = NULL;							//モデルのポインタ
	m_pParentModel = NULL;						//親モデルのポインタ
	m_aModelData = {};							//モデルデータ
}

//=============================================================================
// デストラクタ
//=============================================================================
CWeapon::~CWeapon()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CWeapon::Init(void)
{
	//もしモデルのポインタがnullptrの場合
	if (m_pModel == nullptr)
	{
		//モデルの生成
		m_pModel = CModel::Create(m_aModelData);
		//もしモデルのポインタがNULLじゃない場合
		if (m_pModel != nullptr)
		{
			//モデルの初期化処理関数呼び出し
			m_pModel->Init();
			//モデルに位置を設定する
			m_pModel->SetPosition(m_Position);
			//モデルにサイズを設定する
			m_pModel->SetSize(m_Size);
			//モデルに回転を設定する
			m_pModel->SetRotation(m_Rotation);
			//親モデルを設定する
			m_pModel->SetParentModel(m_pParentModel);
		}
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CWeapon::Uninit(void)
{
	//もしモデルのポインタがnullptrじゃない場合
	if (m_pModel != nullptr)
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
void CWeapon::Update(void)
{
	//もしモデルのポインタがnullptrじゃない場合
	if (m_pModel != nullptr)
	{
		//モデルの更新処理関数呼び出し
		m_pModel->Update();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CWeapon::Draw(void)
{
	//もしモデルのポインタがnullptrじゃない場合
	if (m_pModel != nullptr)
	{
		//モデルの描画処理関数呼び出し
		m_pModel->Draw();
	}
}

//=============================================================================
// 衝突判定関数
//=============================================================================
void CWeapon::Collision(void)
{
}
