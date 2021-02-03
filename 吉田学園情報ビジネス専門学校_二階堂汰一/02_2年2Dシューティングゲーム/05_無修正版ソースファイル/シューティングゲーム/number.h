//=============================================================================
//
// number処理 [number.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NUMBER "data/TEXTURE/number000.png"
#define MAX_NUMBER 10
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CNumber
{
public:
	CNumber();
	~CNumber();
	static HRESULT Load(void);
	static void Unload(void);
	static CNumber * Create(D3DXVECTOR3 pos, float SizeWidth,float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//バッファ
	int m_nPatternAnim;						//アニメパターン
};
#endif