//******************************************************************************
// ダイヤのパーティクル [dust_particle.h]
// Author : 管原　司
//******************************************************************************
#ifndef _DIA_PARTICLE_H_
#define _DIA_PARTICLE_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "particle.h"
//******************************************************************************
// クラス
//******************************************************************************
class CDia_Particle : public CParticle
{
public:
	CDia_Particle(int nPrirority = 0);
	~CDia_Particle();
	static CDia_Particle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 move);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void DiaEffect_Create(D3DXVECTOR3 pos);
private:
	D3DXVECTOR3 m_move;		// 移動
	int m_nLife;			// ライフ
};
#endif