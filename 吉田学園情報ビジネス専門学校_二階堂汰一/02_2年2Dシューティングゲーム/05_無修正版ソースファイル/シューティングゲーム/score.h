//=============================================================================
//
// score処理 [score.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "scene.h"
#include "number.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCORE_SIZE_WIDTH 25		//スコアの幅のサイズ
#define SCORE_SIZE_HEIGHT 25	//スコアの縦のサイズ
#define ADDSCORE_ITEM 500		//アイテムによって加算されるスコア値

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScore :public CScene
{
public:
	CScore(int nPriority = 5);
	~CScore();
	static CScore * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddScore(int nValue);
	void SubScore(int nValue);
	void SetScore(int nScore);
private:
	CNumber *m_apNumber[MAX_NUMBER];
	int m_nScore;	//スコア
};
#endif