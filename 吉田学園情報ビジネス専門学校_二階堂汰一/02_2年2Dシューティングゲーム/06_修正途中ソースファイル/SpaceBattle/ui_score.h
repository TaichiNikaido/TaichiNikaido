//=============================================================================
//
// スコアのUI [ui_score.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _UI_SCORE_H_
#define _UI_SCORE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"
#include "ui_number_texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUINumberTexture;

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScoreUI :public CScene
{
public:
	CScoreUI(int nPriority = 5);
	~CScoreUI();
	static CScoreUI * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(int nScore);
private:
	CUINumberTexture * m_apNumberTexture[MAX_NUMBER];	//UI用数字テクスチャへのポインタ
};
#endif