//******************************************************************************
// スタンエフェクト [stan_effect.h]
// Author : 管原 司
//******************************************************************************
#ifndef _STAN_EFFECT_H_
#define _STAN_EFFECT_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "effect.h"
//******************************************************************************
// クラス
//******************************************************************************
class CStan_Effect : public CEffect
{
public:
	CStan_Effect(int nPriority = 0);
	~CStan_Effect();
	static CStan_Effect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CEffect::TEX_TYPE TexType, float fRadian, float fLength);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void StanEffect_Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, float fLength);
	void AllRelease(void);
private:
	D3DXVECTOR3 m_pos;
	float m_fRadian;		// 弧度
	float m_fLength;		// 半径
	float m_fAngle;			// 角度
};
#endif