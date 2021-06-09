//=============================================================================
//
// ポーズ背景 [pause_bg.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _PAUSE_BG_H_
#define _PAUSE_BG_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPauseBG :public CScene2d
{
public:
	CPauseBG(int nPriority = PRIORITY_BG);
	~CPauseBG();
	static CPauseBG * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
};
#endif