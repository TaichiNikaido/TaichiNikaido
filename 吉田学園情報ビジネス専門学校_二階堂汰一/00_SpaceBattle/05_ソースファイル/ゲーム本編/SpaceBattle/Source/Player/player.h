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
#include "Base/scene2d.h"
#include "System/name.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_POS  (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 180, 0.0f))	//プレイヤーの位置
#define PLAYER_SIZE (D3DXVECTOR3(65.0f,65.0f,0.0f))								//プレイヤーのサイズ													
#define PLAYER_MAX_BOMB (5)														//プレイヤーの最大ボム数
#define PLAYER_MAX_LIFE (5)														//プレイヤーの最大ライフ

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBullet;

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
		STATE_NONE = -1,
		STATE_DEATH,		//死亡
		STATE_INVINCIBLE,	//無敵
		STATE_MAX
	}STATE;		//状態
	typedef enum
	{
		INPUT_NONE = -1,
		INPUT_UP,		//上方向
		INPUT_DOWN,		//下方向
		INPUT_LEFT,		//左方向
		INPUT_RIGHT,	//右方向
		INPUT_BOMB,		//ボム発射
		INPUT_SHOT,		//弾発射
		INPUT_MAX
	}INPUT;		//入力状態
	typedef enum
	{
		ATTACK_NONE = -1,
		ATTACK_SHOT,	//弾発射
		ATTACK_BOMB,	//ボム発射
		ATTACK_MAX
	}ATTACK;	//攻撃状態
	typedef enum
	{
		LEVEL_NONE = -1,
		LEVEL_1,
		LEVEL_2,
		LEVEL_3,
		LEVEL_MAX
	}LEVEL;		//レベル
	CPlayer(int nPriority = PRIORITY_PLAYER);
	~CPlayer();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CPlayer * Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddLife(void);
	void SubLife(int nValue);
	void LevelUp(void);
	void AddBomb(void);
	void SubBomb(void);
	void AddScore(int nValue);
	void SubScore(int nValue);
	STATE GetState(void) { return m_State; }
	int GetScore(void) { return m_nScore; }
	static void SetPlayerName(int nCount, char aName);
	static void SetbReplay(bool bReplay) { m_bReplay = bReplay; }
	static bool GetReplay(void) { return m_bReplay; }
	void Clear(void);
private:
	void Input(void);
	void Move(void);
	void Attack(void);
	void Death(void);
	void Invincible(void);
	void Respawn(void);
	D3DXVECTOR3 MovableRange(void);
	void Replay(void);
	void DeleteAllBullet(void);
	void TimeCount(void);
	void DataSave(void);
	void InputDataSave(void);
	void InputDataLoad(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	static  char m_aPlayerName[MAX_NAME];	//名前
	static bool m_bReplay;					//リプレイなのか
	D3DXVECTOR3 m_Move;						//移動量
	int m_nLife;							//体力
	int m_nBomb;							//爆弾の所持数
	int m_nUseBomb;							//爆弾の使用回数
	int m_nDeathCount;						//死亡数
	int m_nContinue;						//コンティニュー数
	int m_nScore;							//スコア
	int m_nLevel;							//レベル
	int m_nDeathTime;						//死亡時間
	int m_nInvincibleTime;					//無敵時間
	int m_nBulletInterval;					//発射間隔
	float m_fSpeed;							//速さ
	char m_aInputData[15000][INPUT_MAX];	//入力情報
	STATE m_State;							//状態
	INPUT m_Input;							//入力キー情報
	ATTACK m_Attack;						//攻撃情報
};
#endif