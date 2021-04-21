//=============================================================================
//
// スカイボックス [skybox.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "skybox.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/skybox.png")
#define SIZE (D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f))
#define SPHERE_H_COUNT (64)
#define SPHERE_V_COUNT (64) 
#define SPHERE_NUM_VERTEX ((SPHERE_H_COUNT + 1) * (SPHERE_V_COUNT + 1))
#define SPHERE_NUM_INDEX (((SPHERE_H_COUNT + 1) * 2) * SPHERE_V_COUNT + (SPHERE_V_COUNT - 1) * 2)
#define SPHERE_NUM_PRIMITIVE (SPHERE_H_COUNT * SPHERE_V_COUNT * 2) + ((SPHERE_V_COUNT-1) * 4)	

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CSkyBox::m_pTexture = nullptr;	//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CSkyBox::CSkyBox()
{
	memset(m_mtxWorld,NULL,sizeof(m_mtxWorld));		//ワールドマトリクス
	m_pVtxBuff = nullptr;							//頂点バッファのポインタ
	m_pIdxBuff = nullptr;							//インデックスバッファポインタ
	memset(m_aTexture,NULL,sizeof(m_aTexture));		//テクスチャのUV座標
	m_Color = INITIAL_D3DXCOLOR;					//頂点カラー
}

