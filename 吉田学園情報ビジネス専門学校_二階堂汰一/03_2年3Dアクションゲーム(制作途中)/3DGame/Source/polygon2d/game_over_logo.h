//=============================================================================
//
// ゲームオーバーロゴ [game_over_logo.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _GAME_OVER_LOGO_H_
#define _GAME_OVER_LOGO_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGameOverLogo :public CScene2d
{
public:
	CGameOverLogo(int nPriority = PRIORITY_POLYGON2D);
	~CGameOverLogo();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CGameOverLogo * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	float m_fAlpha;								//アルファ値
	float m_fAddAlpha;							//アルファ値の加算量
};
#endif