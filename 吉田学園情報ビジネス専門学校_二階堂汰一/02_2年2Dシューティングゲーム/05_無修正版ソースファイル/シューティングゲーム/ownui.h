//=============================================================================
//
// 自機のUI処理 [ownui.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _OWNUI_H_
#define _OWNUI_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OWNUI_SIZE_WIDTH 30
#define OWNUI_SIZE_HEIGHT 30
//*****************************************************************************
// クラス定義
//*****************************************************************************
class COwnUI :public CScene
{
public:
	COwnUI(int nPriority = 5);
	~COwnUI();
	static COwnUI * Create(D3DXVECTOR3 pos,float SizeWidth,float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos,float SizeWidth,float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetOwnUI(int nOwn);
	void AddOwnUI(int nValue);
	void SubOwnUI(int nValue);
private:
	COwn *m_apOwnUI[MAX_OWN];
	int m_nOwnUI;	//自機のUI
};
#endif