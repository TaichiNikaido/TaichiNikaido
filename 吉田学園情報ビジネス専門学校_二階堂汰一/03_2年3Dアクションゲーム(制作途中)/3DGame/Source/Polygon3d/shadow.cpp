//=============================================================================
//
// 影 [shadow.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/Manager.h"
#include "Base/Renderer.h"
#include "Polygon3d/shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INITIAL_SCALE (1.0f)	//拡縮の初期値
#define INITIAL_ANGLE (0.0f)	//角度の初期値
#define INITIAL_LENGTH (0.0f)	//長さの初期値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CShadow::CShadow()
{
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));	//ワールドマトリクス
	m_pVtxBuff = nullptr;							//頂点バッファへのポインタ
	//テクスチャ座標
	m_aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	m_aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	m_aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	m_aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	m_Position = INITIAL_D3DXVECTOR3;				//位置
	m_Rotation = INITIAL_D3DXVECTOR3;				//回転
	m_Size = INITIAL_D3DXVECTOR3;					//サイズ
	m_Color = INITIAL_D3DXCOLOR;					//頂点カラー
	m_fScale = INITIAL_SCALE;						//縮尺
	m_fAngle = INITIAL_ANGLE;						//角度
	m_fLength = INITIAL_LENGTH;						//長さ
}

//=============================================================================
// デストラクタ
//=============================================================================
CShadow::~CShadow()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CShadow::Init(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, nullptr);
	//頂点情報を設定
	VERTEX_3D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//長さの設定
	m_fLength = sqrtf((float)(((m_Size.x / 2) * (m_Size.x / 2)) + ((m_Size.y / 2) * (m_Size.y / 2))));
	//角度の設定
	m_fAngle = atan2f((m_Size.y / 2), (m_Size.x / 2));
	//頂点座標の設定
	pVtx[0].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;
	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);
	//頂点カラーの設定
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//テクスチャ座標の設定
	pVtx[0].tex = m_aTexture[0];
	pVtx[1].tex = m_aTexture[1];
	pVtx[2].tex = m_aTexture[2];
	pVtx[3].tex = m_aTexture[3];
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CShadow::Uninit(void)
{
	//もし頂点バッファのポインタがnullptrじゃない場合
	if (m_pVtxBuff != nullptr)
	{
		//頂点バッファを破棄する
		m_pVtxBuff->Release();
		//頂点バッファのポインタをnullptrにする
		m_pVtxBuff = nullptr;
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CShadow::Update(void)
{
	// 頂点情報を設定
	VERTEX_3D *pVtx;
	//長さの設定
	m_fLength = sqrtf((float)(((m_Size.x / 2) * (m_Size.x / 2)) + ((m_Size.y / 2) * (m_Size.y / 2))));
	//角度の設定
	m_fAngle = atan2f((m_Size.y / 2), (m_Size.x / 2));
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.y = -sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = +cosf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.y = +sinf(m_fAngle) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;
	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);
	//頂点カラーの設定
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	//テクスチャ座標の設定
	pVtx[0].tex = m_aTexture[0];
	pVtx[1].tex = m_aTexture[1];
	pVtx[2].tex = m_aTexture[2];
	pVtx[3].tex = m_aTexture[3];
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CShadow::Draw(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixTranslation(&mtxTrans, m_Position.x, m_Position.y, m_Position.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// テクスチャのUV座標設定関数
//=============================================================================
void CShadow::SetTexture(D3DXVECTOR2 aTexture[NUM_VERTEX])
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//テクスチャのUV座標の割り当て
		m_aTexture[nCount] = aTexture[nCount];
	}
}