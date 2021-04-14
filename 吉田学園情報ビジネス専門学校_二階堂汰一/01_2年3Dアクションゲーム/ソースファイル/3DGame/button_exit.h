//=============================================================================
//
// 終了ボタン [button_exit.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BUTTON_EXIT_H_
#define _BUTTON_EXIT_H_

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
class CExitButton :public CButton
{
public:
	typedef enum
	{
		TEXTURE_NONE = -1,
		TEXTURE_ENGLISH,
		TEXTURE_JAPANESE,
		TEXTURE_MAX
	}TEXTURE_TYPE;
	CExitButton();
	~CExitButton();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CExitButton * Create(D3DXVECTOR3 Position,TEXTURE_TYPE TextureType);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Press(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_MAX];	//テクスチャのポインタ
	TEXTURE_TYPE m_TextureType;							//テクスチャの種類
};
#endif