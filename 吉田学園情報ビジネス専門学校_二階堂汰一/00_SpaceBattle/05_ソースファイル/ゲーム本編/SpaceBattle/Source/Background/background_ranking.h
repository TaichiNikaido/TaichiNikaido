//=============================================================================
//
// ランキング背景 [background_ranking.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BACKGROUND_RANKING_H_
#define _BACKGROUND_RANKING_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "background.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBackgroundRanking :public CBackground
{
public:
	CBackgroundRanking();
	~CBackgroundRanking();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CBackgroundRanking * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
};
#endif