//=============================================================================
//
// 操作説明表示ボタン [button_controller_guid.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BUTTON_CONTROLLER_GUID_H_
#define _BUTTON_CONTROLLER_GUID_H_

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
class CControllerGuidButton :public CButton
{
public:
	CControllerGuidButton();
	~CControllerGuidButton();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CControllerGuidButton * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Press(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
};
#endif