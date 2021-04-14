//=============================================================================
//
// UI�p���e�̃e�N�X�`������ [ui_bomb_texture.h]
// Author : ��K������
//
//=============================================================================
#ifndef _UI_BOMB_TEXTURE_H_
#define _UI_BOMB_TEXTURE_H_

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
class CUIBombTexture
{
public:
	CUIBombTexture();
	~CUIBombTexture();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CUIBombTexture * Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetBombTexture(int nAlpha);
	void SetPosition(D3DXVECTOR3 Position);
	void SetSize(D3DXVECTOR3 Size);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//�o�b�t�@
	D3DXVECTOR3 m_Position;					//�ʒu
	D3DXVECTOR3 m_Size;						//�T�C�Y
	int m_nPatternAnim;						//�A�j���p�^�[��
};
#endif