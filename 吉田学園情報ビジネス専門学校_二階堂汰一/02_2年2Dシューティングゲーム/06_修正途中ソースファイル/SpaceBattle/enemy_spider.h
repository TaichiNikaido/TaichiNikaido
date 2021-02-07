//=============================================================================
//
// 蜘蛛 [enemy_spider.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _ENEMY_SPIDER_H_
#define _ENEMY_SPIDER_H_

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
class CEnemySpider :public CEnemy
{
public:
	CEnemySpider(int nPriority = DEFAULT_PRIORITY);
	~CEnemySpider();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CEnemySpider * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Move(void);
	void Attack(void);
	void Stop(void);
	void Stay(void);
	void Death(void);
	void Drop(void);
	void Animation(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	D3DXVECTOR3 m_StopPosition;				//止まる位置
	int m_nCountBullet;						//弾のカウンタ
	int m_nCounterAnime;					//アニメカウンタ
	int m_nPatternAnime;					//パターンアニメ
	int m_nStayTime;
};
#endif