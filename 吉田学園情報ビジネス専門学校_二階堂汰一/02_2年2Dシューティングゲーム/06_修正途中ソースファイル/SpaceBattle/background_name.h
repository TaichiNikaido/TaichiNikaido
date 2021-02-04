//=============================================================================
//
// 名前入力背景 [background_name.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BACKGROUND_NAME_H_
#define _BACKGROUND_NAME_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "background.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBackgroundName :public CBackground
{
public:
	CBackgroundName(int nPriority = 1);
	~CBackgroundName();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CBackgroundName * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
};
#endif