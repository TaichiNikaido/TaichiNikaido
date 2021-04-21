//=============================================================================
//
// 名前入力 [name.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _NAME_H_
#define _NAME_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MINIMUM_ALPHABET (0)	//アルファベットの最小値
#define MAX_ALPHABET (26)		//アルファベットの数
#define MAX_COLUMNS (3)			//列の最大数
#define MAX_ROWS (10)			//行の最大数
#define MINIMUM_NAME (0)		//名前の最小値
#define MAX_NAME (8)			//名前の最大数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CLetter;

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
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
		COLUMNS_1,		//1列目
		COLUMNS_2,		//2列目
		COLUMNS_3,		//3列目
		COLUMUNS_MAX
	}COLUMNS;	//列
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
	}LETTER_1;	//1行目の文字番号
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
	}LETTER_2;	//2行目の文字番号
	typedef enum
	{
		Z = 0,
		X,
		C,
		V,
		B,
		N,
		M
	}LETTER_3;	//3行目の文字番号
	void Input(void);
	void LetterLoad(void);
	void InitAllCreate(void);
	int m_nColumns;								//列								
	int m_nLetter;								//文字の番号
	int m_nNameCount;							//名前の文字数カウンタ
	int m_nInputCount;							//入力間隔カウント
	char m_aLetter[MAX_COLUMNS][MAX_ROWS];		//文字
	char m_aName[MAX_NAME];						//名前
	CLetter * m_apLetter[MAX_ALPHABET];			//文字
	CLetter * m_apNameLetter[MAX_NAME];			//名前の文字
};
#endif