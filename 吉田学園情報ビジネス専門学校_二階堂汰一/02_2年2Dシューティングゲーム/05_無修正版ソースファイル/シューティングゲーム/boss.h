//=============================================================================
//
// �{�X [boss.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PART00_TEXTURE "data/TEXTURE/BOSS/core002.png"			//�R�A02
#define PART01_TEXTURE "data/TEXTURE/BOSS/core.png"				//�R�A
#define PART02_TEXTURE "data/TEXTURE/BOSS/core001.png"			//�R�A01
#define PART03_TEXTURE "data/TEXTURE/BOSS/10_body_right2.png"	//�E���g
#define PART04_TEXTURE "data/TEXTURE/BOSS/body_left.png"		//�����g
#define PART05_TEXTURE "data/TEXTURE/BOSS/hand_right.png"		//�E��
#define PART06_TEXTURE "data/TEXTURE/BOSS/hand_left.png"		//����
#define PART07_TEXTURE "data/TEXTURE/BOSS/forearm_right.png"	//�E�O�r
#define PART08_TEXTURE "data/TEXTURE/BOSS/forearm_left.png"		//���O�r
#define PART09_TEXTURE "data/TEXTURE/BOSS/upperarm_right.png"	//�E��r
#define PART10_TEXTURE "data/TEXTURE/BOSS/upperarm_left.png"	//����r
#define PART11_TEXTURE "data/TEXTURE/BOSS/head.png"				//��
#define PART12_TEXTURE "data/TEXTURE/BOSS/chin.png"				//�{
#define PART13_TEXTURE "data/TEXTURE/BOSS/eye.png"				//��
#define PART14_TEXTURE "data/TEXTURE/BOSS/eyeflame.png"			//�ڂ̃t���[��
#define BOSS_LIFE 1000
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBoss :public CScene2d
{
public:
	typedef enum
	{
		PART_NONE = -1,
		CORE_02,
		CORE,
		CORE_01,
		BODY_RIGHT,
		BODY_LEFT,
		HAND_RIGHT,
		HAND_LEFT,
		FOREARM_RIGHT,
		FOREARM_LEFT,
		UPPERARM_RIGHT,
		UPPERARM_LEFT,
		HEAD,
		CHIN,
		EYE,
		EYEFLAME,
		PART_MAX
	}PART;
	CBoss(int nPriority = 5);
	~CBoss();
	static HRESULT Load(void);
	static void Unload(void);
	static CBoss * Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	HRESULT Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SubLife(int nValue);
private:
	typedef struct
	{
		D3DXVECTOR3 m_pos;				//�ʒu
		D3DXVECTOR3 m_vpos[NUM_VERTEX];	//���_���W
		D3DXVECTOR3 m_move;				//�ړ���
		D3DXVECTOR3 m_rot;				//��]
		float m_fWidth;					//��
		float m_fHeight;				//����
		float m_fLength;				//�Ίp���̒���
		float m_fAngle;					//�Ίp���̊p�x
		float m_fScale;					//�g��
	}PART_STATUS;
	static LPDIRECT3DTEXTURE9 m_apTexture[PART_MAX];
	CScene2d * m_apScene[PART_MAX];
	PART_STATUS m_PartStatus[PART_MAX];	//�\���̂̕ϐ�
	int m_nLife;						//�̗�
	int m_nCountBullet;					//�e�̃J�E���g
	CBullet * m_pBullet;				//�e�̃|�C���^
};
#endif