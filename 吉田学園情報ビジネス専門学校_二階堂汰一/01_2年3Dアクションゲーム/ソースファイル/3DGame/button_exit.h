//=============================================================================
//
// �I���{�^�� [button_exit.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BUTTON_EXIT_H_
#define _BUTTON_EXIT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Button.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CExitButton :public CButton
{
public:
	typedef enum
	{
		TEXTURE_NONE = -1,
		TEXTURE_ENGLISH,
		TEXTURE_JAPANESE,
		TEXTURE_MAX
	}TEXTURE_TYPE;
	CExitButton();
	~CExitButton();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CExitButton * Create(D3DXVECTOR3 Position,TEXTURE_TYPE TextureType);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Press(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_MAX];	//�e�N�X�`���̃|�C���^
	TEXTURE_TYPE m_TextureType;							//�e�N�X�`���̎��
};
#endif