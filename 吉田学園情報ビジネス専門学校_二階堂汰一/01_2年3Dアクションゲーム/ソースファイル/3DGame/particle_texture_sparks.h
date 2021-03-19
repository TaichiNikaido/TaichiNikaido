//=============================================================================
//
// 火の粉のテクスチャ [particle_texture_sparks.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _PARTICLE_TEXTURE_SPARKS_H_
#define _PARTICLE_TEXTURE_SPARKS_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "particle_texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSparksTexture :public CParticleTexture
{
public:
	CSparksTexture();
	~CSparksTexture();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CSparksTexture * Create(D3DXVECTOR3 Position, D3DXVECTOR3 Rotation,D3DXVECTOR3 Size,D3DXVECTOR3 Move,int nLife);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
};
#endif