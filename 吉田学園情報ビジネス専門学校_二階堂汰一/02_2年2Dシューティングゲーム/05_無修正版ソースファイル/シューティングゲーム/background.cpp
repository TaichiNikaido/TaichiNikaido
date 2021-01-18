//=============================================================================
//
// 背景処理 [background.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "background.h"
#include "renderer.h"
#include "manager.h"

LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG_TEXTURE] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CBg::CBg(int nPriority) : CScene(nPriority)
{
	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		m_apScene[nCount] = NULL;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
	}
	m_fTextureX = 0.0f;	//テクスチャのX
	m_fTextureY = 0.0f;	//テクスチャのY
	m_fFastMove = 0.0f;	//早い移動量
	m_fSlowMove = 0.0f;	//遅い移動量
	m_fMove = 0.0f;		//移動量
	m_fWidth = 0.0f;	//幅
	m_fHeight = 0.0f;	//高さ
}

//=============================================================================
// デストラクタ
//=============================================================================
CBg::~CBg()
{
}

//=============================================================================
// テクスチャロード関数
//=============================================================================
HRESULT CBg::Load(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_BG1,								// ファイルの名前
		&m_apTexture[0]);								// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_BG2,								// ファイルの名前
		&m_apTexture[1]);								// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_BG3,								// ファイルの名前
		&m_apTexture[2]);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャアンロード関数
//=============================================================================
void CBg::Unload(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// 生成関数
//=============================================================================
CBg * CBg::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight)
{
	CBg * pBg;
	pBg = new CBg;
	pBg->Init(pos,SizeWidth,SizeHeight);
	//pBg->SetPosition(pos);
	return pBg;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CBg::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight)
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_pos = pos;			//位置
	m_fWidth = SizeWidth;	//幅
	m_fHeight = SizeHeight;	//高さ

	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		m_apScene[nCount] = new CScene2d;
		m_apScene[nCount]->Init(pos, SizeWidth, SizeHeight);
		//頂点座標のセット
		m_apScene[nCount]->SetVertexPosition(m_vpos);
		//テクスチャをセット
		m_apScene[nCount]->SetTex(
			m_fTextureX,
			1.0f,
			m_fTextureY - m_fMove, 
			1.0f);
		//テクスチャの割り当て
		m_apScene[nCount]->BindTexture(m_apTexture[nCount]);
	}
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CBg::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CBg::Update(void)
{
	//移動量に加算
	m_fMove += 0.0001f;
	//早い移動量に加算
	m_fFastMove += 0.001f;
	//遅い移動量に加算
	m_fSlowMove += 0.0001f;

	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		m_apScene[nCount]->Update();
		//頂点座標をセット
		m_apScene[nCount]->SetVertexPosition(m_vpos);
	}
	//テクスチャをセット
	m_apScene[0]->SetTex(
		m_fTextureX,
		m_fMove,
		1.0f,
		m_fMove - 1.0f);

	m_apScene[1]->SetTex(
		m_fTextureX,
		m_fSlowMove,
		1.0f,
		m_fSlowMove -1.0f);

	m_apScene[2]->SetTex(
		m_fTextureX,
		m_fFastMove,
		1.0f,
		m_fFastMove - 1.0f);

	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
}

//=============================================================================
// 描画関数
//=============================================================================
void CBg::Draw(void)
{
}
