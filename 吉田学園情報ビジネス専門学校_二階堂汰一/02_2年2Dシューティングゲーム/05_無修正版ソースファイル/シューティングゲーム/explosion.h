//=============================================================================
//
// ���� [explosion.h]
// Author : ��K������
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_EXPLOSION "data/TEXTURE/explosion000.png"	//�e�e�N�X�`���̕ۑ���
#define BOMB_EXPLOSION_SIZE 500.0f	//���e�̔����T�C�Y
#define FIREBALL_EXPLOSION_SIZEX 500.0f	//���e�̔����T�C�Y
#define FIREBALL_EXPLOSION_SIZEY 500.0f	//���e�̔����T�C�Y
#define PLAYER_EXPLOSION_SIZE 50.0f	//�v���C���[�̔����T�C�Y
#define ENEMY_EXPLOSION_SIZE 50.0f	//�G�̔����T�C�Y
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CExplosion :public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_BULLET,
		TYPE_BOMB,
		TYPE_FIERBALL,
		TYPE_MAX
	}TYPE;
	CExplosion();
	~CExplosion();
	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,  TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_vpos[NUM_VERTEX];	//���_���W
	int m_nCounterAnim;				//�A�j���J�E���^
	int m_nPatternAnim;				//�A�j���p�^�[��
	float m_fWidth;					//��
	float m_fHeight;				//����
	TYPE m_type;					//�^�C�v
};
#endif