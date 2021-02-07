//=============================================================================
//
// 目玉(ノーマル) [enemy_eye_normal.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _ENEMY_EYE_NORMAL_H_
#define _ENEMY_EYE_NORMAL_H_

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
class CEnemyEyeNormal :public CEnemy
{
public:
	CEnemyEyeNormal(int nPriority = DEFAULT_PRIORITY);
	~CEnemyEyeNormal();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CEnemyEyeNormal * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Attack(void);
	void Death(void);
	void Gaze(void);
	void Stop(void);
	void Stay(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	D3DXVECTOR3 m_StopPosition;	//敵が止まる場所
	int m_nShotCount;			//発射する数
	int m_nCountBullet;			//弾の発射間隔
	int m_nStayTime;
	float m_fAngleRot;			//向き
	float m_fBulletAngle;		//発射方向
};
#endif