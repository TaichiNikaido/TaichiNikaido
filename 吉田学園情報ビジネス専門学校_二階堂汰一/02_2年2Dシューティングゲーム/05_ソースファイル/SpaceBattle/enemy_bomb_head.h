//=============================================================================
//
// ���e�̓G�̓� [enemy_bomb_head.h]
// Author : ��K������
//
//=============================================================================
#ifndef _ENEMY_BOMB_HEAD_H_
#define _ENEMY_BOMB_HEAD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_BOMB_BODY (5)
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CEnemyBombBody;
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemyBombHead :public CEnemy
{
public:
	CEnemyBombHead();
	~CEnemyBombHead();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CEnemyBombHead * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DeathAll(void);
private:
	void Death(void);
	CEnemyBombBody * m_pBombBody[MAX_BOMB_BODY];
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	float m_fRd;//���W�A��
	float m_fRdScale;//���Z��
	bool m_bCreateBody;
	int m_nCreateCount;
	int m_nCreateBodyCount;
	D3DXVECTOR3 m_InitPos;
	int m_nBombLife;
	bool m_bDeath;
	bool m_bDeathAll;
};
#endif