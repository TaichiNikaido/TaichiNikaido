//===============================================
//
// 倒木処理 (wood.cpp)
// Author : 樋宮匠
//
//===============================================

//========================
// インクルードファイル
//========================
#include "wood.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Character/player.h"
#include "Mode/mode_game.h"

//========================
// 静的メンバ変数宣言
//========================
LPD3DXMESH	CWood::m_pMesh = NULL;
LPD3DXBUFFER CWood::m_pBuffMat = NULL;
DWORD CWood::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CWood::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CWood::CWood(int nPriority) : CModelHimiya(nPriority)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bHit = false;
}

//=============================================================================
// デストラクタ
// Author : 樋宮匠
//=============================================================================
CWood::~CWood()
{
}

//=============================================================================
// 初期化処理
// Author : 樋宮匠
//=============================================================================
HRESULT CWood::Init(void)
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
void CWood::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// 更新処理
// Author : 樋宮匠
//=============================================================================
void CWood::Update(void)
{
	CModelHimiya::Update();
}

//=============================================================================
// 描画処理
// Author : 樋宮匠
//=============================================================================
void CWood::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModelHimiya::Draw();
}

//=============================================================================
// テクスチャ・モデルデータ読み込み処理
// Author : 樋宮匠
//=============================================================================
HRESULT CWood::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/MODEL/wood.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	return S_OK;
}

//=============================================================================
// テクスチャ・モデルデータ破棄処理
// Author : 樋宮匠
//=============================================================================
void CWood::Unload(void)
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
CWood * CWood::Create(D3DXVECTOR3 pos)
{
	CWood *pCube = NULL;
	pCube = new CWood;
	pCube->Init();
	pCube->SetPos(pos);
	pCube->SetObjType(OBJTYPE_WOOD);
	return pCube;
}
