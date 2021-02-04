//=============================================================================
//
// �Ԓe [bullet_flower.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BULLET_FLOWER_H_
#define _BULLET_FLOWER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "bullet_enemy.h"

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
class CBulletFlower :public CBulletEnemy
{
public:
	typedef enum
	{
		COLOR_NONE = -1,
		COLOR_RED,
		COLOR_ORANGE,
		COLOR_YELLOW,
		COLOR_GREEN,
		COLOR_BLUE,
		COLOR_PURPLE,
		COLOR_PINK,
		COLOR_WHITE,
		COLOR_MAX
	}COLOR;
	CBulletFlower(int nPriority = 3);
	~CBulletFlower();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CBulletFlower * Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	COLOR m_Color;
};
#endif


