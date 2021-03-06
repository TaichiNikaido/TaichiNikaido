//=============================================================================
//
// 村のアイコン [ui_village_icon.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _UI_VILLAGE_ICON_H_
#define _UI_VILLAGE_ICON_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CVillageIcon :public CScene2d
{
public:
	CVillageIcon();
	~CVillageIcon();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CVillageIcon * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		ICON_NONE = -1,
		ICON_1,
		ICON_2,
		ICON_3,
		ICON_MAX
	}ICON;
	void DataLoad(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	int m_nPatternAnime;					//パターンアニメ
	float m_fAnimationValue;				//アニメーションの値
};
#endif