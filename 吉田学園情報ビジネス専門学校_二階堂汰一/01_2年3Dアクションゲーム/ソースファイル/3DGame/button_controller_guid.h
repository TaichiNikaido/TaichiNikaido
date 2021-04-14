//=============================================================================
//
// ��������\���{�^�� [button_controller_guid.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BUTTON_CONTROLLER_GUID_H_
#define _BUTTON_CONTROLLER_GUID_H_

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
class CControllerGuidButton :public CButton
{
public:
	CControllerGuidButton();
	~CControllerGuidButton();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CControllerGuidButton * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Press(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̃|�C���^
};
#endif