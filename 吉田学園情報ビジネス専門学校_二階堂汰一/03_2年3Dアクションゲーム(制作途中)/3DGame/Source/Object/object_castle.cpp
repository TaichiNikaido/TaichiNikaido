//=============================================================================
//
// 城 [object_castle.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "object_castle.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PASS ("Data/Model/Object/castle.x")	//モデルスクリプトのパス
#define ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))		//回転
#define SIZE (D3DXVECTOR3(2.0f,2.0f,2.0f))			//サイズ

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODEL_DATA CCastle::m_MeteorModelData = {};		//モデルデータのポインタ
D3DXMATERIAL * CCastle::m_pMaterial = NULL;				//マテリアルのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CCastle::CCastle()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CCastle::~CCastle()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CCastle::ModelLoad(void)
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
		//もしパスのポインタがNULLじゃない場合
		if (pPass != NULL)
		{
			//モデル読み込み
			D3DXLoadMeshFromX(pPass,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_MeteorModelData.pBuffMat,
				NULL,
				&m_MeteorModelData.nNumMat,
				&m_MeteorModelData.pMesh);
			//もしモデルのマテリアル情報がNULLじゃない場合
			if (m_MeteorModelData.pBuffMat != NULL)
			{
				//マテリアルのポインタを取得
				m_pMaterial = (D3DXMATERIAL *)m_MeteorModelData.pBuffMat->GetBufferPointer();
				//モデルデータ数分回す
				for (int nCountMat = 0; nCountMat < (int)m_MeteorModelData.nNumMat; nCountMat++)
				{
					//もしファイルネームがNULLじゃない場合
					if (m_pMaterial[nCountMat].pTextureFilename != NULL)
					{
						//テクスチャを読み込む
						D3DXCreateTextureFromFile(pDevice, m_pMaterial[nCountMat].pTextureFilename, &m_MeteorModelData.pTexture[nCountMat]);
					}
				}
			}
		}
	}
	return S_OK;
}

//=============================================================================
// モデル破棄関数
//=============================================================================
void CCastle::ModelUnload(void)
{
	//もしモデルデータのワールド変換行列がNULLじゃな場合
	if (m_MeteorModelData.mtxWorld != NULL)
	{
		//もしモデルデータのマテリアル情報がNULLじゃな場合
		if (m_MeteorModelData.pBuffMat != NULL)
		{
			//モデルデータのマテリアル情報を破棄
			m_MeteorModelData.pBuffMat->Release();
		}
		//もしモデルデータのメッシュ情報がNULLじゃな場合
		if (m_MeteorModelData.pMesh != NULL)
		{
			//モデルデータのメッシュ情報を破棄
			m_MeteorModelData.pMesh->Release();
		}
		//マテリアルの最大数分回す
		for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
		{
			//もしモデルデータのテクスチャのポインタがNULLじゃな場合
			if (m_MeteorModelData.pTexture[nCountTexture] != NULL)
			{
				//モデルデータのテクスチャのポインタを破棄
				m_MeteorModelData.pTexture[nCountTexture]->Release();
			}
		}
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CCastle * CCastle::Create(D3DXVECTOR3 Position)
{
	//城のポインタ
	CCastle * pCastle = NULL;
	//城のポインタがNULLの場合
	if (pCastle == NULL)
	{
		//城のメモリ確保
		pCastle = new CCastle;
		//城のポインタがNULLではない場合
		if (pCastle != NULL)
		{
			//城の位置を設定する
			pCastle->SetPosition(Position);
			//城の回転を設定する
			pCastle->SetRotation(ROTATION);
			//城のサイズを設定する
			pCastle->SetSize(SIZE);
			//城の初期化処理関数呼び出し
			pCastle->Init();
		}
	}
	//城のポインタを返す
	return pCastle;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CCastle::Init(void)
{
	//モデルデータの設定
	SetModelData(m_MeteorModelData);
	//オブジェクトの初期化処理関数呼び出し
	CObject::Init();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CCastle::Uninit(void)
{
	//オブジェクトの終了処理関数呼び出し
	CObject::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CCastle::Update(void)
{
	//オブジェクトの更新処理関数呼び出し
	CObject::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CCastle::Draw(void)
{
	//オブジェクトの描画処理関数呼び出し
	CObject::Draw();
}