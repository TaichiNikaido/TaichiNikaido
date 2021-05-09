//=============================================================================
//
// キャラクター [character.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "character.h"
#include "Polygon3d/shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SHADOW_SIZE (D3DXVECTOR3(500.0f,500.0f,500.0f))					//影のサイズ
#define SHADOW_ROTATION (D3DXToRadian(D3DXVECTOR3(-90.0f,0.0f,0.0f)))	//影の回転
#define SHADOW_COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))					//影の色

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CCharacter::CCharacter(int nPriority) : CScene3d(nPriority)
{
	memset(m_apModelScriptPass, NULL, sizeof(m_apModelScriptPass));		//モデルのスクリプトパス
	memset(m_aModelData, NULL, sizeof(m_aModelData));					//モデルデータ
	m_CollisionSize = INITIAL_D3DXVECTOR3;								//衝突判定用サイズ
	memset(m_apModel,NULL,sizeof(m_apModel));							//モデルのポインタ
	m_pMotion = nullptr;												//モーションのポインタ
	//m_pShadow = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCharacter::~CCharacter()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CCharacter::Init(void)
{
	//もしモーションのポインタがnullptrの場合
	if (m_pMotion == nullptr)
	{
		//モーションの生成
		m_pMotion = CMotion::Create();
		//もしモーションのポインタがnullptrじゃない場合
		if (m_pMotion != nullptr)
		{
			//モーションの読み込み
			m_pMotion->LoadMotion(m_apModelScriptPass[0]);
			//モーション情報の読み込み
			m_pMotion->LoadModelInformation(m_apModelScriptPass[0]);
			//最大パーツ数分回す
			for (int nCount = 0; nCount < MAX_PARTS; nCount++)
			{
				//もしモデルデータのメッシュがnullptrじゃない場合
				if (m_aModelData[nCount].pMesh != nullptr)
				{
					//親モデルの番号受け取り
					m_aModelData[nCount].nIndexModelParent = m_pMotion->GetParents(nCount);
					//モデルの生成
					m_apModel[nCount] = CModel::Create(m_aModelData[nCount]);
					//モーションの位置を取得
					m_pMotion->GetPosition(nCount);
					//モーションの回転を取得
					m_pMotion->GetRotation(nCount);
					//モデルの割り当て
					m_apModel[nCount]->BindModel(m_aModelData[nCount]);
					// モデルのパーツごとの座標と回転を受け取る
					m_apModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), GetSize());
				}
			}
			//パーツの最大数分回す
			for (int nCount = 0; nCount < MAX_PARTS; nCount++)
			{
				//もし親のモデルが存在したら
				if (m_apModel[m_aModelData[nCount].nIndexModelParent] != nullptr && m_aModelData[nCount].nIndexModelParent != -1)
				{
					//もしモデルデータのメッシュがnullptrじゃない場合
					if (m_aModelData[nCount].pMesh != nullptr)
					{
						//親のモデルポインタを受け取る
						m_aModelData[nCount].pParent = m_apModel[m_aModelData[nCount].nIndexModelParent];
						// モデルの割り当て
						m_apModel[nCount]->BindModel(m_aModelData[nCount]);
					}
				}
			}
			// 座標、回転、サイズのセット
			m_apModel[0]->SetModel(m_pMotion->GetPosition(0) + GetPosition(), m_pMotion->GetRotation(0) + GetRotation(), GetSize());
		}
	}
	//影の生成処理関数呼び出し
	ShadowCreate();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CCharacter::Uninit(void)
{
	//もしモーションのポインタがnullptrの場合
	if (m_pMotion != nullptr)
	{
		//終了処理関数呼び出し
		m_pMotion->Uninit();
	}
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルのポインタがnullptrではない場合
		if (m_apModel[nCount] != nullptr)
		{
			//モデルの終了処理関数呼び出し
			m_apModel[nCount]->Uninit();
		}
	}
	////もし影のポインタがnullptrではない場合
	//if (m_pShadow != nullptr)
	//{
	//	//影の終了処理関数呼び出し
	//	m_pShadow->Uninit();
	//}
	//破棄処理関数呼び出し
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CCharacter::Update(void)
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//もしモーションのポインタがnullptrの場合
	if (m_pMotion != nullptr)
	{
		//更新処理関数呼び出し
		m_pMotion->Update();
	}
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルのポインタがnullptrではない場合	
		if (m_apModel[nCount] != nullptr)
		{
			//モデルの更新処理関数呼び出し
			m_apModel[nCount]->Update();
			// モデルのパーツごとの座標と回転を受け取る
			m_apModel[nCount]->SetModel(m_pMotion->GetPosition(nCount), m_pMotion->GetRotation(nCount), GetSize());
		}
	}
	////もし影のポインタがnullptrではない場合
	//if (m_pShadow != nullptr)
	//{
	//	//影の位置を設定する
	//	m_pShadow->SetPosition(Position);
	//	//影のサイズを設定する
	//	m_pShadow->SetSize(SHADOW_SIZE);
	//	//影の回転を設定する
	//	m_pShadow->SetRotation(SHADOW_ROTATION);
	//	//影の色を設定する
	//	m_pShadow->SetColor(SHADOW_COLOR);
	//	//影の更新処理関数呼び出し
	//	m_pShadow->Update();
	//}
	//位置を保存する
	m_PositionOld = Position;
	// 座標、回転、サイズのセット
	m_apModel[0]->SetModel(m_pMotion->GetPosition(0) + GetPosition(), m_pMotion->GetRotation(0) + GetRotation(), GetSize());
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CCharacter::Draw(void)
{
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//パーツの最大数分回す
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		//もしモデルのポインタがnullptrではない場合
		if (m_apModel[nCount] != nullptr)
		{
			//モデルの描画処理関数呼び出し
			m_apModel[nCount]->Draw();
		}
	}
	////深度テストの設定(必ず不合格にする)
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
	////ステンシルテストを有効にする
	//pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	////ステンシルバッファへ書き込む参照値設定
	//pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	//pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	////ステンシルバッファに書き込む条件
	//pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	//// ステンシルテストのテスト設定
	//pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	//pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
	//pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	////位置を設定する
	//m_apModel[0]->SetPosition(Position);
	////回転を設定する
	//m_apModel[0]->SetRotation(D3DXToRadian(D3DXVECTOR3(90.0f, 0.0f, 0.0f)));
	////パーツの最大数分回す
	//for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	//{
	//	//もしモデルのポインタがnullptrではない場合
	//	if (m_apModel[nCount] != nullptr)
	//	{
	//		//モデルの描画処理関数呼び出し
	//		m_apModel[nCount]->Draw();
	//	}
	//}
	////深度テストの設定
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	////ステンシル参照値の設定
	//pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	////ステンシルマスクの設定
	//pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	//pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	////ステンシルテストのテスト設定
	//pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	//pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	//pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	////もし影のポインタがnullptrではない場合
	//if (m_pShadow != nullptr)
	//{
	//	//影の描画処理関数呼び出し
	//	m_pShadow->Draw();
	//}
	////ステンシルテストを無効にする
	//pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//=============================================================================
