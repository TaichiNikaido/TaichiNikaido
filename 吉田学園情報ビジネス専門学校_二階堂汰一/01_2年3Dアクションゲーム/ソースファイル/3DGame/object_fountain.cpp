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
#include "object_fountain.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PASS ("Data/Model/Fountain.x")					//モデルスクリプトのパス
#define SCRIPT_PASS ("Data/Script/Script/FountainData.txt")		//スクリプトのパス
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))				//サイズの初期値
#define INITIAL_COLLISION_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//衝突判定用サイズの初期値
#define INITIAL_LIFE (0)										//体力の初期値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODEL_DATA CFountain::m_ModelData = {};			//モデルデータのポインタ
D3DXMATERIAL * CFountain::m_pMaterial = NULL;			//マテリアルのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CFountain::CFountain()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CFountain::~CFountain()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CFountain::ModelLoad(void)
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
void CFountain::ModelUnload(void)
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
CFountain * CFountain::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Rotation)
{
	//噴水のポインタ
	CFountain * pFountain = NULL;
	//噴水のポインタがNULLの場合
	if (pFountain == NULL)
	{
		//噴水のメモリ確保
		pFountain = new CFountain;
	}
	//噴水のポインタがNULLではない場合
	if (pFountain != NULL)
	{
		//噴水の位置を設定する
		pFountain->SetPosition(Position);
		//噴水の回転を設定する
		pFountain->SetRotation(Rotation);
		//噴水の初期化処理関数呼び出し
		pFountain->Init();
	}
	//噴水のポインタを返す
	return pFountain;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CFountain::Init(void)
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
void CFountain::Uninit(void)
{
	//オブジェクトの終了処理関数呼び出し
	CObject::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CFountain::Update(void)
{
	//オブジェクトの更新処理関数呼び出し
	CObject::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CFountain::Draw(void)
{
	//オブジェクトの描画処理関数呼び出し
	CObject::Draw();
}