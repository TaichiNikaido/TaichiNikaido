//=============================================================================
//
// 危険地帯 [warning.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _WARNING_H_
#define _WARNING_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WARNING "data/TEXTURE/warning.png"	//テテクスチャの保存先
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CWarning :public CScene2d
{
public:
	CWarning();
	~CWarning();
	static HRESULT Load(void);
	static void Unload(void);
	static CWarning * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_vpos[NUM_VERTEX];	//頂点座標
	D3DCOLOR m_col[NUM_VERTEX];		//色
	float m_fWidth;					//幅
	float m_fHeight;				//高さ
	int m_nColCount;
	int m_nCount;
};
#endif