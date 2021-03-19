//=============================================================================
//
// ボタン [button.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BUTTON_H_
#define _BUTTON_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CButton :public CScene2d
{
public:
	typedef enum
	{
		BUTTON_NONE = -1,
		BUTTON_START,
		BUTTON_TUTORIAL,
		BUTTON_RANKING,
		BUTTON_EXIT,
		BUTTON_MAX
	}BUTTON;
	CButton();
	~CButton();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void NotSelectColor(void);
	void SelectColor(void);
	void SelectSound(void);
	virtual void Press(void) = 0;
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[BUTTON_MAX];	//テクスチャへのポインタ
};
#endif