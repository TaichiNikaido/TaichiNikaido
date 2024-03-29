//******************************************************************************
// エフェクト[effect.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "Base/main.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Base/billboard.h"
#include "effect.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define TEX_STAR	("Data/Texture/Effect/star.png")		// テクスチャパス
#define TEX_BYTE	("Data/Texture/Effect/byte0.png")		// テクスチャパス
#define MIN_UV		(0.0f)									// UV最小値
#define MAX_UV		(1.0f)									// UV最大値
//******************************************************************************
//静的メンバ変数宣言
//******************************************************************************
LPDIRECT3DTEXTURE9 CEffect::m_pTexture[TEX_TYPE_MAX] = {};
//******************************************************************************
// コンストラクタ
//******************************************************************************
CEffect::CEffect(int mPriority)
{
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CEffect::~CEffect()
{
}
//******************************************************************************
// テクスチャの読み込み
//******************************************************************************
HRESULT CEffect::Load(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TEX_STAR, &m_pTexture[TEX_TYPE_STAR]);
	D3DXCreateTextureFromFile(pDevice, TEX_BYTE, &m_pTexture[TEX_TYPE_BYTE]);
	return S_OK;
}

//******************************************************************************
// テクスチャの破棄
//******************************************************************************
void CEffect::Unload(void)
{
	// TYPE_MAX回繰り返す
	for (int nCnt = INIT_INT; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			// テクスチャRelease
			m_pTexture[nCnt]->Release();

			// m_pTextureをNULLに
			m_pTexture[nCnt] = NULL;
		}
	}
}
//******************************************************************************
// 初期化
//******************************************************************************
HRESULT CEffect::Init(void)
{
	// 初期化
	CBillboard::Init();

	// テクスチャ受け渡し
	BindTexture(m_pTexture[m_TexType]);

	return S_OK;
}
//******************************************************************************
// 終了
//******************************************************************************
void CEffect::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}
//******************************************************************************
// 更新
//******************************************************************************
void CEffect::Update(void)
{
	// 更新
	CBillboard::Update();
}
//******************************************************************************
// 描画
//******************************************************************************
void CEffect::Draw(void)
{
	// 描画
	CBillboard::Draw();
}
//******************************************************************************
// 情報設定
//******************************************************************************
void CEffect::SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TEX_TYPE TexType)
{
	// 位置設定
	SetPosition(pos);

	// サイズ設定
	SetSize(size);

	// 向き設定
	SetRotation(rot);

	// 色設定
	SetColor(col);

	// テクスチャタイプ設定
	m_TexType = TexType;
}