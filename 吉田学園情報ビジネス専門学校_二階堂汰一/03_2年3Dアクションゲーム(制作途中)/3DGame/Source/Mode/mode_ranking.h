//=============================================================================
//
// ランキングモード [mode_ranking.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MODE_RANKING_H_
#define _MODE_RANKING_H_

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
class CRankingMode : CScene
{
public:
	CRankingMode();
	~CRankingMode();
	static CRankingMode * Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Input(void);
	void CreateAll(void);
};
#endif
