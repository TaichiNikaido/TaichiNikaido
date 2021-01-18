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
#include "scene.h"
#include "button.h"

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
	void SetButtonUI(void);
	void Input(void);
	void Select(void);
private:
	typedef struct
	{
		int nCount;
		bool bTrigger;
	}IsCount;
	typedef struct
	{
		IsCount Up;
		IsCount Down;
		IsCount Right;
		IsCount Left;
	}IsPress;
	void CreateAll(void);
	IsPress m_IsTrigger;
	int   m_nButtonPosition;
	CButton * m_apButton[CButton::BUTTON_MAX];
};
#endif
