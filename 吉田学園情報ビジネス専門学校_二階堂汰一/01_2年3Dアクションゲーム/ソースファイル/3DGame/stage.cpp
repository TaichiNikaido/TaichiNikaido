//=============================================================================
//
// ステージ [stage.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "stage.h"
#include "object_wood_house.h"
#include "object_stone_house.h"
#include "object_fountain.h"
#include "object_fence.h"
#include "object_corpse.h"
#include "ui_village_life.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INITIAL_LIFE (0)

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CStage::CStage()
{
	m_nLife = INITIAL_LIFE;							//体力
	memset(m_apObject, NULL, sizeof(m_apObject));	//オブジェクトのポインタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CStage::~CStage()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CStage * CStage::Create()
{
	//ステージのポインタ
	CStage * pStage = NULL;
	//もしステージのポインタをNULLだった場合
	if (pStage == NULL)
	{
		//ステージのメモリ確保
		pStage = new CStage;
	}
	//もしステージのポインタをNULLじゃない場合
	if (pStage != NULL)
	{
		//ステージの初期化関数呼び出し
		pStage->Init();
	}
	//ステージのポインタを返す
	return pStage;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CStage::Init(void)
{
	//初期全生成処理関数呼び出し
	InitCreateAll();
	int nLife = 0;	//体力
	//オブジェクトの最大数分回す
	for (int nCount = 0; nCount < 5; nCount++)
	{
		//もしオブジェクトのポインタがNULLじゃない場合
		if (m_apObject[nCount] != NULL)
		{
			//ライフを加算する
			nLife += m_apObject[nCount]->GetLife();
		}
	}
	//体力を保存する
	m_nLife = nLife;
	
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CStage::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CStage::Update(void)
{
	int nLife = 0;	//体力
	//オブジェクトの最大数分回す
	for (int nCount = 0; nCount < 5; nCount++)
	{
		//もしオブジェクトのポインタがNULLじゃない場合
		if (m_apObject[nCount] != NULL)
		{
			//ライフを加算する
			nLife += m_apObject[nCount]->GetLife();
		}
	}
	//体力を保存する
	m_nLife = nLife;
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CStage::Draw(void)
{
}

//=============================================================================
// 初期全生成処理関数
//=============================================================================
void CStage::InitCreateAll(void)
{
	m_apObject[0] = CStoneHouse::Create(D3DXVECTOR3(1100.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	m_apObject[1] = CStoneHouse::Create(D3DXVECTOR3(800.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	m_apObject[2] = CStoneHouse::Create(D3DXVECTOR3(500.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	m_apObject[3] = CWoodHouse::Create(D3DXVECTOR3(-850.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	m_apObject[4] = CWoodHouse::Create(D3DXVECTOR3(-900.0f, 0.0f, 750.0f), D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f));
	m_apObject[5] = CWoodHouse::Create(D3DXVECTOR3(1050.0f, 0.0f, 750.0f), D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f));
	m_apObject[5] = CFountain::Create(D3DXVECTOR3(20.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));



	CFence::Create(D3DXVECTOR3(600.0f, 0.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CFence::Create(D3DXVECTOR3(-600.0f, 0.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CFence::Create(D3DXVECTOR3(-1150.0f, 0.0f, 550.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	CFence::Create(D3DXVECTOR3(-1150.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	CFence::Create(D3DXVECTOR3(1275.0f, 0.0f, 550.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	CFence::Create(D3DXVECTOR3(1275.0f, 0.0f, -550.0f), D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));
	CFence::Create(D3DXVECTOR3(600.0f, 0.0f, -1225.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CFence::Create(D3DXVECTOR3(-600.0f, 0.0f, -1225.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CCorpse::Create(D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}