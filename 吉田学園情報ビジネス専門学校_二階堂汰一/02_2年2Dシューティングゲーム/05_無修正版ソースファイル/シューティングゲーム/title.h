//=============================================================================
//
// タイトル [title.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"
#include "scene2d.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_TITLE1	"data/TEXTURE/titlebg.png"
#define TEXTURE_TITLE2	"data/TEXTURE/titlelogo.png"
#define TEXTURE_TITLE3	"data/TEXTURE/start1.png"
#define TEXTURE_TITLE4	"data/TEXTURE/replay.png"
#define TEXTURE_TITLE5	"data/TEXTURE/exit.png"

#define LOGO_SIZE_WIDTH 988
#define LOGO_SIZE_HEIGHT 353

#define TBUTTON_SIZE_WIDTH 431
#define TBUTTON_SIZE_HEIGHT 83
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTitle :public CScene
{
public:
	CTitle(int nPriority = 0);
	~CTitle();
	static HRESULT Load(void);
	static void Unload(void);
	static CTitle * Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	HRESULT Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static bool GetbReplay(void) { return m_bReplay; };
private:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_BG,
		TYPE_LOGO,
		TYPE_START,
		TYPE_RPLAY,
		TYPE_EXIT,
		TYPE_MAX
	}TYPE;
	typedef struct
	{
		int nCount;
		bool bTrigger;
	}IsCount;//押されてるか？と押し中カウント
	typedef struct
	{
		IsCount Up;
		IsCount Down;
		IsCount Right;
		IsCount Left;
	}IsPress;//押されてるか？
	IsPress m_IsTrigger;                                         //押されてるかどうか
	int     m_TriggerCount;                                     //押し中のカウンタ
	int   m_nButtonPos;
	int   m_aButtonAlpha[TYPE_MAX];
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];
	static bool m_bReplay;
	D3DXVECTOR3 m_pos;
	CScene2d * m_apScene[MAX_POLYGON];
	D3DXVECTOR3 m_vpos[NUM_VERTEX];
	D3DCOLOR m_col[NUM_VERTEX];
	float m_fTextureX;
	float m_fTextureY;
	float m_fFastMove;
	float m_fSlowMove;
	float m_fMove;
	float m_fWidth;
	float m_fHeight;
};
#endif