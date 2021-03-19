//=============================================================================
//
// ボタン [button.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <cmath>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mode_game.h"
#include "button.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE (D3DXVECTOR3(431.0f,83.0f,0.0f))							//サイズ
#define SHOW_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						//見える色
#define HIDE_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,0.3f))						//若干見える色
#define PLAY_BUTTON_TEXTURE ("Data/Texture/Button/button_play.png")		//プレイボタンのテクスチャ
#define REPLAY_BUTTON_TEXTURE ("Data/Texture/Button/button_replay.png")	//リプレイボタンのテクスチャ
#define EXIT_BUTTON_TEXTRUE ("Data/Texture/Button/button_exit.png")		//終了ボタンのテクスチャ

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CButton::m_apTexture[BUTTON_MAX] = {};	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CButton::CButton(int nPriority)
{
	m_Button = BUTTON_NONE;	//ボタン情報
}

//=============================================================================
// デストラクタ
//=============================================================================
CButton::~CButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CButton::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		PLAY_BUTTON_TEXTURE,				// ファイルの名前
		&m_apTexture[BUTTON_PLAY]);			// 読み込むメモリー
	D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		REPLAY_BUTTON_TEXTURE,				// ファイルの名前
		&m_apTexture[BUTTON_REPLAY]);		// 読み込むメモリー
	D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		EXIT_BUTTON_TEXTRUE,				// ファイルの名前
		&m_apTexture[BUTTON_EXIT]);			// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CButton::TextureUnload(void)
{
	//ボタンの最大数回す
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
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
CButton * CButton::Create(D3DXVECTOR3 Positon, BUTTON Button)
{
	//ボタンのポインタ
	CButton * pButton = NULL;
	//ボタンのポインタがNULLの場合
	if (pButton == NULL)
	{
		//ボタンのメモリ確保
		pButton = new CButton;
		//ボタンのポインタがNULLじゃない場合
		if (pButton != NULL)
		{
			//位置を設定する
			pButton->SetPosition(Positon);
			//初期化処理関数呼び出し
			pButton->Init(Button);
		}
	}
	//ボタンのポインタを返す
	return pButton;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CButton::Init(BUTTON Button)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//2dシーンの初期化処理関数呼び出し
	CScene2d::Init();
	//サイズの設定
	SetSize(SIZE);
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_apTexture[Button]);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CButton::Uninit(void)
{
	//2dシーンの終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CButton::Update(void)
{
	//2dシーンの更新処理関数呼び出し
	CScene2d::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CButton::Draw(void)
{
	//2dシーンの描画処理関数呼び出し
	CScene2d::Draw();
}

//=============================================================================
// 選択処理関数
//=============================================================================
void CButton::SelectButton(bool bSelect)
{
	//もし選択されたら
	if (bSelect == true)
	{
		//色を指定する
		D3DXCOLOR Color = SHOW_COLOR;
		//色を設定する
		SetColor(Color);
	}
	else
	{
		//色を指定する
		D3DXCOLOR Color = HIDE_COLOR;
		//色を設定する
		SetColor(Color);
	}
}