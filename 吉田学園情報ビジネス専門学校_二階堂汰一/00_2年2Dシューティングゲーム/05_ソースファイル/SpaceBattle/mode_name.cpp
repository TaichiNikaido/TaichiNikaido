//=============================================================================
//
// 名前入力モード [mode_name.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "mode_name.h"
#include "background_name.h"
#include "name.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CNameMode::CNameMode()
{
	m_pName = NULL;		//名前入力のポインタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CNameMode::~CNameMode()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CNameMode * CNameMode::Create()
{
	//名前入力モードのポインタ
	CNameMode * pNameMode = NULL;
	//名前入力モードのポインタがNULLの場合
	if (pNameMode == NULL)
	{
		//名前入力モードのメモリ確保
		pNameMode = new CNameMode;
	}
	//名前入力モードのポインタがNULLじゃない場合
	if (pNameMode != NULL)
	{
		//名前入力モードの初期化処理関数呼び出し
		pNameMode->Init();
	}
	//名前入力モードのポインタを返す
	return pNameMode;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CNameMode::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//BGMの再生
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_NAME);
	//全生成処理関数呼び出し
	CreateAll();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CNameMode::Uninit(void)
{
	if (m_pName != NULL)
	{
		m_pName->Uninit();
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CNameMode::Update(void)
{
	if (m_pName != NULL)
	{
		m_pName->Update();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CNameMode::Draw(void)
{
	if (m_pName != NULL)
	{
		m_pName->Draw();
	}
}

//=============================================================================
// 全生成処理関数
//=============================================================================
void CNameMode::CreateAll(void)
{
	//名前入力背景生成処理関数呼び出し
	CBackgroundName::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	//名前入力処理生成処理関数呼び出し
	m_pName = CName::Create();
}
