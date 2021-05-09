//=============================================================================
//
// 剣 [sword.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Mode/mode_game.h"
#include "weapon_sword.h"
#include "Character/player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PASS ("Data/Model/Weapon/Sword.x")	//モデルスクリプトのパス
#define POSITION (D3DXVECTOR3(1.0f,1.0f,1.0f))		//位置
#define ROTATION (D3DXVECTOR3(1.0f,1.0f,1.0f))		//回転
#define SIZE (D3DXVECTOR3(1.0f,1.0f,1.0f))			//サイズ

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODEL_DATA CSword::m_aModelData = {};	//モデルデータのポインタ
D3DXMATERIAL * CSword::m_pMaterial = nullptr;	//マテリアルのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CSword::CSword()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSword::~CSword()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CSword::ModelLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//パスのポインタ
	char * pPass = nullptr;
	//もしパスのポインタがnullptrの場合
	if (pPass == nullptr)
	{
		//パスを取得
		pPass = MODEL_PASS;
	}
	//もしパスのポインタがnullptrじゃない場合
	if (pPass != nullptr)
	{
		//モデル読み込み
		D3DXLoadMeshFromX(pPass,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_aModelData.pBuffMat,
			NULL,
			&m_aModelData.nNumMat,
			&m_aModelData.pMesh);
		//もしモデルのマテリアル情報がNULLじゃない場合
		if (m_aModelData.pBuffMat != NULL)
		{
			//マテリアルのポインタを取得
			m_pMaterial = (D3DXMATERIAL *)m_aModelData.pBuffMat->GetBufferPointer();
			//モデルデータ数分回す
			for (int nCountMat = 0; nCountMat < (int)m_aModelData.nNumMat; nCountMat++)
			{
				//もしファイルネームがNULLじゃない場合
				if (m_pMaterial[nCountMat].pTextureFilename != NULL)
				{
					//テクスチャを読み込む
					D3DXCreateTextureFromFile(pDevice, m_pMaterial[nCountMat].pTextureFilename, &m_aModelData.pTexture[nCountMat]);
				}
			}
		}
	}
	return S_OK;
}

//=============================================================================
// モデル破棄関数
//=============================================================================
void CSword::ModelUnload(void)
{
	//もしモデルデータのワールド変換行列がNULLじゃな場合
	if (m_aModelData.mtxWorld != NULL)
	{
		//もしモデルデータのマテリアル情報がNULLじゃな場合
		if (m_aModelData.pBuffMat != NULL)
		{
			//モデルデータのマテリアル情報を破棄
			m_aModelData.pBuffMat->Release();
		}
		//もしモデルデータのメッシュ情報がNULLじゃな場合
		if (m_aModelData.pMesh != NULL)
		{
			//モデルデータのメッシュ情報を破棄
			m_aModelData.pMesh->Release();
		}
		//マテリアルの最大数分回す
		for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
		{
			//もしモデルデータのテクスチャのポインタがNULLじゃな場合
			if (m_aModelData.pTexture[nCountTexture] != NULL)
			{
				//モデルデータのテクスチャのポインタを破棄
				m_aModelData.pTexture[nCountTexture]->Release();
			}
		}
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CSword * CSword::Create()
{
	//剣のポインタ
	CSword * pSword = nullptr;
	//剣のポインタがnullptrの場合
	if (pSword == nullptr)
	{
		//剣のメモリ確保
		pSword = new CSword;
		//剣のポインタがnullptrではない場合
		if (pSword != nullptr)
		{
			//位置を設定する
			pSword->SetPosition(POSITION);
			//回転を設定する
			pSword->SetRotation(ROTATION);
			//サイズを設定する
			pSword->SetSize(SIZE);
			//剣の初期化処理関数呼び出し
			pSword->Init();
		}
	}
	//剣のポインタを返す
	return pSword;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CSword::Init(void)
{
	//プレイヤーを取得する
	CPlayer * pPlayer = CManager::GetGameMode()->GetPlayer();
	//もしプレイヤーがnullptrじゃない場合
	if (pPlayer != nullptr)
	{
		//親モデルの設定
		SetParentModel(pPlayer->GetModel(9));
	}
	//モデルデータの設定
	SetModelData(m_aModelData);
	//武器の初期化処理関数呼び出し
	CWeapon::Init();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CSword::Uninit(void)
{
	//武器の終了処理関数呼び出し
	CWeapon::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CSword::Update(void)
{
	//武器の更新処理関数呼び出し
	CWeapon::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CSword::Draw(void)
{
	//武器の描画処理関数呼び出し
	CWeapon::Draw();
}