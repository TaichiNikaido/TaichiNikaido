//=============================================================================
//
// 爆弾のUI処理 [bombui.cpp]
// Author: 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "player.h"
#include "bombtexture.h"
#include "bomb.h"
#include "bombui.h"
#include <cmath>

//=============================================================================
// コンストラクタ
//=============================================================================
CBombUI::CBombUI(int nPriority) :CScene(nPriority)
{
	memset(m_apBombUI, 0, sizeof(m_apBombUI));
	m_nBombUI = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CBombUI::~CBombUI()
{
}

//=============================================================================
// 生成
//=============================================================================
CBombUI * CBombUI::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight)
{
	CBombUI * pBombUI;
	pBombUI = new CBombUI;
	pBombUI->Init(pos, SizeWidth, SizeHeight);
	return pBombUI;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CBombUI::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight)
{
	for (int nCount = 0; nCount < PLAYER_MAX_BOMB; nCount++)
	{
		m_apBombUI[nCount] = CBombTexture::Create(D3DXVECTOR3(pos.x + (SizeWidth * nCount), pos.y, 0.0f), SizeWidth, SizeHeight);
	}

	m_nBombUI = 0;	//爆弾のUI
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CBombUI::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CBombUI::Update(void)
{
}

//=============================================================================
// 描画関数
//=============================================================================
void CBombUI::Draw(void)
{
	for (int nCount = 0; nCount < PLAYER_MAX_BOMB; nCount++)
	{
		m_apBombUI[nCount]->Draw();
	}
}

//=============================================================================
// セット関数
//=============================================================================
void CBombUI::SetBombUI(int nBomb)
{
	//もし爆弾のUIが最大数以下だった時
	if (m_nBombUI <= PLAYER_MAX_BOMB)
	{
		//爆弾のUIに引数を代入
		m_nBombUI = nBomb;

		for (int nCount = 0; nCount < PLAYER_MAX_BOMB; nCount++)
		{
			m_apBombUI[nCount]->SetBombTexture(100);
		}

		for (int nCount = 0; nCount < m_nBombUI; nCount++)
		{
			m_apBombUI[nCount]->SetBombTexture(255);
		}
	}
}

//=============================================================================
// 加算関数
//=============================================================================
void CBombUI::AddBombUI(int nValue)
{
	//爆弾のUIに引数を加算する
	m_nBombUI += nValue;
	//爆弾のUIをセット
	SetBombUI(m_nBombUI);
}

//=============================================================================
// 減算関数
//=============================================================================
void CBombUI::SubBombUI(int nValue)
{
	//爆弾のUIに引数を減算する
	m_nBombUI -= nValue;
	//爆弾のUIをセット
	SetBombUI(m_nBombUI);
}
