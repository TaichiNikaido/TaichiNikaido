//=============================================================================
//
// 2D�V�[���Ǘ����� [scene2d.h]
// Author : ��K������
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene2d :public CScene
{
public:
	CScene2d(int nPriority = DEFAULT_PRIORITY);
	~CScene2d();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position);
	void SetRotation(D3DXVECTOR3 Rotation);
	void SetSize(D3DXVECTOR3 Size);
	void SetScale(float fScale);
	void SetColor(D3DXCOLOR m_Color);
	void SetVertexPosition(D3DXVECTOR3 aVertexPosition[NUM_VERTEX]);
	void SetTexture(D3DXVECTOR2 aTexture[NUM_VERTEX]);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	D3DXVECTOR3 GetSize(void) { return m_Size; }
	D3DXCOLOR GetColor(void) { return m_Color; }
private:
	LPDIRECT3DTEXTURE9		m_pTexture;					//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_Position;					//���W
	D3DXVECTOR3				m_Size;						//�T�C�Y
	D3DXVECTOR3				m_Rotation;					//����
	D3DXVECTOR3				m_aVtxPosition[NUM_VERTEX];	//���_���W
	D3DXVECTOR2				m_aTexture[NUM_VERTEX];		//�e�N�X�`����UV���W
	D3DXCOLOR	 			m_Color;					//�J���[
	float					m_fScale;					//�k��
	float					m_fAngle;					//�p�x
	float					m_fLength;					//����
};
#endif





////=============================================================================
////
//// 2D�|���S�� [scene2d.h]
//// Author : ��K������
////
////=============================================================================
//#ifndef _SCENE2D_H_
//#define _SCENE2D_H_
////*****************************************************************************
//// �w�b�_�t�@�C���̃C���N���[�h
////*****************************************************************************
//#include "scene.h"
//
////*****************************************************************************
//// �}�N����`
////*****************************************************************************
//#define NUM_VERTEX	4
//#define NUM_POLYGON 2
//#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
//#define TEXTURE_SIZE 200
//#define TEXTURE_WIDTH 200
//#define TEXTURE_HEIGHT 200
//#define MAX_POLYGON 256
//#define TEXTURE_SCENE2D "data/TEXTURE/1.png"
////*****************************************************************************
//// �\���̒�`
////*****************************************************************************
//typedef struct
//{
//	D3DXVECTOR3 pos; //���_���W
//	float		rhw; //���W�ϊ��p���W��
//	D3DCOLOR	col; //���_�J���[
//	D3DXVECTOR2	tex; //�e�N�X�`��
//}VERTEX_2D;
//
////*****************************************************************************
//// �N���X��`
////*****************************************************************************
//class CScene2d :public CScene
//{
//public:
//	CScene2d(int nPriority = 3);
//	~CScene2d();
//	HRESULT Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
//	void Uninit(void);
//	void Update(void);
//	void Draw(void);
//	void SetPosition(D3DXVECTOR3 pos);
//	void SetVertexPosition(D3DXVECTOR3 vpos[NUM_VERTEX]);
//	void SetTex(float fTexX, float fTexY, float fTexX2, float fTexY2);
//	void SetColor(D3DCOLOR col[NUM_VERTEX]);
//	D3DXVECTOR3 GetPosition(void);
//	static CScene2d * Create(D3DXVECTOR3 pos);
//	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
//private:
//	LPDIRECT3DTEXTURE9 m_pTexture;
//	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
//	D3DXVECTOR3 m_Position;
//	D3DXVECTOR3 m_vpos[NUM_VERTEX];
//	D3DCOLOR m_col[NUM_VERTEX];
//	float m_fTexX;
//	float m_fTexY;
//	float m_fTexX2;
//	float m_fTexY2;
//	float m_fSizeX;
//	float m_fSizeY;
//	float m_fTexAnim;
//};
//#endif