//=============================================================================
//
// 弾 [bullet.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"
#include "effect.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_BULLET "data/TEXTURE/bullet000.png"		//弾のテクスチャの保存先
#define TEXTURE_FIERBALL "data/TEXTURE/bullet000.png"   //火球のテクスチャの保存先
#define TEXTURE_BREATHE "data/TEXTURE/bullet000.png"	//ブレスのテクスチャの保存先
#define TEXTURE_BEAM "data/TEXTURE/beam.png"			//ビームのテクスチャの保存先
#define TEXTURE_BIRA "data/TEXTURE/bira.png"			//ビームのテクスチャの保存先
#define TEXTURE_FIRE "data/TEXTURE/fire.png"			//ビームのテクスチャの保存先
#define BULLET_SIZE 10.0f								//弾のサイズ
#define BEAM_SIZE 50.0f									//ビームのサイズ
#define PLAYER_BULLET_ATTACK 10							//プレイヤーの弾の攻撃力
#define PLAYER_BEAM_LIFE 50								//プレイヤーのビームのライフ
#define PLAYER_BEAM_ATTACK 5							//プレイヤーのビームの攻撃力
#define EASY_ENEMY_BULLET_ATTACK 10						//ザコ敵の弾の攻撃力
#define BULLET_SPEAD 7.0f
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBullet :public CScene2d
{
public:
	typedef enum
	{
		USER_NONE = -1,
		USER_PLAYER,
		USER_ENEMY,
		USER_DRAGON,
	}USER;

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_NORMAL,
		TYPE_AIM,
		TYPE_GUID,
		TYPE_N_WAY,
		TYPE_FIREBALL,
		TYPE_FIRE,
		TYPE_FLOWER,
		TYPE_BREATHE,
		TYPE_MAX
	}TYPE;

	typedef enum
	{
		COLOR_NONE = -1,
		COLOR_RED,
		COLOR_ORANGE,
		COLOR_YELLOW,
		COLOR_GREEN,
		COLOR_BLUE,
		COLOR_PURPLE,
		COLOR_PINK,
		COLOR_WHITE,
		COLOR_MAX
	}COLOR;

	typedef enum
	{
		TEXTURE_NONE = -1,
		BULLET_TEXTURE,
		BEAM_TEXTURE,
		FLOWER_TEXTURE,
		FIRE_TEXTURE,
		TEXTURE_MAX
	}TEXTURE;

	CBullet(int nPriority = 4);
	~CBullet();
	static HRESULT Load(void);
	static void Unload(void);
	static CBullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight, USER user ,TYPE type, COLOR col,TEXTURE textureint ,int nAttack);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight, USER user, TYPE type, COLOR col, TEXTURE textureint, int nAttack);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static bool GetbFireBall(void) { return m_bFireBall; };
	static bool GetbCharage(void) { return m_bCharage; };
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_MAX];
	static D3DCOLOR         m_aColor[COLOR_MAX];//7色プリセット
	static bool m_bFireBall;
	static bool m_bCharage;
	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_TargetPos;
	D3DXVECTOR3 m_vpos[NUM_VERTEX];	//頂点座標
	D3DCOLOR m_col[NUM_VERTEX];
	D3DXVECTOR3 m_move;				//移動
	D3DXVECTOR3	m_rot;				//向き
	COLOR m_pCol;
	USER m_user;					//使用者
	TYPE m_type;					//タイプ
	TEXTURE m_texture;				//テクスチャ
	int m_nAttack;					//攻撃力
	float m_fWidth;					//幅
	float m_fHeight;				//高さ
	CEffect * m_pEffect;			//エフェクトのポインタ
	float m_fAngle;					//角度
	int m_nCount;					//カウント
	int m_nBreatheCount;			//ブレスの長さ
	int m_nLife;					//ライフ
	//弾の速度
	float m_fVx; 
	float m_fVy;
	int m_nCountBullet;
	float m_fadd;
	float m_theta;
	//弾幕の本
	float m_fDistance;
	float m_fSpeed;
	float m_fLength;			//長さ
	float m_fScale;			//大きさ
	float m_fAddScale;		//大きさの加算量
	bool m_bShotFireball;
	bool m_bShotFire;
};
#endif