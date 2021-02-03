 //=============================================================================
//
// 敵 [enemy.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"
#include "bullet.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_EYE	"data/TEXTURE/ENEMY/enemy_easy.png"		//目の敵のテクスチャ保存先
#define TEXTURE_FLOWER	"data/TEXTURE/ENEMY/flower.png"		//花の敵のテクスチャ保存先
#define TEXTURE_SPIDER	"data/TEXTURE/ENEMY/spider.png"		//花の敵のテクスチャ保存先
#define TEXTURE_BOMBHEAD	"data/TEXTURE/ENEMY/bombhead.png"		//花の敵のテクスチャ保存先
#define TEXTURE_BOMBBODY	"data/TEXTURE/ENEMY/bombbody.png"		//花の敵のテクスチャ保存先
#define TEXTURE_EYE2	"data/TEXTURE/ENEMY/eye2.png"		//花の敵のテクスチャ保存先
#define EYE_SIZE 50.0f			//敵(目)の当たり判定
#define FLOWER_SIZE 100.0f			//敵(花)の当たり判定
#define SPIDER_SIZE 150.0f			//敵(蜘蛛)の当たり判定
#define EASY_EYE_MAX_HP 30		//ザコ敵のライフの最大値
#define EASY_FLOWER_MAX_HP 130		//ザコ敵のライフの最大値
#define EASY_SPIDER_MAX_HP 120		//ザコ敵のライフの最大値
#define NORMAL_ENEMY_MAX_HP 75		//普通の敵のライフの最大値
#define MIDDLE_ENEMY_MAX_HP 500		//中ボスのライフの最大値
#define HARD_ENEMY_MAX_HP 1500		//ラスボスのライフの最大値
#define ENEMY_MIN_HP 0				//敵の体力の死亡ライン
#define MAX_LOCATION 4
#define RATE_MOVE 0.03f
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemy :public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_EYE,
		TYPE_FLOWER,
		TYPE_SPIDER,
		TYPE_MIDDLE,
		TYPE_HARD,
		TYPE_BOMBHEAD,
		TYPE_BOMBBODY,
		TYPE_EYE2,
		TYPE_MAX
	}TYPE;
	CEnemy(int nPriority = 4);
	~CEnemy();
	static HRESULT Load(void);
	static void Unload(void);
	static CEnemy * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type,int nLife);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type, int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);
	void SubLife(int nValue);
private:
	void AI(void);
	void Damage(void);
	void Animation(void);
	void MovableRange(void);
	static LPDIRECT3DTEXTURE9 m_apScene[TYPE_MAX];
	static int m_nCountEnemy;		//敵の総数
	static int  m_nBombEnemyLife;	//爆弾敵のライフ
	TYPE m_type;					//敵の種類
	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_vpos[NUM_VERTEX]; //頂点座標
	D3DXVECTOR3 m_move;				//敵の移動量
	float       m_fRd;				//ラジアン
	float       m_fRdScale;			//ラジアン拡縮
	D3DXVECTOR3 m_Location[MAX_LOCATION];	//地点
	D3DCOLOR	m_col[NUM_VERTEX];			//色
	float m_fLength;				//長さ
	float m_fAngle;					//角度
	float m_fRot;					//向き
	float m_fScale;					//拡縮
	int m_nLife;					//体力
	int m_nCountBullet;				//弾のカウンタ
	int m_nEnemyTimeCount;			//敵の滞在時間
	int m_nBulletIndex;				//弾の発射数
	int m_nHitCount;				//HITカウント
	float m_fBulletAngle;			//弾の角度
	float m_fWidth;					//幅
	float m_fHeight;				//高さ
	float m_fTime;					//タイム
	float m_fStop;					//敵が止まる場所
	bool m_bHit;					//ヒットしたかどうか
	bool m_bShot;					//弾を撃ったかどうか
	bool m_bStay;					//滞在してるかどうか
	int m_nStayCount;				//滞在時間
	int m_nCounterAnim;				//アニメカウンタ
	int m_nPatternAnim;				//パターンアニメ
	int m_nColorCount;				//色カウンタ
	CBullet * m_pBullet;			//弾のポインタ
};
#endif