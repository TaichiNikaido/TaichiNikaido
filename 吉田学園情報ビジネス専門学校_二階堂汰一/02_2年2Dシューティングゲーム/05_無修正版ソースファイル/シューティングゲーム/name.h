//=============================================================================
//
// 名前 [name.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _NAME_H_
#define _NAME_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"
#include "scene2D.h"
//*****************************************************************************
// マクロ定義
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
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
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
	}IsCount;//推されてるか？と押し中カウント
	typedef struct
	{
		IsCount Up;
		IsCount Down;
		IsCount Right;
		IsCount Left;
	}IsPress;//推されてるか？
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_NAME_TEXTURE];	//テクスチャ
	static Letter m_aLetter[MAX_COLUMN][COLUMN_MAXNUMBER];
	D3DXVECTOR3 m_pos;											//位置
	CScene2d * m_apSceneBG[MAX_POLYGON];						//シーン
	CScene2d * m_apScene[MAX_POLYGON];							//シーン
	CScene2d * m_apSceneText[MAX_NAME];							//シーン（上のテキスト表示用）
	D3DXVECTOR3 m_vPos[NUM_VERTEX];								//頂点座標
	D3DCOLOR m_col[NUM_VERTEX];									//色
	float m_fTextureX;											//テクスチャの幅
	float m_fTextureY;											//テクスチャの高さ
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