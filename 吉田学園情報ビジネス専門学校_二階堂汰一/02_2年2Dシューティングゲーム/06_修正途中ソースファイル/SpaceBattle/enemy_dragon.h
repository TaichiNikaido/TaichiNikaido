//=============================================================================
//
// ドラゴン [enemy_spider.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _ENEMY_DRAGON_H_
#define _ENEMY_DRAGON_H_

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
class CBulletFireball;

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemyDragon :public CEnemy
{
public:
	CEnemyDragon(int nPriority = DEFAULT_PRIORITY);
	~CEnemyDragon();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CEnemyDragon * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CBulletFireball * GetBulletFireBall(void) { return m_pBulletFireBall; }
private:
	void Scale(void);
	void Attack(void);
	void Death(void);
	void Animation(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	D3DXVECTOR3 m_TargetDistance;//目標までの距離
	D3DXVECTOR3 m_TargetPos;//目標地点
	int m_nPatternAnime;					//パターンアニメ
	int m_nCounterAnime;					//カウンターアニメ
	int m_nBulletTime;						//弾の発射間隔
	bool m_bCharge;
	int m_nChargeTime;
	CBulletFireball * m_pBulletFireBall;
};
#endif