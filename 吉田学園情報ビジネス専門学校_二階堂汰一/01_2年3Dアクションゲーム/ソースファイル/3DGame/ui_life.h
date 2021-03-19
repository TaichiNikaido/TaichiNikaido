//=============================================================================
//
// ���C�t��UI [ui_life.h]
// Author : ��K������
//
//=============================================================================
#ifndef _UI_LIFE_H_
#define _UI_LIFE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

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
class CLifeUI :public CScene
{
public:
	CLifeUI();
	~CLifeUI();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetMaxLife(int nMaxLife) { m_nMaxLife = nMaxLife; }
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetGauge(CGauge * pGauge) { m_pGauge = pGauge; }
private:
	void DataLoad(void);
	D3DXVECTOR3 m_Position;							//�ʒu
	D3DXVECTOR3 m_Size;								//�T�C�Y
	D3DXCOLOR m_Color;								//�F
	int m_nMaxLife;									//�̗͂̍ő�l
	int m_nLife;									//�̗�
	const char * m_apDataPass[MAX_PASS_LETTER];		//�f�[�^�X�N���v�g�̃p�X
	CGauge * m_pGauge;								//�Q�[�W�̃|�C���^
};
#endif