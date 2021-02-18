//=============================================================================
//
// �G [enemy.h]
// Author : ��K������
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
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
	D3DXVECTOR3 m_Move;		//�ړ���
	int m_nLife;			//�̗�
	int m_nChangeColorTime;	//�F�ύX����
	bool m_bHit;			//�q�b�g
	STATE m_State;			//���
};
#endif