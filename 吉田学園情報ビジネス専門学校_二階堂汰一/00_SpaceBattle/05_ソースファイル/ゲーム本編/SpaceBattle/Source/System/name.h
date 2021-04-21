//=============================================================================
//
// ���O���� [name.h]
// Author : ��K������
//
//=============================================================================
#ifndef _NAME_H_
#define _NAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MINIMUM_ALPHABET (0)	//�A���t�@�x�b�g�̍ŏ��l
#define MAX_ALPHABET (26)		//�A���t�@�x�b�g�̐�
#define MAX_COLUMNS (3)			//��̍ő吔
#define MAX_ROWS (10)			//�s�̍ő吔
#define MINIMUM_NAME (0)		//���O�̍ŏ��l
#define MAX_NAME (8)			//���O�̍ő吔

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CLetter;

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
	static CName * Create();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		COLUMNS_NONE = -1,
		COLUMNS_1,		//1���
		COLUMNS_2,		//2���
		COLUMNS_3,		//3���
		COLUMUNS_MAX
	}COLUMNS;	//��
	typedef enum
	{
		Q = 0,
		W,
		E,
		R,
		T,
		Y,
		U,
		I,
		O,
		P
	}LETTER_1;	//1�s�ڂ̕����ԍ�
	typedef enum
	{
		A = 0,
		S,
		D,
		F,
		G,
		H,
		J,
		K,
		L
	}LETTER_2;	//2�s�ڂ̕����ԍ�
	typedef enum
	{
		Z = 0,
		X,
		C,
		V,
		B,
		N,
		M
	}LETTER_3;	//3�s�ڂ̕����ԍ�
	void Input(void);
	void LetterLoad(void);
	void InitAllCreate(void);
	int m_nColumns;								//��								
	int m_nLetter;								//�����̔ԍ�
	int m_nNameCount;							//���O�̕������J�E���^
	int m_nInputCount;							//���͊Ԋu�J�E���g
	char m_aLetter[MAX_COLUMNS][MAX_ROWS];		//����
	char m_aName[MAX_NAME];						//���O
	CLetter * m_apLetter[MAX_ALPHABET];			//����
	CLetter * m_apNameLetter[MAX_NAME];			//���O�̕���
};
#endif