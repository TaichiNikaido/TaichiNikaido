//=============================================================================
//
// n-way [bullet_n-way.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BULLET_N_WAY_H_
#define _BULLET_N_WAY_H_

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
class CBulletN_Way :public CBulletEnemy
{
public:
	CBulletN_Way(int nPriority = 3);
	~CBulletN_Way();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CBulletN_Way * Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Death(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
};
#endif


