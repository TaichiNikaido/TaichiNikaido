//=============================================================================
//
// �v���C���[ [player.h]
// Author : ��K������
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"
#include "bullet.h"
#include "bomb.h"
#include "name.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PLAYER	"data/TEXTURE/Battleship.png"	//�v���C���[�̃e�N�X�`���̕ۑ���
#define PLAYER_SIZE 65.0f			//�v���C���[�̃T�C�Y
#define PLAYER_INIT_OWN 3			//�v���C���[�̎��@�̏����l
#define PLAYER_MAX_OWN 5			//�v���C���[�̎��@�̍ő�l
#define PLAYER_MIN_OWN 0			//�v���C���[�̎��@�̍ŏ��l
#define PLAYER_INIT_BOMB 3			//�v���C���[�̔��e�̏����l
#define PLAYER_MIN_BOMB 0			//�v���C���[�̔��e�̏����l
#define PLAYER_MAX_BOMB 5			//�v���C���[�̔��e�̍ő�l
#define PLAYER_BOMB_COST 1			//�v���C���[�̕K�v�Ȕ��e��
#define PLAYER_ADD_BOMB 1			//�v���C���[�̔��e�̉��Z��
#define PLAYER_SUB_BOMB 1			//�v���C���[�̔��e�̌��Y��
#define PLAYER_ADD_OWN 1			//�v���C���[�̎��@�̉��Z�l
#define PLAYER_SUB_OWN 1			//�v���C���[�̎��@�̌��Z�l
#define PLAYER_ADD_LEVEL 1			//�v���C���[�̃��x���̉��Z�l
#define PLAYER_SPEED 5.0f			//�v���C���[�̈ړ����x
#define PLAYER_INVINCIBLE_TIME 80	//�v���C���[�̖��G����
#define PLAYER_DEATH_TIME 100		//�v���C���[�̎��S����

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer :public CScene2d
{
public:
	typedef enum
	{
		INPUT_NONE = -1,
		INPUT_UP,
		INPUT_DOWN,
		INPUT_LEFT,
		INPUT_RIGHT,
		INPUT_SHOT,
		INPUT_BOMB,
		INPUT_MAX
	}INPUT_TYPE;
	CPlayer(int nPriority = 4);
	~CPlayer();
	static HRESULT Load(void);
	static void Unload(void);
	static CPlayer * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,int nOwn);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, int nOwn);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);
	void AddOwn(int nValue);
	void SubOwn(int nValue);
	void AddLevel(int nValue);
	void AddBomb(int nValue);
	void SubBomb(int nValue);
	static void SetPlayerScpre(int nValue);
	static void SetPlayerName(int nCount, char aName);
	static bool GetbDeath(void) { return m_bDeath; };
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
private:
	void Input(void);
	void Attack(void);
	void MovableRange(void);
	void Invincible(void);
	void Death(void);
	void Save(void);
	void InputSave(void);
	void InputLoad(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	static int m_nScore;					//�X�R�A
	static  char m_aPlayerName[MAX_NAME];	//���O
	static int m_nNameCount;				//���O�̕������J�E���^
	static 	bool m_bDeath;					//���񂾂��ǂ���
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DCOLOR m_col[NUM_VERTEX];				//�F
	D3DXVECTOR3 m_move;						//�ړ�
	D3DXVECTOR3 m_vpos[NUM_VERTEX];			//���_���W
	D3DXVECTOR3 m_rot;						//����
	float m_fLength;						//�|���S���̑Ίp���̒���
	float m_fAngle;							//�|���S���̊p�x
	float m_fScale;							//�g��
	float m_fAddScale;						//�g����Z�l
	float m_fWidth;							//��
	float m_fHeight;						//����
	float m_fSpeed;							//����
	int m_nOwn;								//���@�̐�
	int m_nLevel;							//�v���C���[���x��
	int m_nCountBullet;						//�e�̃J�E���g
	int m_nBomb;							//���e�̐�
	int m_nCount;							//�J�E���g
	int m_nDeathCount;						//���S����
	int m_nInvincibleCount;					//���G���J�E���g
	bool m_bShot;							//���˂��Ă邩�ǂ���
	bool m_bInvincible;						//���G���ǂ���
	bool m_bHit;							//�q�b�g�������ǂ���
	int m_nContinue;						//���U���g��
	int m_nDeath;							//���S��
	int m_nUseBomb;							//�g�p�����{���̐�
	char m_aInputData[15000][6];			//���͏��
	CBullet * m_pBullet;					//�e�̃|�C���^
	CBomb * m_pBomb;						//���e�̃|�C���^
};
#endif