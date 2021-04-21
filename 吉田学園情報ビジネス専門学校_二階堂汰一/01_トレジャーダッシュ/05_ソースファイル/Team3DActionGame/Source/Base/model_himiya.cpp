//===============================================
//
// 3Dモデル処理 (scene3d.cpp)
// Author : 樋宮匠
//
//===============================================

//========================
// インクルードファイル
//========================
#include "model_himiya.h"
#include "manager.h"
#include "renderer.h"

//========================================
// 静的メンバ変数宣言
//========================================

//=============================================================================
// コンストラクタ
//=============================================================================
CModelHimiya::CModelHimiya(int nPriority) : CScene(nPriority)
{
    m_pTexture = NULL;
    m_pBuffMat = NULL;
    m_pMesh = NULL;
    m_nNumMat = 0;
    D3DXMatrixIdentity(&m_mtxWorld);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CModelHimiya::~CModelHimiya()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CModelHimiya::Init(void)
{
    m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CModelHimiya::Uninit(void)
{
    Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CModelHimiya::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CModelHimiya::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    D3DXMATRIX mtxRot, mtxTrans, mtxScale;
    D3DMATERIAL9 matDef;
    D3DXMATERIAL *pMat;

    D3DXMatrixIdentity(&m_mtxWorld);

    D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

    D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

    pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

    pDevice->GetMaterial(&matDef);

    pDevice->SetTexture(0, m_pTexture);

    ZeroMemory(&matDef, sizeof(D3DMATERIAL9));

    pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < m_nNumMat; nCntMat++)
    {
        pMat[nCntMat].MatD3D.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

        pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

        m_pMesh->DrawSubset(nCntMat);
    }

    pDevice->SetMaterial(&matDef);

    pDevice->SetTexture(0, NULL);
}

//=============================================================================
// メッシュ割り当て
//=============================================================================
void CModelHimiya::BindMesh(const LPD3DXMESH pMesh, const LPD3DXBUFFER pBuffMat, const DWORD nNumMat)
{
    m_pMesh = pMesh;
    m_pBuffMat = pBuffMat;
    m_nNumMat = nNumMat;
}

//=============================================================================
// テクスチャ割り当て
//=============================================================================
void CModelHimiya::BindTexture(const LPDIRECT3DTEXTURE9 pTex)
{
    m_pTexture = pTex;
}
