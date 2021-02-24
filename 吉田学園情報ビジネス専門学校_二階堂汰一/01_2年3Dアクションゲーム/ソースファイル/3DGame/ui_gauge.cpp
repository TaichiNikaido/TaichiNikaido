//=============================================================================
//
// UIのゲージ [ui_gauge.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// 警告制御
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ui_gauge.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/UI/Gauge.png")		//テクスチャのパス
#define SCRIPT_PASS ("Data/Script/Floor/Data.txt")		//プレイヤーデータのスクリプトのパス
#define INITIAL_POSITION (D3DXVECTOR3(0.0f,0.0f,0.0f))	//位置の初期値
#define INITIAL_SIZE (D3DXVECTOR3(0.0f,0.0f,0.0f))		//サイズ
#define INITIAL_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	//色
#define INITIAL_VALUE (0)								//値の初期値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGauge::m_pTexture = NULL;	//テクスチャ

//=============================================================================
// コンストラクタ
//=============================================================================
CGauge::CGauge()
{
	m_pVtxBuff = NULL;					//頂点バッファのポインタ
	m_Position = INITIAL_POSITION;		//位置
	m_Size = INITIAL_SIZE;				//サイズ
	m_Color = INITIAL_COLOR;			//色
	m_nMaxValue = INITIAL_VALUE;		//値の最大値
	m_nValue = INITIAL_VALUE;			//値
}

//=============================================================================
// デストラクタ
//=============================================================================
CGauge::~CGauge()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CGauge::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_PASS,					// ファイルの名前
		&m_pTexture);					// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CGauge::TextureUnload(void)
{
	// テクスチャの破棄
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
CGauge * CGauge::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size, D3DXCOLOR Color)
{
	//ゲージのポインタ
	CGauge * pGauge = NULL;
	//ゲージのポインタがNULLの場合
	if (pGauge == NULL)
	{
		//ゲージのメモリ確保
		pGauge = new CGauge;
	}
	//ゲージのポインタがNULLじゃない場合
	if (pGauge != NULL)
	{
		//位置を設定する
		pGauge->SetPosition(Position);
		//サイズを設定する
		pGauge->SetSize(Size);
		//色を設定する
		pGauge->SetColor(Color);
		//ゲージの初期化処理関数呼び出し
		pGauge->Init();
	}
	//ゲージのポインタを返す
	return pGauge;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CGauge::Init(void)
{
	//レンダラーの取得
	CRenderer * pRenderer = CManager::GetRenderer();
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}
	//頂点情報のポインタ
	VERTEX_2D *pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (-m_Size.x / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (-m_Size.x / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Position.x + (-m_Size.x / 2), m_Position.y + (m_Size.x / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Position.x + (m_Size.x / 2), m_Position.y + (m_Size.x / 2), 0.0f);
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
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
void CGauge::Uninit(void)
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
void CGauge::Update(void)
{
	//頂点情報のポインタ
	VERTEX_2D *pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点座標を設定
	pVtx[0].pos = D3DXVECTOR3(m_Position.x, m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Position.x + m_Size.x * (m_nValue / m_nMaxValue), m_Position.y + (-m_Size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Position.x, m_Position.y + (m_Size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Position.x + m_Size.x * (m_nValue / m_nMaxValue), m_Position.y + (m_Size.y / 2), 0.0f);
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGauge::Draw(void)
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
