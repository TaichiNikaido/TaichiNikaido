//=============================================================================
//
// ゲージの枠 [gaugeflame.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _FLAME_H_
#define _FLAME_H_

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
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGaugeFlame :public CScene2d
{
public:
	CGaugeFlame(int nPriority = PRIORITY_POLYGON2D);
	~CGaugeFlame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetAnimationPattern(int nAnimationPattern) { m_nAnimationPattern = nAnimationPattern; }
	void SetAnimationValue(float fAnimationValue) { m_fAnimationValue = fAnimationValue; }
	void SetScriptPass(char * pScriptPass) { m_apScriptPass[0] = pScriptPass; }
private:
	int m_nAnimationPattern;				//アニメーションパターン
	float m_fAnimationValue;				//アニメーションの値
	char * m_apScriptPass[MAX_PASS_LETTER];	//スクリプトパス
};
#endif