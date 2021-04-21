#pragma once
//====================================================================
//
// 木の処理 (tree.h)
// Author : 樋宮匠
//
//====================================================================
#ifndef _TREE_H_
#define _TREE_H_

//================================================
// インクルードファイル
//================================================
#include "Base/main.h"
#include "Base/model_himiya.h"

//================================================
// マクロ定義
//================================================
#define COLLISION_SIZE D3DXVECTOR3(200.0f, 100.0f, 200.0f)

//================================================
// クラス宣言
//================================================

// UIクラス
class CTree : public CModelHimiya
{
public:
	CTree();
	~CTree();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CTree *Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh;
	static LPD3DXBUFFER				m_pBuffMat;
	static DWORD					m_nNumMat;
	D3DXVECTOR3						m_rot;
};

#endif
