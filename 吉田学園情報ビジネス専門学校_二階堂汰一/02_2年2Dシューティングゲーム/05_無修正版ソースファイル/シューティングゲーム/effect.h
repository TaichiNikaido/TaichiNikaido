//=============================================================================
//
// �G�t�F�N�g [effect.h]
// Author : ��K������
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_EFFECT "data/TEXTURE/bullet000.png"		//�e�̃e�N�X�`���̕ۑ���
#define EFFECT_LIFE 10
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEffect :public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_DRAGON,
		TYPE_MAX
	}TYPE;
	CEffect(int nPriority = 3);
	~CEffect();
	static HRESULT Load(void);
	static void Unload(void);
	static CEffect * Create(D3DXVECTOR3 pos,D3DCOLOR col,float SizeHeight, float SizeWidth,int nLife, TYPE nType);
	HRESULT Init(D3DXVECTOR3 pos, D3DCOLOR col, float SizeHeight, float SizeWidth, int nLife, TYPE nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_vpos[NUM_VERTEX];
	D3DCOLOR m_col[NUM_VERTEX];
	TYPE m_Type;
	int m_nLife;
	float m_fWidth;
	float m_fHeight;
	int m_nAlpha;
	float m_fScale;
	D3DXVECTOR3 m_rot;
	float m_fLength;
	float m_fAngle;
};
#endif