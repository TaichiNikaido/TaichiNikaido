//=============================================================================
//
// フェンス [object_fence.cpp]
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
#include "object_fence.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PASS ("Data/Model/Fence.x")						//モデルスクリプトのパス
#define SCRIPT_PASS ("Data/Script/Object/FenceData.txt")		//スクリプトのパス
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))				//サイズの初期値
#define INITIAL_COLLISION_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))	//衝突判定用サイズの初期値
#define INITIAL_LIFE (0)										//体力の初期値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODEL_DATA CFence::m_ModelData = {};			//モデルデータのポインタ
D3DXMATERIAL * CFence::m_pMaterial = NULL;				//マテリアルのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CFence::CFence()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CFence::~CFence()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CFence::ModelLoad(void)
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
void CFence::ModelUnload(void)
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
CFence * CFence::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Rotation)
{
	//フェンスのポインタ
	CFence * pFence = NULL;
	//フェンスのポインタがNULLの場合
	if (pFence == NULL)
	{
		//フェンスのメモリ確保
		pFence = new CFence;
	}
	//フェンスのポインタがNULLではない場合
	if (pFence != NULL)
	{
		//フェンスの位置を設定する
		pFence->SetPosition(Position);
		//フェンスの回転を設定する
		pFence->SetRotation(Rotation);
		//フェンスの初期化処理関数呼び出し
		pFence->Init();
	}
	//フェンスのポインタを返す
	return pFence;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CFence::Init(void)
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
void CFence::Uninit(void)
{
	//オブジェクトの終了処理関数呼び出し
	CObject::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CFence::Update(void)
{
	//オブジェクトの更新処理関数呼び出し
	CObject::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CFence::Draw(void)
{
	//オブジェクトの描画処理関数呼び出し
	CObject::Draw();
}
