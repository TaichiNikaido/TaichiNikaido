//=============================================================================
//
// チュートリアル背景 [bg_tutorial.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "Base/main.h"
#include "Base/manager.h"
#include "Mode/mode_game.h"
#include "Base/renderer.h"
#include "Base/scene2d.h"
#include "Input/Keyboard.h"
#include "Input/joystick.h"
#include "bg_tutorial.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_KEYBOARD	("Data/Texture/TutorialBG0.png")						// テクスチャ
#define TEXTURE_CONTROLLER	("Data/Texture/TutorialBG1.png")						// テクスチャ1
#define SIZE				(D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))			// サイズ
#define POSITION			(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))	// 位置
#define COLOR				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))						// 色
#define FLAME				(0)														// フレーム

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTutorialBG::m_pTexture[TEX_TYPE_MAX] = {};						//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorialBG::CTutorialBG(int nPriority) : CScene2d(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorialBG::~CTutorialBG()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CTutorialBG::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_KEYBOARD,									// ファイルの名前
		&m_pTexture[TEX_TYPE_KEYBOARD]);					// 読み込むメモリー
															// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_CONTROLLER,									// ファイルの名前
		&m_pTexture[TEX_TYPE_CONTROLLER]);					// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CTutorialBG::TextureUnload(void)
{
	for (int nCnt = INIT_INT; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		//もしテクスチャがNULLじゃない場合
		if (m_pTexture[nCnt] != NULL)
		{
			//テクスチャの破棄処理関数呼び出し
			m_pTexture[nCnt]->Release();
			//テクスチャをNULLにする
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 生成処理関数
//=============================================================================
CTutorialBG * CTutorialBG::Create(void)
{
	//タイトル背景のポインタ
	CTutorialBG * pTitleBG = NULL;
	//もしタイトル背景のポインタがNULLの場合
	if (pTitleBG == NULL)
	{
		//タイトル背景のメモリ確保
		pTitleBG = new CTutorialBG;
		//もしタイトル背景がNULLじゃない場合
		if (pTitleBG != NULL)
		{
			//位置を設定する
			pTitleBG->SetPosition(POSITION);

			//サイズを設定する
			pTitleBG->SetSize(SIZE);

			//色を設定する
			pTitleBG->SetColor(COLOR);

			// オブジェタイプ設定
			pTitleBG->SetObjType(OBJTYPE_TUTORIAL);

			//初期化処理関数呼び出し
			pTitleBG->Init();
		}
	}
	//タイトル背景のポインタを返す
	return pTitleBG;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CTutorialBG::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);

	//シーン2Dの初期化処理関数呼び出し
	CScene2d::Init();

	//テクスチャの設定
	SetTexture(aTexture);

	//キーボードの取得
	CKeyboard * pKeyboard = CManager::GetKeyboard();

	//ジョイスティックの取得
	CJoystick * pJoystick = CManager::GetJoystick();

	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();

	DIJOYSTATE js;

	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	// NULLでない場合
	if (lpDIDevice != NULL)
	{
		//テクスチャの割り当て
		BindTexture(m_pTexture[TEX_TYPE_CONTROLLER]);
	}
	// NULLの場合
	if (lpDIDevice == NULL)
	{
		//テクスチャの割り当て
		BindTexture(m_pTexture[TEX_TYPE_KEYBOARD]);
	}

	// 全体の更新停止
	CScene::SetUpdateStop(true);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CTutorialBG::Uninit(void)
{
	//シーン2Dの終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CTutorialBG::Update(void)
{
	//シーン2Dの更新処理関数呼び出し
	CScene2d::Update();

	//キーボードの取得
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//サウンドの取得
	CSound * pSound = CManager::GetSound();

	//ジョイスティックの取得
	CJoystick * pJoystick = CManager::GetJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CJoystick::GetDevice();
	DIJOYSTATE js;

	//ジョイスティックの振動取得
	LPDIRECTINPUTEFFECT pDIEffect = CJoystick::GetEffect();
	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	//もしENTERかAボタンを押したとき
	if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pJoystick->GetJoystickTrigger(JS_A))
	{
		// 全体の更新停止
		CScene::SetUpdateStop(false);
		// 終了
		Uninit();
		return;
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CTutorialBG::Draw(void)
{
	//シーン2Dの描画処理関数呼び出し
	CScene2d::Draw();
}
