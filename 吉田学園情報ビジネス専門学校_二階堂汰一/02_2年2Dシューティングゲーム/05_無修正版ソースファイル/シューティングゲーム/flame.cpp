//=============================================================================
//
// 枠処理 [flame.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "scene.h"
#include "scene2d.h"
#include "score.h"
#include "bullet.h"
#include "flame.h"
#include "sound.h"
#include "explosion.h"
#include "item.h"
#include "player.h"

LPDIRECT3DTEXTURE9 CFlame::m_pTexture = NULL;
//=============================================================================
// コンストラクタ
//=============================================================================
CFlame::CFlame(int nPriority) :CScene2d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //位置
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
		m_col[nCount] = D3DCOLOR_RGBA(0, 0, 0, 255);	//頂点カラー
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CFlame::~CFlame()
{
}

//=============================================================================
// テクスチャのロード関数
//=============================================================================
HRESULT CFlame::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_FLAME1,								// ファイルの名前
		&m_pTexture);									// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// テクスチャのアンロード関数
//=============================================================================
void CFlame::Unload(void)
{
		//テクスチャの破棄
		if (m_pTexture!= NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}

//=============================================================================
// 生成関数
//=============================================================================
CFlame * CFlame::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight)
{
	CFlame * pFlame;
	pFlame = new CFlame;
	pFlame->Init(pos, SizeWidth, SizeHeight);
	return pFlame;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CFlame::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight)
{
	CScene2d::Init(pos, SizeWidth, SizeHeight);

	//オブジェタイプを敵にする
	SetObjType(CScene::OBJTYPE_NONE);
	m_pos = pos;	//位置
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
	}
	//位置の設定
	SetPosition(m_pos);
	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-SizeWidth / 2), m_pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (SizeWidth / 2), m_pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-SizeWidth / 2), m_pos.y + (SizeHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (SizeWidth / 2), m_pos.y + (SizeHeight / 2), 0.0f);
	//頂点座標のセット
	SetVertexPosition(m_vpos);
	//テクスチャの設定
	SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	//色の設定
	SetColor(m_col);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CFlame::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CFlame::Update(void)
{
	CScene2d::Update();
	//位置を取得
	m_pos = GetPosition();
}

//=============================================================================
// 描画関数
//=============================================================================
void CFlame::Draw(void)
{
	CScene2d::Draw();
}