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
#include "Base/main.h"
#include "Base/character.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLLISION_SIZE_PLAYER D3DXVECTOR3(180.0f, 180.0f, 180.0f)

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// プレイヤークラス定義
//*****************************************************************************
class CPlayer :public CCharacter
{
public:
	// モデルの各パーツ
	typedef enum
	{
		PARTS_BODY = 0,
		PARTS_HEAD,
		PARTS_RARM,
		PARTS_RHAND,
		PARTS_LARM,
		PARTS_LHAND,
		PARTS_RLEG,
		PARTS_RSHOE,
		PARTS_LLEG,
		PARTS_LSHOE,
		PARTS_MAX,
	}PARTS;
	typedef enum
	{
		STATE_NONE = -1,
		STATE_LIVE,
		STATE_DEATH,
		STATE_MAX
	}STATE;
	typedef enum
	{
		INPUT_NONE = -1,
		INPUT_LEFT,
		INPUT_RIGHT,
		INPUT_SPACE,
		INPUT_MAX
	}INPUT;
	typedef enum
	{
		MOTION_NONE = -1,
		MOTION_WAIT,
		MOTION_DUSH,
		MOTION_JUMP,
		MOTION_LANDING,
		MOTION_DOWN,
		MOTION_GETUP,
		MOTION_STAN
	}MOTIONPLAYER;
	CPlayer();
	~CPlayer();
	static HRESULT Load(void);
	static void Unload(void);
	static CPlayer * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);
	void Death(void);
	void AddDiamond(int nValue) { m_nDiamond += nValue; }
	void SetbContinue(bool bContinue) { m_bContinue = bContinue; }
	void SetbSlow(bool bSlowRun) { m_bSlowRun = bSlowRun; }
	void SetbStop(bool bStop) { m_bStop = bStop; }
	void SetbContinuePositionSave(bool bContinuePositionSave) { m_bContinuePositionSave = bContinuePositionSave; }
	int GetMeat(void) { return m_nMeat; }
	int GetDiamond(void) { return m_nDiamond; }
	bool GetbHit(void) { return m_bHit; }
	bool GetContinue(void) { return m_bContinue; }
	STATE GetState(void) { return m_State; }
	bool GetIsJump(void) { return m_bJump; }
private:
	void Input(void);
	void Move(void);
	void Gravity(void);
	void Continue(void);
	void MovableRange(void);
	void DataLoad(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static LPD3DXMESH m_pMesh[PARTS_MAX];
	static LPD3DXBUFFER	m_pBuffMat[PARTS_MAX];
	static DWORD m_nNumMat[PARTS_MAX];
	D3DXVECTOR3 m_Size;										//サイズ
	D3DXVECTOR3 m_Move;										//移動量
	D3DXVECTOR3 m_ContinuePosition;							//コンティニューするポジション
	int m_nMeat;											//肉の所持数
	int m_nMaxMeat;											//肉の最大数
	int m_nDiamond;											//ダイヤモンドの所持数
	int m_nStunTime;										//スタン時間
	int m_nStunTimeCount;									//スタン時間のカウント
	int m_nLife;											//体力
	float m_fAutoRunSpeed;									//オートランの速度
	float m_fSlowSpeed;										//スロウの速度
	float m_fLeftRightSpeed;								//左右移動速度
	float m_fJumpPower;										//ジャンプ力
	float m_fGravity;										//重力
	bool m_bHit;											//ヒットしたか
	bool m_bJump;											//ジャンプしたかどうが
	bool m_bContinue;										//コンティニューするか
	bool m_bSlowRun;										//スロウにする
	bool m_bStop;											//停止するか
	bool m_bContinuePositionSave;							//コンティニューする位置を保存するか
	STATE m_State;											//状態
	INPUT m_Input;											//入力
};
#endif