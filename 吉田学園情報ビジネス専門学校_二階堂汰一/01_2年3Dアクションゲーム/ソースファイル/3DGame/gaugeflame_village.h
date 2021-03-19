//=============================================================================
//
// 村ゲージの枠 [gaugeflame_village.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _GAUGEFLAME_VILLAGE_H_
#define _GAUGEFLAME_VILLAGE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "gaugeflame.h"

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
class CGaugeFlameVillage :public CGaugeFlame
{
public:
	CGaugeFlameVillage();
	~CGaugeFlameVillage();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CGaugeFlameVillage * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
};
#endif