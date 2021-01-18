//=============================================================================
//
// 爆発 [explosion.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "sound.h"
#include "explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosion::CExplosion(int nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CExplosion::~CExplosion()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CExplosion::Init(void)
{
	//2Dシーン初期化処理関数呼び出し
	CScene2d::Init();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CExplosion::Uninit(void)
{
	//2Dシーン終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CExplosion::Update(void)
{
	//2Dシーン更新処理関数呼び出し
	CScene2d::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CExplosion::Draw(void)
{
	//2Dシーン描画処理関数呼び出し
	CScene2d::Draw();
}
