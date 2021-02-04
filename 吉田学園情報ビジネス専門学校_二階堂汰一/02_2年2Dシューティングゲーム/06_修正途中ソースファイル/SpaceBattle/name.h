//=============================================================================
//
// 名前入力配列 [namepad.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _NAMEPAD_H_
#define _NAMEPAD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_ROW 3 //行数
#define MAX_COLUMN 9 //列数
#define MAX_WORD 27 //入力可能文字種類数（終了ボタン含む）
#define MAX_NAME 8 //最大文字数
#define MAX_NAME_TEXTURE 1
#define TEXT_SCALE 2//テキストサイズのスケール
#define TEXT_SIZE 80.0f * TEXT_SCALE
#define WORD_BUTTON_INTERVEL 80.0f //文字間

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
	}Letter;//文字ボタン情報
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

	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_NAME_TEXTURE];	//テクスチャ												
	static Letter m_aLetter[MAX_ROW][MAX_COLUMN];               //文字列
	D3DXVECTOR3 m_pos;											//位置
	CScene2d * m_apScene[MAX_WORD];							    //シーン
	CScene2d * m_apSceneText[MAX_NAME];							//シーン（上のテキスト表示用）
	CScene2d * m_apSceneBg[2];							        //シーン背景
	float m_fMove;
	float m_fWidth;												//幅
	float m_fHeight;											//高さ
	char m_aName[MAX_NAME];										//名前格納用
	bool m_bOK;													//決定判定
	int m_nNameCount;											//名前の文字数カウンタ
	int m_nColumn;                                              //現在列番号
	int m_nRow;                                                 //現在行番号
	IsPress m_IsTrigger;                                         //押されてるかどうか
	int     m_TriggerCount;                                     //押し中のカウンタ
};
#endif