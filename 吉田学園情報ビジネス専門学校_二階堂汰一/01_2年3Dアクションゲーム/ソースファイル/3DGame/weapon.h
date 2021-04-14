//=============================================================================
//
// ���� [weapon.h]
// Author : ��K������
//
//=============================================================================
#ifndef _WEAPON_H_
#define _WEAPON_H_

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
class CWeapon : public CScene
{
public:
	CWeapon();
	~CWeapon();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetCollisionSize(D3DXVECTOR3 CollisionSize) { m_CollisionSize = CollisionSize; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetModelData(CModel::MODEL_DATA ModelData) { m_aModelData = ModelData; }
	void SetParentModel(CModel * pParentModel) { m_pParentModel = pParentModel; }
private:
	void Collision(void);
	D3DXVECTOR3 m_Position;				//�ʒu
	D3DXVECTOR3 m_Size;					//�T�C�Y
	D3DXVECTOR3 m_CollisionSize;		//�Փ˔���p�T�C�Y
	D3DXVECTOR3 m_Rotation;				//��]
	CModel * m_pModel;					//���f���̃|�C���^
	CModel * m_pParentModel;			//�e���f���̃|�C���^
	CModel::MODEL_DATA m_aModelData;		//���f���f�[�^
};
#endif