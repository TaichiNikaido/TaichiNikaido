//=============================================================================
//
// 方向弾 [bullet_direction.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BULLET_DIRECTION_H_
#define _BULLET_DIRECTION_H_

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
class CBulletDirection :public CBulletEnemy
{
public:
	CBulletDirection(int nPriority = 3);
	~CBulletDirection();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CBulletDirection * Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Death(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
};
#endif


