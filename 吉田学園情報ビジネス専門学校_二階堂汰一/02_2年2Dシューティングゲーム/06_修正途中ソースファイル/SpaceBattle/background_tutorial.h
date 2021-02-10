//=============================================================================
//
// �`���[�g���A���w�i [background_tutorial.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BACKGROUND_TUTORIAL_H_
#define _BACKGROUND_TUTORIAL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "background.h"

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
class CBackgroundTutorial :public CBackground
{
public:
	CBackgroundTutorial();
	~CBackgroundTutorial();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CBackgroundTutorial * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		TEXTURE_NONE = -1,
		TEXTURE_KEYBOARD_GUID,
		TEXTURE_JOYSTICK_GUID,
		TEXTURE_MAX
	}TEXTURE;
	static LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_MAX];	//�e�N�X�`���ւ̃|�C���^
};
#endif