//=============================================================================
//
// ���[�V���� [motion.h]
// Author : ��K������
//
//=============================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOTIONKEY_SET_MAX (60)	//���[�V�����L�[�̍ő吔

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMotion
{
public:
	typedef struct
	{
		int nIndex;					//���f���ԍ�
		int nParents;				//���f���̐e�ԍ�
		D3DXVECTOR3 Position;		//�ʒu
		D3DXVECTOR3 PositionOrigin; //�����ʒu
		D3DXVECTOR3 Rotation;		//��]
	}MODEL;	//���f�����
	typedef struct
	{
		D3DXVECTOR3 Position[MAX_PARTS];	//�ʒu
		D3DXVECTOR3 Rotation[MAX_PARTS];	//��]
		int nFrame;							//�t���[����
	}KEY_INFORMATION;	//�L�[���
	typedef struct
	{
		bool bLoop;											//���[�v���邩
		int nNumKey;										//���[�V�����̃L�[��
		KEY_INFORMATION KeyInformation[MOTIONKEY_SET_MAX];	//���[�V�����Ɋ܂ރL�[�Z�b�g���
	}MOTION;	//���[�V�������
	typedef enum
	{
		MOTION_PLAYER_IDLE = 0,		//�A�C�h�����[�V����
		MOTION_PLAYER_WALK,			//�������[�V����
		MOTION_PLAYER_DASH,			//���胂�[�V����
		MOTION_DRAGON_ATTACK1,		//�h���S���̍U��1
		MOTION_DRAGON_ATTACK2,		//�h���S���̍U��2
		MOTION_MAX					//���[�V�����̍ő�
	}MOTION_STATE;	//���[�V�������
	CMotion();
	~CMotion();
	static CMotion * Create(void);
	void Uninit(void);
	void Update(void);
	void LoadMotion(const char * cText);
	void LoadModelInformation(const char * cText);
	void SetMotion(MOTION_STATE MotionState) { m_MotionState = MotionState; }
	MOTION_STATE GetMotion(void) { return m_MotionState; }
	int GetIndex(int nCount) { return m_ModelParent[nCount].nIndex; }
	int GetParents(int nCount) { return m_ModelParent[nCount].nParents; }
	D3DXVECTOR3 GetPosition(int nCount) { return m_ModelParent[nCount].Position; }
	D3DXVECTOR3 GetRotation(int nCount) { return m_ModelParent[nCount].Rotation; }
private:
	D3DXVECTOR3 m_NumPositionDifference[MAX_PARTS];		//�ʒu�̍���
	D3DXVECTOR3 m_NumDirectionDifference[MAX_PARTS];	//�����̍���
	D3DXVECTOR3 m_NumRotationDifference[MAX_PARTS];		//��]�̍���
	int m_nFrame;										//�t���[����
	int m_nAddChangeFreme;								//���[�V�����ύX���ɉ��Z����t���[��
	int m_nCurrentKey;									//���݂̃L�[��
	bool m_bChange;										//�ύX������
	MODEL m_ModelParent[MAX_PARTS];						//���f���̃p�[�c���Ƃ̏��
	MOTION m_Motion[MOTION_MAX];						//���[�V�������Ƃ̏��
	MOTION_STATE m_MotionState;							//���[�V�����̏��
	MOTION_STATE m_MotionOldState;						//1�t���[���O�̃��[�V�����̏��
};
#endif