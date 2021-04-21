//******************************************************************************
// パーティクル [ particle.h]
// Author : 管原 司
//******************************************************************************
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "Base/billboard.h"
//******************************************************************************
// クラス
//******************************************************************************
class CParticle : public CBillboard
{
public:
	// テクスチャタイプ
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_1,
		TEX_TYPE_2,
		TEX_TYPE_3,
		TEX_TYPE_MAX,
	}TEX_TYPE;

	CParticle();
	~CParticle();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TEX_TYPE TexType);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEX_TYPE_MAX];	// texture
	TEX_TYPE m_TexType;								// テクスチャタイプ
};
#endif