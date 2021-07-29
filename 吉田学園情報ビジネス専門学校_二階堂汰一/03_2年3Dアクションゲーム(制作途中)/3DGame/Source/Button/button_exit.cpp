//=============================================================================
//
// 終了ボタン [button_exit.cpp]
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
#include "button_exit.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_ENGLISH_PASS ("Data/Texture/Button/Button_English_Exit.png")	//テクスチャのパス
#define TEXTURE_JAPANESE_PASS ("Data/Texture/Button/Button_Japanese_Exit.png")	//テクスチャのパス

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExitButton::m_apTexture[TEXTURE_MAX] = {};	//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CExitButton::CExitButton()
{
	m_TextureType = TEXTURE_NONE;	//テクスチャの種類
}

//=============================================================================
// デストラクタ
//=============================================================================
CExitButton::~CExitButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CExitButton::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,		//デバイスへのポインタ
		TEXTURE_ENGLISH_PASS,				//ファイルの名前
		&m_apTexture[TEXTURE_ENGLISH]);		//読み込むメモリー
	//テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,		//デバイスへのポインタ
		TEXTURE_JAPANESE_PASS,				//ファイルの名前
		&m_apTexture[TEXTURE_JAPANESE]);	//読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CExitButton::TextureUnload(void)
{
	//テクスチャの最大数分回す
	for (int nCount = TEXTURE_ENGLISH; nCount < TEXTURE_MAX; nCount++)
	{
		//もしテクスチャのポインタがnullptrではない場合
		if (m_apTexture[nCount] != nullptr)
		{
			//テクスチャの破棄処理関数呼び出し
			m_apTexture[nCount]->Release();
			//テクスチャをnullptrにする
			m_apTexture[nCount] = nullptr;
		}
	}
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CExitButton * CExitButton::Create(D3DXVECTOR3 Position, TEXTURE_TYPE TextureType)
{
	//終了ボタンのポインタ
	CExitButton * pExitButton = nullptr;
	//終了ボタンのポインタがnullptrの場合
	if (pExitButton == nullptr)
	{
		//終了ボタンのメモリ確保
		pExitButton = new CExitButton;
		//終了ボタンのポインタがnullptrではない場合
		if (pExitButton != nullptr)
		{
			//終了ボタンの位置設定
			pExitButton->SetPosition(Position);
			//テクスチャの種類を設定
			pExitButton->m_TextureType = TextureType;
			//終了ボタンの初期化処理関数呼び出し
			pExitButton->Init();
		}
	}
	//終了ボタンのポインタを返す
	return pExitButton;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CExitButton::Init(void)
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
	BindTexture(m_apTexture[m_TextureType]);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CExitButton::Uninit(void)
{
	//ボタンの終了処理関数呼び出し
	CButton::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CExitButton::Update(void)
{
	//ボタンの更新処理関数呼び出し
	CButton::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CExitButton::Draw(void)
{
	//ボタンの描画処理関数呼び出し
	CButton::Draw();
}

//=============================================================================
// プレス処理関数
//=============================================================================
void CExitButton::Press(void)
{
	//押したときのサウンド再生
	PlayButtonSE(CButton::BUTTON_SE_PUSH);
	//終了させる
	exit(0);
}
