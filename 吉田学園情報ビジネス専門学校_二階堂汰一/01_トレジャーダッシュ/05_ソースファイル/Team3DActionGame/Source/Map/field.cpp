//===============================================
//
// フィールド処理 (field.cpp)
// Author : 樋宮匠
//
//===============================================

#define _CRT_SECURE_NO_WARNINGS

//========================
// インクルードファイル
//========================
#include "field.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include <stdio.h>
#include "tree.h"
#include "wood.h"
#include "Item/dia.h"
#include "needle.h"

//========================================
// 静的メンバ変数宣言
//========================================

//=============================================================================
// コンストラクタ
// Author : 樋宮匠
//=============================================================================
CField::CField()
{
	for (int nCountHeight = 0; nCountHeight < FIELD_HEIGHT; nCountHeight++)
	{
		for (int nCountWidth = 0; nCountWidth < FIELD_WIDTH; nCountWidth++)
		{
			m_apTile[nCountHeight][nCountWidth] = NULL;
			m_aGround[nCountHeight][nCountWidth] = 0;
		}
	}
}

//=============================================================================
// デストラクタ
// Author : 樋宮匠
//=============================================================================
CField::~CField()
{
}

//=============================================================================
// 初期化処理
// Author : 樋宮匠
//=============================================================================
HRESULT CField::Init(void)
{
	return S_OK;
}

//=============================================================================
// 終了処理
// Author : 樋宮匠
//=============================================================================
void CField::Uninit(void)
{
	for (int nCountHeight = 0; nCountHeight < FIELD_HEIGHT; nCountHeight++)
	{
		for (int nCountWidth = 0; nCountWidth < FIELD_WIDTH; nCountWidth++)
		{
			// 中身があるなら
			if (m_apTile[nCountHeight][nCountWidth] != NULL)
			{
				// 終了処理
				m_apTile[nCountHeight][nCountWidth]->Uninit();

				// メモリ開放
				delete m_apTile[nCountHeight][nCountWidth];
				m_apTile[nCountHeight][nCountWidth] = NULL;
			}
		}
	}

	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
// Author : 樋宮匠
//=============================================================================
void CField::Update(void)
{
	for (int nCountHeight = 0; nCountHeight < FIELD_HEIGHT; nCountHeight++)
	{
		for (int nCountWidth = 0; nCountWidth < FIELD_WIDTH; nCountWidth++)
		{
			// 中身があるなら
			if (m_apTile[nCountHeight][nCountWidth] != NULL)
			{
				m_apTile[nCountHeight][nCountWidth]->Update();
			}
		}
	}
}

//=============================================================================
// 描画処理
// Author : 樋宮匠
//=============================================================================
void CField::Draw(void)
{
	for (int nCountHeight = 0; nCountHeight < FIELD_HEIGHT; nCountHeight++)
	{
		for (int nCountWidth = 0; nCountWidth < FIELD_WIDTH; nCountWidth++)
		{
			// 中身があるなら
			if (m_apTile[nCountHeight][nCountWidth] != NULL)
			{
				m_apTile[nCountHeight][nCountWidth]->Draw();
			}
		}
	}
}

//=============================================================================
// マップデータ読み込み処理
// Author : 樋宮匠
//=============================================================================
void CField::LoadMapData(TYPE type, int nWidth, int nDepth)
{
	FILE *pFile = NULL;
	int nLoadHeight = 0;
	int nLoadWidth = 0;

	pFile = fopen("./data/MAPS/Map_01.csv", "r");

	// 開けた
	if (pFile != NULL)
	{
		for (int nCountMap = 0; nCountMap < nWidth * nDepth; nCountMap++)
		{
			while (fscanf(pFile, "%d,", &m_aGround[nLoadHeight][nLoadWidth]) != EOF)
			{
				nLoadWidth++;
				if (nLoadWidth >= nWidth)
				{
					nLoadWidth = 0;
					nLoadHeight++;
				}
			}
		}

		fclose(pFile);
	}
	// 開けない
	else
	{
		printf("開けれませんでした\n");
	}
}

//=============================================================================
// インスタンス生成処理
// Author : 樋宮匠
//=============================================================================
CField * CField::Create(TYPE type, int nWidth, int nDepth)
{
	CField *m_pField;

	m_pField = new CField;
	m_pField->Init();

	// フィールド読み込み
	m_pField->LoadMapData(type, nWidth, nDepth);

	// フィールド設置
	m_pField->SetField(nWidth, nDepth);

	return m_pField;
}

//=============================================================================
// フィールド生成処理
// Author : 樋宮匠
//=============================================================================
void CField::SetField(int nWidth, int nDepth)
{
	int nHeight = 0;

	for (int nCountHeight = 0; nCountHeight < nDepth; nCountHeight++)
	{
		for (int nCountWidth = 0; nCountWidth < nWidth; nCountWidth++)
		{
			switch (m_aGround[nHeight][nCountWidth])
			{
			case CTile::TILE_DIRT:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_DIRT);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_GRASS:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_GRASS);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_TREE_DIRT:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_TREE_DIRT);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));

				CTree::Create(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_TREE_GRASS:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_TREE_GRASS);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));

				CTree::Create(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_WOOD_DIRT:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_WOOD_DIRT);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));

				CWood::Create(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_WOOD_GRASS:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_WOOD_GRASS);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));

				CWood::Create(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_MUD:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_MUD);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_DIA_DIRT:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_DIA_DIRT);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));

				CDia::Create(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 50.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_NEEDLE:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_DIRT);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));

				CNeedle::Create(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_DIA_MUD:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_DIA_MUD);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));

				CDia::Create(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 50.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_CHECK_POINT:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_CHECK_POINT);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;

			case CTile::TILE_GOAL:
				m_apTile[nCountHeight][nCountWidth] = new CTile;
				m_apTile[nCountHeight][nCountWidth]->Init(CTile::TILE_GOAL);
				m_apTile[nCountHeight][nCountWidth]->SetPos(D3DXVECTOR3(-nCountWidth * TILE_SIZE, 0.0f, nCountHeight * TILE_SIZE));
				break;
			default:
				break;
			}
		}

		nHeight++;
	}
}
