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
#include "character.h"
#include "model.h"
#include "motion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CCharacter
{
public:
	typedef enum
	{
		MOTION_IDLE = 0,
		MOTION_WALK,	//���s���[�V����
		MOTION_DASH,	//�_�b�V�����[�V����
	}MOTION;	//���[�V����
	typedef enum
	{
		STATE_NONE = -1,
		STATE_LIVE,		//�����Ă�
		STATE_DEATH,	//����ł�
		STATE_MAX
	}STATE;		//���
	typedef enum
	{
		INPUT_NONE = -1,
		INPUT_UP,		//�����
		INPUT_DOWN,		//������
		INPUT_LEFT,		//������
		INPUT_RIGHT,	//�E����
		INPUT_CAMERA,	//�J�����̎��_
		INPUT_MAX
	}INPUT;		//���͏��
	typedef enum
	{
		ATTACK_NONE = 0,
		ATTACK_1,
		ATTACK_2,
		ATTACK_3,
		ATTACK_MAX
	}ATTACK;	//�U�����
	CPlayer();
	~CPlayer();
	static HRESULT ModelLoad(void);
	static void ModelUnload(void);
	static CPlayer * Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);
	void SubLife(void);
	void SetMove(D3DXVECTOR3 Move) { m_Move = Move; }
	D3DXVECTOR3 GetPositionOld(void) { return m_PositionOld; }
	D3DXVECTOR3 GetCollisionSize(void) { return m_CollisionSize; }
	D3DXVECTOR3 GetMove(void) { return m_Move; }
	int GetLife(void) { return m_nLife; }
	float GetCameraDistance(void) { return m_fCameraDistance; }
private:
	void Input(void);
	void Move(void);
	void Attack(void);
	void Death(void);
	void Collision(void);
	void DataLoad(void);
	void UICreate(void);
	static CModel::MODEL_DATA m_aPlayerModelData[MAX_PARTS];	//���f�����
	D3DXVECTOR3 m_PositionOld;									//�O�̈ʒu
	D3DXVECTOR3 m_CollisionSize;								//�����蔻��p�T�C�Y
	D3DXVECTOR3 m_DirectionDest;								//�ړI�̌���
	D3DXVECTOR3 m_Move;											//�ړ���
	int m_nLife;												//�̗�
	int m_nAttack;												//�U����
	int m_nAttackCombo;											//�U���R���{
	int m_nCoolTime;											//�N�[���^�C��
	int m_nCoolTimeCount;										//�N�[���^�C���J�E���g
	float m_fSpeed;												//����
	float m_fWalkSpeed;											//���s���x
	float m_fDashSpeed;											//�_�b�V�����x
	float m_fDirectionValue;									//�����̒l
	float m_fCameraDistance;									//�J�����Ƃ̋���
	bool m_bDash;												//�_�b�V�����Ă邩
	bool m_bWeapon;												//������g�p���Ă��邩
	bool m_bAttack;												//�U�������Ă��邩
	STATE m_State;												//���
	INPUT m_Input;												//���͏��
};
#endif
