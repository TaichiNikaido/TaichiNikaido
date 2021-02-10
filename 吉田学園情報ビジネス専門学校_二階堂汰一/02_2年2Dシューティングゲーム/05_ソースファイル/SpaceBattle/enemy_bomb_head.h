//=============================================================================
//
// 爆弾の敵の頭 [enemy_bomb_head.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _ENEMY_BOMB_HEAD_H_
#define _ENEMY_BOMB_HEAD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BOMB_BODY (5)
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CEnemyBombBody;
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemyBombHead :public CEnemy
{
public:
	CEnemyBombHead();
	~CEnemyBombHead();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CEnemyBombHead * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DeathAll(void);
private:
	void Death(void);
	CEnemyBombBody * m_pBombBody[MAX_BOMB_BODY];
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	float m_fRd;//ラジアン
	float m_fRdScale;//加算量
	bool m_bCreateBody;
	int m_nCreateCount;
	int m_nCreateBodyCount;
	D3DXVECTOR3 m_InitPos;
	int m_nBombLife;
	bool m_bDeath;
	bool m_bDeathAll;
};
#endif