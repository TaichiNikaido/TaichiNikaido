//=============================================================================
//
// �e [shadow.h]
// Author : ��K������
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/polygon3d.h"
#include "Base/model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CShadow
{
public:
	CShadow();
	~CShadow();
	static CShadow * Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
	void SetTexture(D3DXVECTOR2 aTexture[NUM_VERTEX]);
private:
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���N�X
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR2	m_aTexture[NUM_VERTEX];		//�e�N�X�`����UV���W
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Size;
	D3DXCOLOR m_Color;
	float m_fLength;
	float m_fAngle;
	float m_fScale;
};
#endif