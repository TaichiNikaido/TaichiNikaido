 //=============================================================================
//
// �G [enemy.h]
// Author : ��K������
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"
#include "bullet.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_EYE	"data/TEXTURE/ENEMY/enemy_easy.png"		//�ڂ̓G�̃e�N�X�`���ۑ���
#define TEXTURE_FLOWER	"data/TEXTURE/ENEMY/flower.png"		//�Ԃ̓G�̃e�N�X�`���ۑ���
#define TEXTURE_SPIDER	"data/TEXTURE/ENEMY/spider.png"		//�Ԃ̓G�̃e�N�X�`���ۑ���
#define TEXTURE_BOMBHEAD	"data/TEXTURE/ENEMY/bombhead.png"		//�Ԃ̓G�̃e�N�X�`���ۑ���
#define TEXTURE_BOMBBODY	"data/TEXTURE/ENEMY/bombbody.png"		//�Ԃ̓G�̃e�N�X�`���ۑ���
#define TEXTURE_EYE2	"data/TEXTURE/ENEMY/eye2.png"		//�Ԃ̓G�̃e�N�X�`���ۑ���
#define EYE_SIZE 50.0f			//�G(��)�̓����蔻��
#define FLOWER_SIZE 100.0f			//�G(��)�̓����蔻��
#define SPIDER_SIZE 150.0f			//�G(�w�)�̓����蔻��
#define EASY_EYE_MAX_HP 30		//�U�R�G�̃��C�t�̍ő�l
#define EASY_FLOWER_MAX_HP 130		//�U�R�G�̃��C�t�̍ő�l
#define EASY_SPIDER_MAX_HP 120		//�U�R�G�̃��C�t�̍ő�l
#define NORMAL_ENEMY_MAX_HP 75		//���ʂ̓G�̃��C�t�̍ő�l
#define MIDDLE_ENEMY_MAX_HP 500		//���{�X�̃��C�t�̍ő�l
#define HARD_ENEMY_MAX_HP 1500		//���X�{�X�̃��C�t�̍ő�l
#define ENEMY_MIN_HP 0				//�G�̗̑͂̎��S���C��
#define MAX_LOCATION 4
#define RATE_MOVE 0.03f
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemy :public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_EYE,
		TYPE_FLOWER,
		TYPE_SPIDER,
		TYPE_MIDDLE,
		TYPE_HARD,
		TYPE_BOMBHEAD,
		TYPE_BOMBBODY,
		TYPE_EYE2,
		TYPE_MAX
	}TYPE;
	CEnemy(int nPriority = 4);
	~CEnemy();
	static HRESULT Load(void);
	static void Unload(void);
	static CEnemy * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type,int nLife);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type, int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);
	void SubLife(int nValue);
private:
	void AI(void);
	void Damage(void);
	void Animation(void);
	void MovableRange(void);
	static LPDIRECT3DTEXTURE9 m_apScene[TYPE_MAX];
	static int m_nCountEnemy;		//�G�̑���
	static int  m_nBombEnemyLife;	//���e�G�̃��C�t
	TYPE m_type;					//�G�̎��
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_vpos[NUM_VERTEX]; //���_���W
	D3DXVECTOR3 m_move;				//�G�̈ړ���
	float       m_fRd;				//���W�A��
	float       m_fRdScale;			//���W�A���g�k
	D3DXVECTOR3 m_Location[MAX_LOCATION];	//�n�_
	D3DCOLOR	m_col[NUM_VERTEX];			//�F
	float m_fLength;				//����
	float m_fAngle;					//�p�x
	float m_fRot;					//����
	float m_fScale;					//�g�k
	int m_nLife;					//�̗�
	int m_nCountBullet;				//�e�̃J�E���^
	int m_nEnemyTimeCount;			//�G�̑؍ݎ���
	int m_nBulletIndex;				//�e�̔��ː�
	int m_nHitCount;				//HIT�J�E���g
	float m_fBulletAngle;			//�e�̊p�x
	float m_fWidth;					//��
	float m_fHeight;				//����
	float m_fTime;					//�^�C��
	float m_fStop;					//�G���~�܂�ꏊ
	bool m_bHit;					//�q�b�g�������ǂ���
	bool m_bShot;					//�e�����������ǂ���
	bool m_bStay;					//�؍݂��Ă邩�ǂ���
	int m_nStayCount;				//�؍ݎ���
	int m_nCounterAnim;				//�A�j���J�E���^
	int m_nPatternAnim;				//�p�^�[���A�j��
	int m_nColorCount;				//�F�J�E���^
	CBullet * m_pBullet;			//�e�̃|�C���^
};
#endif