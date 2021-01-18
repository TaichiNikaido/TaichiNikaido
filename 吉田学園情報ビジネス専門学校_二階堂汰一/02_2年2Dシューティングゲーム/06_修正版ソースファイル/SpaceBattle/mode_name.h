//=============================================================================
//
// 名前入力モード [mode_name.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MODE_NAME_H_
#define _MODE_NAME_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CName;

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CNameMode : CScene
{
public:
	CNameMode();
	~CNameMode();
	static CNameMode * Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void CreateAll(void);
	CName * m_pName;
};
#endif
