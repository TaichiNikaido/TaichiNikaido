//=============================================================================
//
// �g [flame.h]
// Author : ��K������
//
//=============================================================================
#ifndef _FLAME_H_
#define _FLAME_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_FLAME1	"data/TEXTURE/ENEMY/name.png"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFlame :public CScene2d
{
public:
	CFlame(int nPriority = 5);
	~CFlame();
	static HRESULT Load(void);
	static void Unload(void);
	static CFlame * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_vpos[NUM_VERTEX];			//���_���W
	D3DCOLOR m_col[NUM_VERTEX];				//�F
};
#endif