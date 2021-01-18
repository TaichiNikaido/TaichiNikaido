//=============================================================================
//
// ボス [boss.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PART00_TEXTURE "data/TEXTURE/BOSS/core002.png"			//コア02
#define PART01_TEXTURE "data/TEXTURE/BOSS/core.png"				//コア
#define PART02_TEXTURE "data/TEXTURE/BOSS/core001.png"			//コア01
#define PART03_TEXTURE "data/TEXTURE/BOSS/10_body_right2.png"	//右半身
#define PART04_TEXTURE "data/TEXTURE/BOSS/body_left.png"		//左半身
#define PART05_TEXTURE "data/TEXTURE/BOSS/hand_right.png"		//右手
#define PART06_TEXTURE "data/TEXTURE/BOSS/hand_left.png"		//左手
#define PART07_TEXTURE "data/TEXTURE/BOSS/forearm_right.png"	//右前腕
#define PART08_TEXTURE "data/TEXTURE/BOSS/forearm_left.png"		//左前腕
#define PART09_TEXTURE "data/TEXTURE/BOSS/upperarm_right.png"	//右上腕
#define PART10_TEXTURE "data/TEXTURE/BOSS/upperarm_left.png"	//左上腕
#define PART11_TEXTURE "data/TEXTURE/BOSS/head.png"				//頭
#define PART12_TEXTURE "data/TEXTURE/BOSS/chin.png"				//顎
#define PART13_TEXTURE "data/TEXTURE/BOSS/eye.png"				//目
#define PART14_TEXTURE "data/TEXTURE/BOSS/eyeflame.png"			//目のフレーム
#define BOSS_LIFE 1000
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBoss :public CScene2d
{
public:
	typedef enum
	{
		PART_NONE = -1,
		CORE_02,
		CORE,
		CORE_01,
		BODY_RIGHT,
		BODY_LEFT,
		HAND_RIGHT,
		HAND_LEFT,
		FOREARM_RIGHT,
		FOREARM_LEFT,
		UPPERARM_RIGHT,
		UPPERARM_LEFT,
		HEAD,
		CHIN,
		EYE,
		EYEFLAME,
		PART_MAX
	}PART;
	CBoss(int nPriority = 5);
	~CBoss();
	static HRESULT Load(void);
	static void Unload(void);
	static CBoss * Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	HRESULT Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SubLife(int nValue);
private:
	typedef struct
	{
		D3DXVECTOR3 m_pos;				//位置
		D3DXVECTOR3 m_vpos[NUM_VERTEX];	//頂点座標
		D3DXVECTOR3 m_move;				//移動量
		D3DXVECTOR3 m_rot;				//回転
		float m_fWidth;					//幅
		float m_fHeight;				//高さ
		float m_fLength;				//対角線の長さ
		float m_fAngle;					//対角線の角度
		float m_fScale;					//拡大
	}PART_STATUS;
	static LPDIRECT3DTEXTURE9 m_apTexture[PART_MAX];
	CScene2d * m_apScene[PART_MAX];
	PART_STATUS m_PartStatus[PART_MAX];	//構造体の変数
	int m_nLife;						//体力
	int m_nCountBullet;					//弾のカウント
	CBullet * m_pBullet;				//弾のポインタ
};
#endif