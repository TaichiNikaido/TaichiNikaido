//=============================================================================
//
// ドラゴン [enemy_dragon.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/model.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "Mode/mode_game.h"
#include "enemy_dragon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PASS ("Data/Script/Dragon/DragonModel.txt")		//モデルスクリプトのパス
#define SCRIPT_PASS ("Data/Script/Dragon/DragonData.txt")		//スケルトンのスクリプトのパス

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODEL_DATA CDragon::m_aModelData[MAX_PARTS] = {};		//モデルデータのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CDragon::CDragon()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CDragon::~CDragon()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CDragon::ModelLoad(void)
{
	//マテリアルのポインタ
	D3DXMATERIAL * pMaterial;
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//パスのポインタ
	char * pPass = nullptr;
	//もしパスのポインタがnullptrの場合
	if (pPass == nullptr)
	{
		//パスを取得
		pPass = CModel::LoadModelText(MODEL_PASS);
		//パーツの最大数分回す
		for (int nCount = 0; nCount < MAX_PARTS; nCount++)
		{
			//もしパスのポインタがnullptrじゃない場合
			if (pPass != nullptr)
			{
				//モデル読み込み
				D3DXLoadMeshFromX(pPass,
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&m_aModelData[nCount].pBuffMat,
					NULL,
					&m_aModelData[nCount].nNumMat,
					&m_aModelData[nCount].pMesh);
				//もしモデルのマテリアル情報がNULLじゃない場合
				if (m_aModelData[nCount].pBuffMat != nullptr)
				{
					//マテリアルのポインタを取得
					pMaterial = (D3DXMATERIAL *)m_aModelData[nCount].pBuffMat->GetBufferPointer();
					//モデルデータ数分回す
					for (int nCountMat = 0; nCountMat < (int)m_aModelData[nCount].nNumMat; nCountMat++)
					{
						//もしファイルネームがNULLじゃない場合
						if (pMaterial[nCountMat].pTextureFilename != NULL)
						{
							//テクスチャを読み込む
							D3DXCreateTextureFromFile(pDevice, pMaterial[nCountMat].pTextureFilename, &m_aModelData[nCount].pTexture[nCountMat]);
						}
					}
				}
				//ポインタを捨てる
				pPass += MAX_TEXT;
			}
		}
	}
	return S_OK;
}

//=============================================================================
// モデル破棄関数
//=============================================================================
void CDragon::ModelUnload(void)
{
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルデータのワールド変換行列がNULLではない場合
		if (m_aModelData[nCount].mtxWorld != NULL)
		{
			//もしモデルデータのマテリアル情報がNULLではない場合
			if (m_aModelData[nCount].pBuffMat != NULL)
			{
				//モデルデータのマテリアル情報を破棄
				m_aModelData[nCount].pBuffMat->Release();
			}
			//もしモデルデータのメッシュ情報がNULLではない場合
			if (m_aModelData[nCount].pMesh != NULL)
			{
				//モデルデータのメッシュ情報を破棄
				m_aModelData[nCount].pMesh->Release();
			}
			//マテリアルの最大数分回す
			for (int nCountTexture = 0; nCountTexture < MAX_MATERIAL; nCountTexture++)
			{
				//もしモデルデータのテクスチャのポインタがNULLではない場合
				if (m_aModelData[nCount].pTexture[nCountTexture] != NULL)
				{
					//モデルデータのテクスチャのポインタを破棄
					m_aModelData[nCount].pTexture[nCountTexture]->Release();
				}
			}
		}
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CDragon * CDragon::Create()
{
	//ドラゴンのポインタ
	CDragon * pDragon = nullptr;
	//ドラゴンのポインタがnullptrの場合
	if (pDragon == nullptr)
	{
		//ドラゴンのメモリ確保
		pDragon = new CDragon;
		//ドラゴンのポインタがnullptrではない場合
		if (pDragon != nullptr)
		{
			//ドラゴンの初期化処理関数呼び出し
			pDragon->Init();
		}
	}
	//ドラゴンのポインタを返す
	return pDragon;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CDragon::Init(void)
{
	//スクリプトのパスを設定
	SetScriptPass(SCRIPT_PASS);
	//モデルのパスを設定
	SetModelScriptPass(MODEL_PASS);
	//モデルデータの設定
	SetModelData(m_aModelData);
	//敵の初期化処理関数呼び出し
	CEnemy::Init();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CDragon::Uninit(void)
{
	//敵の終了処理関数呼び出し
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CDragon::Update(void)
{
	//キーボードの取得
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	//ジョイスティックの取得
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//ジョイスティックの振動取得
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != nullptr)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//敵の更新処理関数呼び出し
	CEnemy::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CDragon::Draw(void)
{
	//敵の描画処理関数呼び出し
	CEnemy::Draw();
}