//=============================================================================
//
// 何らかのボタン入力 [button_any.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "stdlib.h"
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/sound.h"
#include "Input/keyboard.h"
#include "Input/joystick.h"
#include "button_any.h"
#include "title_button_manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PASS ("Data/Texture/Button/Button_Any.png")									//テクスチャのパス
#define POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT - SCREEN_HEIGHT / 4,0.0f))		//位置

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CAnyButton::m_pTexture;	//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CAnyButton::CAnyButton()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CAnyButton::~CAnyButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CAnyButton::TextureLoad(void)
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
void CAnyButton::TextureUnload(void)
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
CAnyButton * CAnyButton::Create()
{
	//何らかのボタンのポインタ
	CAnyButton * pAnyButton = nullptr;
	//何らかのボタンのポインタがnullptrの場合
	if (pAnyButton == nullptr)
	{
		//何らかのボタンのメモリ確保
		pAnyButton = new CAnyButton;
		//何らかのボタンのポインタがnullptrではない場合
		if (pAnyButton != nullptr)
		{
			//何らかのボタンの位置設定
			pAnyButton->SetPosition(POSITION);
			//何らかのボタンの初期化処理関数呼び出し
			pAnyButton->Init();
		}
	}
	//何らかのボタンのポインタを返す
	return pAnyButton;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CAnyButton::Init(void)
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
	//選択時色変更処理関数呼び出し
	SelectColor();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CAnyButton::Uninit(void)
{
	//ボタンの終了処理関数呼び出し
	CButton::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CAnyButton::Update(void)
{
	//ボタンの更新処理関数呼び出し
	CButton::Update();
	//入力処理関数呼び出し
	Input();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CAnyButton::Draw(void)
{
	//ボタンの描画処理関数呼び出し
	CButton::Draw();
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CAnyButton::Input(void)
{
	//キーボードの番号
	int nKeyNumber = 0;
	//キーボードの取得
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	//ジョイスティックの取得
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//ジョイスティックの振動取得
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != nullptr)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//任意のボタン数分回す
	for (int nCount = 0; nCount <= JS_START; nCount++)
	{
		//もし任意のボタンが押されたら
		if (pJoystick->GetJoystickTrigger(nCount))
		{
			//プレス処理関数呼び出し
			Press();
		}
	}
	//最大キー数分回す
	for (int nCount = 0; nCount <= NUM_KEY_MAX; nCount++)
	{
		//もし任意のキー押されたら
		if (pKeyboard->GetKeyboardTrigger(nCount))
		{
			//プレス処理関数呼び出し
			Press();
		}
	}
}

//=============================================================================
// プレス処理関数
//=============================================================================
void CAnyButton::Press(void)
{
	//キーボードの取得
	CKeyboard * pKeyboard = CManager::GetKeyboard();
	//ジョイスティックの取得
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;
	//ジョイスティックの振動取得
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != nullptr)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//もしサウンドのポインタがNULLではない場合
	if (pSound != nullptr)
	{
		//決定音の再生
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);
	}
	//タイトルボタンマネージャーの生成
	CTitleButtonManager::Create();
	//キーボードの更新処理関数呼び出し
	pKeyboard->Update();
	//ジョイスティックの更新処理関数呼び出し
	pJoystick->Update();
	//終了処理関数呼び出し
	Uninit();
	return;
}