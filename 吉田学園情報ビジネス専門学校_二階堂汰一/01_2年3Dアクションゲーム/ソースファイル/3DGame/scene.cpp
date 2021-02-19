//=============================================================================
//
// シーン管理 [scene.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CScene * CScene::m_apScene[PRIORITY_MAX][MAX_SCENE] = {};	//シーンへのポインタ
int CScene::m_nNumAll = 0;									//シーンの総数

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	m_nID = 0;
	m_nPriority = nPriority;
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		if (m_apScene[m_nPriority][nCount] == NULL)
		{
			m_apScene[m_nPriority][nCount] = this;
			m_nID = nCount;
			m_nNumAll++;
			break;
		}
	}
	m_objType = OBJTYPE_NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// 全体更新関数
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			if (m_apScene[nCountPriority][nCount] != NULL)
			{
				m_apScene[nCountPriority][nCount]->Update();
			}
		}
	}
}

//=============================================================================
// 全体描画関数
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			if (m_apScene[nCountPriority][nCount] != NULL)
			{
				m_apScene[nCountPriority][nCount]->Draw();
			}
		}
	}
}

//=============================================================================
// 全体破棄関数
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			if (m_apScene[nCountPriority][nCount] != NULL)
			{
				m_apScene[nCountPriority][nCount]->Uninit();
				m_apScene[nCountPriority][nCount] = NULL;
			}
		}
	}
}

//=============================================================================
// シーンの総数取得関数
//=============================================================================
int CScene::GetNumAll(void)
{
	return m_nNumAll;
}

//=============================================================================
// 破棄関数
//=============================================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}

//=============================================================================
// 種類を設定
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//=============================================================================
// 種類を取得
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//=============================================================================
// 取得
//=============================================================================
CScene * CScene::GetScene(int nPriority, int nCnt)
{
	return m_apScene[nPriority][nCnt];
}
