//=============================================================================
//
// タイトルモード [mode_title.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MODE_TITLE_H_
#define _MODE_TITLE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/scene.h"
#include "button/button.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CButton;

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTitleMode : CScene
{
public:
	CTitleMode();
	~CTitleMode();
	static CTitleMode * Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void CreateAll(void);
};
#endif
