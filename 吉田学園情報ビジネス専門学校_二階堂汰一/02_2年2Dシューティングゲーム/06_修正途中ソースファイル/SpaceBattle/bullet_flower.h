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
		COLOR_NUMBER_NONE = -1,
		COLOR_NUMBER_RED,
		COLOR_NUMBER_ORANGE,
		COLOR_NUMBER_YELLOW,
		COLOR_NUMBER_GREEN,
		COLOR_NUMBER_BLUE,
		COLOR_NUMBER_PURPLE,
		COLOR_NUMBER_PINK,
		COLOR_NUMBER_WHITE,
		COLOR_NUMBER_MAX
	}COLOR_NUMBER;
	CBulletFlower();
	~CBulletFlower();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CBulletFlower * Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed,COLOR_NUMBER nColor);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Move(void);
	void ColorSelect(void);
	void Death(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	COLOR_NUMBER m_ColorNumber;				//�F�̔ԍ�
	int m_nTime;							//����
};
#endif


