//=============================================================================
//
// �ڋ�(�m�[�}��) [enemy_eye_normal.h]
// Author : ��K������
//
//=============================================================================
#ifndef _ENEMY_EYE_NORMAL_H_
#define _ENEMY_EYE_NORMAL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemyEyeNormal :public CEnemy
{
public:
	CEnemyEyeNormal(int nPriority = DEFAULT_PRIORITY);
	~CEnemyEyeNormal();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CEnemyEyeNormal * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Attack(void);
	void Death(void);
	void Gaze(void);
	void Stop(void);
	void Stay(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_StopPosition;	//�G���~�܂�ꏊ
	int m_nShotCount;			//���˂��鐔
	int m_nCountBullet;			//�e�̔��ˊԊu
	int m_nStayTime;
	float m_fAngleRot;			//����
	float m_fBulletAngle;		//���˕���
};
#endif