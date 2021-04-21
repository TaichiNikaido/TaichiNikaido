//******************************************************************************
// 円形のパーティクル [circle_particle.h]
// Author : 管原　司
//******************************************************************************
#ifndef _CIRCLE_PARTICLE_H_
#define _CIRCLE_PARTICLE_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "particle.h"
//******************************************************************************
// クラス
//******************************************************************************
class CCircle_Particle : public CParticle
{
public:
	CCircle_Particle(int nPrirority = 0);
	~CCircle_Particle();
	static CCircle_Particle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Effect_Create(D3DXVECTOR3 pos);
private:
	D3DXVECTOR3 m_move;		// 移動
	float m_fMinColor;		//	色の減算値
};
#endif