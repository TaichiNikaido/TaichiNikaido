//=============================================================================
//
// パーティクル [particle.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "particle_texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DEATH_LINE (0)		//死亡ライン

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CParticleTexture::CParticleTexture()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CParticleTexture::~CParticleTexture()
{
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CParticleTexture::Init(void)
{
	//ビルボードの初期化処理関数呼び出し
	CBillboard::Init();
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CParticleTexture::Uninit(void)
{
	//ビルボードのの終了処理関数呼び出し
	CBillboard::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CParticleTexture::Update(void)
{
	//ビルボードの更新処理関数呼び出し
	CBillboard::Update();
	//体力減算処理関数呼び出し
	SubLife();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CParticleTexture::Draw(void)
{
	//ビルボードの描画処理関数呼び出し
	CBillboard::Draw();
}

//=============================================================================
// 体力減算処理関数
//=============================================================================
void CParticleTexture::SubLife(void)
{
	//体力を減算する
	m_nLife--;
	//もし体力が0以下になったらb
	if (m_nLife <= DEATH_LINE)
	{
		//死亡処理関数呼び出し
		Death();
	}
}

//=============================================================================
// 死亡処理関数
//=============================================================================
void CParticleTexture::Death(void)
{
	//終了処理関数呼び出し
	Uninit();
	return;
}
