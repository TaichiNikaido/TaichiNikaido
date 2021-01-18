//=============================================================================
//
// リザルト [result.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"
#include "scene2d.h"
#include "name.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_RESULT1	"data/TEXTURE/resultbg.png"
#define TEXTURE_RESULT2	"data/TEXTURE/bg101.png"
#define TEXTURE_RESULT3	"data/TEXTURE/bg102.png"
#define MAX_RESULT_TEXTURE 3
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CResult :public CScene
{
public:
	typedef struct
	{
		char aName[MAX_NAME];
		int nDeath;
		int nContinue;
		int nBomb;
		int nScore;
	}PLAYER_DATA;

	CResult(int nPriority = 0);
	~CResult();
	static HRESULT Load(void);
	static void Unload(void);
	static CResult * Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	HRESULT Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void TextLoad(void);
	static PLAYER_DATA GetPlayerData(void) { return m_PlayerData; };
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_RESULT_TEXTURE];
	static PLAYER_DATA m_PlayerData;
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