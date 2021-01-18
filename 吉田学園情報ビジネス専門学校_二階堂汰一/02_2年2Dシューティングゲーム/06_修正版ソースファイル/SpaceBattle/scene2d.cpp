//=============================================================================
//
// 2Dシーン管理処理 [scene2d.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CScene2d::CScene2d(int nPriority)
{
	m_pTexture = NULL;										//テクスチャへのポインタ
	m_pVtxBuff = NULL;										//頂点バッファへのポインタ
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//座標
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//サイズ
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			//カラー
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
	memset(m_aVtxPosition, NULL, sizeof(m_aVtxPosition));	//頂点座標
	memset(m_aTexture, NULL, sizeof(m_aTexture));			//テクスチャのUV座標
	m_fScale = 1.0f;										//縮尺
	m_fAngle = 0.0f;										//角度
	m_fLength = 0.0f;										//長さ
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene2d::~CScene2d()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CScene2d::Init(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//長さの設定
	m_fLength = sqrtf((float)(((m_Size.x / 2) * (m_Size.x / 2)) + ((m_Size.y / 2) * (m_Size.y / 2))));

	//角度の設定
	m_fAngle = atan2f((m_Size.y / 2), (m_Size.x / 2));

	//頂点座標の設定
	pVtx[0].pos.x = m_Position.x - cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_Position.y - sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_Position.x + cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_Position.y - sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_Position.x - cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_Position.y + sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_Position.x + cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_Position.y + sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;

	// テクスチャ座標の設定
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
void CScene2d::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CScene2d::Update(void)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//長さの設定
	m_fLength = sqrtf((float)(((m_Size.x / 2) * (m_Size.x / 2)) + ((m_Size.y / 2) * (m_Size.y / 2))));

	//角度の設定
	m_fAngle = atan2f((m_Size.y / 2), (m_Size.x / 2));

	//頂点座標の設定
	pVtx[0].pos.x = m_Position.x - cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.y = m_Position.y - sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_Position.x + cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.y = m_Position.y - sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_Position.x - cosf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.y = m_Position.y + sinf(m_fAngle + m_Rotation.z) * m_fLength * m_fScale;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_Position.x + cosf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.y = m_Position.y + sinf(m_fAngle - m_Rotation.z) * m_fLength * m_fScale;
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;

	// テクスチャ座標の設定
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
void CScene2d::Draw(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 座標設定関数
//=============================================================================
void CScene2d::SetPosition(D3DXVECTOR3 Pos)
{
	//座標の割り当て
	m_Position = Pos;
}

//=============================================================================
// 向き設定関数
//=============================================================================
void CScene2d::SetRotation(D3DXVECTOR3 Rot)
{
	//向きの割り当て
	m_Rotation = Rot;
}

//=============================================================================
// サイズ設定関数
//=============================================================================
void CScene2d::SetSize(D3DXVECTOR3 Size)
{
	//サイズの割り当て
	m_Size = Size;
}

//=============================================================================
// 縮尺設定関数
//=============================================================================
void CScene2d::SetScale(float fScale)
{
	//縮尺の割り当て
	m_fScale = fScale;
}

//=============================================================================
// 頂点カラー設定関数
//=============================================================================
void CScene2d::SetColor(D3DXCOLOR Color)
{
	//色の設定をする
	m_Color = Color;
}

//=============================================================================
// 頂点座標設定関数
//=============================================================================
void CScene2d::SetVertexPosition(D3DXVECTOR3 VtxPos[NUM_VERTEX])
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//テクスチャのUV座標割り当て
		m_aVtxPosition[nCount] = VtxPos[nCount];
	}
}

//=============================================================================
// テクスチャのUV座標設定関数
//=============================================================================
void CScene2d::SetTexture(D3DXVECTOR2 aTex[NUM_VERTEX])
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//テクスチャのUV座標の割り当て
		m_aTexture[nCount] = aTex[nCount];
	}
}

//=============================================================================
// テクスチャの割り当て関数
//=============================================================================
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//テクスチャの割り当て
	m_pTexture = pTexture;
}
























