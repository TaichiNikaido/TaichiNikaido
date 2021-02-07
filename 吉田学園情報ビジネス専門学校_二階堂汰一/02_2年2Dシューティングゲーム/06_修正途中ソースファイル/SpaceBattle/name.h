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
#include "scene2d.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_NAME (8)
#define MAX_COLUMN 3
#define COLUMN_MAXNUMBER 10
#define MAX_NAME_TEXTURE 2
#define TEXT_SCALE 2.0f//テキストサイズのスケール
#define TEXT_SIZE 50.0f * TEXT_SCALE
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
	static CName * Create();
	HRESULT Init();
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
	}IsCount;//推されてるか？と押し中カウント
	typedef struct
	{
		IsCount Up;
		IsCount Down;
		IsCount Right;
		IsCount Left;
	}IsPress;//推されてるか？
	void Input(void);
	void SetLetter(void);
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_NAME_TEXTURE];	//テクスチャ
	static Letter m_aLetter[MAX_COLUMN][COLUMN_MAXNUMBER];
	D3DXVECTOR3 m_pos;											//位置
	CScene2d * m_apScene[MAX_POLYGON];							//シーン
	CScene2d * m_apSceneText[MAX_NAME];							//シーン（上のテキスト表示用）
	float m_fTextureX;											//テクスチャの幅
	float m_fTextureY;											//テクスチャの高さ
	float m_fMove;
	float m_fWidth;												//幅
	float m_fHeight;											//高さ
	bool m_bName;												//名前の記録状態
	bool m_bCanselName;											//名前の取り消し状態
	char m_aName[MAX_NAME];										//名前格納用
	bool m_bColumnDown;											//下矢印判定
	bool m_bColumnUp;											//上矢印判定
	int m_nColumnCount;											//行数カウンタ
	bool m_bLetterRight;										//右矢印判定
	bool m_bLetterLeft;											//左矢印判定
	bool m_bOK;													//決定判定
	int m_nLetterCount;											//文字数カウンタ
	int m_nNameCount;											//名前の文字数カウンタ
	IsPress m_IsTrigger;                                        //推されてるかどうか
	int m_TriggerCount;											//押し中のカウンタ

};
#endif