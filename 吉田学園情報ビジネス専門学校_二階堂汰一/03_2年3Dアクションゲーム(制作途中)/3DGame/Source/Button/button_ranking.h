//=============================================================================
//
// ランキンボタン [button_ranking.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BUTTON_RANKING_H_
#define _BUTTON_RANKING_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "button.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CRankingButton :public CButton
{
public:
	CRankingButton();
	~CRankingButton();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CRankingButton * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Press(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
};
#endif