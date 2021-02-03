//=============================================================================
//
// ワームホール [wormhole.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _WORMHOLE_H_
#define _WORMHOLE_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WORMHOLE		"data/TEXTURE/hole002.png"	//テクスチャの保存先
#define TEXTURE_WORMHOLEEFFECT	"data/TEXTURE/hole001.png"	//テクスチャの保存先
#define MAX_WORMHOLE_TEXTURE 2								//ワームホールのテクスチャの最大数
#define WORMHOLE_TEXTURE_SIZE 50.0f							//ワームホールのテクスチャサイズ
#define WORMHOLEEFFECT_TEXTURE_SIZE 200.0f					//ワームホールのエフェクトサイズ
#define WORMHOLE_SPEED 1.0f									//ワームホールのスピード
#define WORMHOLE_SIZE 50.0f									//ワームホールの当たり判定

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CWormhole :public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_DRAGON,
		TYPE_BOSS,
		TYPE_MAX
	}TYPE;
	typedef enum
	{
		TEX_NONE = -1,
		TEX_HOLE,
		TEX_EFFECT,
		TEX_MAX
	}TEXTURE;
	CWormhole(int nPriority = 4);
	~CWormhole();
	static HRESULT Load(void);
	static void Unload(void);
	static CWormhole * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,TYPE type,TEXTURE texture,D3DCOLOR col);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type, TEXTURE texture, D3DCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Spawn(void);
	static bool GetSpawn(void){return m_bSpawn; };
	static void SetSpawn(bool bSpawn);
private:
	void Scale(void);
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_WORMHOLE_TEXTURE];
	static bool	m_bSpawn;
	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_vpos[NUM_VERTEX];	//頂点座標
	D3DCOLOR	m_col[NUM_VERTEX];	//頂点カラー
	D3DXVECTOR3	m_rot;				//向き
	TYPE		m_Type;				//タイプ
	TEXTURE     m_Texture;			//テクスチャ
	float		m_fAngle;			//角度
	float		m_fLength;			//長さ
	float		m_fScale;			//大きさ
	float		m_fAddScale;		//大きさの加算量
	int			m_nCountSpawn;		//スポーンカウント
};
#endif