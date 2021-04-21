//=============================================================================
//
// コンティニューボタン [button_continue.cpp]
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
#include "Base/sound.h"
#include "button_continue.h"
#include "Character/player.h"
#include "Character/enemy.h"
#include "Mode/continue.h"
#include "Map/needle.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE ("Data/Texture/YES.png")

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CContinueButton::m_pTexture = NULL;	//テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CContinueButton::CContinueButton()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CContinueButton::~CContinueButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CContinueButton::TextureLoad(void)
{
	//レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE,						// ファイルの名前
		&m_pTexture);					// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CContinueButton::TextureUnload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄処理関数呼び出し
		m_pTexture->Release();
		//テクスチャをNULLにする
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CContinueButton * CContinueButton::Create(D3DXVECTOR3 Position)
{
	//コンティニューボタンのポインタ
	CContinueButton * pContinueButton = NULL;
	//コンティニューボタンのポインタがNULLの場合
	if (pContinueButton == NULL)
	{
		//コンティニューボタンのメモリ確保
		pContinueButton = new CContinueButton;
		//コンティニューボタンのポインタがNULLではない場合
		if (pContinueButton != NULL)
		{
			//コンティニューボタンの位置設定
			pContinueButton->SetPosition(Position);
			//コンティニューボタンの初期化処理関数呼び出し
			pContinueButton->Init();
		}
	}
	//コンティニューボタンのポインタを返す
	return pContinueButton;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CContinueButton::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(0.0f, 0.0f);
	aTexture[1] = D3DXVECTOR2(1.0f, 0.0f);
	aTexture[2] = D3DXVECTOR2(0.0f, 1.0f);
	aTexture[3] = D3DXVECTOR2(1.0f, 1.0f);
	//テクスチャの設定
	SetTexture(aTexture);
	//テクスチャの割り当て
	BindTexture(m_pTexture);
	//ボタンの初期化処理関数呼び出し
	CButton::Init();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CContinueButton::Uninit(void)
{
	//ボタンの終了処理関数呼び出し
	CButton::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CContinueButton::Update(void)
{
	//ボタンの更新処理関数呼び出し
	CButton::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CContinueButton::Draw(void)
{
	//ボタンの描画処理関数呼び出し
	CButton::Draw();
}

//=============================================================================
// プレス処理関数
//=============================================================================
void CContinueButton::Press(void)
{
	CContinue * pContinue = CGameMode::GetContinue();
	//プレイヤーの取得
	CPlayer * pPlayer = CGameMode::GetPlayer();
	//敵の取得
	CEnemy * pEnemy = CGameMode::GetEnemy();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//もしサウンドのポインタがNULLじゃない場合
	if (pSound != NULL)
	{
		//決定音の再生
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);
	}
	//もしプレイヤーのポインタがNULLじゃない場合
	if (pPlayer != NULL)
	{
		//プレイヤーのコンティニューをtrueにする
		pPlayer->SetbContinue(true);
	}
	//もし敵のポインタがNULLじゃない場合
	if (pEnemy != NULL)
	{
		//敵のコンティニューをtrueにする
		pEnemy->SetbContinue(true);
	}
	pContinue->Uninit();
}
