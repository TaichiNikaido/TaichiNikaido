//=============================================================================
//
// チュートリアルモード [mode_tutorial.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MODE_TUTORIAL_H_
#define _MODE_TUTORIAL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTutorialMode : CScene
{
public:
	CTutorialMode();
	~CTutorialMode();
	static CTutorialMode * Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetbPouse(bool bPouse) { m_bPouse = bPouse; }
private:
	void Input(void);
	void CreateAll(void);
	bool m_bPouse;	//ポーズを使用してるか
};
#endif
