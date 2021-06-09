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
#include "Base/scene3d.h"
#include "Base/model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObject :public CScene3d
{
public:
	CObject();
	~CObject();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetCollisionSize(D3DXVECTOR3 CollisionSize) { m_CollisionSize = CollisionSize; }
	void SetModelData(CModel::MODEL_DATA ModelData) { m_ModelData = ModelData; }
	bool GetbCollision(void) { return m_bCollision; }
private:
	void Collision(void);
	D3DXVECTOR3 m_CollisionSize;		//�Փ˔���p�̃T�C�Y
	bool m_bCollision;					//�Փ˂�����
	CModel::MODEL_DATA m_ModelData;		//���f���f�[�^
	CModel * m_pModel;					//���f���̃|�C���^
};
#endif