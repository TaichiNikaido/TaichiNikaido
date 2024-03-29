//=============================================================================
//
// 爆弾 [bullet_bomb.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef BULLET_BOMB_H_
#define BULLET_BOMB_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BOMB_SPEED (D3DXVECTOR3(0.0f,-10.0f,0.0f))

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBulletBomb :public CBullet
{
public:
	CBulletBomb();
	~CBulletBomb();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CBulletBomb * Create(D3DXVECTOR3 Position, D3DXVECTOR3 Speed);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Death(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
};
#endif


