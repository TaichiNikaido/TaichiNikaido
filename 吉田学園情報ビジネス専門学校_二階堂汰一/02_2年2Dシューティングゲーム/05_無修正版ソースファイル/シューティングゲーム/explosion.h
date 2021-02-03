//=============================================================================
//
// 爆発 [explosion.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_EXPLOSION "data/TEXTURE/explosion000.png"
#define BOMB_EXPLOSION_SIZE 500.0f		
#define FIREBALL_EXPLOSION_SIZEX 500.0f	
#define FIREBALL_EXPLOSION_SIZEY 500.0f	
#define PLAYER_EXPLOSION_SIZE 50.0f		
#define ENEMY_EXPLOSION_SIZE 50.0f		
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CExplosion :public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_BULLET,
		TYPE_BOMB,
		TYPE_FIERBALL,
		TYPE_MAX
	}TYPE;
	CExplosion();
	~CExplosion();
	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,  TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Animation(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	D3DXVECTOR3 m_vpos[NUM_VERTEX];			//頂点座標
	int m_nCounterAnim;						//アニメカウンタ
	int m_nPatternAnim;						//アニメパターン
	float m_fWidth;							//幅
	float m_fHeight;						//高さ
	TYPE m_type;							//タイプ
};
#endif