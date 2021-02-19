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
#include "scene.h"
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
class CPlayer : public CScene
{
public:
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
		ATTACK_NONE = -1,
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
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	float GetCameraDistance(void) { return m_fCameraDistance; }
	CModel * GetModel(int nParts) { return m_pModel[nParts]; }
private:
	void Input(void);
	void Move(void);
	void Attack(void);
	void Death(void);
	void Collision(void);
	void Motion(void);
	void DataLoad(void);
	static CModel::MODEL_DATA m_ModelData[MAX_PARTS];		//モデルデータ
	static D3DXMATERIAL * m_pMaterial;						//マテリアルのポインタ
	D3DXVECTOR3 m_Position;									//位置
	D3DXVECTOR3 m_Size;										//サイズ
	D3DXVECTOR3 m_CollisionSize;							//当たり判定用サイズ
	D3DXVECTOR3 m_Rotation;									//回転
	D3DXVECTOR3 m_Move;										//移動量
	int m_nLife;											//体力
	int m_nAttack[ATTACK_MAX];								//攻撃力
	int m_nCoolTime[ATTACK_MAX];							//クールタイム
	int m_nCoolTimeCount;									//クールタイムカウント
	float m_fSpeed;											//速さ
	float m_fWalkSpeed;										//歩行速度
	float m_fDashSpeed;										//ダッシュ速度
	float m_fCameraDistance;								//カメラとの距離
	bool m_bDash;											//ダッシュしてるか
	STATE m_State;											//状態
	INPUT m_Input;											//入力情報
	ATTACK m_Attack;										//攻撃情報
	CModel * m_pModel[MAX_PARTS];							//モデルのポインタ
	CMotion * m_pMotion;									//モーションのポインタ
};
#endif
