//=============================================================================
//
// ボタン [button.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/sound.h"
#include "button.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SELECT_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))		//選択時の色
#define NOT_SELECT_COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,0.5f))	//選択されていないときの色
#define SIZE (D3DXVECTOR3(300.0f,70.0f,0.0f))				//サイズ

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CButton::CButton(int nPriority) : CScene2d(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CButton::~CButton()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CButton::Init(void)
{
	//シーン2D管理の初期化処理関数呼び出し
	CScene2d::Init();
	//サイズを設定する
	SetSize(SIZE);
	//色を設定する
	SetColor(NOT_SELECT_COLOR);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CButton::Uninit(void)
{
	//シーン2D管理の終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CButton::Update(void)
{
	//シーン2D管理の更新処理関数呼び出し
	CScene2d::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CButton::Draw(void)
{
	//シーン2D管理の描画処理関数呼び出し
	CScene2d::Draw();
}

//=============================================================================
// 選択時の色変更処理関数
//=============================================================================
void CButton::ChangeTranslucent(bool bTranslucent)
{
	if (bTranslucent == true)
	{
		//色を変更する
		SetColor(SELECT_COLOR);
	}
	else
	{
		//色を変更する
		SetColor(NOT_SELECT_COLOR);
	}
}

//=============================================================================
// ボタンのSE再生処理関数
//=============================================================================
void CButton::PlayButtonSE(BUTTON_SE PlayButtonSE)
{
	// サウンドの取得
	CSound * pSound = CManager::GetSound();
	// ボタンSEの種類を設定
	BUTTON_SE ButtonSE = PlayButtonSE;
	// もしサウンドのポインタがnullptrではない場合
	if (pSound != nullptr)
	{
		switch (ButtonSE)
		{
		case BUTTON_SE_SELECT:
			// ボタン選択音の再生
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_SELECT);
			break;
		case BUTTON_SE_PUSH:
			// ボタンを押す音の再生
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_PUSH);
			break;
		case BUTTON_SE_CANCEL:
			// ボタンキャンセル音の再生
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON_CANCEL);
			break;
		default:
			break;
		}
	}
}

