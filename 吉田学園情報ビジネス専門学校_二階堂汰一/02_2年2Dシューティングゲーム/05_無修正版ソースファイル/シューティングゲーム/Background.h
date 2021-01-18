//=============================================================================
//
// 背景 [background.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"
#include "scene2d.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_BG1	"data/TEXTURE/bg_0001.png"	//テクスチャの保存先
#define TEXTURE_BG2	"data/TEXTURE/bg_0002.png"	//テクスチャの保存先
#define TEXTURE_BG3	"data/TEXTURE/bg_0003.png"	//テクスチャの保存先
#define MAX_BG_TEXTURE 3	//テクスチャの最大数
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBg :public CScene
{
public:
	CBg(int nPriority = 0);
	~CBg();
	static HRESULT Load(void);
	static void Unload(void);
	static CBg * Create(D3DXVECTOR3 pos,float SizeWidth,float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG_TEXTURE];
	CScene2d * m_apScene[MAX_POLYGON];
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_vpos[NUM_VERTEX];	//頂点座標
	float m_fTextureX;	//テクスチャのX
	float m_fTextureY;	//テクスチャのY
	float m_fFastMove;	//早い移動量
	float m_fSlowMove;	//遅い移動量
	float m_fMove;		//移動量
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
};
#endif