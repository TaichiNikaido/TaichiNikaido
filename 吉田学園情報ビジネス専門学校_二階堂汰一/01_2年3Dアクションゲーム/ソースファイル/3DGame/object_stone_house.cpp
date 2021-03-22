//=============================================================================
//
// 石造の家 [object_house.cpp]
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
#include "object_stone_house.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PASS ("Data/Model/House/StoneHouse.x")			//モデルスクリプトのパス
#define SCRIPT_PASS ("Data/Script/Object/StoneHouseData.txt")	//スクリプトのパス

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODEL_DATA CStoneHouse::m_ModelData = {};			//モデルデータのポインタ
D3DXMATERIAL * CStoneHouse::m_pMaterial = NULL;				//マテリアルのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CStoneHouse::CStoneHouse()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CStoneHouse::~CStoneHouse()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CStoneHouse::ModelLoad(void)
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
void CStoneHouse::ModelUnload(void)
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
CStoneHouse * CStoneHouse::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Rotation)
{
	//石造の家のポインタ
	CStoneHouse * pStoneHouse = NULL;
	//石造の家のポインタがNULLの場合
	if (pStoneHouse == NULL)
	{
		//石造の家のメモリ確保
		pStoneHouse = new CStoneHouse;
		//石造の家のポインタがNULLではない場合
		if (pStoneHouse != NULL)
		{
			//石造の家の位置を設定する
			pStoneHouse->SetPosition(Position);
			//石造の家の回転を設定する
			pStoneHouse->SetRotation(Rotation);
			//石造の家の初期化処理関数呼び出し
			pStoneHouse->Init();
		}
	}
	//石造の家のポインタを返す
	return pStoneHouse;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CStoneHouse::Init(void)
{
	//モデルデータの設定
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
void CStoneHouse::Uninit(void)
{
	//オブジェクトの終了処理関数呼び出し
	CObject::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CStoneHouse::Update(void)
{
	//オブジェクトの更新処理関数呼び出し
	CObject::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CStoneHouse::Draw(void)
{
	//オブジェクトの描画処理関数呼び出し
	CObject::Draw();
}
