//=============================================================================
//
// 花弾 [bullet_flower.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BULLET_FLOWER_H_
#define _BULLET_FLOWER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "bullet_enemy.h"

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
class CBulletFlower :public CBulletEnemy
{
public:
	typedef enum
	{
		COLOR_NONE = -1,
		COLOR_RED,
		COLOR_ORANGE,
		COLOR_YELLOW,
		COLOR_GREEN,
		COLOR_BLUE,
		COLOR_PURPLE,
		COLOR_PINK,
		COLOR_WHITE,
		COLOR_MAX
	}COLOR;
	CBulletFlower(int nPriority = 3);
	~CBulletFlower();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CBulletFlower * Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	COLOR m_Color;
};
#endif


