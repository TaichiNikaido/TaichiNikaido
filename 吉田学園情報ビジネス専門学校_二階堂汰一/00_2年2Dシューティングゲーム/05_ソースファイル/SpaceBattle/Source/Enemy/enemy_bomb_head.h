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
	static LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	CEnemyBombBody * m_pBombBody[MAX_BOMB_BODY];	//爆弾敵の体のポインタ
	D3DXVECTOR3 m_InitialPosition;					//初期位置
	int m_nCreateTime;								//生成する時間
	int m_nCreateBodyCount;							//生成した体の数
	int m_nBombLife;								//全体の体力					
	float m_fRadian;								//ラジアン
	float m_fAddRadian;								//ラジアンの加算量
	bool m_bCreateBody;								//体を生成したか
	bool m_bDeath;									//死んだか
	bool m_bDeathAll;								//全て死んだか
};
#endif