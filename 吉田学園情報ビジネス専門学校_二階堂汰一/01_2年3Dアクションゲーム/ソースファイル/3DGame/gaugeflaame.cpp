//=============================================================================
//
// ゲージ枠 [gaugeflame.cpp]
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
#include "gaugeflame.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MINIMUM_ANIMATIN_PATTERN (0)	//アニメーションパターンの最小値
#define MINIMUM_ANIMATION_VALUE (0.0f)	//アニメーションの値の最小値

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CGaugeFlame::CGaugeFlame()
{
	m_nAnimationPattern = MINIMUM_ANIMATIN_PATTERN;	//アニメーションパターン
	m_fAnimationValue = MINIMUM_ANIMATION_VALUE;	//アニメーションの値
}

//=============================================================================
// デストラクタ
//=============================================================================
CGaugeFlame::~CGaugeFlame()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CGaugeFlame::Init(void)
{
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern + m_fAnimationValue, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern + m_fAnimationValue, 1.0f);
	//2Dシーンの初期化処理関数呼び出し
	CScene2d::Init();
	//テクスチャのUV座標の設定
	SetTexture(aTexture);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CGaugeFlame::Uninit(void)
{
	//2Dシーンの終了処理関数呼び出し
	CScene2d::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CGaugeFlame::Update(void)
{
	//2Dシーンの更新処理関数呼び出し
	CScene2d::Update();
	//テクスチャのUV座標の設定
	D3DXVECTOR2 aTexture[NUM_VERTEX];
	aTexture[0] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern, 0.0f);
	aTexture[1] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern + m_fAnimationValue, 0.0f);
	aTexture[2] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern, 1.0f);
	aTexture[3] = D3DXVECTOR2(m_fAnimationValue * m_nAnimationPattern + m_fAnimationValue, 1.0f);
	//テクスチャのUV座標の設定
	SetTexture(aTexture);
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CGaugeFlame::Draw(void)
{
	//2Dシーンの描画処理関数呼び出し
	CScene2d::Draw();
}
