//================================================
//
// 肉の所持数処理 [Meat.h]
// Author : 佐藤颯紀
//
//================================================

#ifndef _MEAT_H_
#define _MEAT_H_

//================================================
//インクルードファイル
//================================================
#include "Base/main.h"
#include "Base/scene.h"
#include "number.h"

//================================================
//マクロ定義
//================================================
#define MEATE_MAX_DIGITS	(2)			// 肉の最大桁数
#define MEAT_NUMBER_POS_X	(1790.0f)	// 肉の所持数のX座標
#define MEAT_NUMBER_POS_Y	(350.0f)	// 肉の所持数のY座標
#define MEAT_NUMBER_SIZE	(35.0f)		// 肉の所持数のサイズ
#define MEAT_POSSESSION		(3)			// 肉の初期の数

//================================================
//クラス宣言
//================================================
class CMeatUI : public CScene
{
public:
	CMeatUI(int nPriority = OBJTYPE_DEFAULT);
	~CMeatUI();

	static CMeatUI *Create();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static int GetMeat(void) { return m_nMeat; }	// 肉の取得

private:
	CNumber *m_apNumber[MEATE_MAX_DIGITS];	// 桁数
	static int m_nMeat;						// 肉
};

#endif // ! _UI_NUMBER_H_
