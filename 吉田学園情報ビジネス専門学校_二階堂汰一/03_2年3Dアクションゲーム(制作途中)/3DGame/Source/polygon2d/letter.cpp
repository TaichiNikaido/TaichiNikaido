//=============================================================================
//
// 文字 [letter.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "letter.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/letter.png")	//テクスチャのパス
#define SIZE (D3DXVECTOR3(125.0f,125.0f,0.0f))		//サイズ
#define SELECT_ALPHA (0.5f)							//選択時のα値
#define NOT_SELECT_ALPHA (1.0f)						//無選択時のα値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLetter::m_pTexture = nullptr;		//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CLetter::CLetter()
{
	m_pVtxBuff = nullptr;							//バッファへのポインタ
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//サイズ
	m_fAlpha = 0.0f;								//透明度
}

//=============================================================================
// デストラクタ
//=============================================================================
CLetter::~CLetter()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CLetter::TextureLoad(void)
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
void CLetter::TextureUnload(void)
{
	//もしテクスチャがnullptrではない場合
	if (m_pTexture != nullptr)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャをnullptrにする
		m_pTexture = nullptr;
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CLetter * CLetter::Create(D3DXVECTOR3 Position)
{
	//番号のテクスチャのポインタ
	CLetter * pLetter = nullptr;
	//もし番号のテクスチャのポインタがNULLの場合
	if (pLetter == nullptr)
	{
		//番号のテクスチャのメモリ確保
		pLetter = new CLetter;
		//もし番号のテクスチャのポインタがnullptrではない場合
		if (pLetter != nullptr)
		{
			//位置を設定する
			pLetter->SetPostion(Position);
			//サイズを設定する
			pLetter->SetSize(SIZE);
			//初期化処理関数呼び出し
			pLetter->Init();
		}
	}
	//番号のテクスチャのポインタを返す
	return pLetter;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CLetter::Init(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	//頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			//頂点バッファの使用法　
		FVF_VERTEX_2D,				//使用する頂点フォーマット
		D3DPOOL_MANAGED,			//リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				//頂点バッファへのポインタ
		NULL)))						//NULLに設定
	{
		return E_FAIL;
	}
	//頂点情報を設定
	VERTEX_2D *pVtx;
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
	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2((1.0f / 26.0f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / 26.0f) + (1.0f / 26.0f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / 26.0f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / 26.0f) + (1.0f / 26.0f), 1.0f);
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CLetter::Uninit(void)
{
	//もし頂点バッファのポインタがnullptrではない場合
	if (m_pVtxBuff != nullptr)
	{
		//頂点バッファの破棄処理関数呼び出し
		m_pVtxBuff->Release();
		//頂点バッファのポインタをnullptrにする
		m_pVtxBuff = nullptr;
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CLetter::Update(void)
{
	//頂点情報を設定
	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CLetter::Draw(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスにレンダラーのデバイスを代入
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 選択時色変更処理関数
//=============================================================================
void CLetter::SelectColor(void)
{
	//α値を設定する
	m_fAlpha = SELECT_ALPHA;
}

//=============================================================================
// 無選択時色変更処理関数
//=============================================================================
void CLetter::NotSelectColor(void)
{
	//α値を設定する
	m_fAlpha = NOT_SELECT_ALPHA;
}

//=============================================================================
// 数字割り当て処理関数
//=============================================================================
void CLetter::SetLetter(int nLetter)
{
	//頂点情報
	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	if (nLetter != -1)//-1じゃなければ不透明に
	{
		//透明度を設定する
		m_fAlpha = 1.0f;
		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(nLetter * (1.0f / 26.0f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nLetter * (1.0f / 26.0f) + (1.0f / 26.0f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nLetter * (1.0f / 26.0f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nLetter * (1.0f / 26.0f) + (1.0f / 26.0f), 1.0f);
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
	}
	else
	{
		//透明度を設定する
		m_fAlpha = 0.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha);
	}
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
