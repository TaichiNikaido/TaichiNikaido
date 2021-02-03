//=============================================================================
//
// ���@��UI���� [ownui.h]
// Author : ��K������
//
//=============================================================================
#ifndef _OWNUI_H_
#define _OWNUI_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OWNUI_SIZE_WIDTH 30
#define OWNUI_SIZE_HEIGHT 30
//*****************************************************************************
// �N���X��`
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
	int m_nOwnUI;	//���@��UI
};
#endif