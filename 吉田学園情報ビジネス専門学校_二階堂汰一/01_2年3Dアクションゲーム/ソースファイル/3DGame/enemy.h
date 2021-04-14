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
#include "character.h"
#include "model.h"
#include "motion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemy : public CCharacter
{
public:
	CEnemy();
	~CEnemy();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetCollisionSize(D3DXVECTOR3 CollisionSize) { m_CollisionSize = CollisionSize; }
	void SetMove(D3DXVECTOR3 Move) { m_Move = Move; }
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetAttack(int nAttack) { m_nAttack = nAttack; }
	void SetScriptPass(const char * ScriptPass) { m_apScriptPass[0] = ScriptPass; }
	D3DXVECTOR3 GetCollisionSize(void) { return m_CollisionSize; }
	int GetLife(void) { return m_nLife; }
	int GetAttack(void) { return m_nAttack; }
private:
	void Hit(void);
	void SubLife(void);
	void DataLoad(void);
	D3DXVECTOR3 m_CollisionSize;							//�Փ˔���p�T�C�Y
	D3DXVECTOR3 m_Move;										//�ړ���
	int m_nLife;											//�̗�
	int m_nAttack;											//�U����
	const char * m_apScriptPass[MAX_PASS_LETTER];			//�X�N���v�g�̃p�X
};
#endif