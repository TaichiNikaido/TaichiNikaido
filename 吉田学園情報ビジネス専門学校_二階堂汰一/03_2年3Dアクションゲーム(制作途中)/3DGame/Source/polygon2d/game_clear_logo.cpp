//=============================================================================
//
// ゲームクリアロゴ [game_clear_logo.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "game_clear_logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/Logo/game_clear_logo.png")				//テクスチャのパス
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))		//位置
#define SIZE (D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))					//サイズ
#define COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,0.5f))								//色
#define DISPLAY_MINIMUM_TIME (0)											//表示時間の最小値
#define DISPLAY_MAX_TIME (300)												//表示時間の最大値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGameClearLogo::m_pTexture = NULL;		//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CGameClearLogo::CGameClearLogo(int nPriority) : CScene2d(nPriority)
{
	m_nDisplayTimeCount = DISPLAY_MINIMUM_TIME;		//表示時間のカウント
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameClearLogo::~CGameClearLogo()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CGameClearLogo::TextureLoad(void)
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
void CGameClearLogo::TextureUnload(void)
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
CGameClearLogo * CGameClearLogo::Create(void)
{
	//ゲームクリアロゴのポインタ
	CGameClearLogo * pGameClearLogo = nullptr;
	//ゲームクリアロゴのポインタがnullptrの場合
	if (pGameClearLogo == nullptr)
	{
		//ゲームクリアロゴのメモリ確保
		pGameClearLogo = new CGameClearLogo;
		//ゲームクリアロゴのポインタがnullptrではない場合
		if (pGameClearLogo != nullptr)
		{
			//ゲームクリアロゴの位置設定
			pGameClearLogo->SetPosition(POSITION);
			//ゲームクリアロゴのサイズ設定
			pGameClearLogo->SetSize(SIZE);
			//ゲームクリアロゴの色設定
			pGameClearLogo->SetColor(COLOR);
			//ゲームクリアロゴの初期化処理関数呼び出し
			pGameClearLogo->Init();
		}
	}
	//ゲームクリアロゴのポインタを返す
	return pGameClearLogo;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CGameClearLogo::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//2Dシーンの初期化処理関数呼び出し
	CScene2d::Init();
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CGameClearLogo::Uninit(void)
{
	//2Dシーンの終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CGameClearLogo::Update(void)
{
	//2Dシーンの更新処理関数呼び出し
	CScene2d::Update();
	//もし表示時間のカウントが最大値を越えたら
	if (m_nDisplayTimeCount >= DISPLAY_MAX_TIME)
	{
		//リザルトモードに遷移する
		CManager::StartFade(CManager::MODE_RESULT);
	}
	//表示時間のカウントを加算する
	m_nDisplayTimeCount++;
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGameClearLogo::Draw(void)
{
	//2Dシーンの描画処理関数呼び出し
	CScene2d::Draw();
}
