//===============================================
//
// 肉処理 (meat.cpp)
// Author : 樋宮匠
//
//===============================================

//========================
// インクルードファイル
//========================
#include "meat.h"
#include "Base/manager.h"
#include "Base/renderer.h"
#include "Character/enemy.h"
#include "Mode/mode_game.h"
#include "Character/player.h"

//========================
// 静的メンバ変数宣言
//========================
LPD3DXMESH	CMeat::m_pMesh = NULL;
LPD3DXBUFFER CMeat::m_pBuffMat = NULL;
DWORD CMeat::m_nNumMat = NULL;
LPDIRECT3DTEXTURE9 CMeat::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CMeat::CMeat(int nPriority) : CModelHimiya(nPriority)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
// Author : 樋宮匠
//=============================================================================
CMeat::~CMeat()
{
}

//=============================================================================
// 初期化処理
// Author : 樋宮匠
//=============================================================================
HRESULT CMeat::Init(void)
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
void CMeat::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// 更新処理
// Author : 樋宮匠
//=============================================================================
void CMeat::Update(void)
{
	// プレイヤーとの当たり判定処理
	CEnemy *pEnemy = CGameMode::GetEnemy();
	D3DXVECTOR3 EnemyPosition = pEnemy->GetPos();
	CPlayer *pPlayer = CGameMode::GetPlayer();
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (EnemyPosition.x >= pos.x - COLLISION_SIZE_MEAT.x / 2 &&
		EnemyPosition.x <= pos.x + COLLISION_SIZE_MEAT.x / 2 &&
		EnemyPosition.z >= pos.z - COLLISION_SIZE_MEAT.z / 2 &&
		EnemyPosition.z <= pos.z + COLLISION_SIZE_MEAT.z / 2)
	{
		pEnemy->SetbEat(true);
		Uninit();
	}
	else
	{
		// 回転させる
		rot.y += D3DXToRadian(1);
		SetRot(rot);
		CModelHimiya::Update();
	}
	// コンティニューした場合
	if (pPlayer->GetState() == CPlayer::STATE_DEATH)
	{
		// 終了
		Uninit();
		return;
	}
}

//=============================================================================
// 描画処理
// Author : 樋宮匠
//=============================================================================
void CMeat::Draw(void)
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
HRESULT CMeat::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("Data/model/meet.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/meet_texture.jpg", &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャ・モデルデータ破棄処理
// Author : 樋宮匠
//=============================================================================
void CMeat::Unload(void)
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
CMeat * CMeat::Create(D3DXVECTOR3 pos)
{
	CMeat *pMeat = NULL;
	pMeat = new CMeat;
	pMeat->Init();
	pMeat->SetPos(pos);
	return pMeat;
}
