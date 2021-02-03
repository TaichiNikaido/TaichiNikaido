//=============================================================================
//
// UI�p�������� [ui_number_texture.h]
// Author : ��K������
//
//=============================================================================
#ifndef _UI_NUMBER_TEXTURE_H_
#define _UI_NUMBER_TEXTURE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_NUMBER (8)

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CUINumberTexture
{
public:
	CUINumberTexture();
	~CUINumberTexture();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CUINumberTexture* Create(D3DXVECTOR3 Position,D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);
	void SetPostion(D3DXVECTOR3 Position);
	void SetSize(D3DXVECTOR3 Size);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_Position;					//�ʒu
	D3DXVECTOR3 m_Size;						//�T�C�Y
};
#endif