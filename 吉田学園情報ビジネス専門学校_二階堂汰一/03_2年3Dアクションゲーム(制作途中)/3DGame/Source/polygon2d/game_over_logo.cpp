//=============================================================================
//
// ゲームオーバーロゴ [game_over_logo.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "game_over_logo.h"
#include "game_over_bg.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/Logo/game_over_logo.png")						//テクスチャのパス
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))				//位置
#define SIZE (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 3,0.0f))					//サイズ
#define COLOR (D3DXCOLOR(1.0f,0.0f,0.0f,0.1f))										//色
#define MINIMUM_ALPHA (0.0f)														//アルファ値の最小値
#define MAX_ALPHA (1.0f)															//アルファ値の最大値
#define ADD_ALPHA (0.005f)															//アルファ値の加算量

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGameOverLogo::m_pTexture = NULL;		//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CGameOverLogo::CGameOverLogo(int nPriority) : CScene2d(nPriority)
{
	m_fAlpha = MINIMUM_ALPHA;		//アルファ値
	m_fAddAlpha = MINIMUM_ALPHA;	//加算するアルファ値
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameOverLogo::~CGameOverLogo()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CGameOverLogo::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,	//デバイスへのポインタ
		TEXTURE_PASS,					//ファイルの名前
		&m_pTexture);					//読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CGameOverLogo::TextureUnload(void)
{
	//もしテクスチャのポインタがnullptrではない場合
	if (m_pTexture != nullptr)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャのポインタをnullptrにする
		m_pTexture = nullptr;
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CGameOverLogo * CGameOverLogo::Create(void)
{
	//ゲームオーバーロゴのポインタ
	CGameOverLogo * pGameOverLogo = nullptr;
	//ゲームオーバーロゴのポインタがnullptrの場合
	if (pGameOverLogo == nullptr)
	{
		//ゲームオーバーロゴのメモリ確保
		pGameOverLogo = new CGameOverLogo;
		//ゲームオーバーロゴのポインタがnullptrではない場合
		if (pGameOverLogo != nullptr)
		{
			//ゲームオーバーロゴの位置設定
			pGameOverLogo->SetPosition(POSITION);
			//ゲームオーバーロゴのサイズ設定
			pGameOverLogo->SetSize(SIZE);
			//ゲームオーバーロゴの色設定
			pGameOverLogo->SetColor(COLOR);
			//ゲームオーバーロゴの初期化処理関数呼び出し
			pGameOverLogo->Init();
		}
	}
	//ゲームオーバーロゴのポインタを返す
	return pGameOverLogo;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CGameOverLogo::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//2Dシーンの初期化処理関数呼び出し
	CScene2d::Init();
	//アルファ値の加算量を設定
	m_fAddAlpha = ADD_ALPHA;
	//ゲームオーバー背景の生成
	CGameOverBG::Create();
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CGameOverLogo::Uninit(void)
{
	//2Dシーンの終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CGameOverLogo::Update(void)
{
	//2Dシーンの更新処理関数呼び出し
	CScene2d::Update();
	//もしアルファチが最大値より下の場合
	if (m_fAlpha < MAX_ALPHA)
	{
		//アルファ値を加算する
		m_fAlpha += m_fAddAlpha;
		//色を設定する
		SetColor(D3DXCOLOR(COLOR.r, COLOR.g, COLOR.b, m_fAlpha));
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGameOverLogo::Draw(void)
{
	//2Dシーンの描画処理関数呼び出し
	CScene2d::Draw();
}
