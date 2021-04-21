//=============================================================================
//
// ���� [letter.h]
// Author : ��K������
//
//=============================================================================
#ifndef _LETTER_H_
#define _LETTER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************

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
class CLetter
{
public:
	CLetter();
	~CLetter();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CLetter* Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SelectColor(void);
	void NotSelectColor(void);
	void SetLetter(int nLetter);
	void SetPostion(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_Position;					//�ʒu
	D3DXVECTOR3 m_Size;						//�T�C�Y
	float m_fAlpha;							//�����x
};
#endif