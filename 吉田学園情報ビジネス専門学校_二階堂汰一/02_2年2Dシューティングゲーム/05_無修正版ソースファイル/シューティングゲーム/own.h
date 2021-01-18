//=============================================================================
//
// 自機の表示処理 [own.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _OWN_H_
#define _OWN_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_OWN "data/TEXTURE/Battleship.png"	//自機のテクスチャの保存先
#define MAX_OWN 5	//自機の最大数
//*****************************************************************************
// クラス定義
//*****************************************************************************
class COwn
{
public:
	COwn();
	~COwn();
	static HRESULT Load(void);
	static void Unload(void);
	static COwn * Create(D3DXVECTOR3 pos,float SizeWidth,float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos,float SizeWidth,float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetOwn(int nAlpha);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//バッファ
	int m_nPatternAnim;	//アニメパターン
};
#endif