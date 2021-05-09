//=============================================================================
//
// �̗�UI [ui_life.h]
// Author : ��K������
//
//=============================================================================
#ifndef _UI_LIFE_H_
#define _UI_LIFE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CGauge;

//*****************************************************************************
// �N���X��`
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
	D3DXVECTOR3 m_Position;							//�ʒu
	D3DXVECTOR3 m_Size;								//�T�C�Y
	D3DXCOLOR m_Color;								//�F
	int m_nMaxLife;									//�̗͂̍ő�l
	int m_nLife;									//�̗�
	CGauge * m_pGauge;								//�Q�[�W�̃|�C���^
};
#endif