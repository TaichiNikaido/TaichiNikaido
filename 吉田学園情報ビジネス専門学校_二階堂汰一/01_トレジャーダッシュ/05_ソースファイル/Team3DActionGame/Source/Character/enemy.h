//=============================================================================
//
// 敵処理 [enemy.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "Base/main.h"
#include "Base/character.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//*****************************************************************************
// プレイヤークラス定義
//*****************************************************************************
class CEnemy :public CCharacter
{
public:
	CEnemy();
	~CEnemy();

	// モデルの各パーツ
	typedef enum
	{
		PARTS_WAIST = 0,
		PARTS_BODY,
		PARTS_HEAD,
		PARTS_RARM,
		PARTS_LARM,
		PARTS_RLEG,
		PARTS_RSHOE,
		PARTS_LLEG,
		PARTS_LSHOE,
		PARTS_MAINTAIL,
		PARTS_SUBTAIL,
		PARTS_ENDTAIL,
		PARTS_CHIN,
		PARTS_MAX,
	}PARTS;
	typedef enum
	{
		TEX_TYPE_NONE = -1,
		TEX_TYPE_1,
		TEX_TYPE_2,
		TEX_TYPE_3,
		TEX_TYPE_4,
		TEX_TYPE_5,
		TEX_TYPE_6,
		TEX_TYPE_MAX
	}TEX_TYPE;
	typedef enum
	{
		MOTION_NONE = -1,
		MOTION_DUSH,
		MOTION_MEAL,
		MOTION_FALL,
		MOTION_ATTACK
	}MOTIONENEMY;
	typedef enum
	{
		ATTACK_TYPE_NONE = -1,
		ATTACK_TYPE_1,
		ATTACK_TYPE_2,
		ATTACK_TYPE_3,
		ATTACK_TYPE_MAX
	}ATTACK_TYPE;

	static HRESULT Load(void);
	static HRESULT LoadTexture(void);
	static void Unload(void);
	static CEnemy * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetbEat(bool bEat) { m_bEat = bEat; }
	void SetbStop(bool bStop) { m_bStop = bStop; }
	void SetbContinue(bool bContinue) { m_bContinue = bContinue; }
	void SetbContinuePositionSave(bool bContinuePositionSave) { m_bContinuePositionSave = bContinuePositionSave; }
private:
	void AutoRun(void);
	void Attack(void);
	void Warning_Create(void);
	void Step(void);
	void Death(void);
	void Continue(void);
	void DataLoad(void);
	static LPDIRECT3DTEXTURE9 m_apTexture[PARTS_MAX];		// テクスチャへのポインタ
	static LPD3DXMESH m_pMesh[PARTS_MAX];
	static LPD3DXBUFFER m_pBuffMat[PARTS_MAX];
	static DWORD m_nNumMat[PARTS_MAX];
	D3DXVECTOR3 m_Size;										//サイズ
	D3DXVECTOR3 m_Move;										//移動量
	D3DXVECTOR3 m_ContinuePosition;							//コンティニューするポジション
	int m_nMeatEatTime;										//肉を食べる時間
	int m_nMeatEatTimeCount;								//肉を食べる時間のカウント
	int m_nAttackCoolTime;									//攻撃のクールタイム
	int m_nAttackCoolTimeCount;								//攻撃のクールタイムカウント
	ATTACK_TYPE Attack_Type;								//攻撃の種類
	float m_fAutoRunSpeed;									//オートランの速度
	bool m_bEat;											//食事をしてるかどうか
	bool m_bAttack;											//攻撃をしたか
	bool m_bStop;											//停止するか
	bool m_bContinue;										//コンティニューするか
	bool m_bContinuePositionSave;							//コンティニューする位置を保存するか
};
#endif