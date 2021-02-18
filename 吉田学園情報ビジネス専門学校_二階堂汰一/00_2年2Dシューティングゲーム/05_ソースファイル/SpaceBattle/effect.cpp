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
#define TEXTURE ("Data/Texture/Bullet/Bullet.png")	//テクスチャ
#define SCALE (1.0f)								//拡縮
#define MINIMUM_SCALE (0.0f)
#define ALPHA (255.0f)
#define SUB_ALPHA (10.0f)
#define SUB_SCALE (0.1f)
#define MINIMUM_LIFE (0)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CEffect::CEffect(int nPriority)
{
	m_fScale = MINIMUM_SCALE;	//拡縮
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
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
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
CEffect * CEffect::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size, D3DXCOLOR Color, int nLife)
{
	//エフェクトのポインタ
	CEffect * pEffect = NULL;
	//もしエフェクトのポインタがNULLの場合
	if (pEffect == NULL)
	{
		//エフェクトのメモリ確保
		pEffect = new CEffect;
	}
	//もしエフェクトのポインタがNULLじゃない場合
	if (pEffect != NULL)
	{
		//初期化処理関数呼び出し
		pEffect->Init(Position, Size, Color, nLife);
	}
	//エフェクトのポインタを返す
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
	//カラーの初期設定
	SetColor(Color);
	//ライフの初期設定
	m_nLife = nLife;
	//スケールの初期設定
	m_fScale = SCALE;
	//拡縮を設定する
	SetScale(m_fScale);
	//アルファ値の代入
	m_fAlpha = ALPHA;
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
	if (m_nLife <= MINIMUM_LIFE)
	{
		//終了処理関数呼び出し
		Uninit();
		return;
	}
	//もしライフが0より上だったら
	if (m_nLife > MINIMUM_LIFE)
	{
		//アルファ値を減算する
		m_fAlpha -= SUB_ALPHA;
		//縮小する
		m_fScale -= SUB_SCALE;
	}
	//ライフを減算する
	m_nLife--;
	//色を代入する
	D3DXCOLOR Color = D3DXCOLOR(GetColor().r, GetColor().g, GetColor().b,m_fAlpha);
	//色を設定する
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
	//レンダラーの取得
	CRenderer * pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//アルファブレンド
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//描画処理関数呼び出し
	CScene2d::Draw();
	//アルファブレンドを元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
