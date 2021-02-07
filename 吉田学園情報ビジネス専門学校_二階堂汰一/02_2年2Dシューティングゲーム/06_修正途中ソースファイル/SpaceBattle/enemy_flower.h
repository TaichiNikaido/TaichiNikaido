//=============================================================================
//
// 花 [enemy_flower.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _ENEMY_FLOWER_H_
#define _ENEMY_FLOWER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "enemy.h"

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
class CEnemyFlower :public CEnemy
{
public:
	CEnemyFlower(int nPriority = DEFAULT_PRIORITY);
	~CEnemyFlower();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CEnemyFlower * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Attack(void);
	void Stop(void);
	void Stay(void);
	void Death(void);
	void Drop(void);
	void Animation(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	D3DXVECTOR3 m_StopPosition;				//止まる位置
	int m_nCounterAnime;					//アニメカウンタ
	int m_nPatternAnime;					//アニメパターン
	int m_nBulletTime;						//弾の発射間隔
	int m_nColorCount;						//色カウント
	int m_nStayTime;
};
#endif