//=============================================================================
//
// UI用体力のテクスチャ処理 [ui_life_texture.h]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/scene.h"
#include "Base/scene2d.h"
#include "Base/renderer.h"
#include "Base/manager.h"
#include "ui_life_texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/UI/ui_life.png")	//テクスチャ

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CUILifeTexture::m_pTexture = NULL;	//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CUILifeTexture::CUILifeTexture()
{
	m_pVtxBuff = NULL;							//バッファ
	m_Position = D3DXVECTOR3(0.0f,0.0f,0.0f);	//位置
	m_Size = D3DXVECTOR3(0.0f,0.0f,0.0f);		//サイズ
	m_nPatternAnim = 0;							//アニメパターン
}

//=============================================================================
//デストラクタ
//=============================================================================
CUILifeTexture::~CUILifeTexture()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CUILifeTexture::TextureLoad(void)
{
	//レンダラーの設定
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE,									// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CUILifeTexture::TextureUnload(void)
{
	//もしテクスチャがNULLじゃない場合
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャをNULLにする
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CUILifeTexture * CUILifeTexture::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size)
{
	//体力テクスチャのポインタ
	CUILifeTexture * pUILifeTexture = NULL;
	//もし体力テクスチャのポインタがNULLの場合
	if (pUILifeTexture == NULL)
	{
		//体力テクスチャのメモリ確保
		pUILifeTexture = new CUILifeTexture;
	}
	//もし体力テクスチャのポインタがNULLじゃない場合
	if (pUILifeTexture != NULL)
	{
		//位置を設定する
		pUILifeTexture->SetPosition(Position);
		//サイズを設定する
		pUILifeTexture->SetSize(Size);
		//初期化処理関数呼び出し
		pUILifeTexture->Init();
	}
	//体力テクスチャのポインタを返す
	return pUILifeTexture;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CUILifeTexture::Init(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//頂点情報を設定
	VERTEX_2D *pVtx;
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (m_Size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (m_Size.y / 2), 0.0f);
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//貯点バッファのアンロック
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CUILifeTexture::Uninit(void)
{
	//もし頂点バッファがNULLじゃない場合
	if (m_pVtxBuff != NULL)
	{
		//破棄処理関数呼び出し
		m_pVtxBuff->Release();
		//頂点バッファをNULLにする
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CUILifeTexture::Update(void)
{
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CUILifeTexture::Draw(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスを取得
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
// テクスチャ設定関数
//=============================================================================
void CUILifeTexture::SetLifeTexture(int nAlpha)
{
	//頂点情報を設定
	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//テクスチャ座標の設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nAlpha);
	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 位置設定関数
//=============================================================================
void CUILifeTexture::SetPosition(D3DXVECTOR3 Position)
{
	//位置を設定する
	m_Position = Position;
}

//=============================================================================
// サイズ設定関数
//=============================================================================
void CUILifeTexture::SetSize(D3DXVECTOR3 Size)
{
	//位置を設定する
	m_Size = Size;
}