////=============================================================================
////
//// ポリゴン処理 [scene2d.cpp]
//// Author : 二階堂汰一
////
////=============================================================================
//
////*****************************************************************************
//// ヘッダファイルのインクルード
////*****************************************************************************
//#include "main.h"
//#include "scene.h"
//#include "scene2d.h"
//#include "renderer.h"
//#include "manager.h"
//#include "keyboard.h"
//
////=============================================================================
//// コンストラクタ
//
////=============================================================================
//CScene2d::CScene2d(int nPriority) :CScene(nPriority)
//{
//	m_pTexture = NULL;
//	m_pVtxBuff = NULL;
//	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//	{
//		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		m_col[nCount] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
//	}
//	m_fSizeX = 0.0f;
//	m_fSizeY = 0.0f;
//	m_fTexAnim = 0.0f;
//}
//
////=============================================================================
////デストラクタ
////=============================================================================
//CScene2d::~CScene2d()
//{
//}
//
////=============================================================================
//// 初期化関数
////=============================================================================
//HRESULT CScene2d::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
//{
//	CRenderer *pRenderer = CManager::GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	// 頂点情報を設定
//	VERTEX_2D *pVtx;
//
//	// 頂点バッファの生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
//
//	// ポリゴンの位置を設定
//	//m_Position = D3DXVECTOR3((float)FIELD_WIDTH / 2, FIELD_HEIGHT / 2, 0.0f);
//
//	m_fSizeX = SizeWidth;
//	m_fSizeY = SizeHeight;
//	m_Position = pos;
//	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//	{
//		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		m_col[nCount] = D3DXCOLOR(255, 255, 255, 255);
//	}
//	// 頂点バッファをロックし、頂点情報へのポインタを取得
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	//pVtx[0].pos = D3DXVECTOR3(m_Position.x + (-m_fSizeX / 2), m_Position.y + (-m_fSizeY / 2), 0.0f);
//	//pVtx[1].pos = D3DXVECTOR3(m_Position.x + (m_fSizeX / 2), m_Position.y + (-m_fSizeY / 2), 0.0f);
//	//pVtx[2].pos = D3DXVECTOR3(m_Position.x + (-m_fSizeX / 2), m_Position.y + (m_fSizeY / 2), 0.0f);
//	//pVtx[3].pos = D3DXVECTOR3(m_Position.x + (m_fSizeX / 2), m_Position.y + (m_fSizeY / 2), 0.0f);
//
//	pVtx[0].pos = m_vpos[0];
//	pVtx[1].pos = m_vpos[1];
//	pVtx[2].pos = m_vpos[2];
//	pVtx[3].pos = m_vpos[3];
//
//	// rhwの設定
//	pVtx[0].rhw = 1.0f;
//	pVtx[1].rhw = 1.0f;
//	pVtx[2].rhw = 1.0f;
//	pVtx[3].rhw = 1.0f;
//
//	// 頂点カラーの設定
//	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//	// テクスチャ座標の設定
//	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
//	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
//	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
//	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);
//
//	m_pVtxBuff->Unlock();
//
//	CScene::SetPosition(pos);
//	return S_OK;
//}
//
////=============================================================================
//// 終了関数
////=============================================================================
//void CScene2d::Uninit(void)
//{
//	// 頂点バッファの破棄
//	if (m_pVtxBuff != NULL)
//	{
//		m_pVtxBuff->Release();
//		m_pVtxBuff = NULL;
//	}
//	Release();
//}
//
////=============================================================================
//// 更新関数
////=============================================================================
//void CScene2d::Update(void)
//{
//	CRenderer *pRenderer = CManager::GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	// 頂点情報を設定
//	VERTEX_2D *pVtx;
//
//	// 頂点バッファをロックし、頂点情報へのポインタを取得
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	//D3DXVECTOR3 pos = GetPosition();
//
//	//pVtx[0].pos = D3DXVECTOR3(m_Position.x + (-m_fSizeX / 2), m_Position.y + (-m_fSizeY / 2), 0.0f);
//	//pVtx[1].pos = D3DXVECTOR3(m_Position.x + (m_fSizeX / 2), m_Position.y + (-m_fSizeY / 2), 0.0f);
//	//pVtx[2].pos = D3DXVECTOR3(m_Position.x + (-m_fSizeX / 2), m_Position.y + (m_fSizeY / 2), 0.0f);
//	//pVtx[3].pos = D3DXVECTOR3(m_Position.x + (m_fSizeX / 2), m_Position.y + (m_fSizeY / 2), 0.0f);7
//
//	pVtx[0].pos = m_vpos[0];
//	pVtx[1].pos = m_vpos[1];
//	pVtx[2].pos = m_vpos[2];
//	pVtx[3].pos = m_vpos[3];
//
//	pVtx[0].rhw = 1.0f;
//	pVtx[1].rhw = 1.0f;
//	pVtx[2].rhw = 1.0f;
//	pVtx[3].rhw = 1.0f;
//
//	pVtx[0].col = m_col[0];
//	pVtx[1].col = m_col[1];
//	pVtx[2].col = m_col[2];
//	pVtx[3].col = m_col[3];
//
//	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
//	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
//	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
//	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);
//
//	//SetPosition(pos);
//	// 頂点バッファをアンロックする
//	m_pVtxBuff->Unlock();
//	CScene::SetPosition(m_Position);
//}
//
////=============================================================================
//// 描画関数
////=============================================================================
//void CScene2d::Draw(void)
//{
//	CRenderer *pRenderer = CManager::GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//	// 頂点バッファをデータストリームに設定
//	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
//
//	// 頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	// テクスチャの設定
//	pDevice->SetTexture(0, m_pTexture);
//
//	// ポリゴンの描画
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
//}
//
//void CScene2d::SetPosition(D3DXVECTOR3 pos)
//{
//	m_Position = pos;
//}
//
//void CScene2d::SetVertexPosition(D3DXVECTOR3 vpos[NUM_VERTEX])
//{
//	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//	{
//		m_vpos[nCount] = vpos[nCount];
//	}
//}
//
//void CScene2d::SetTex(float fTexX, float fTexY, float fTexX2, float fTexY2)
//{
//	m_fTexX = fTexX;
//	m_fTexY = fTexY;
//	m_fTexX2 = fTexX2;
//	m_fTexY2 = fTexY2;
//}
//
//void CScene2d::SetColor(D3DCOLOR col[NUM_VERTEX])
//{
//	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
//	{
//		m_col[nCount] = col[nCount];
//	}
//}
//
//D3DXVECTOR3 CScene2d::GetPosition(void)
//{
//	return m_Position;
//}
//
//CScene2d * CScene2d::Create(D3DXVECTOR3 pos)
//{
//	CScene2d * pScene2d;
//	pScene2d = new CScene2d;
//	pScene2d->SetPosition(pos);
//	pScene2d->Init(pos, 50.0f, 50.0f);
//	return pScene2d;
//}
//
//void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
//{
//	//テクスチャの割り当て
//	m_pTexture = pTexture;
//}
