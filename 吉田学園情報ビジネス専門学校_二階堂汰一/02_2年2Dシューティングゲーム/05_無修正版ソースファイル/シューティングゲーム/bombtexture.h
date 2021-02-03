//=============================================================================
//
// 爆弾のテクスチャ処理 [bombtexture.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BOMBTEXTURE_H_
#define _BOMBTEXTURE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_BOMB "data/TEXTURE/bomb.png"	//ボムのテクスチャの保存先

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBombTexture
{
public:
	CBombTexture();
	~CBombTexture();
	static HRESULT Load(void);
	static void Unload(void);
	static CBombTexture * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetBombTexture(int nAlpha);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//バッファ
	int m_nPatternAnim;						//アニメパターン
};
#endif