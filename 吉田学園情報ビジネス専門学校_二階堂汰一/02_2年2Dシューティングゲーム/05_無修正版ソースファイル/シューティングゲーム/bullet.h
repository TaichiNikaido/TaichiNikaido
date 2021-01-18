//=============================================================================
//
// �e [bullet.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"
#include "effect.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_BULLET "data/TEXTURE/bullet000.png"		//�e�̃e�N�X�`���̕ۑ���
#define TEXTURE_FIERBALL "data/TEXTURE/bullet000.png"   //�΋��̃e�N�X�`���̕ۑ���
#define TEXTURE_BREATHE "data/TEXTURE/bullet000.png"	//�u���X�̃e�N�X�`���̕ۑ���
#define TEXTURE_BEAM "data/TEXTURE/beam.png"			//�r�[���̃e�N�X�`���̕ۑ���
#define TEXTURE_BIRA "data/TEXTURE/bira.png"			//�r�[���̃e�N�X�`���̕ۑ���
#define TEXTURE_FIRE "data/TEXTURE/fire.png"			//�r�[���̃e�N�X�`���̕ۑ���
#define BULLET_SIZE 10.0f								//�e�̃T�C�Y
#define BEAM_SIZE 50.0f									//�r�[���̃T�C�Y
#define PLAYER_BULLET_ATTACK 10							//�v���C���[�̒e�̍U����
#define PLAYER_BEAM_LIFE 50								//�v���C���[�̃r�[���̃��C�t
#define PLAYER_BEAM_ATTACK 5							//�v���C���[�̃r�[���̍U����
#define EASY_ENEMY_BULLET_ATTACK 10						//�U�R�G�̒e�̍U����
#define BULLET_SPEAD 7.0f
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBullet :public CScene2d
{
public:
	typedef enum
	{
		USER_NONE = -1,
		USER_PLAYER,
		USER_ENEMY,
		USER_DRAGON,
	}USER;

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_NORMAL,
		TYPE_AIM,
		TYPE_GUID,
		TYPE_N_WAY,
		TYPE_FIREBALL,
		TYPE_FIRE,
		TYPE_FLOWER,
		TYPE_BREATHE,
		TYPE_MAX
	}TYPE;

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

	typedef enum
	{
		TEXTURE_NONE = -1,
		BULLET_TEXTURE,
		BEAM_TEXTURE,
		FLOWER_TEXTURE,
		FIRE_TEXTURE,
		TEXTURE_MAX
	}TEXTURE;

	CBullet(int nPriority = 4);
	~CBullet();
	static HRESULT Load(void);
	static void Unload(void);
	static CBullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight, USER user ,TYPE type, COLOR col,TEXTURE textureint ,int nAttack);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight, USER user, TYPE type, COLOR col, TEXTURE textureint, int nAttack);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static bool GetbFireBall(void) { return m_bFireBall; };
	static bool GetbCharage(void) { return m_bCharage; };
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_MAX];
	static D3DCOLOR         m_aColor[COLOR_MAX];//7�F�v���Z�b�g
	static bool m_bFireBall;
	static bool m_bCharage;
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_TargetPos;
	D3DXVECTOR3 m_vpos[NUM_VERTEX];	//���_���W
	D3DCOLOR m_col[NUM_VERTEX];
	D3DXVECTOR3 m_move;				//�ړ�
	D3DXVECTOR3	m_rot;				//����
	COLOR m_pCol;
	USER m_user;					//�g�p��
	TYPE m_type;					//�^�C�v
	TEXTURE m_texture;				//�e�N�X�`��
	int m_nAttack;					//�U����
	float m_fWidth;					//��
	float m_fHeight;				//����
	CEffect * m_pEffect;			//�G�t�F�N�g�̃|�C���^
	float m_fAngle;					//�p�x
	int m_nCount;					//�J�E���g
	int m_nBreatheCount;			//�u���X�̒���
	int m_nLife;					//���C�t
	//�e�̑��x
	float m_fVx; 
	float m_fVy;
	int m_nCountBullet;
	float m_fadd;
	float m_theta;
	//�e���̖{
	float m_fDistance;
	float m_fSpeed;
	float m_fLength;			//����
	float m_fScale;			//�傫��
	float m_fAddScale;		//�傫���̉��Z��
	bool m_bShotFireball;
	bool m_bShotFire;
};
#endif