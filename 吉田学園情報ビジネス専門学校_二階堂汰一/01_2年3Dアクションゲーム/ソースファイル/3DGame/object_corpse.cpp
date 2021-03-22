//=============================================================================
//
// 家 [object_house.cpp]
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
#include "object_corpse.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PASS ("Data/Model/CorpseSW.x")					//モデルスクリプトのパス
#define SCRIPT_PASS ("Data/Script/Object/CorpseData.txt")		//スクリプトのパス

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODEL_DATA CCorpse::m_ModelData = {};			//モデルデータのポインタ
D3DXMATERIAL * CCorpse::m_pMaterial = NULL;				//マテリアルのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CCorpse::CCorpse()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CCorpse::~CCorpse()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CCorpse::ModelLoad(void)
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
void CCorpse::ModelUnload(void)
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
CCorpse * CCorpse::Create(D3DXVECTOR3 Position,D3DXVECTOR3 Rotation)
{
	//屍のポインタ
	CCorpse * pCorpse = NULL;
	//屍のポインタがNULLの場合
	if (pCorpse == NULL)
	{
		//屍のメモリ確保
		pCorpse = new CCorpse;
		//屍のポインタがNULLではない場合
		if (pCorpse != NULL)
		{
			//屍の位置を設定する
			pCorpse->SetPosition(Position);
			//屍の回転を設定する
			pCorpse->SetRotation(Rotation);
			//屍の初期化処理関数呼び出し
			pCorpse->Init();
		}
	}
	//屍のポインタを返す
	return pCorpse;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CCorpse::Init(void)
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
void CCorpse::Uninit(void)
{
	//オブジェクトの終了処理関数呼び出し
	CObject::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CCorpse::Update(void)
{
	//オブジェクトの更新処理関数呼び出し
	CObject::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CCorpse::Draw(void)
{
	//オブジェクトの描画処理関数呼び出し
	CObject::Draw();
}