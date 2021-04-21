//=============================================================================
//
// ライフのUI [ui_life.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _UI_LIFE_H_
#define _UI_LIFE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/scene.h"
#include "Player/player.h"
#include "ui_life_texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUILifeTexture;

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CLifeUI :public CScene
{
public:
	CLifeUI(int nPriority = PRIORITY_UI);
	~CLifeUI();
	static CLifeUI * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetLife(int nScore);
private:
	CUILifeTexture * m_apLifeTexture[PLAYER_MAX_LIFE];	//UI用数字テクスチャへのポインタ
};
#endif