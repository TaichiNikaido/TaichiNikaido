//=============================================================================
//
// 枠 [flame.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _FLAME_H_
#define _FLAME_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_FLAME1	"data/TEXTURE/ENEMY/name.png"
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFlame :public CScene2d
{
public:
	CFlame(int nPriority = 5);
	~CFlame();
	static HRESULT Load(void);
	static void Unload(void);
	static CFlame * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_vpos[NUM_VERTEX];			//頂点座標
	D3DCOLOR m_col[NUM_VERTEX];				//色
};
#endif