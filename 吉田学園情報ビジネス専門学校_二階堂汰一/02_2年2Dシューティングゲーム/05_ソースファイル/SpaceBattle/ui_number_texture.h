//=============================================================================
//
// UI用数字処理 [ui_number_texture.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _UI_NUMBER_TEXTURE_H_
#define _UI_NUMBER_TEXTURE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_NUMBER (8)

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CUINumberTexture
{
public:
	CUINumberTexture();
	~CUINumberTexture();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CUINumberTexture* Create(D3DXVECTOR3 Position,D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);
	void SetPostion(D3DXVECTOR3 Position);
	void SetSize(D3DXVECTOR3 Size);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;	//頂点バッファへのポインタ
	D3DXVECTOR3 m_Position;					//位置
	D3DXVECTOR3 m_Size;						//サイズ
};
#endif