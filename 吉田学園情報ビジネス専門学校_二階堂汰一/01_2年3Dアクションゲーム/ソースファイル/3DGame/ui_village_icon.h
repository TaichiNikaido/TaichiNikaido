//=============================================================================
//
// ���̃A�C�R�� [ui_village_icon.h]
// Author : ��K������
//
//=============================================================================
#ifndef _UI_VILLAGE_ICON_H_
#define _UI_VILLAGE_ICON_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CVillageIcon :public CScene2d
{
public:
	CVillageIcon();
	~CVillageIcon();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CVillageIcon * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		ICON_NONE = -1,
		ICON_1,
		ICON_2,
		ICON_3,
		ICON_MAX
	}ICON;
	void DataLoad(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	int m_nPatternAnime;					//�p�^�[���A�j��
	float m_fAnimationValue;				//�A�j���[�V�����̒l
};
#endif