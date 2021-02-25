//=============================================================================
//
// 背景管理処理 [background_manager.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "background_manager.h"
#include "background_under_layer.h"
#include "background_middle_layer.h"
#include "background_upper_layer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BACKGROUND_UNDER_LAYR_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))		//下層背景の位置
#define BACKGROUND_MIDDLE_LAYER_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))	//中層背景の位置
#define BACKGROUND_UPPER_LAYER_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))	//上層背景の位置

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CBackgroundManager::CBackgroundManager()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBackgroundManager::~CBackgroundManager()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CBackgroundManager * CBackgroundManager::Create()
{
	//背景管理のポインタ
	CBackgroundManager * pBackgroundManager = NULL;
	//もし背景管理のポインタがNULLの場合
	if (pBackgroundManager == NULL)
	{
		//背景管理のメモリ確保
		pBackgroundManager = new CBackgroundManager;
		//もし背景管理のポインタがNULLじゃない場合
		if (pBackgroundManager != NULL)
		{
			//背景管理の初期化処理関数呼び出し
			pBackgroundManager->Init();
		}
	}
	//背景管理のポインタを返す
	return pBackgroundManager;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
void CBackgroundManager::Init(void)
{
	//下層背景の生成
	CBackgroundUnderLayer::Create(BACKGROUND_UNDER_LAYR_POSITION);
	//中層背景の生成
	CBackgroundMiddleLayer::Create(BACKGROUND_MIDDLE_LAYER_POSITION);
	//上層背景の生成
	CBackgroundUpperLayer::Create(BACKGROUND_UPPER_LAYER_POSITION);
}
