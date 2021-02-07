//=============================================================================
//
// �h���S�� [enemy_spider.h]
// Author : ��K������
//
//=============================================================================
#ifndef _ENEMY_DRAGON_H_
#define _ENEMY_DRAGON_H_

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
class CBulletFireball;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemyDragon :public CEnemy
{
public:
	CEnemyDragon(int nPriority = DEFAULT_PRIORITY);
	~CEnemyDragon();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CEnemyDragon * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CBulletFireball * GetBulletFireBall(void) { return m_pBulletFireBall; }
private:
	void Scale(void);
	void Attack(void);
	void Death(void);
	void Animation(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_TargetDistance;//�ڕW�܂ł̋���
	D3DXVECTOR3 m_TargetPos;//�ڕW�n�_
	int m_nPatternAnime;					//�p�^�[���A�j��
	int m_nCounterAnime;					//�J�E���^�[�A�j��
	int m_nBulletTime;						//�e�̔��ˊԊu
	bool m_bCharge;
	int m_nChargeTime;
	CBulletFireball * m_pBulletFireBall;
};
#endif