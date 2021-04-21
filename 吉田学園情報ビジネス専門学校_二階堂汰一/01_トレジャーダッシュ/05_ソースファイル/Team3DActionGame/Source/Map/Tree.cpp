//===============================================
//
// 木処理 (tree.cpp)
// Author : 樋宮匠
//
//===============================================

//========================
// インクルードファイル
//========================
#include "tree.h"
#include "Base/manager.h"
#include "Base/renderer.h"

//========================
// 静的メンバ変数宣言
//========================
LPD3DXMESH	CTree::m_pMesh = NULL;
LPD3DXBUFFER CTree::m_pBuffMat = NULL;
DWORD CTree::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CTree::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CTree::CTree()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
// Author : 樋宮匠
//=============================================================================
CTree::~CTree()
{
}

//=============================================================================
// 初期化処理
// Author : 樋宮匠
//=============================================================================
HRESULT CTree::Init(void)
{
	CModelHimiya::Init();

	BindMesh(m_pMesh, m_pBuffMat, m_nNumMat);

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
// Author : 樋宮匠
//=============================================================================
void CTree::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// 更新処理
// Author : 樋宮匠
//=============================================================================
void CTree::Update(void)
{
	CModelHimiya::Update();
}

//=============================================================================
// 描画処理
// Author : 樋宮匠
//=============================================================================
void CTree::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModelHimiya::Draw();
}

//=============================================================================
// テクスチャ・モデルデータ読み込み処理
// Author : 樋宮匠
//=============================================================================
HRESULT CTree::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/MODEL/tree.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	return S_OK;
}

//=============================================================================
// テクスチャ・モデルデータ破棄処理
// Author : 樋宮匠
//=============================================================================
void CTree::Unload(void)
{
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// インスタンス生成処理
// Author : 樋宮匠
//=============================================================================
CTree * CTree::Create(D3DXVECTOR3 pos)
{
	CTree *pCube = NULL;
	pCube = new CTree;
	pCube->Init();
	pCube->SetPos(pos);
	return pCube;
}
