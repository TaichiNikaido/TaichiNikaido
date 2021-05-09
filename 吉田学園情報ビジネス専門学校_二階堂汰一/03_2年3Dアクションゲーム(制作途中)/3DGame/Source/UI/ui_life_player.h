//=============================================================================
//
// プレイヤーの体力UI [ui_life_player.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _UI_LIFE_PLAYER_H_
#define _UI_LIFE_PLAYER_H_

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
class CPlayerLifeUI :public CScene
{
public:
	CPlayerLifeUI(int nPriority = PRIORITY_UI);
	~CPlayerLifeUI();
	static CPlayerLifeUI * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
};
#endif