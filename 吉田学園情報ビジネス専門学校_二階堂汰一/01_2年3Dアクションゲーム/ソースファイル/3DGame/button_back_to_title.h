//=============================================================================
//
// タイトルに戻るボタン [button_back_to_title.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BUTTON_BACK_TOT_TITLE_H_
#define _BUTTON_BACK_TOT_TITLE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Button.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBackToTitleButton :public CButton
{
public:
	CBackToTitleButton();
	~CBackToTitleButton();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CBackToTitleButton * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Press(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
};
#endif