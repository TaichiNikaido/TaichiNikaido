//******************************************************************************
// 砂埃のパーティクル [dust_particle.h]
// Author : 管原　司
//******************************************************************************
#ifndef _DUST_PARTICLE_H_
#define _DUST_PARTICLE_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "particle.h"
//******************************************************************************
// クラス
//******************************************************************************
class CDust_Particle : public CParticle
{
public:
	CDust_Particle(int nPrirority = 0);
	~CDust_Particle();
	static CDust_Particle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SandDust_Create(D3DXVECTOR3 pos);
private:
	D3DXVECTOR3 m_move;		// 移動
	float m_fAddScale;		// 拡大率加算
	float m_fMinColor;		//	色の減算値
};
#endif