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
#include "scene.h"
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
class CEnemy : CScene
{
public:
	CEnemy();
	~CEnemy();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetCollisionSize(D3DXVECTOR3 CollisionSize) { m_CollisionSize = CollisionSize; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetMove(D3DXVECTOR3 Move) { m_Move = Move; }
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetAttack(int nAttack) { m_nAttack = nAttack; }
	void SetModelData(CModel::MODEL_DATA ModelData[MAX_PARTS]);
	void SetMotionPass(const char * MotionPass) { m_apMotionPass[0] = MotionPass; }
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	D3DXVECTOR3 GetCollisionSize(void) { return m_CollisionSize; }
	int GetLife(void) { return m_nLife; }
	int GetAttack(void) { return m_nAttack; }
private:
	void Hit(void);
	void SubLife(void);
	void Motion(void);
	D3DXVECTOR3 m_Position;									//�ʒu
	D3DXVECTOR3 m_Size;										//�T�C�Y
	D3DXVECTOR3 m_CollisionSize;							//�Փ˔���p�T�C�Y
	D3DXVECTOR3 m_Rotation;									//��]
	D3DXVECTOR3 m_Move;										//�ړ���
	int m_nLife;											//�̗�
	int m_nAttack;											//�U����
	const char * m_apMotionPass[MAX_PASS_LETTER];			//���[�V�����f�[�^�̃p�X
	CModel::MODEL_DATA m_aModelData[MAX_PARTS];			//���f���f�[�^
	CModel * m_apModel[MAX_PARTS];							//���f���̃|�C���^
	CMotion * m_pMotion;									//���[�V�����̃|�C���^
};
#endif