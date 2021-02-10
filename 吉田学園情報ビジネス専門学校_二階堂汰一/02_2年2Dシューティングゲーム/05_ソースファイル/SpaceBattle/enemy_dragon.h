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
	CEnemyDragon();
	~CEnemyDragon();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CEnemyDragon * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetbCharge(bool bCharge) { m_bCharge = bCharge; }
	CBulletFireball * GetBulletFireBall(void) { return m_pBulletFireBall; }
private:
	void Scale(void);
	void AI(void);
	void Attack(void);
	void Death(void);
	void Animation(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_TargetDistance;			//�ڕW�܂ł̋���
	int m_nPatternAnime;					//�p�^�[���A�j��
	int m_nCounterAnime;					//�J�E���^�[�A�j��
	int m_nBulletTime;						//�e�̔��˂܂ł̎���
	bool m_bCharge;							//�`���[�W���Ă邩
	CBulletFireball * m_pBulletFireBall;	//�΋��̃|�C���^
};
#endif