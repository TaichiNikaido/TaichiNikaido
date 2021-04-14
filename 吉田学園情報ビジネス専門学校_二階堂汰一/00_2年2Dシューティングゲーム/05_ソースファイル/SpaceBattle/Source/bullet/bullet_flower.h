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
		COLOR_NUMBER_NONE = -1,
		COLOR_NUMBER_RED,
		COLOR_NUMBER_ORANGE,
		COLOR_NUMBER_YELLOW,
		COLOR_NUMBER_GREEN,
		COLOR_NUMBER_BLUE,
		COLOR_NUMBER_PURPLE,
		COLOR_NUMBER_PINK,
		COLOR_NUMBER_WHITE,
		COLOR_NUMBER_MAX
	}COLOR_NUMBER;
	CBulletFlower();
	~CBulletFlower();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CBulletFlower * Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed,COLOR_NUMBER nColor);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Move(void);
	void ColorSelect(void);
	void Death(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	COLOR_NUMBER m_ColorNumber;				//色の番号
	int m_nTime;							//時間
};
#endif


