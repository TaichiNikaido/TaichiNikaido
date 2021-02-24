//=============================================================================
//
// �I�u�W�F�N�g [object.h]
// Author : ��K������
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObject : public CScene
{
public:
	CObject();
	~CObject();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetCollisionSize(D3DXVECTOR3 CollisionSize) { m_CollisionSize = CollisionSize; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetModelData(CModel::MODEL_DATA ModelData) { m_ModelData = ModelData; }
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	D3DXVECTOR3 GetCollisionSize(void) { return m_CollisionSize; }
	int GetLife(void) { return m_nLife; }
private:
	void SubLife(void);
	void Collision(void);
	D3DXVECTOR3 m_Position;				//�ʒu
	D3DXVECTOR3 m_Size;					//�T�C�Y
	D3DXVECTOR3 m_CollisionSize;		//�Փ˔���p�T�C�Y
	D3DXVECTOR3 m_Rotation;				//��]
	int m_nLife;						//�̗�
	CModel * m_pModel;					//���f���̃|�C���^
	CModel::MODEL_DATA m_ModelData;		//���f���f�[�^
};
#endif