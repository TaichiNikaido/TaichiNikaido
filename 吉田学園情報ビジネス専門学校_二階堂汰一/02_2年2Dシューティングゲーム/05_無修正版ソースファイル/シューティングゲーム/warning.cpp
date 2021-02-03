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

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CWarning::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CWarning::CWarning()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//頂点座標
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);	//頂点カラー
	}
	m_fWidth = 0;		//幅
	m_fHeight = 0;		//高さ
	m_nColCount = 0;	//色変更カウント
	m_nCount = 0;		//カウント
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

	m_pos = pos;	//位置
	m_move = move;	//移動量
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//頂点座標
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);	//色
	}
	m_fWidth = SizeWidth;	//幅
	m_fHeight = SizeHeight; //高さ
	m_nColCount = 0;		//色変更カウント
	m_nCount = 0;			//カウント
	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(pos.x + (-SizeWidth / 2), pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(pos.x + (SizeWidth / 2), pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(pos.x + (-SizeWidth / 2), pos.y + (SizeHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(pos.x + (SizeWidth / 2), pos.y + (SizeHeight / 2), 0.0f);
	//頂点座標のセット
	SetVertexPosition(m_vpos);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	//テクスチャの設定
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
				//オブジェクトタイプを取得
				objType = pScene->GetObjType();
				//目標の位置を取得
				D3DXVECTOR3 target_pos = pScene->GetPosition();
				//もしオブジェクトタイプが火球だったら
				if (objType == OBJTYPE_FIREBALL)
				{
					m_pos.x = target_pos.x;
				}
				//もしオブジェタイプがプレイヤーだったら
				if (objType == OBJTYPE_PLAYER)
				{
					m_pos.y = target_pos.y;
				}
			}
		}
	}
	//色変更処理関数呼び出し
	ColorChange();
	//もし火球が偽になったら
	if (CBullet::GetbFireBall() == false)
	{
		//終了処理関数呼び出し
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
	//テクスチャの設定
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

//=============================================================================
// 色変更処理関数関数
//=============================================================================
void CWarning::ColorChange(void)
{
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
}
