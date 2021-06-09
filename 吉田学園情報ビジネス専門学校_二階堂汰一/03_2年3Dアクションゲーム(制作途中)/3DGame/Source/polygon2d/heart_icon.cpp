//=============================================================================
//
// ハートアイコン [heart_icon.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Mode/mode_game.h"
#include "Base/renderer.h"
#include "heart_icon.h"
#include "Character/player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/heart_icon.png")			//テクスチャパス
#define SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))					//サイズ
#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))					//色
#define ANIMATION_VALUE (0.2f)									//アニメーションの値
#define MINIMUM_PATTERN_ANIME (0)								//パターンアニメの最小値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CHeartIcon::m_pTexture = nullptr;	//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CHeartIcon::CHeartIcon(int nPriority) : CScene2d(nPriority)
{
	m_nPatternAnime = MINIMUM_PATTERN_ANIME;	//パターンアニメ
}

//=============================================================================
// デストラクタ
//=============================================================================
CHeartIcon::~CHeartIcon()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CHeartIcon::TextureLoad(void)
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
void CHeartIcon::TextureUnload(void)
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
// 生成処理関数呼び出し
//=============================================================================
CHeartIcon * CHeartIcon::Create(D3DXVECTOR3 Position)
{
	//ポーズ背景のポインタ
	CHeartIcon * pHeartIcon = nullptr;
	//ポーズ背景のポインタがnullptrの場合
	if (pHeartIcon == nullptr)
	{
		//ポーズ背景のメモリ確保
		pHeartIcon = new CHeartIcon;
		//ポーズ背景のポインタがnullptrではない場合
		if (pHeartIcon != nullptr)
		{
			//ポーズ背景の位置設定
			pHeartIcon->SetPosition(Position);
			//ポーズ背景のサイズ設定
			pHeartIcon->SetSize(SIZE);
			//ポーズ背景の色設定
			pHeartIcon->SetColor(COLOR);
			//ポーズ背景の初期化処理関数呼び出し
			pHeartIcon->Init();
		}
	}
	//ポーズ背景のポインタを返す
	return pHeartIcon;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CHeartIcon::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
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
void CHeartIcon::Uninit(void)
{
	//2Dシーンの終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CHeartIcon::Update(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 0.0f);
	aTexture[1] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 0.0f);
	aTexture[2] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime, 1.0f);
	aTexture[3] = D3DXVECTOR2(ANIMATION_VALUE * m_nPatternAnime + ANIMATION_VALUE, 1.0f);
	//2Dシーンの更新処理関数呼び出し
	CScene2d::Update();
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CHeartIcon::Draw(void)
{
	//ゲームモードの取得
	CGameMode * pGameMode = CManager::GetGameMode();
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//もしゲームモードのポインタがnullptrではないかつプレイヤーのポインタがnullptrではない場合
	if (pGameMode != nullptr && pPlayer != nullptr)
	{
		//もしポーズが生成されてないかつプレイヤーが死亡状態ではない場合
		if (pGameMode->GetbCreatePause() == false && pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			//2Dシーンの描画処理関数呼び出し
			CScene2d::Draw();
		}
	}
}