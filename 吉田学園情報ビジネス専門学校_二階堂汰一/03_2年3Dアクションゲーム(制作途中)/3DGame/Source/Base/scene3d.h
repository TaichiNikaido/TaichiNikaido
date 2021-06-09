//=============================================================================
//
// 3D�V�[�� [scene3d.h]
// Author : ��K������
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene3d :public CScene
{
public:
	CScene3d(int nPriority = PRIORITY_BASE);
	virtual ~CScene3d();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }
	D3DXVECTOR3 GetSize(void) { return m_Size; }
private:
	D3DXVECTOR3 m_Position;	//�ʒu
	D3DXVECTOR3 m_Rotation;	//��]�l
	D3DXVECTOR3 m_Size;		//�T�C�Y
};
#endif