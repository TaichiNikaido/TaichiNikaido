//=============================================================================
//
// ハートアイコン [heart_icon.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _HEART_ICON_H_
#define _HEART_ICON_H_

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
class CHeartIcon :public CScene2d
{
public:
	CHeartIcon(int nPriority = PRIORITY_POLYGON2D);
	~CHeartIcon();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CHeartIcon * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPatternAnime(int nPatternAnime) { m_nPatternAnime = nPatternAnime; }
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
	int m_nPatternAnime;					//パターンアニメ
};
#endif