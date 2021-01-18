//=============================================================================
//
//	危険地帯処理 [warning.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "warning.h"

LPDIRECT3DTEXTURE9 CWarning::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CWarning::CWarning()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	m_fWidth = 0;		//幅
	m_fHeight = 0;		//高さ
	m_nColCount = 0;
	m_nCount = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CWarning::~CWarning()
{
}

//=============================================================================
// テクスチャロード関数
//=============================================================================
HRESULT CWarning::Load(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_WARNING,								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャアンロード関数
//=============================================================================
void CWarning::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成関数
//=============================================================================
CWarning * CWarning::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight)
{
	CWarning * pWarning;
	pWarning = new CWarning;
	pWarning->SetPosition(pos);
	pWarning->Init(pos,move, SizeWidth, SizeHeight);

	return pWarning;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CWarning::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight)
{
	CScene2d::Init(pos, SizeWidth, SizeHeight);

	m_pos = pos;
	m_move = move;
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点座標
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	m_fWidth = SizeWidth;	//幅
	m_fHeight = SizeHeight; //高さ
	m_nColCount = 0;
	m_nCount = 0;
	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(pos.x + (-SizeWidth / 2), pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(pos.x + (SizeWidth / 2), pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(pos.x + (-SizeWidth / 2), pos.y + (SizeHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(pos.x + (SizeWidth / 2), pos.y + (SizeHeight / 2), 0.0f);

	//頂点座標のセット
	SetVertexPosition(m_vpos);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	SetTex(
		0.0f, 0.0f, 1.0f, 1.0f
	);
	//色のセット
	SetColor(m_col);
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CWarning::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// 爆発更新関数
//=============================================================================
void CWarning::Update(void)
{
	//更新
	CScene2d::Update();
	//位置の取得
	D3DXVECTOR3 pos = GetPosition();

	for (int nCountPriority = 1; nCountPriority < 5; nCountPriority++)
	{
		for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
		{
			CScene * pScene = GetScene(nCountPriority, nCountScene);

			if (pScene != NULL)
			{
				//オブジェタイプの取得
				OBJTYPE objType;
				objType = pScene->GetObjType();
				//敵の位置を取得
				D3DXVECTOR3 target_pos;
				target_pos = pScene->GetPosition();

				if (objType == OBJTYPE_FIREBALL)
				{
					m_pos.x = target_pos.x;
					//m_move.x = 1.0f;
				}

				if (objType == OBJTYPE_PLAYER)
				{
					m_pos.y = target_pos.y;
				}
			}
		}
	}

	//位置更新
	//m_pos.x += m_move.x;
	//m_pos.y += m_move.y;

	if (m_nCount % 10 == 0)
	{
		if (m_nColCount % 2 == 0)
		{
			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
			{
				m_col[nCount] = D3DCOLOR_RGBA(255, 255, 0, 255);
			}
		}
		else
		{
			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
			{
				m_col[nCount] = D3DCOLOR_RGBA(255, 0, 0, 255);
			}
		}
		m_nColCount++;
	}

	m_nCount++;

	if (CBullet::GetbFireBall() == false)
	{
		Uninit();
		return;
	}

	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(pos.x + (-m_fWidth / 2), pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(pos.x + (m_fWidth / 2), pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(pos.x + (-m_fWidth / 2), pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(pos.x + (m_fWidth / 2), pos.y + (m_fHeight / 2), 0.0f);
	//現在位置のセット
	SetPosition(m_pos);
	//頂点座標の設定
	SetVertexPosition(m_vpos);

	SetTex(
		0.0f, 0.0f, 1.0f, 1.0f
	);
	//色のセット
	SetColor(m_col);
}


//=============================================================================
// 描画関数
//=============================================================================
void CWarning::Draw(void)
{
	CScene2d::Draw();
}