//=============================================================================
//
// �r���{�[�h [billboard.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

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

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBillboard :public CScene
{
public:
	CBillboard();
	~CBillboard();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
	void SetMove(D3DXVECTOR3 Move) { m_Move = Move; }
	void SetTexture(D3DXVECTOR2 aTexture[NUM_VERTEX]);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	D3DXVECTOR3 GetPosition(void) { return m_Position; };
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; };
	D3DXVECTOR3 GetSize(void) { return m_Size; };
	D3DXCOLOR GetColor(void) { return m_Color; };
private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
	D3DXMATRIX m_mtxWorld;					//�s��v�Z�p
	D3DXVECTOR3 m_Position;					//�ʒu
	D3DXVECTOR3 m_Rotation;					//��]
	D3DXVECTOR3 m_Size;						//�T�C�Y
	D3DXCOLOR m_Color;						//�J���[
	D3DXVECTOR3 m_Move;						//�ړ���
	D3DXVECTOR2	m_aTexture[NUM_VERTEX];		//�e�N�X�`����UV���W
};
#endif