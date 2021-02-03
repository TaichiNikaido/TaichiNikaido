//=============================================================================
//
// タイトル [title.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"
#include "scene2d.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_TUTORIAL	"data/TEXTURE/cyu.png"
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
class CTutorial :public CScene
{
public:
	CTutorial(int nPriority = 0);
	~CTutorial();
	static HRESULT Load(void);
	static void Unload(void);
	static CTutorial * Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	HRESULT Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	CScene2d * m_pScene;
	D3DXVECTOR3 m_vpos[NUM_VERTEX];
	D3DCOLOR m_col[NUM_VERTEX];
	D3DXVECTOR3 m_pos;
	float m_fTextureX;
	float m_fTextureY;
	float m_fWidth;
	float m_fHeight;
};
#endif