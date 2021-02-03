//=============================================================================
//
// プレイヤー [player.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"
#include "bullet.h"
#include "bomb.h"
#include "name.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PLAYER	"data/TEXTURE/Battleship.png"	//プレイヤーのテクスチャの保存先
#define PLAYER_SIZE 65.0f			//プレイヤーのサイズ
#define PLAYER_INIT_OWN 3			//プレイヤーの自機の初期値
#define PLAYER_MAX_OWN 5			//プレイヤーの自機の最大値
#define PLAYER_MIN_OWN 0			//プレイヤーの自機の最小値
#define PLAYER_INIT_BOMB 3			//プレイヤーの爆弾の初期値
#define PLAYER_MIN_BOMB 0			//プレイヤーの爆弾の初期値
#define PLAYER_MAX_BOMB 5			//プレイヤーの爆弾の最大値
#define PLAYER_BOMB_COST 1			//プレイヤーの必要な爆弾数
#define PLAYER_ADD_BOMB 1			//プレイヤーの爆弾の加算量
#define PLAYER_SUB_BOMB 1			//プレイヤーの爆弾の減産量
#define PLAYER_ADD_OWN 1			//プレイヤーの自機の加算値
#define PLAYER_SUB_OWN 1			//プレイヤーの自機の減算値
#define PLAYER_ADD_LEVEL 1			//プレイヤーのレベルの加算値
#define PLAYER_SPEED 5.0f			//プレイヤーの移動速度
#define PLAYER_INVINCIBLE_TIME 80	//プレイヤーの無敵時間
#define PLAYER_DEATH_TIME 100		//プレイヤーの死亡時間

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer :public CScene2d
{
public:
	typedef enum
	{
		INPUT_NONE = -1,
		INPUT_UP,
		INPUT_DOWN,
		INPUT_LEFT,
		INPUT_RIGHT,
		INPUT_SHOT,
		INPUT_BOMB,
		INPUT_MAX
	}INPUT_TYPE;
	CPlayer(int nPriority = 4);
	~CPlayer();
	static HRESULT Load(void);
	static void Unload(void);
	static CPlayer * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,int nOwn);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, int nOwn);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);
	void AddOwn(int nValue);
	void SubOwn(int nValue);
	void AddLevel(int nValue);
	void AddBomb(int nValue);
	void SubBomb(int nValue);
	static void SetPlayerScpre(int nValue);
	static void SetPlayerName(int nCount, char aName);
	static bool GetbDeath(void) { return m_bDeath; };
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
private:
	void Input(void);
	void Attack(void);
	void MovableRange(void);
	void Invincible(void);
	void Death(void);
	void Save(void);
	void InputSave(void);
	void InputLoad(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	static int m_nScore;					//スコア
	static  char m_aPlayerName[MAX_NAME];	//名前
	static int m_nNameCount;				//名前の文字数カウンタ
	static 	bool m_bDeath;					//死んだかどうか
	D3DXVECTOR3 m_pos;						//位置
	D3DCOLOR m_col[NUM_VERTEX];				//色
	D3DXVECTOR3 m_move;						//移動
	D3DXVECTOR3 m_vpos[NUM_VERTEX];			//頂点座標
	D3DXVECTOR3 m_rot;						//向き
	float m_fLength;						//ポリゴンの対角線の長さ
	float m_fAngle;							//ポリゴンの角度
	float m_fScale;							//拡大
	float m_fAddScale;						//拡大加算値
	float m_fWidth;							//幅
	float m_fHeight;						//高さ
	float m_fSpeed;							//速さ
	int m_nOwn;								//自機の数
	int m_nLevel;							//プレイヤーレベル
	int m_nCountBullet;						//弾のカウント
	int m_nBomb;							//爆弾の数
	int m_nCount;							//カウント
	int m_nDeathCount;						//死亡時間
	int m_nInvincibleCount;					//無敵中カウント
	bool m_bShot;							//発射してるかどうか
	bool m_bInvincible;						//無敵かどうか
	bool m_bHit;							//ヒットしたかどうか
	int m_nContinue;						//リザルト数
	int m_nDeath;							//死亡数
	int m_nUseBomb;							//使用したボムの数
	char m_aInputData[15000][6];			//入力情報
	CBullet * m_pBullet;					//弾のポインタ
	CBomb * m_pBomb;						//爆弾のポインタ
};
#endif