//=============================================================================
//
// モーション [motion.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOTIONKEY_SET_MAX (60)	//モーションキーの最大数

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMotion
{
public:
	typedef struct
	{
		int nIndex;					//モデル番号
		int nParents;				//モデルの親番号
		D3DXVECTOR3 Position;		//位置
		D3DXVECTOR3 PositionOrigin; //初期位置
		D3DXVECTOR3 Rotation;		//回転
	}MODEL;	//モデル情報
	typedef struct
	{
		D3DXVECTOR3 Position[MAX_PARTS];	//位置
		D3DXVECTOR3 Rotation[MAX_PARTS];	//回転
		int nFrame;							//フレーム数
	}KEY_INFORMATION;	//キー情報
	typedef struct
	{
		bool bLoop;											//ループするか
		int nNumKey;										//モーションのキー数
		KEY_INFORMATION KeyInformation[MOTIONKEY_SET_MAX];	//モーションに含むキーセット情報
	}MOTION;	//モーション情報
	typedef enum
	{
		MOTION_PLAYER_IDLE = 0,		//アイドルモーション
		MOTION_PLAYER_WALK,			//歩きモーション
		MOTION_PLAYER_DASH,			//走りモーション
		MOTION_DRAGON_ATTACK1,		//ドラゴンの攻撃1
		MOTION_DRAGON_ATTACK2,		//ドラゴンの攻撃2
		MOTION_MAX					//モーションの最大
	}MOTION_STATE;	//モーション状態
	CMotion();
	~CMotion();
	static CMotion * Create(void);
	void Uninit(void);
	void Update(void);
	void LoadMotion(const char * cText);
	void LoadModelInformation(const char * cText);
	void SetMotion(MOTION_STATE MotionState) { m_MotionState = MotionState; }
	MOTION_STATE GetMotion(void) { return m_MotionState; }
	int GetIndex(int nCount) { return m_ModelParent[nCount].nIndex; }
	int GetParents(int nCount) { return m_ModelParent[nCount].nParents; }
	D3DXVECTOR3 GetPosition(int nCount) { return m_ModelParent[nCount].Position; }
	D3DXVECTOR3 GetRotation(int nCount) { return m_ModelParent[nCount].Rotation; }
private:
	D3DXVECTOR3 m_NumPositionDifference[MAX_PARTS];		//位置の差分
	D3DXVECTOR3 m_NumDirectionDifference[MAX_PARTS];	//向きの差分
	D3DXVECTOR3 m_NumRotationDifference[MAX_PARTS];		//回転の差分
	int m_nFrame;										//フレーム数
	int m_nAddChangeFreme;								//モーション変更時に加算するフレーム
	int m_nCurrentKey;									//現在のキー数
	bool m_bChange;										//変更したか
	MODEL m_ModelParent[MAX_PARTS];						//モデルのパーツごとの情報
	MOTION m_Motion[MOTION_MAX];						//モーションごとの情報
	MOTION_STATE m_MotionState;							//モーションの状態
	MOTION_STATE m_MotionOldState;						//1フレーム前のモーションの状態
};
#endif