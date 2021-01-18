//=============================================================================
//
// �w�i [background.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"
#include "scene2d.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_BG1	"data/TEXTURE/bg_0001.png"	//�e�N�X�`���̕ۑ���
#define TEXTURE_BG2	"data/TEXTURE/bg_0002.png"	//�e�N�X�`���̕ۑ���
#define TEXTURE_BG3	"data/TEXTURE/bg_0003.png"	//�e�N�X�`���̕ۑ���
#define MAX_BG_TEXTURE 3	//�e�N�X�`���̍ő吔
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBg :public CScene
{
public:
	CBg(int nPriority = 0);
	~CBg();
	static HRESULT Load(void);
	static void Unload(void);
	static CBg * Create(D3DXVECTOR3 pos,float SizeWidth,float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG_TEXTURE];
	CScene2d * m_apScene[MAX_POLYGON];
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_vpos[NUM_VERTEX];	//���_���W
	float m_fTextureX;	//�e�N�X�`����X
	float m_fTextureY;	//�e�N�X�`����Y
	float m_fFastMove;	//�����ړ���
	float m_fSlowMove;	//�x���ړ���
	float m_fMove;		//�ړ���
	float m_fWidth;		//��
	float m_fHeight;	//����
};
#endif