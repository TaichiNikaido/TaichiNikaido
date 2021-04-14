//=============================================================================
//
// UI用数字処理 [ui_number_texture.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/scene.h"
#include "ui_number_texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/UI/ui_number.png")	//テクスチャ

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CUINumberTexture::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CUINumberTexture::CUINumberTexture()
{
	m_pVtxBuff = NULL;							//バッファへのポインタ
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//サイズ
}

//=============================================================================
// デストラクタ
//=============================================================================
CUINumberTexture::~CUINumberTexture()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CUINumberTexture::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE,							// ファイルの名前
		&m_pTexture);						// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CUINumberTexture::TextureUnload(void)
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
CUINumberTexture * CUINumberTexture::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size)
{
	//番号のテクスチャのポインタ
	CUINumberTexture * pUINumberTexture = NULL;
	//もし番号のテクスチャのポインタがNULLの場合
	if (pUINumberTexture == NULL)
	{
		//番号のテクスチャのメモリ確保
		pUINumberTexture = new CUINumberTexture;
	}
	//もし番号のテクスチャのポインタがNULLじゃない場合
	if (pUINumberTexture != NULL)
	{
		//位置を設定する
		pUINumberTexture->SetPostion(Position);
		//サイズを取得する
		pUINumberTexture->SetSize(Size);
		//初期化処理関数呼び出し
		pUINumberTexture->Init();
	}
	//番号のテクスチャのポインタを返す
	return pUINumberTexture;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CUINumberTexture::Init(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}
	//頂点情報を設定
	VERTEX_2D *pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CUINumberTexture::Uninit(void)
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
void CUINumberTexture::Update(void)
{
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CUINumberTexture::Draw(void)
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
// 数字割り当て処理関数
//=============================================================================
void CUINumberTexture::SetNumber(int nNumber)
{
	//頂点情報
	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 位置設定処理関数
//=============================================================================
void CUINumberTexture::SetPostion(D3DXVECTOR3 Position)
{
	//位置の設定
	m_Position = Position;
}

//=============================================================================
// サイズ設定処理関数
//=============================================================================
void CUINumberTexture::SetSize(D3DXVECTOR3 Size)
{
	//サイズの設定
	m_Size = Size;
}
