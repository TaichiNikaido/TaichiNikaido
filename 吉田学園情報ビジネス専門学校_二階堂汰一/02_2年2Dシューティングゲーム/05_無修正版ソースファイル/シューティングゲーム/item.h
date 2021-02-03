//=============================================================================
//
// �A�C�e�� [item.h]
// Author : ��K������
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_OWN_ITEM	"data/TEXTURE/life.png"			//�A�C�e���̃e�N�X�`���̕ۑ���
#define TEXTURE_LEVEL_ITEM	"data/TEXTURE/lvup.png"			//�A�C�e���̃e�N�X�`���̕ۑ���
#define TEXTURE_SCORE_ITEM	"data/TEXTURE/ScoreItem.png"	//�A�C�e���̃e�N�X�`���̕ۑ���
#define TEXTURE_BOMB_ITEM	"data/TEXTURE/bomb.png"			//�A�C�e���̃e�N�X�`���̕ۑ���
#define MAX_ITEM_TEXTURE 4	//�A�C�e���̃e�N�X�`���̍ő吔
#define ITEM_SIZE 50.0f		//�A�C�e���̃T�C�Y
#define ITEM_SPEED 4.0f		//�A�C�e���̑f����
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CItem :public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_OWN,
		TYPE_LEVEL,
		TYPE_SCORE,
		TYPE_BOMB,
		TYPE_MAX
	}TYPE;
	CItem();
	~CItem();
	static HRESULT Load(void);
	static void Unload(void);
	static CItem * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CItem::isCollision(D3DXVECTOR3 pos);
private:
	void Effect(void);
	void MovableRange(void);
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ITEM_TEXTURE];
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_vpos[NUM_VERTEX];	//���_���W
	D3DXVECTOR3 m_move;	//�ړ���
	float m_fWidth;		//��
	float m_fHeight;	//����
	TYPE m_Type;		//�^�C�v
};
#endif