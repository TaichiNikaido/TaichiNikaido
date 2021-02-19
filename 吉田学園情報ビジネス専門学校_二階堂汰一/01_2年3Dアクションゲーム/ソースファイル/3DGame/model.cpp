//=============================================================================
//
// モデル [model.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// 警告制御
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// ヘッダファイルのインクルード
//****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CModel::CModel()
{
	ZeroMemory(&m_ModelData, sizeof(m_ModelData));	//モデルデータの初期化
}

//=============================================================================
// デストラクタ
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
// モデルテキスト読み込み関数
//=============================================================================
char * CModel::LoadModelText(const char * cText)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	int	 nCntModel = 0;					//モーションの数のカウント
	char aReadText[MAX_TEXT];			//文字として読み取り用
	char aCurrentText[MAX_TEXT];		//文字の判別用
	char cDie[MAX_TEXT];				//使わない文字
	MODEL_DATA ModelData[MAX_PARTS];		//モデルデータ
	char aPass[MAX_PARTS][MAX_TEXT];
	memset(aReadText, NULL, sizeof(aReadText));
	memset(aCurrentText, NULL, sizeof(aCurrentText));
	memset(cDie, NULL, sizeof(cDie));
	memset(ModelData, NULL, sizeof(ModelData));
	memset(aPass, NULL, sizeof(aPass));
	//ファイルのポインタ
	FILE *pFile = NULL;
	//もしファイルのポインタがNULLの場合
	if (pFile == NULL)
	{
		// ファイルを開く
		pFile = fopen(cText, "r");
	}
	//もしファイルのポインタがNULLじゃない場合
	if (pFile != NULL)
	{
		// SCRIPTの文字が見つかるまで
		while (strcmp(aCurrentText, "SCRIPT") != 0)
		{
			// テキストからaReadText分文字を読み込む
			fgets(aReadText, sizeof(aReadText), pFile);
			// 読み込んだ文字ををaCurrentTextに格納
			sscanf(aReadText, "%s", &aCurrentText);
		}
		// aCurrentTextがSCRIPTだったら
		if (strcmp(aCurrentText, "SCRIPT") == 0)
		{
			// END_SCRIPTの文字が見つかるまで
			while (strcmp(aCurrentText, "END_SCRIPT") != 0)
			{
				// テキストからaReadText分文字を読み込む
				fgets(aReadText, sizeof(aReadText), pFile);
				// 読み込んだ文字ををaCurrentTextに格納
				sscanf(aReadText, "%s", &aCurrentText);
				// aCurrentTextがMODEL_FILENAMEだったら
				if (strcmp(aCurrentText, "MODEL_FILENAME") == 0)
				{
					// モデルパーツのパスを格納
					sscanf(aReadText, "%s %s %s", &cDie, &cDie, &aPass[nCntModel]);
					// カウントの加算
					nCntModel++;
				}
			}
			// ファイルを閉じる
			fclose(pFile);
		}
	}
	return aPass[0];
}

//=============================================================================
// 生成処理関数
//=============================================================================
CModel * CModel::Create(MODEL_DATA modeldata)
{
	//モデルのポインタ
	CModel* pModel = NULL;
	//モデルのポインタがNULLの場合
	if (pModel == NULL)
	{
		//モデルのメモリ確保
		pModel = new CModel;
	}
	//モデルのポインタがNULLじゃない場合
	if (pModel != NULL)
	{
		//各種情報の設定
		pModel->m_ModelData = modeldata;
		// 初期化処理
		pModel->Init();
	}
	//モデルのポインタを返す
	return pModel;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CModel::Init(void)
{
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CModel::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CModel::Update(void)
{
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CModel::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	//行列
	D3DXMATERIAL * pMat;					//マテリアルのポインタ
	D3DXMATRIX mtxParent;					//親の行列
	//ワールド変換行列の初期化
	D3DXMatrixIdentity(&m_ModelData.mtxWorld);
	//拡大縮小行列の生成と計算
	D3DXMatrixScaling(&mtxScale, GetSize().x, GetSize().y, GetSize().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxScale);
	//回転行列の生成と計算
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRotation().y, GetRotation().x, GetRotation().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);
	//平行移動行列の生成と計算
	D3DXMatrixTranslation(&mtxTrans, GetPosition().x, GetPosition().y, GetPosition().z);
	D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);
	//もし親モデルがNULLじゃない場合
	if (m_ModelData.pParent != NULL)
	{
		//親のマトリクスを設定
		mtxParent = m_ModelData.pParent->m_ModelData.mtxWorld;
		//モデルパーツに親のマトリックスを掛け合わせることで、位置や回転を親に追従させる
		D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxParent);
	}
	else
	{
		//トランスフームを取得
		pDevice->GetTransform(D3DTS_WORLD2, &mtxParent);
		//モデルパーツにマトリックスを掛け合わせることで、位置や回転を親に追従させる
		D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxParent);
	}
	//計算結果を適用
	pDevice->SetTransform(D3DTS_WORLD, &m_ModelData.mtxWorld);
	//もしマテリアルがNULLじゃない場合
	if (m_ModelData.pBuffMat != NULL)
	{
		//マテリアルのポインタを取得
		pMat = (D3DXMATERIAL*)m_ModelData.pBuffMat->GetBufferPointer();
	}
	//マテリアル情報の設定とマテリアルごとに描画
	for (int nCntMat = 0; nCntMat < (int)m_ModelData.nNumMat; nCntMat++)
	{
		//マテリアルを設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//マテリアルのテクスチャを設定
		pDevice->SetTexture(0, m_ModelData.pTexture[nCntMat]);
		//拡散光の設定
		pMat[nCntMat].MatD3D.Emissive = pMat[nCntMat].MatD3D.Diffuse;
		//メッシュがNULLじゃない場合
		if (m_ModelData.pMesh != NULL)
		{
			//メッシュを描画する
			m_ModelData.pMesh->DrawSubset(nCntMat);
		}
	}
}

//=============================================================================
// 親モデルの設定関数
//=============================================================================
void CModel::SetParentModel(CModel * pParentModel)
{
	//親モデルのポインタを設定
	m_ModelData.pParent = pParentModel;
}

//=============================================================================
// モデルの設定関数
//=============================================================================
void CModel::SetModel(D3DXVECTOR3 Position, D3DXVECTOR3 Rotation, D3DXVECTOR3 Size)
{
	//位置を設定する
	SetPosition(Position);
	//回転値を設定する
	SetRotation(Rotation);
	//サイズを設定する
	SetSize(Size);
}

//=============================================================================
// テクスチャの割り当て関数
//=============================================================================
void CModel::BindTexture(LPDIRECT3DTEXTURE9 pTexture, int nCount)
{
	//テクスチャのポインタを設定する
	m_ModelData.pTexture[nCount] = pTexture;
}
