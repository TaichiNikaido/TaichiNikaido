//=============================================================================
//
// 敵 [enemy.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

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
class CEnemy :public CScene2d
{
public:
	typedef enum
	{
		STATE_NONE = -1,
		STATE_ATTACK,
		STATE_MOVE,
		STATE_MAX
	}STATE;
	CEnemy(int nPriority = PRIORITY_ENEMY);
	~CEnemy();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);
	void SetMove(D3DXVECTOR3 Move) { m_Move = Move; }
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetState(STATE State) { m_State = State; }
	D3DXVECTOR3 GetMove(void) { return m_Move; }
	int GetLife(void) { return m_nLife; }
	STATE GetState(void) { return m_State; }
private:
	void SubLife(void);
	D3DXVECTOR3 m_Move;		//移動量
	int m_nLife;			//体力
	int m_nChangeColorTime;	//色変更時間
	bool m_bHit;			//ヒット
	STATE m_State;			//状態
};
#endif