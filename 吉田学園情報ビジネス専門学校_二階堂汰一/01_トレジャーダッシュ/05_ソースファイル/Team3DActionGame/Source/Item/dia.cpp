//===============================================
//
// ダイア処理 (dia.cpp)
// Author : 樋宮匠
//
//===============================================

//========================
// インクルードファイル
//========================
#include "dia.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Character/player.h"
#include "Mode/mode_game.h"
#include "Effect/dia_particle.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define EFFECT_POS (D3DXVECTOR3(pos.x,pos.y,pos.z + 20.0f))
//========================
// 静的メンバ変数宣言
//========================
LPD3DXMESH	CDia::m_pMesh = NULL;
LPD3DXBUFFER CDia::m_pBuffMat = NULL;
DWORD CDia::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CDia::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CDia::CDia(int nPrirority) : CModelHimiya(nPrirority)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
// Author : 樋宮匠
//=============================================================================
CDia::~CDia()
{
}

//=============================================================================
// 初期化処理
// Author : 樋宮匠
//=============================================================================
HRESULT CDia::Init(void)
{
	CModelHimiya::Init();

	BindMesh(m_pMesh, m_pBuffMat, m_nNumMat);
	BindTexture(m_pTexture);

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
// Author : 樋宮匠
//=============================================================================
void CDia::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// 更新処理
// Author : 樋宮匠
//=============================================================================
void CDia::Update(void)
{
	// プレイヤーとの当たり判定処理
	CPlayer *pPlayer = CGameMode::GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (playerPos.x >= pos.x - COLLISION_SIZE_DIA.x / 2 &&
		playerPos.x <= pos.x + COLLISION_SIZE_DIA.x / 2 && 
		playerPos.z >= pos.z - COLLISION_SIZE_DIA.z / 2 && 
		playerPos.z <= pos.z + COLLISION_SIZE_DIA.z / 2 )
	{
		pPlayer->AddDiamond(1);
		CDia_Particle::DiaEffect_Create(EFFECT_POS);
		Uninit();
	}
	else
	{
		// 回転させる
		rot.y += D3DXToRadian(1);
		SetRot(rot);
		CModelHimiya::Update();
	}
}

//=============================================================================
// 描画処理
// Author : 樋宮匠
//=============================================================================
void CDia::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	CModelHimiya::Draw();

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// テクスチャ・モデルデータ読み込み処理
// Author : 樋宮匠
//=============================================================================
HRESULT CDia::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/MODEL/dia.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/dia.jpg", &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャ・モデルデータ破棄処理
// Author : 樋宮匠
//=============================================================================
void CDia::Unload(void)
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
CDia * CDia::Create(D3DXVECTOR3 pos)
{
	CDia *pCube = NULL;
	pCube = new CDia;
	pCube->Init();
	pCube->SetPos(pos);
	return pCube;
}
