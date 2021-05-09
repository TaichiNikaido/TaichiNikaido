//=============================================================================
//
// 体力UI [ui_life.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _UI_LIFE_H_
#define _UI_LIFE_H_

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
class CGauge;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CLifeGaugeUI :public CScene
{
public:
	CLifeGaugeUI(int nPriority = PRIORITY_UI);
	~CLifeGaugeUI();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
	void SetMaxLife(int nMaxLife) { m_nMaxLife = nMaxLife; }
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetGauge(CGauge * pGauge) { m_pGauge = pGauge; }
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	D3DXVECTOR3 GetSize(void) { return m_Size; }
	D3DXCOLOR GetColor(void) { return m_Color; }
private:
	D3DXVECTOR3 m_Position;							//位置
	D3DXVECTOR3 m_Size;								//サイズ
	D3DXCOLOR m_Color;								//色
	int m_nMaxLife;									//体力の最大値
	int m_nLife;									//体力
	CGauge * m_pGauge;								//ゲージのポインタ
};
#endif