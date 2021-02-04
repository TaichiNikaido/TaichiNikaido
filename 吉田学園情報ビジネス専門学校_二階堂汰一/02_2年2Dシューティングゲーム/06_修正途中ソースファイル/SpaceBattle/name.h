//=============================================================================
//
// ���O���͔z�� [namepad.h]
// Author : ��K������
//
//=============================================================================
#ifndef _NAMEPAD_H_
#define _NAMEPAD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ROW 3 //�s��
#define MAX_COLUMN 9 //��
#define MAX_WORD 27 //���͉\������ސ��i�I���{�^���܂ށj
#define MAX_NAME 8 //�ő啶����
#define MAX_NAME_TEXTURE 1
#define TEXT_SCALE 2//�e�L�X�g�T�C�Y�̃X�P�[��
#define TEXT_SIZE 80.0f * TEXT_SCALE
#define WORD_BUTTON_INTERVEL 80.0f //������

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CName
{
public:
	CName();
	~CName();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
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
	}Letter;//�����{�^�����
	typedef struct
	{
		int nCount;
		bool bTrigger;
	}IsCount;
	typedef struct
	{
		IsCount Up;
		IsCount Down;
		IsCount Right;
		IsCount Left;
	}IsPress;

	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_NAME_TEXTURE];	//�e�N�X�`��												
	static Letter m_aLetter[MAX_ROW][MAX_COLUMN];               //������
	D3DXVECTOR3 m_pos;											//�ʒu
	CScene2d * m_apScene[MAX_WORD];							    //�V�[��
	CScene2d * m_apSceneText[MAX_NAME];							//�V�[���i��̃e�L�X�g�\���p�j
	CScene2d * m_apSceneBg[2];							        //�V�[���w�i
	float m_fMove;
	float m_fWidth;												//��
	float m_fHeight;											//����
	char m_aName[MAX_NAME];										//���O�i�[�p
	bool m_bOK;													//���蔻��
	int m_nNameCount;											//���O�̕������J�E���^
	int m_nColumn;                                              //���ݗ�ԍ�
	int m_nRow;                                                 //���ݍs�ԍ�
	IsPress m_IsTrigger;                                         //������Ă邩�ǂ���
	int     m_TriggerCount;                                     //�������̃J�E���^
};
#endif