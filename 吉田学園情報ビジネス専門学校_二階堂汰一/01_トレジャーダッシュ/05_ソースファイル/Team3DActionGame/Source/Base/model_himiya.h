//====================================================================
//
// 3Dモデル処理 (scene3d.h)
// Author : 樋宮匠
//
//====================================================================
#ifndef _MODEL_HIMIYA_H_
#define _MODEL_HIMIYA_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//================================================
// クラス宣言
//================================================

// 3Dモデルクラス
class CModelHimiya : public CScene
{
public:
    CModelHimiya(int nPriority = OBJTYPE_DEFAULT);
    virtual ~CModelHimiya();

    virtual HRESULT Init(void);
    virtual void Uninit(void);
    virtual void Update(void);
    virtual void Draw(void);
    void BindMesh(const LPD3DXMESH pMesh, const  LPD3DXBUFFER pBuffMat, const DWORD nNumMat);
    void BindTexture(const LPDIRECT3DTEXTURE9 pTex);
    void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
    void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
    void SetScale(const D3DXVECTOR3 scale) { m_scale = scale; }

    D3DXVECTOR3 GetPos(void) { return m_pos; }
    D3DXVECTOR3 GetRot(void) { return m_rot; }
    D3DXVECTOR3 GetScale(void) { return m_scale; }

private:
    LPDIRECT3DTEXTURE9		m_pTexture;
    LPD3DXMESH				m_pMesh;
    LPD3DXBUFFER			m_pBuffMat;
    DWORD					m_nNumMat;
    D3DXMATRIX			    m_mtxWorld;		// ワールドマトリックス
    D3DXVECTOR3				m_pos;			// 座標
    D3DXVECTOR3				m_rot;			// 回転
    D3DXVECTOR3				m_scale;
};

#endif