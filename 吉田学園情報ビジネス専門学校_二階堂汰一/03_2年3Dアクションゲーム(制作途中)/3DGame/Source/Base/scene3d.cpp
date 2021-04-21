//=============================================================================
//
// 3Dシーン管理 [scene3d.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene3d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CScene3d::CScene3d(int nPriority) : CScene(nPriority)
{
	m_Position = INITIAL_D3DXVECTOR3;	//位置
	m_Rotation = INITIAL_ROTATION;		//回転値
	m_Size = INITIAL_D3DXVECTOR3;		//サイズ
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene3d::~CScene3d()
{
}