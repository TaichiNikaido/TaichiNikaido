//=============================================================================
//
// 名前入力モード [mode_name.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/sound.h"
#include "mode_name.h"
#include "System/name.h"

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
	m_pName = NULL;	//名前入力のポインタ
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
	CNameMode * pNameMode = nullptr;
	//名前入力モードのポインタがnullptrの場合
	if (pNameMode == nullptr)
	{
		//名前入力モードのメモリ確保
		pNameMode = new CNameMode;
		//もし名前入力モードのポインタがnullptrではない場合
		if (pNameMode != nullptr)
		{
			//名前入力モードの初期化処理関数呼び出し
			pNameMode->Init();
		}
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
	//もしサウンドのポインタがnullptrではない場合
	if (pSound != nullptr)
	{
		//サウンドの停止
		pSound->StopSound(CSound::SOUND_LABEL_BGM_TITLE);
		//名前入力画面のBGM再生
		pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_NAME);
	}
	//全生成処理関数呼び出し
	CreateAll();
	//もし名前入力のポインタがnullptrではない場合
	if (m_pName != nullptr)
	{
		//名前入力の初期化処理関数呼び出し
		m_pName->Init();
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CNameMode::Uninit(void)
{
	//もし名前入力のポインタがnullptrではない場合
	if (m_pName != nullptr)
	{
		//名前入力の終了処理関数呼び出し
		m_pName->Uninit();
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CNameMode::Update(void)
{
	//もし名前入力のポインタがnullptrではない場合
	if (m_pName != nullptr)
	{
		//名前入力の更新処理関数呼び出し
		m_pName->Update();
	}
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CNameMode::Draw(void)
{
	//もし名前入力のポインタがnullptrではない場合
	if (m_pName != nullptr)
	{
		//名前入力の描画処理関数呼び出し
		m_pName->Draw();
	}
}

//=============================================================================
// 全生成処理関数
//=============================================================================
void CNameMode::CreateAll(void)
{
	//もし名前入力のポインタがnullptrの場合
	if (m_pName == nullptr)
	{
		//名前入力の生成処理関数呼び出し
		m_pName = CName::Create();
	}
}
