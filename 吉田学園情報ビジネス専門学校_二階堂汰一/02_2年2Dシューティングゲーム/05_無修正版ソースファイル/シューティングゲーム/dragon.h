//=============================================================================
//
// ドラゴン [dragon.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _DRAGON_H_
#define _DRAGON_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"
#include "bullet.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_DRAGON	"data/TEXTURE/dragon002.png"
#define DRAGON_SIZE_WIDTH 600.0f			//ドラゴンの幅の当たり判定
#define DRAGON_SIZE_HEIGHT 600.0f			//ドラゴンの高さの当たり判定
#define DRAGON_MAX_HP 3000					//ドラゴン死亡ライン
#define DRAGON_MIN_HP 0						//ドラゴン死亡ライン
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CDragon :public CScene2d
{
public:
	CDragon(int nPriority = 4);
	~CDragon();
	static HRESULT Load(void);
	static void Unload(void);
	static CDragon * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,int nLife);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);
	void SubLife(int nValue);
	static bool GetSpawn(void) { return m_bSpawn; };
	static bool GetDeath(void) { return m_bDeath; };
	static void SetSpawn(bool bSpawn);
	static void SetDeath(bool bDeath);
private:
	void AI(void);
	void Animation(void);
	void Damage(void);
	void Attack(void);
	static LPDIRECT3DTEXTURE9 m_pScene;
	static 	bool m_bSpawn;			//スポーンしたかどうか
	static 	bool m_bDeath;			//死亡したかどうか
	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_vpos[NUM_VERTEX]; //頂点座標
	D3DXVECTOR3 m_move;				//敵の移動量
	D3DCOLOR m_col[NUM_VERTEX];		//色
	D3DXVECTOR3	m_rot;				//向き
	D3DXVECTOR3 m_TargetDistance;	//目標までの距離
	D3DXVECTOR3 m_TargetPos;		//目標地点
	int m_nLife;					//体力
	int m_nCountBullet;				//弾のカウンタ
	int m_nCountAI;					//AIカウンタ
	int m_nCounterAnim;				//アニメカウンタ
	int m_nPatternAnim;				//アニメパターン
	int m_nHitCount;				//HITカウンタ
	float m_fWidth;					//幅
	float m_fHeight;				//高さ
	float m_fTime;					//タイム
	float m_fAngle;					//角度
	float m_fLength;				//長さ
	float m_fScale;					//大きさ
	float m_fAddScale;				//大きさの加算量
	bool m_bHit;					//ヒットしたかどうか
	CBullet * m_pBullet;			//弾のポインタ
};
#endif