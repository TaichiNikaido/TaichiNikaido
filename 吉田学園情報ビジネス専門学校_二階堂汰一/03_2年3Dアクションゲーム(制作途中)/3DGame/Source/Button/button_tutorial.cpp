//=============================================================================
//
// チュートリアルボタン [button_tutorial.cpp]
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
#include "button_tutorial.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/Button/Button_Tutorial.png")	//テクスチャのパス

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTutorialButton::m_pTexture;		//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorialButton::CTutorialButton()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorialButton::~CTutorialButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CTutorialButton::TextureLoad(void)
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
void CTutorialButton::TextureUnload(void)
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
CTutorialButton * CTutorialButton::Create(D3DXVECTOR3 Position)
{
	//チュートリアルボタンのポインタ
	CTutorialButton * pTutoruialButton = NULL;
	//チュートリアルボタンのポインタがnullptrの場合
	if (pTutoruialButton == nullptr)
	{
		//チュートリアルボタンのメモリ確保
		pTutoruialButton = new CTutorialButton;
		//チュートリアルボタンのポインタがnullptrではない場合
		if (pTutoruialButton != nullptr)
		{
			//チュートリアルボタンの位置を設定する
			pTutoruialButton->SetPosition(Position);
			//チュートリアルボタンの初期化処理関数呼び出し
			pTutoruialButton->Init();
		}
	}
	//チュートリアルボタンのポインタを返す
	return pTutoruialButton;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CTutorialButton::Init(void)
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
void CTutorialButton::Uninit(void)
{
	//ボタンの終了処理関数呼び出し
	CButton::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CTutorialButton::Update(void)
{
	//ボタンの更新処理関数呼び出し
	CButton::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CTutorialButton::Draw(void)
{
	//ボタンの描画処理関数呼び出し
	CButton::Draw();
}

//=============================================================================
// プレス処理関数
//=============================================================================
void CTutorialButton::Press(void)
{
	//押したときのサウンド再生
	PlayButtonSE(CButton::BUTTON_SE_PUSH);
	//チュートリアルモードに遷移する
	CManager::StartFade(CManager::MODE_TUTORIAL);
}
