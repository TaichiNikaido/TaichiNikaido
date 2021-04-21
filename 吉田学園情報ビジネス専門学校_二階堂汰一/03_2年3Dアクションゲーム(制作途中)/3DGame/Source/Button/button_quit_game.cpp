//=============================================================================
//
// ゲームに戻るボタン [button_quit_game.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/sound.h"
#include "Mode/mode_tutorial.h"
#include "Mode/mode_game.h"
#include "button_quit_game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/Button/Button_ReturnGame.png")		//テクスチャのパス

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CQuitGameButton::m_pTexture;	//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CQuitGameButton::CQuitGameButton()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CQuitGameButton::~CQuitGameButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CQuitGameButton::TextureLoad(void)
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
void CQuitGameButton::TextureUnload(void)
{
	//もしテクスチャのポインタがnullptrではない場合
	if (m_pTexture != nullptr)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャをnullptrにする
		m_pTexture = nullptr;
	}
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CQuitGameButton * CQuitGameButton::Create(D3DXVECTOR3 Position)
{
	//ゲームに戻るボタンのポインタ
	CQuitGameButton * pQuitGameButton = nullptr;
	//ゲームに戻るボタンポインタがnullptrの場合
	if (pQuitGameButton == nullptr)
	{
		//ゲームに戻るボタンのメモリ確保
		pQuitGameButton = new CQuitGameButton;
		//ゲームに戻るボタンのポインタがnullptrではない場合
		if (pQuitGameButton != nullptr)
		{
			//ゲームに戻るボタンの位置設定
			pQuitGameButton->SetPosition(Position);
			//ゲームに戻るボタンの初期化処理関数呼び出し
			pQuitGameButton->Init();
		}
	}
	//ゲームに戻るボタンのポインタを返す
	return pQuitGameButton;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CQuitGameButton::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//ボタンの初期化処理関数呼び出し
	CButton::Init();
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CQuitGameButton::Uninit(void)
{
	//ボタンの終了処理関数呼び出し
	CButton::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CQuitGameButton::Update(void)
{
	//ボタンの更新処理関数呼び出し
	CButton::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CQuitGameButton::Draw(void)
{
	//ボタンの描画処理関数呼び出し
	CButton::Draw();
}

//=============================================================================
// プレス処理関数
//=============================================================================
void CQuitGameButton::Press(void)
{
	//チュートリアルモードの取得
	CTutorialMode * pTutorialMode = CManager::GetTutorialMode();
	//ゲームモードの取得
	CGameMode * pGameMode = CManager::GetGameMode();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//もしサウンドのポインタがnullptrではない場合
	if (pSound != nullptr)
	{
		//決定音の再生
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);
	}
	//もしチュートリアルモードのポインタがnullptrではない場合
	if (pTutorialMode != nullptr)
	{
		//ポーズ未使用状態にする
		pTutorialMode->SetbPouse(false);
	}
	//もしゲームモードのポインタがnullptrじゃない場合
	if (pGameMode != nullptr)
	{
		//ポーズ未使用状態にする
		pGameMode->SetbPouse(false);
	}
}