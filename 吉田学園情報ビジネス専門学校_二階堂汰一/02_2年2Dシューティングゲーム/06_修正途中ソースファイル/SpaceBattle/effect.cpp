//=============================================================================
//
// エフェクト [effect.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/Bullet/Bullet.png")
#define SCALE (1.0f)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CEffect::CEffect(int nPriority)
{
	m_fScale = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEffect::~CEffect()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CEffect::TextureLoad(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
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
void CEffect::TextureUnload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CEffect * CEffect::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size, D3DXCOLOR Color, int nLife)
{
	CEffect * pEffect;
	pEffect = new CEffect;
	pEffect->Init(Position, Size, Color, nLife);
	return pEffect;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 Position, D3DXVECTOR3 Size, D3DXCOLOR Color, int nLife)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//2Dシーンの初期化処理関数呼び出し
	CScene2d::Init();
	//位置の初期設定
	SetPosition(Position);
	//サイズの初期設定
	SetSize(Size);
	SetColor(Color);
	//ライフの初期設定
	m_nLife = nLife;
	//スケールの初期設定
	m_fScale = SCALE;
	SetScale(m_fScale);
	m_fAlpha = 255.0f;
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CEffect::Uninit(void)
{
	//2Dシーンの終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CEffect::Update(void)
{
	//位置を取得
	D3DXVECTOR3 Position = GetPosition();
	//サイズを取得
	D3DXVECTOR3 Size = GetSize();
	//2Dシーンの更新処理関数呼び出し
	CScene2d::Update();
	//ライフが0になったら
	if (m_nLife <= 0)
	{
		//終了処理関数呼び出し
		Uninit();
		return;
	}

	if (m_nLife > 0)
	{
		m_fAlpha -= 10.0f;
		m_fScale -= 0.1f;
	}

	//ライフを減算する
	m_nLife--;

	//色を設定する
	D3DXCOLOR Color = D3DXCOLOR(GetColor().r, GetColor().g, GetColor().b,m_fAlpha);
	SetColor(Color);
	//位置を設定
	SetPosition(Position);
	//サイズを設定
	SetSize(Size);
	//スケールを設定
	SetScale(m_fScale);
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CEffect::Draw(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	CScene2d::Draw();
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
