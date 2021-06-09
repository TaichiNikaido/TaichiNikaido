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
#include "character.h"
#include "Base/model.h"
#include "Base/motion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRoundShadow;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer : public CCharacter
{
public:
	typedef enum
	{
		MOTION_IDLE = 0,
		MOTION_IDLE_WEAPON,
		MOTION_WALK,
		MOTION_WALK_WEAPON,
		MOTION_GUARD,
		MOTION_MAX
	}MOTION;	//モーション
	typedef enum
	{
		STATE_NONE = -1,
		STATE_WALK,		//歩行
		STATE_DASH,		//ダッシュ
		STATE_DEATH,	//死んでる
		STATE_ATTACK,	//攻撃
		STATE_MAX
	}STATE;		//状態
	typedef enum
	{
		INPUT_NONE = -1,
		INPUT_UP,		//上方向
		INPUT_DOWN,		//下方向
		INPUT_LEFT,		//左方向
		INPUT_RIGHT,	//右方向
		INPUT_CAMERA,	//カメラの視点
		INPUT_MAX
	}INPUT;		//入力状態
	typedef enum
	{
		ATTACK_NONE = 0,
		ATTACK_1,
		ATTACK_2,
		ATTACK_3,
		ATTACK_MAX
	}ATTACK;	//攻撃情報
	CPlayer();
	~CPlayer();
	static HRESULT ModelLoad(void);
	static void ModelUnload(void);
	static CPlayer * Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);
	void AddLife(int nValue);
	void SubLife(int nValue);
	void SetMove(D3DXVECTOR3 Move) { m_Move = Move; }
	void SetbBurning(bool bBurning) { m_bBurning = bBurning; }
	D3DXVECTOR3 GetMove(void) { return m_Move; }
	int GetLife(void) { return m_nLife; }
	float GetCameraDistance(void) { return m_fCameraDistance; }
	STATE GetState(void) { return m_State; }
private:
	void Input(void);
	void Move(void);
	void Attack(void);
	void Guard(void);
	void Burning(void);
	void Death(void);
	void Collision(void);
	void Motion(void);
	void DataLoad(void);
	static CModel::MODEL_DATA m_aPlayerModelData[MAX_PARTS];	//モデル情報
	D3DXVECTOR3 m_DirectionDest;								//目的の向き
	D3DXVECTOR3 m_Move;											//移動量
	int m_nMaxLife;												//最大体力
	int m_nLife;												//体力
	int m_nAttack;												//攻撃力
	int m_nAttackCombo;											//攻撃コンボ
	int m_nCoolTime;											//クールタイム
	int m_nCoolTimeCount;										//クールタイムカウント
	int m_nBurningTime;											//燃焼タイム
	int m_nBurningTiming;										//燃焼タイミング
	int m_nBurningTimeCount;									//燃焼カウント
	float m_fSpeed;												//速さ
	float m_fWalkSpeed;											//歩行速度
	float m_fDashSpeed;											//ダッシュ速度
	float m_fDirectionValue;									//向きの値
	float m_fCameraDistance;									//カメラとの距離
	bool m_bWeapon;												//武器を使用しているか
	bool m_bBurning;												//燃えているか
	STATE m_State;												//状態
	INPUT m_Input;												//入力情報
	CRoundShadow * m_pRoundShadow;								//丸影のポインタ
};
#endif
