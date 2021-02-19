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
#include "scene.h"
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
class CPlayer : public CScene
{
public:
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
		ATTACK_NONE = -1,
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
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	float GetCameraDistance(void) { return m_fCameraDistance; }
	CModel * GetModel(int nParts) { return m_pModel[nParts]; }
private:
	void Input(void);
	void Move(void);
	void Attack(void);
	void Death(void);
	void Collision(void);
	void Motion(void);
	void DataLoad(void);
	static CModel::MODEL_DATA m_ModelData[MAX_PARTS];		//���f���f�[�^
	static D3DXMATERIAL * m_pMaterial;						//�}�e���A���̃|�C���^
	D3DXVECTOR3 m_Position;									//�ʒu
	D3DXVECTOR3 m_Size;										//�T�C�Y
	D3DXVECTOR3 m_CollisionSize;							//�����蔻��p�T�C�Y
	D3DXVECTOR3 m_Rotation;									//��]
	D3DXVECTOR3 m_Move;										//�ړ���
	int m_nLife;											//�̗�
	int m_nAttack[ATTACK_MAX];								//�U����
	int m_nCoolTime[ATTACK_MAX];							//�N�[���^�C��
	int m_nCoolTimeCount;									//�N�[���^�C���J�E���g
	float m_fSpeed;											//����
	float m_fWalkSpeed;										//���s���x
	float m_fDashSpeed;										//�_�b�V�����x
	float m_fCameraDistance;								//�J�����Ƃ̋���
	bool m_bDash;											//�_�b�V�����Ă邩
	STATE m_State;											//���
	INPUT m_Input;											//���͏��
	ATTACK m_Attack;										//�U�����
	CModel * m_pModel[MAX_PARTS];							//���f���̃|�C���^
	CMotion * m_pMotion;									//���[�V�����̃|�C���^
};
#endif
