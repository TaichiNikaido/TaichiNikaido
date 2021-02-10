//=============================================================================
//
// 背景 [background.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"

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
class CBackground :public CScene2d
{
public:
	CBackground(int nPriority = PRIORITY_BG);
	~CBackground();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetFlame(int nFlame);
private:
	int m_nPatternAnime;	//パターンアニメ
	int m_nCountAnime;		//カウントアニメ
	int m_nFlame;			//切り替えるフレーム
};
#endif