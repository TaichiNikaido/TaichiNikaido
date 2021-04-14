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
#include "model.h"
#include "motion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer : public CCharacter
{
public:
	typedef enum
	{
		MOTION_IDLE = 0,
		MOTION_WALK,	//歩行モーション
		MOTION_DASH,	//ダッシュモーション
	}MOTION;	//モーション
	typedef enum
	{
		STATE_NONE = -1,
		STATE_LIVE,		//生きてる
		STATE_DEATH,	//死んでる
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
	void SubLife(void);
	void SetMove(D3DXVECTOR3 Move) { m_Move = Move; }
	D3DXVECTOR3 GetPositionOld(void) { return m_PositionOld; }
	D3DXVECTOR3 GetCollisionSize(void) { return m_CollisionSize; }
	D3DXVECTOR3 GetMove(void) { return m_Move; }
	int GetLife(void) { return m_nLife; }
	float GetCameraDistance(void) { return m_fCameraDistance; }
private:
	void Input(void);
	void Move(void);
	void Attack(void);
	void Death(void);
	void Collision(void);
	void DataLoad(void);
	void UICreate(void);
	static CModel::MODEL_DATA m_aPlayerModelData[MAX_PARTS];	//モデル情報
	D3DXVECTOR3 m_PositionOld;									//前の位置
	D3DXVECTOR3 m_CollisionSize;								//当たり判定用サイズ
	D3DXVECTOR3 m_DirectionDest;								//目的の向き
	D3DXVECTOR3 m_Move;											//移動量
	int m_nLife;												//体力
	int m_nAttack;												//攻撃力
	int m_nAttackCombo;											//攻撃コンボ
	int m_nCoolTime;											//クールタイム
	int m_nCoolTimeCount;										//クールタイムカウント
	float m_fSpeed;												//速さ
	float m_fWalkSpeed;											//歩行速度
	float m_fDashSpeed;											//ダッシュ速度
	float m_fDirectionValue;									//向きの値
	float m_fCameraDistance;									//カメラとの距離
	bool m_bDash;												//ダッシュしてるか
	bool m_bWeapon;												//武器を使用しているか
	bool m_bAttack;												//攻撃をしているか
	STATE m_State;												//状態
	INPUT m_Input;												//入力情報
};
#endif
