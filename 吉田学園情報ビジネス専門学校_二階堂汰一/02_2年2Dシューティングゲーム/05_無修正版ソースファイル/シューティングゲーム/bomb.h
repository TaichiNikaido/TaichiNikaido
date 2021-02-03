//=============================================================================
//
// ���e [bomb.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BOMB_H_
#define _BOMB_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_BOMB "data/TEXTURE/bomb.png"		//�e�̃e�N�X�`���̕ۑ���
#define BOMB_SIZE 50.0f								//�e�̃T�C�Y
#define PLAYER_BOMB_LIFE 50							//�v���C���[�̔��e�̃��C�t
#define PLAYER_BOMB_DAMAGE 10						//�v���C���[�̔��e�_���[�W
#define ENEMY_BOMB_LIFE 100							//�G�l�~�[�̔��e���C�t
#define ENEMY_BOMB_DAMAGE 10						//�G�l�~�[�̔��e�̃_���[�W
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBomb :public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_MAX
	}TYPE;
	CBomb();
	~CBomb();
	static HRESULT Load(void);
	static void Unload(void);
	static CBomb * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight,  int nLife, int nAttack);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight, int nLife, int nAttack);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void SubLife(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_vpos[NUM_VERTEX];			//���_���W
	D3DXVECTOR3 m_move;						//�ړ�
	TYPE m_Type;							//�^�C�v
	int m_nLife;							//���C�t
	int m_nAttack;							//�U����
	float m_fWidth;							//��
	float m_fHeight;						//����
};
#endif