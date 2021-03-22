//=============================================================================
//
// 木造の家 [object_house.cpp]
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
#include "renderer.h"
#include "object_wood_house.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PASS ("Data/Model/House/WoodHouse.x")				//モデルスクリプトのパス
#define SCRIPT_PASS ("Data/Script/Object/WoodHouseData.txt")	//スクリプトのパス

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODEL_DATA CWoodHouse::m_ModelData = {};			//モデルデータのポインタ
D3DXMATERIAL * CWoodHouse::m_pMaterial = NULL;				//マテリアルのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CWoodHouse::CWoodHouse()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CWoodHouse::~CWoodHouse()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CWoodHouse::ModelLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//パスのポインタ
	char * pPass = NULL;
	//もしパスのポインタがNULLの場合
	if (pPass == NULL)
	{
		//パスを取得
		pPass = MODEL_PASS;
	}
	//もしパスのポインタがNULLじゃない場合
	if (pPass != NULL)
	{
		//モデル読み込み
		D3DXLoadMeshFromX(pPass,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_ModelData.pBuffMat,
			NULL,
			&m_ModelData.nNumMat,
			&m_ModelData.pMesh);
		//もしモデルのマテリアル情報がNULLじゃない場合
		if (m_ModelData.pBuffMat != NULL)
		{
			//マテリアルのポインタを取得
			m_pMaterial = (D3DXMATERIAL *)m_ModelData.pBuffMat->GetBufferPointer();
			//モデルデータ数分回す
			for (int nCountMat = 0; nCountMat < (int)m_ModelData.nNumMat; nCountMat++)
			{
				//もしファイルネームがNULLじゃない場合
				if (m_pMaterial[nCountMat].pTextureFilename != NULL)
				{
					//テクスチャを読み込む
					D3DXCreateTextureFromFile(pDevice, m_pMaterial[nCountMat].pTextureFilename, &m_ModelData.pTexture[nCountMat]);
				}
			}
		}
	}
	return S_OK;
}

//=============================================================================
// モデル破棄関数
//=============================================================================
void CWoodHouse::ModelUnload(void)
{
	//もしモデルデータのワールド変換行列がNULLじゃな場合
	if (m_ModelData.mtxWorld != NULL)
	{
		//もしモデルデータのマテリアル情報がNULLじゃな場合
		if (m_ModelData.pBuffMat != NULL)
		{
			//モデルデータのマテリアル情報を破棄
			m_ModelData.pBuffMat->Release();
		}
		//もしモデルデータのメッシュ情報がNULLじゃな場合
		if (m_ModelData.pMesh != NULL)
		{
			//モデルデータのメッシュ情報を破棄
			m_ModelData.pMesh->Release();
		}
		//マテリアルの最大数分回す
		for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
		{
			//もしモデルデータのテクスチャのポインタがNULLじゃな場合
			if (m_ModelData.pTexture[nCountTexture] != NULL)
			{
				//モデルデータのテクスチャのポインタを破棄
				m_ModelData.pTexture[nCountTexture]->Release();
			}
		}
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CWoodHouse * CWoodHouse::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Rotation)
{
	//木造の家のポインタ
	CWoodHouse * pWoodHouse = NULL;
	//木造の家のポインタがNULLの場合
	if (pWoodHouse == NULL)
	{
		//木造の家のメモリ確保
		pWoodHouse = new CWoodHouse;
		//木造の家のポインタがNULLではない場合
		if (pWoodHouse != NULL)
		{
			//木造の家の位置を設定する
			pWoodHouse->SetPosition(Position);
			//木造の家の回転を設定する
			pWoodHouse->SetRotation(Rotation);
			//木造の家の初期化処理関数呼び出し
			pWoodHouse->Init();
		}
	}
	//木造の家のポインタを返す
	return pWoodHouse;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CWoodHouse::Init(void)
{
	//モデルデータを設定
	SetModelData(m_ModelData);
	//スクリプトのパスを設定
	SetScriptPass(SCRIPT_PASS);
	//オブジェクトの初期化処理関数呼び出し
	CObject::Init();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CWoodHouse::Uninit(void)
{
	//オブジェクトの終了処理関数呼び出し
	CObject::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CWoodHouse::Update(void)
{
	//オブジェクトの更新処理関数呼び出し
	CObject::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CWoodHouse::Draw(void)
{
	//オブジェクトの描画処理関数呼び出し
	CObject::Draw();
}