// モデル情報の設定処理関数
//=============================================================================
void CCharacter::SetModelData(CModel::MODEL_DATA ModelData[MAX_PARTS])
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		if (ModelData[nCount].pMesh != nullptr)
		{
			m_aModelData[nCount] = ModelData[nCount];
		}
	}
}

//=============================================================================
// 影生成処理関数
//=============================================================================
void CCharacter::ShadowCreate(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//位置を取得する
	D3DXVECTOR3 Position = GetPosition();
	////もし影のポインタがnullptrの場合
	//if (m_pShadow == nullptr)
	//{
	//	//影の生成
	//	m_pShadow = new CShadow;
	//	//もし影のポインタがnullptrではない場合
	//	if (m_pShadow != nullptr)
	//	{
	//		//影の位置を設定する
	//		m_pShadow->SetPosition(Position);
	//		//影のサイズを設定する
	//		m_pShadow->SetSize(SHADOW_SIZE);
	//		//影の回転を設定する
	//		m_pShadow->SetRotation(SHADOW_ROTATION);
	//		//影の色を設定する
	//		m_pShadow->SetColor(SHADOW_COLOR);
	//		//影の頂点座標を設定する
	//		m_pShadow->SetTexture(aTexture);
	//		//影の初期化処理関数呼び出し
	//		m_pShadow->Init();
	//	}
	//}
}
