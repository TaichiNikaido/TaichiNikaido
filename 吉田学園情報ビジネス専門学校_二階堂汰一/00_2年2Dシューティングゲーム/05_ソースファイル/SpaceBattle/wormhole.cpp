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
#include "sound.h"
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
#define MAX_SCALE (2.0f)
#define MINIMUM_SCALE (0.0f)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CWormhole::m_apTexture[2] = {};	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CWormhole::CWormhole(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2d, NULL, sizeof(m_apScene2d));	//シーン2Dへのポインタ
	m_bSpawn = false;								//スポーンしたか
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
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		WORMHOLE_EFFECT,							// ファイルの名前
		&m_apTexture[TEXTURE_WORMHOLE]);				// 読み込むメモリー
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		WORMHOLE,									// ファイルの名前
		&m_apTexture[TEXTURE_WORMHOLE_EFFECT]);		// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CWormhole::TextureUnload(void)
{
	//最大テクスチャ数分回す
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		//もしテクスチャがNULLじゃない場合
		if (m_apTexture[nCount] != NULL)
		{
			//テクスチャの破棄処理関数呼び出し
			m_apTexture[nCount]->Release();
			//テクスチャをNULLにする
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CWormhole * CWormhole::Create(D3DXVECTOR3 Position)
{
	//ワームホールのポインタ
	CWormhole * pWormhole = NULL;
	//もしワームホールがNULLの場合
	if (pWormhole == NULL)
	{
		//ワームホールのメモリ確保
		pWormhole = new CWormhole;
	}
	//もしワームホールがNULLじゃない場合
	if (pWormhole != NULL)
	{
		//初期化処理関数呼び出し
		pWormhole->Init();
		//テクスチャの最大数分回す
		for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
		{
			//位置を設定する
			pWormhole->m_apScene2d[nCount]->SetPosition(Position);
		}
	}
	//ワームホールのポインタを返す
	return pWormhole;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CWormhole::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//テクスチャの最大数分回す
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		//もしシーン2DがNULLの場合
		if (m_apScene2d[nCount] == NULL)
		{
			//シーン2Dのメモリ確保
			m_apScene2d[nCount] = new CScene2d(2);
		}
		//シーン2Dの初期化処理関数呼び出し
		m_apScene2d[nCount]->Init();
	}
	//サイズの初期設定
	m_apScene2d[TEXTURE_WORMHOLE]->SetSize(WORMHOLE_SIZE);
	//色の初期設定
	m_apScene2d[TEXTURE_WORMHOLE]->SetColor(WORMHOLE_COLOR);
	//サイズの初期設定
	m_apScene2d[TEXTURE_WORMHOLE_EFFECT]->SetSize(WORMHOLE_EFFECT_SIZE);
	//色の初期設定
	m_apScene2d[TEXTURE_WORMHOLE_EFFECT]->SetColor(WORMHOLE_EFFECT_COLOR);
	//テクスチャの最大数分回す
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		//テクスチャの設定
		m_apScene2d[nCount]->SetTexture(aTexture);
		//テクスチャの割り当て
		m_apScene2d[nCount]->BindTexture(m_apTexture[nCount]);
	}
	//もしサウンドがNULLじゃない場合
	if (pSound != NULL)
	{
		//サウンドの停止
		pSound->StopSound();
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
	//テクスチャの最大数分回す
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		//回転を取得する
		Rotation = m_apScene2d[nCount]->GetRotation();
		//拡縮を取得する
		fScale = m_apScene2d[nCount]->GetScale();
	}
	//回転処理
	Rotation.z -= D3DX_PI * 0.01f;
	//もし回転が円周率を越えたら
	if (Rotation.z >= D3DX_PI)
	{
		//回転を代入する
		Rotation.z += D3DX_PI * 2.0f;
	}
	//もし拡縮が最大になりかつスポーンしていない場合
	if (fScale <= MAX_SCALE && m_bSpawn == false)
	{
		//拡大する
		fScale += ADD_SCALE;
	}
	else
	{
		//もしスポーンしていなかったら
		if (m_bSpawn == false)
		{
			//スポーン処理関数呼び出し
			Spawn();
		}
	}
	//もしスポーンしたら
	if (m_bSpawn == true)
	{
		//縮小する
		fScale -= SUB_SCALE;
		//拡大率が0以下になったら
		if (fScale <= MINIMUM_SCALE)
		{
			//終了処理関数呼び出し
			Uninit();
			return;
		}
	}
	//テクスチャの最大数分回す
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{
		//回転の設定
		m_apScene2d[nCount]->SetRotation(Rotation);
		//拡縮の設定
		m_apScene2d[nCount]->SetScale(fScale);
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
	D3DXVECTOR3 Position = m_apScene2d[TEXTURE_WORMHOLE]->GetPosition();
	//ドラゴンの生成処理関数呼び出し
	CGameMode::SetDragon(CEnemyDragon::Create(Position));
}