//=============================================================================
// デストラクタ
//=============================================================================
CSkyBox::~CSkyBox()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CSkyBox::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,		//デバイスへのポインタ
		TEXTURE_PASS,						//ファイルの名前
		&m_pTexture);						//読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CSkyBox::TextureUnload(void)
{
	//もしテクスチャのポインタがnullptrではない場合
	if (m_pTexture != nullptr)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャのポインタをnullptrにする
		m_pTexture = nullptr;
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CSkyBox * CSkyBox::Create(void)
{
	//スカイボックスのポインタ
	CSkyBox * pSkyBox = nullptr;
	//スカイボックスのポインタがnullptrの場合
	if (pSkyBox == nullptr)
	{
		//スカイボックスのメモリ確保
		pSkyBox = new CSkyBox;
		//スカイボックスのポインタがnullptrではない場合
		if (pSkyBox != nullptr)
		{
			//スカイボックスの初期化処理関数呼び出し
			pSkyBox->Init();
		}
	}
	//スカイボックスのポインタを返す
	return pSkyBox;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CSkyBox::Init(void)
{
	//サイズの初期設定
	SetSize(SIZE);
	//法線の初期設定
	D3DXVECTOR3 Normal = INITIAL_D3DXVECTOR3;
	//頂点情報
	VERTEX_3D * pVtx;
	//インデックス情報
	WORD * pIdx;
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SPHERE_NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//インデックス
	int nIndex = 0;
	//テクスチャのインデックス
	int nTextureIndex = 0;
	for (int vIndex = 0; vIndex < SPHERE_V_COUNT + 1; vIndex++)
	{
		float fAngleY = 180.0f / SPHERE_V_COUNT * vIndex;
		nTextureIndex = 0;
		for (int hIndex = 0; hIndex < SPHERE_H_COUNT + 1; hIndex++)
		{
			float fAngle = hIndex * 360.0f / SPHERE_H_COUNT;
			pVtx[nIndex].pos = D3DXVECTOR3(cosf(D3DXToRadian(fAngleY))* (GetSize().y / 2)*sinf(D3DXToRadian(fAngle)),
				sinf(D3DXToRadian(fAngleY)) * (GetSize().y / 2),
				cosf(D3DXToRadian(fAngleY)) * (GetSize().y / 2)*cosf(D3DXToRadian(fAngle)));
			//法線正規化
			D3DXVec3Normalize(&pVtx[nIndex].nor, &GetRotation());
			// 法線の設定
			pVtx[nIndex].nor = -GetRotation();
			// 頂点カラーの設定
			pVtx[nIndex].col = m_Color;
			// テクスチャ座標の設定
			pVtx[nIndex].tex = D3DXVECTOR2((float)nTextureIndex, (float)vIndex);
			nIndex++;
			nTextureIndex++;
		}
	}
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * SPHERE_NUM_INDEX, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuff, NULL);
	// インデックスバッファをロックし、頂点情報へのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	nIndex = 0;
	for (int vIndex = 0; vIndex < SPHERE_V_COUNT + 1; vIndex++)
	{
		for (int hIndex = 0; hIndex < SPHERE_H_COUNT + 1; hIndex++)
		{
			pIdx[nIndex] = (SPHERE_H_COUNT + 1) + (nIndex / 2) - vIndex;
			pIdx[nIndex + 1] = (nIndex / 2) - vIndex;
			nIndex += 2;
		}
	}
	//頂点バッファのアンロック
	m_pIdxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CSkyBox::Uninit(void)
{
	//もし頂点バッファのポインタがnullptrではない場合
	if (m_pVtxBuff != nullptr)
	{
		//頂点バッファの破棄処理関数呼び出し
		m_pVtxBuff->Release();
		//頂点バッファをnullptrにする
		m_pVtxBuff = nullptr;
	}
	//破棄処理関数
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CSkyBox::Update(void)
{
	//頂点情報を設定
	VERTEX_3D *pVtx;
	WORD * pIdx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	int nIndex = 0;
	int nTexIndex = 0;
	for (int vIndex = 0; vIndex < SPHERE_V_COUNT + 1; vIndex++)
	{
		float fAngleY = vIndex * 180.0f / SPHERE_V_COUNT;
		fAngleY += 90.0f;
		nTexIndex = 0;
		for (int hIndex = 0; hIndex < SPHERE_H_COUNT + 1; hIndex++)
		{
			float fAngle = hIndex * 360.0f / SPHERE_H_COUNT;
			pVtx[nIndex].pos = D3DXVECTOR3(cosf(D3DXToRadian(fAngleY))* (GetSize().y / 2) * sinf(D3DXToRadian(fAngle)),
				sinf(D3DXToRadian(fAngleY)) * (GetSize().y / 2),
				cosf(D3DXToRadian(fAngleY)) * (GetSize().y / 2) * cosf(D3DXToRadian(fAngle)));
			//法線正規化
			D3DXVec3Normalize(&pVtx[nIndex].nor, &GetRotation());
			//法線の設定
			pVtx[nIndex].nor = D3DXVECTOR3(D3DXToRadian(-fAngle) * hIndex, D3DXToRadian(-fAngleY) * vIndex, D3DXToRadian(-fAngle)  *hIndex);
			//頂点カラーの設定
			pVtx[nIndex].col = m_Color;
			//テクスチャ座標の設定
			pVtx[nIndex].tex = D3DXVECTOR2((1.0f / SPHERE_H_COUNT) * (float)nTexIndex, (1.0f / SPHERE_V_COUNT) * (float)vIndex);
			nIndex++;
			nTexIndex++;
		}
	}
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	//インデックスバッファをロックし、頂点情報へのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	nIndex = 0;
	for (int vIndex = 0; vIndex < SPHERE_V_COUNT + 1; vIndex++)
	{
		for (int hIndex = 0; hIndex < SPHERE_H_COUNT + 1; hIndex++)
		{
			pIdx[nIndex] = (SPHERE_H_COUNT + 1) + (nIndex / 2) - vIndex;
			pIdx[nIndex + 1] = (nIndex / 2) - vIndex;
			nIndex += 2;
		}
	}
	//頂点バッファのアンロック
	m_pIdxBuff->Unlock();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CSkyBox::Draw(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	//アルファテストの比較方法の設定（GREATERは基準値より大きい場合)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	ZeroMemory(&matDef, sizeof(matDef));
	//ワールドマトリクス初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	//向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DXToRadian(GetRotation().y), D3DXToRadian(GetRotation().x), D3DXToRadian(GetRotation().z));
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//位置反映
	D3DXMatrixTranslation(&mtxTrans, GetPosition().x, GetPosition().y, GetPosition().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//ワールドマトリクス
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//色セット
	matDef.Ambient = m_Color;
	pDevice->SetMaterial(&matDef);
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャセット
	pDevice->SetTexture(0, m_pTexture);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SPHERE_NUM_VERTEX, 0, SPHERE_NUM_PRIMITIVE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//保持していたマテリアルを元に戻す
	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetMaterial(&matDef);
	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
