//=============================================================================
//
// シーン管理処理 [scene.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"

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
	m_nID = 0;					//現在のシーン
	m_nPriority = nPriority;	//プライオリティー
	//シーンの最大数分回す
	for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		//もしシーンのポインタがNULLの場合
		if (m_apScene[m_nPriority][nCount] == NULL)
		{
			//シーンの確保
			m_apScene[m_nPriority][nCount] = this;
			m_nID = nCount;
			//シーンの総数を加算する
			m_nNumAll++;
			break;
		}
	}
	m_ObjectType = OBJECT_TYPE_NONE;	//オブジェクトの種類
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// 全更新処理関数
//=============================================================================
void CScene::UpdateAll(void)
{
	//プライオリティーの最大数分回す
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		//シーンの最大数分回す
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			//もしシーンのポンタがNULLではない場合
			if (m_apScene[nCountPriority][nCount] != NULL)
			{
				//シーンの更新処理関数呼び出し
				m_apScene[nCountPriority][nCount]->Update();
			}
		}
	}
}

//=============================================================================
// 全描画処理関数
//=============================================================================
void CScene::DrawAll(void)
{
	//プライオリティーの最大数分回す
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		//シーンの最大数分回す
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			//もしシーンのポンタがNULLではない場合
			if (m_apScene[nCountPriority][nCount] != NULL)
			{
				//シーンの更新処理関数呼び出し
				m_apScene[nCountPriority][nCount]->Draw();
			}
		}
	}
}

//=============================================================================
// 全破棄処理関数
//=============================================================================
void CScene::ReleaseAll(void)
{
	//プライオリティーの最大数分回す
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		//シーンの最大数分回す
		for (int nCount = 0; nCount < MAX_SCENE; nCount++)
		{
			//もしシーンのポンタがNULLではない場合
			if (m_apScene[nCountPriority][nCount] != NULL)
			{
				//シーンの終了処理関数呼び出し
				m_apScene[nCountPriority][nCount]->Uninit();
				//シーンをNULLにする
				m_apScene[nCountPriority][nCount] = NULL;
			}
		}
	}
}

//=============================================================================
// 破棄処理関数
//=============================================================================
void CScene::Release(void)
{
	//もしシーンがNULLではない場合
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;
		//シーンのメモリを破棄する
		delete m_apScene[nPriority][nID];
		//シーンをNULLにする
		m_apScene[nPriority][nID] = NULL;
		//シーンの総数を減算する
		m_nNumAll--;
	}
}