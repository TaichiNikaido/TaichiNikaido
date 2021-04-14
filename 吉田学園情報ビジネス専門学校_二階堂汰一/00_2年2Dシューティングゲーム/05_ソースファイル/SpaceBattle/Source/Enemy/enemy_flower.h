//=============================================================================
//
// �� [enemy_flower.h]
// Author : ��K������
//
//=============================================================================
#ifndef _ENEMY_FLOWER_H_
#define _ENEMY_FLOWER_H_

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
class CEnemyFlower :public CEnemy
{
public:
	CEnemyFlower();
	~CEnemyFlower();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CEnemyFlower * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Attack(void);
	void Stop(void);
	void Stay(void);
	void Death(void);
	void Drop(void);
	void Animation(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_StopPosition;				//�~�܂�ʒu
	int m_nCounterAnime;					//�A�j���J�E���^
	int m_nPatternAnime;					//�A�j���p�^�[��
	int m_nShotTime;						//�e�𔭎˂���܂ł̎���
	int m_nColorCount;						//�F�J�E���g
	int m_nStayTime;						//�؍ݎ���
};
#endif