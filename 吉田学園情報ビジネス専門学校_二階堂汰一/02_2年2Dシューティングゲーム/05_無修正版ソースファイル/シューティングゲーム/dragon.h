//=============================================================================
//
// �h���S�� [dragon.h]
// Author : ��K������
//
//=============================================================================
#ifndef _DRAGON_H_
#define _DRAGON_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"
#include "bullet.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_DRAGON	"data/TEXTURE/dragon002.png"
#define DRAGON_SIZE_WIDTH 600.0f			//�h���S���̕��̓����蔻��
#define DRAGON_SIZE_HEIGHT 600.0f			//�h���S���̍����̓����蔻��
#define DRAGON_MAX_HP 3000					//�h���S�����S���C��
#define DRAGON_MIN_HP 0						//�h���S�����S���C��
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CDragon :public CScene2d
{
public:
	CDragon(int nPriority = 4);
	~CDragon();
	static HRESULT Load(void);
	static void Unload(void);
	static CDragon * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,int nLife);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);
	void SubLife(int nValue);
	static bool GetSpawn(void) { return m_bSpawn; };
	static bool GetDeath(void) { return m_bDeath; };
	static void SetSpawn(bool bSpawn);
	static void SetDeath(bool bDeath);
private:
	void AI(void);
	void Animation(void);
	void Damage(void);
	void Attack(void);
	static LPDIRECT3DTEXTURE9 m_pScene;
	static 	bool m_bSpawn;			//�X�|�[���������ǂ���
	static 	bool m_bDeath;			//���S�������ǂ���
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_vpos[NUM_VERTEX]; //���_���W
	D3DXVECTOR3 m_move;				//�G�̈ړ���
	D3DCOLOR m_col[NUM_VERTEX];		//�F
	D3DXVECTOR3	m_rot;				//����
	D3DXVECTOR3 m_TargetDistance;	//�ڕW�܂ł̋���
	D3DXVECTOR3 m_TargetPos;		//�ڕW�n�_
	int m_nLife;					//�̗�
	int m_nCountBullet;				//�e�̃J�E���^
	int m_nCountAI;					//AI�J�E���^
	int m_nCounterAnim;				//�A�j���J�E���^
	int m_nPatternAnim;				//�A�j���p�^�[��
	int m_nHitCount;				//HIT�J�E���^
	float m_fWidth;					//��
	float m_fHeight;				//����
	float m_fTime;					//�^�C��
	float m_fAngle;					//�p�x
	float m_fLength;				//����
	float m_fScale;					//�傫��
	float m_fAddScale;				//�傫���̉��Z��
	bool m_bHit;					//�q�b�g�������ǂ���
	CBullet * m_pBullet;			//�e�̃|�C���^
};
#endif