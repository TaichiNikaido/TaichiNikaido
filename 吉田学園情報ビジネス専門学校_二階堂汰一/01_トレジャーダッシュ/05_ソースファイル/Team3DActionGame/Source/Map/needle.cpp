//===============================================
//
// 木処理 (tree.cpp)
// Author : 樋宮匠
//
//===============================================

//========================
// インクルードファイル
//========================
#include "needle.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Character/player.h"
#include "Mode/mode_game.h"
#include "Character/player.h"

//========================
// 静的メンバ変数宣言
//========================
LPD3DXMESH	CNeedle::m_pMesh = NULL;
LPD3DXBUFFER CNeedle::m_pBuffMat = NULL;
DWORD CNeedle::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CNeedle::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CNeedle::CNeedle()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//=============================================================================
// デストラクタ
// Author : 樋宮匠
//=============================================================================
CNeedle::~CNeedle()
{
}

//=============================================================================
// 初期化処理
// Author : 樋宮匠
//=============================================================================
HRESULT CNeedle::Init(void)
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
void CNeedle::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// 更新処理
// Author : 樋宮匠
//=============================================================================
void CNeedle::Update(void)
{
	// プレイヤーとの当たり判定処理
	CPlayer *pPlayer = CGameMode::GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 pos = GetPos();

	if (playerPos.x >= pos.x - COLLISION_SIZE_NEEDLE.x / 2 &&
		playerPos.x <= pos.x + COLLISION_SIZE_NEEDLE.x / 2 &&
		playerPos.y >= pos.y - COLLISION_SIZE_NEEDLE.y / 2 &&
		playerPos.y <= pos.y + COLLISION_SIZE_NEEDLE.y / 2 &&
		playerPos.z >= pos.z - COLLISION_SIZE_NEEDLE.z / 2 &&
		playerPos.z <= pos.z + COLLISION_SIZE_NEEDLE.z / 2)
	{
		if (pPlayer->GetState() != CPlayer::STATE_DEATH)
		{
			// プレイヤー死亡
			pPlayer->Death();
		}
	}
	else
	{
		CModelHimiya::Update();
	}
}

//=============================================================================
// 描画処理
// Author : 樋宮匠
//=============================================================================
void CNeedle::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModelHimiya::Draw();
}

//=============================================================================
// テクスチャ・モデルデータ読み込み処理
// Author : 樋宮匠
//=============================================================================
HRESULT CNeedle::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/MODEL/needle.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	return S_OK;
}

//=============================================================================
// テクスチャ・モデルデータ破棄処理
// Author : 樋宮匠
//=============================================================================
void CNeedle::Unload(void)
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
CNeedle * CNeedle::Create(D3DXVECTOR3 pos)
{
	CNeedle *pCube = NULL;
	pCube = new CNeedle;
	pCube->Init();
	pCube->SetPos(pos);
	return pCube;
}