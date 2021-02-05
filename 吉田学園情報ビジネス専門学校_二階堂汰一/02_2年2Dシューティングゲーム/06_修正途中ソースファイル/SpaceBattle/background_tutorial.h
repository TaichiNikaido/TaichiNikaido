//=============================================================================
//
// チュートリアル背景 [background_tutorial.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BACKGROUND_TUTORIAL_H_
#define _BACKGROUND_TUTORIAL_H_

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
class CBackgroundTutorial :public CBackground
{
public:
	CBackgroundTutorial(int nPriority = 1);
	~CBackgroundTutorial();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CBackgroundTutorial * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		TEXTURE_NONE = -1,
		TEXTURE_KEYBOARD_GUID,
		TEXTURE_JOYSTICK_GUID,
		TEXTURE_MAX
	}TEXTURE;
	static LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_MAX];	//テクスチャへのポインタ
};
#endif