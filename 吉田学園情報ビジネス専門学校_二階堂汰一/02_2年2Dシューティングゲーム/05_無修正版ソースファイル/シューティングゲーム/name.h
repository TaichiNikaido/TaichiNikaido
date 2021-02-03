//=============================================================================
//
// ���O [name.h]
// Author : ��K������
//
//=============================================================================
#ifndef _NAME_H_
#define _NAME_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"
#include "scene2D.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAMEBG	"data/TEXTURE/name.png"
#define TEXTURE_NAME	"data/TEXTURE/alphabet001.png"
#define MAX_COLUMN 3
#define COLUMN_MAXNUMBER 10
#define MAX_NAME 8
#define MAX_NAME_TEXTURE 2
#define TEXT_SCALE 2.0f
#define TEXT_SIZE 50.0f * TEXT_SCALE
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CName :public CScene
{
public:
	CName(int nPriority = 0);
	~CName();
	static HRESULT Load(void);
	static void Unload(void);
	static CName * Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	HRESULT Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef struct
	{
		char aLetter;
		int  LetterIndex;
	}Letter;
	typedef struct
	{
		int nCount;
		bool bTrigger;
	}IsCount;//������Ă邩�H�Ɖ������J�E���g
	typedef struct
	{
		IsCount Up;
		IsCount Down;
		IsCount Right;
		IsCount Left;
	}IsPress;//������Ă邩�H
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_NAME_TEXTURE];	//�e�N�X�`��
	static Letter m_aLetter[MAX_COLUMN][COLUMN_MAXNUMBER];
	D3DXVECTOR3 m_pos;											//�ʒu
	CScene2d * m_apSceneBG[MAX_POLYGON];						//�V�[��
	CScene2d * m_apScene[MAX_POLYGON];							//�V�[��
	CScene2d * m_apSceneText[MAX_NAME];							//�V�[���i��̃e�L�X�g�\���p�j
	D3DXVECTOR3 m_vPos[NUM_VERTEX];								//���_���W
	D3DCOLOR m_col[NUM_VERTEX];									//�F
	float m_fTextureX;											//�e�N�X�`���̕�
	float m_fTextureY;											//�e�N�X�`���̍���
	float m_fWidth;												//��
	float m_fHeight;											//����
	bool m_bName;												//���O�̋L�^���
	bool m_bCanselName;											//���O�̎��������
	char m_aName[MAX_NAME];										//���O�i�[�p
	bool m_bColumnDown;											//����󔻒�
	bool m_bColumnUp;											//���󔻒�
	int m_nColumnCount;											//�s���J�E���^
	bool m_bLetterRight;										//�E��󔻒�
	bool m_bLetterLeft;											//����󔻒�
	bool m_bOK;													//���蔻��
	int m_nLetterCount;											//�������J�E���^
	int m_nNameCount;											//���O�̕������J�E���^
	IsPress m_IsTrigger;                                        //������Ă邩�ǂ���
	int m_TriggerCount;											//�������̃J�E���^
};
#endif