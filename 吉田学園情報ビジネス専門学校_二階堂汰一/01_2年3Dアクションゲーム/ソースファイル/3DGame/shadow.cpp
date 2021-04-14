//=============================================================================
//
// 影 [shadow.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PASS ("Data/Script/Player/PlayerModel.txt")	//モデルスクリプトのパス

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODEL_DATA CShadow::m_aShadowModelData[MAX_PARTS] = {};		//モデル情報

//=============================================================================
// コンストラクタ
//=============================================================================
CShadow::CShadow()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CShadow::~CShadow()
{
}

HRESULT CShadow::ModelLoad(void)
{
	//マテリアルのポインタ
	D3DXMATERIAL * pMaterial;
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//パスのポインタ
	char * pPass = NULL;
	//もしパスのポインタがNULLの場合
	if (pPass == NULL)
	{
		//パスを取得
		pPass = CModel::LoadModelText(MODEL_PASS);
	}
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしパスのポインタがNULLじゃない場合
		if (pPass != NULL)
		{
			//モデル読み込み
			D3DXLoadMeshFromX(pPass,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_aShadowModelData[nCount].pBuffMat,
				NULL,
				&m_aShadowModelData[nCount].nNumMat,
				&m_aShadowModelData[nCount].pMesh);
			//もしモデルのマテリアル情報がNULLじゃない場合
			if (m_aShadowModelData[nCount].pBuffMat != NULL)
			{
				//マテリアルのポインタを取得
				pMaterial = (D3DXMATERIAL *)m_aShadowModelData[nCount].pBuffMat->GetBufferPointer();
				//モデルデータ数分回す
				for (int nCountMat = 0; nCountMat < (int)m_aShadowModelData[nCount].nNumMat; nCountMat++)
				{
					//もしファイルネームがNULLじゃない場合
					if (pMaterial[nCountMat].pTextureFilename != NULL)
					{
						//テクスチャを読み込む
						D3DXCreateTextureFromFile(pDevice, pMaterial[nCountMat].pTextureFilename, &m_aShadowModelData[nCount].pTexture[nCountMat]);
					}
				}
			}
			//ポインタを捨てる
			pPass += MAX_TEXT;
		}
	}
	return S_OK;
}

void CShadow::ModelUnload(void)
{
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルデータのワールド変換行列がNULLではない場合
		if (m_aShadowModelData[nCount].mtxWorld != NULL)
		{
			//もしモデルデータのマテリアル情報がNULLではない場合
			if (m_aShadowModelData[nCount].pBuffMat != NULL)
			{
				//モデルデータのマテリアル情報を破棄
				m_aShadowModelData[nCount].pBuffMat->Release();
			}
			//もしモデルデータのメッシュ情報がNULLではない場合
			if (m_aShadowModelData[nCount].pMesh != NULL)
			{
				//モデルデータのメッシュ情報を破棄
				m_aShadowModelData[nCount].pMesh->Release();
			}
			//マテリアルの最大数分回す
			for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
			{
				//もしモデルデータのテクスチャのポインタがNULLではない場合
				if (m_aShadowModelData[nCount].pTexture[nCountTexture] != NULL)
				{
					//モデルデータのテクスチャのポインタを破棄
					m_aShadowModelData[nCount].pTexture[nCountTexture]->Release();
				}
			}
		}
	}
}

CShadow * CShadow::Create()
{
	//影のポインタ
	CShadow * pShadow = NULL;
	//影のポインタがNULLの場合
	if (pShadow == NULL)
	{
		//影のメモリ確保
		pShadow = new CShadow;
		//影のポインタがNULLではない場合
		if (pShadow != NULL)
		{
			//影の初期化処理関数呼び出し
			pShadow->Init();
		}
	}
	//影のポインタを返す
	return pShadow;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CShadow::Init(void)
{
	D3DXVECTOR3 Position = D3DXVECTOR3(0.0f,0.0f,400.0f);
	SetPosition(Position);
	D3DXVECTOR3 Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetRotation(Rotation);
	D3DXVECTOR3 Size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	SetSize(Size);
	SetModelScriptPass(MODEL_PASS);
	//モデル情報の設定
	SetModelData(m_aShadowModelData);
	//キャラクターの初期化処理関数呼び出し
	CCharacter::Init();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CShadow::Uninit(void)
{
	//キャラクターの終了処理関数呼び出し
	CCharacter::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CShadow::Update(void)
{
	//キャラクターの更新処理関数呼び出し
	CCharacter::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CShadow::Draw(void)
{
	//キャラクターの描画処理関数呼び出し
	CCharacter::Draw();
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	//深度テストを不合格にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
	//ステンシル参照値を設定する
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x05);
	//ステンシルマスクの設定
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	//ステンシルバッファに書き込む条件の設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	//書き込む値の設定
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
}