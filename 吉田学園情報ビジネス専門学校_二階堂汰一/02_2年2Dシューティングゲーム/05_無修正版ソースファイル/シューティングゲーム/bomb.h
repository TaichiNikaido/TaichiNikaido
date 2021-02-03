//=============================================================================
//
// 爆弾 [bomb.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BOMB_H_
#define _BOMB_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_BOMB "data/TEXTURE/bomb.png"		//弾のテクスチャの保存先
#define BOMB_SIZE 50.0f								//弾のサイズ
#define PLAYER_BOMB_LIFE 50							//プレイヤーの爆弾のライフ
#define PLAYER_BOMB_DAMAGE 10						//プレイヤーの爆弾ダメージ
#define ENEMY_BOMB_LIFE 100							//エネミーの爆弾ライフ
#define ENEMY_BOMB_DAMAGE 10						//エネミーの爆弾のダメージ
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBomb :public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_MAX
	}TYPE;
	CBomb();
	~CBomb();
	static HRESULT Load(void);
	static void Unload(void);
	static CBomb * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight,  int nLife, int nAttack);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight, int nLife, int nAttack);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void SubLife(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_vpos[NUM_VERTEX];			//頂点座標
	D3DXVECTOR3 m_move;						//移動
	TYPE m_Type;							//タイプ
	int m_nLife;							//ライフ
	int m_nAttack;							//攻撃力
	float m_fWidth;							//幅
	float m_fHeight;						//高さ
};
#endif