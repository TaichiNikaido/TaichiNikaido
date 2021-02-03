//=============================================================================
//
// アイテム [item.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_OWN_ITEM	"data/TEXTURE/life.png"			//アイテムのテクスチャの保存先
#define TEXTURE_LEVEL_ITEM	"data/TEXTURE/lvup.png"			//アイテムのテクスチャの保存先
#define TEXTURE_SCORE_ITEM	"data/TEXTURE/ScoreItem.png"	//アイテムのテクスチャの保存先
#define TEXTURE_BOMB_ITEM	"data/TEXTURE/bomb.png"			//アイテムのテクスチャの保存先
#define MAX_ITEM_TEXTURE 4	//アイテムのテクスチャの最大数
#define ITEM_SIZE 50.0f		//アイテムのサイズ
#define ITEM_SPEED 4.0f		//アイテムの素早さ
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CItem :public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_OWN,
		TYPE_LEVEL,
		TYPE_SCORE,
		TYPE_BOMB,
		TYPE_MAX
	}TYPE;
	CItem();
	~CItem();
	static HRESULT Load(void);
	static void Unload(void);
	static CItem * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CItem::isCollision(D3DXVECTOR3 pos);
private:
	void Effect(void);
	void MovableRange(void);
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ITEM_TEXTURE];
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_vpos[NUM_VERTEX];	//頂点座標
	D3DXVECTOR3 m_move;	//移動量
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
	TYPE m_Type;		//タイプ
};
#endif