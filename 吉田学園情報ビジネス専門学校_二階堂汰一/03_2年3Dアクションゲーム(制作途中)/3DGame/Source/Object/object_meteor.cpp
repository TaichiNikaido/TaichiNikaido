//=============================================================================
//
// メテオ [object_meteor.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "object_meteor.h"
#include "Polygon3d/round_shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PASS ("Data/Model/Object/meteor.x")						//モデルスクリプトのパス
#define ROTATION (D3DXVECTOR3(0.0f,0.0f,0.0f))							//回転
#define MOVE (D3DXVECTOR3(0.0f,-5.0f,0.0f))								//移動量
#define SIZE (D3DXVECTOR3(2.0f,2.0f,2.0f))								//サイズ
#define COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,0.0f))							//色
#define METEOR_SHADOW_POSITION (D3DXVECTOR3(0.0f,1.0f,0.0f))			//メテオの影の位置
#define MINIMUM_METEOR_HEIGHT (0.0f)									//メテオの高さの最小値
#define INITIAL_METEOR_SHADOW_SIZE (D3DXVECTOR3(150.0f,150.0f,150.0f))	//メテオの影の初期サイズ
#define METEOR_SHADOW_MAX_SIZE (80.0f)									//メテオの影のサイズの最大値
#define MAX_ALPHA (1.0f)												//アルファ値の最大値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CModel::MODEL_DATA CMeteor::m_MeteorModelData = {};		//モデルデータのポインタ
D3DXMATERIAL * CMeteor::m_pMaterial = NULL;				//マテリアルのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CMeteor::CMeteor()
{
	m_Move = INITIAL_D3DXVECTOR3;					//移動量
	m_MeteorShadowSize = INITIAL_D3DXVECTOR3;		//メテオの影のサイズ
	m_MeteorShadowColor = INITIAL_D3DXCOLOR;		//メテオの影の色
	m_fMeteorMaxHeight = MINIMUM_METEOR_HEIGHT;		//メテオの高さの最小値
	m_fMeteorHeight = MINIMUM_METEOR_HEIGHT;		//隕石の現在の高さ
	m_pRoundShadow = nullptr;						//丸影のポインタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeteor::~CMeteor()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CMeteor::ModelLoad(void)
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
void CMeteor::ModelUnload(void)
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
CMeteor * CMeteor::Create(D3DXVECTOR3 Position)
{
	//メテオのポインタ
	CMeteor * pMeteor = NULL;
	//メテオのポインタがNULLの場合
	if (pMeteor == NULL)
	{
		//メテオのメモリ確保
		pMeteor = new CMeteor;
		//メテオのポインタがNULLではない場合
		if (pMeteor != NULL)
		{
			//メテオの位置を設定する
			pMeteor->SetPosition(Position);
			//メテオの回転を設定する
			pMeteor->SetRotation(ROTATION);
			//メテオのサイズを設定する
			pMeteor->SetSize(SIZE);
			//メテオの初期化処理関数呼び出し
			pMeteor->Init();
		}
	}
	//メテオのポインタを返す
	return pMeteor;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CMeteor::Init(void)
{
	//モデルデータの設定
	SetModelData(m_MeteorModelData);
	//オブジェクトの初期化処理関数呼び出し
	CObject::Init();
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//隕石の高さの最大値を求める
	m_fMeteorMaxHeight = Position.y;
	//移動量の設定
	m_Move = MOVE;
	//もし丸影のポインタがnullptrの場合
	if (m_pRoundShadow == nullptr)
	{
		//メテオの影の色を設定する
		m_MeteorShadowColor = COLOR;
		//丸影の生成
		m_pRoundShadow = CRoundShadow::Create(D3DXVECTOR3(Position.x,INITIAL_D3DXVECTOR3.y + 1.0f,Position.z), INITIAL_METEOR_SHADOW_SIZE, m_MeteorShadowColor);
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CMeteor::Uninit(void)
{
	//オブジェクトの終了処理関数呼び出し
	CObject::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CMeteor::Update(void)
{
	//隕石との距離
	float fMeteorDistance;
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//オブジェクトの更新処理関数呼び出し
	CObject::Update();
	//隕石の現在の高さ
	m_fMeteorHeight = Position.y;
	//位置更新
	Position += m_Move;
	//地面から隕石の距離を求める
	fMeteorDistance = m_fMeteorMaxHeight - INITIAL_D3DXVECTOR3.y;
	//高さに応じて影のサイズを求める
	m_MeteorShadowSize.x = (1 - m_fMeteorHeight / fMeteorDistance) * METEOR_SHADOW_MAX_SIZE;
	m_MeteorShadowSize.y = (1 - m_fMeteorHeight / fMeteorDistance) * METEOR_SHADOW_MAX_SIZE;
	m_MeteorShadowSize.z = (1 - m_fMeteorHeight / fMeteorDistance) * METEOR_SHADOW_MAX_SIZE;
	m_MeteorShadowColor.a = (1 - m_fMeteorHeight / fMeteorDistance) * MAX_ALPHA;
	//もし丸影のポインタがnullptrではない場合
	if (m_pRoundShadow != nullptr)
	{
		//影にサイズを設定する
		m_pRoundShadow->SetSize(m_MeteorShadowSize);
		//影に色を設定する
		m_pRoundShadow->SetColor(m_MeteorShadowColor);
	}
	//もし位置が初期値より下になった場合
	if (Position.y <= INITIAL_D3DXVECTOR3.y)
	{
		//もし丸影のポインタがnullptrではない場合
		if (m_pRoundShadow != nullptr)
		{
			//影の終了処理関数呼び出し
			m_pRoundShadow->Uninit();
		}
		//終了処理関数呼び出し
		Uninit();
		return;
	}
	//位置を設定する
	SetPosition(Position);
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CMeteor::Draw(void)
{
	//オブジェクトの描画処理関数呼び出し
	CObject::Draw();
}