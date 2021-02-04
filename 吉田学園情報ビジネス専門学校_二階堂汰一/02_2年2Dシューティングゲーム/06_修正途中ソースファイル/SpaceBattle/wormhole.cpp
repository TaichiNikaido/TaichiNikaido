//=============================================================================
//
// ワームホール [wormhole.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "mode_game.h"
#include "wormhole.h"
#include "enemy_dragon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WORMHOLE ("Data/Texture/wormhole/wormhole.png")
#define WORMHOLE_EFFECT ("Data/Texture/wormhole/wormhole_effect.png")
#define ADD_SCALE (0.01f)
#define SUB_SCALE (0.01f)
#define WORMHOLE_EFFECT_SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))
#define WORMHOLE_SIZE (D3DXVECTOR3(200.0f,200.0f,0.0f))
#define WORMHOLE_EFFECT_COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))
#define WORMHOLE_COLOR (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CWormhole::m_pTexture[2] = {};	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CWormhole::CWormhole(int nPriority) : CScene(nPriority)
{
	memset(m_pScene2d, NULL, sizeof(m_pScene2d));	//シーン2Dへのポインタ
	m_bSpawn = false;								//スポーンの真偽
}

//=============================================================================
// デストラクタ
//=============================================================================
CWormhole::~CWormhole()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CWormhole::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		WORMHOLE_EFFECT,							// ファイルの名前
		&m_pTexture[TEXTURE_WORMHOLE]);			// 読み込むメモリー

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		WORMHOLE,									// ファイルの名前
		&m_pTexture[TEXTURE_WORMHOLE_EFFECT]);		// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CWormhole::TextureUnload(void)
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CWormhole * CWormhole::Create(D3DXVECTOR3 Position)
{
	CWormhole * pWormhole;
	pWormhole = new CWormhole;
	pWormhole->Init();
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		pWormhole->m_pScene2d[nCount]->SetPosition(Position);
	}
	return pWormhole;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CWormhole::Init(void)
{
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		if (m_pScene2d[nCount] == NULL)
		{
			//シーン2Dのメモリ確保
			m_pScene2d[nCount] = new CScene2d(2);
		}
		//シーン2Dの初期化処理関数呼び出し
		m_pScene2d[nCount]->Init();
	}
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//サイズの初期設定
	m_pScene2d[TEXTURE_WORMHOLE]->SetSize(WORMHOLE_SIZE);
	//色の初期設定
	m_pScene2d[TEXTURE_WORMHOLE]->SetColor(WORMHOLE_COLOR);
	//サイズの初期設定
	m_pScene2d[TEXTURE_WORMHOLE_EFFECT]->SetSize(WORMHOLE_EFFECT_SIZE);
	//色の初期設定
	m_pScene2d[TEXTURE_WORMHOLE_EFFECT]->SetColor(WORMHOLE_EFFECT_COLOR);
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		//テクスチャの設定
		m_pScene2d[nCount]->SetTexture(aTexture);
		//テクスチャの割り当て
		m_pScene2d[nCount]->BindTexture(m_pTexture[nCount]);
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CWormhole::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CWormhole::Update(void)
{
	//拡縮処理関数呼び出し
	Scale();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CWormhole::Draw(void)
{
}

//=============================================================================
// 拡縮処理関数
//=============================================================================
void CWormhole::Scale(void)
{
	D3DXVECTOR3 Rotation;	//回転
	float fScale;			//拡縮
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		//回転
		Rotation = m_pScene2d[nCount]->GetRotation();
		//拡縮
		fScale = m_pScene2d[nCount]->GetScale();
	}
	//回転処理
	Rotation.z -= D3DX_PI * 0.01f;
	if (Rotation.z >= D3DX_PI)
	{
		Rotation.z += D3DX_PI * 2.0f;
	}
	if (fScale <= 2.0f && m_bSpawn == false)
	{
		//拡大する
		fScale += ADD_SCALE;
	}
	else
	{
		//もしスポーンが偽だったら
		if (m_bSpawn == false)
		{
			//スポーン処理関数呼び出し
			Spawn();
		}
	}
	//もしスポーンが新だったら
	if (m_bSpawn == true)
	{
		//縮小する
		fScale -= SUB_SCALE;
		//拡大率が0以下になったら
		if (fScale <= 0.0f)
		{
			//終了処理関数呼び出し
			Uninit();
			return;
		}
	}
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		//回転の設定
		m_pScene2d[nCount]->SetRotation(Rotation);
		//拡縮の設定
		m_pScene2d[nCount]->SetScale(fScale);
	}
}

//=============================================================================
// スポーン処理関数
//=============================================================================
void CWormhole::Spawn(void)
{
	//スポーンを真にする
	m_bSpawn = true;
	//位置を取得
	D3DXVECTOR3 Position = m_pScene2d[TEXTURE_WORMHOLE]->GetPosition();	//位置
	//ドラゴンの生成処理関数呼び出し
	CGameMode::SetDragon(CEnemyDragon::Create(Position));
}
