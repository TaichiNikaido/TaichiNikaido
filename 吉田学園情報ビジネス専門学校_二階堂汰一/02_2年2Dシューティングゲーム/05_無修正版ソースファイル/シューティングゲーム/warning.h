//=============================================================================
//
// �댯�n�� [warning.h]
// Author : ��K������
//
//=============================================================================
#ifndef _WARNING_H_
#define _WARNING_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WARNING "data/TEXTURE/warning.png"	//�e�e�N�X�`���̕ۑ���
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CWarning :public CScene2d
{
public:
	CWarning();
	~CWarning();
	static HRESULT Load(void);
	static void Unload(void);
	static CWarning * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void ColorChange(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_vpos[NUM_VERTEX];			//���_���W
	D3DCOLOR m_col[NUM_VERTEX];				//�F
	float m_fWidth;							//��
	float m_fHeight;						//����
	int m_nColCount;						//�F�ύX�J�E���g
	int m_nCount;							//�J�E���g
};
#endif