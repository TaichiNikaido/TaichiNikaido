//=============================================================================
//
// 敵 [enemy.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

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
class CEnemy : CScene
{
public:
	CEnemy();
	~CEnemy();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetCollisionSize(D3DXVECTOR3 CollisionSize) { m_CollisionSize = CollisionSize; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetMove(D3DXVECTOR3 Move) { m_Move = Move; }
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetAttack(int nAttack) { m_nAttack = nAttack; }
	void SetModelData(CModel::MODEL_DATA ModelData[MAX_PARTS]);
	void SetMotionPass(const char * MotionPass) { m_apMotionPass[0] = MotionPass; }
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	D3DXVECTOR3 GetCollisionSize(void) { return m_CollisionSize; }
	int GetLife(void) { return m_nLife; }
	int GetAttack(void) { return m_nAttack; }
private:
	void Hit(void);
	void SubLife(void);
	void Motion(void);
	D3DXVECTOR3 m_Position;									//位置
	D3DXVECTOR3 m_Size;										//サイズ
	D3DXVECTOR3 m_CollisionSize;							//衝突判定用サイズ
	D3DXVECTOR3 m_Rotation;									//回転
	D3DXVECTOR3 m_Move;										//移動量
	int m_nLife;											//体力
	int m_nAttack;											//攻撃力
	const char * m_apMotionPass[MAX_PASS_LETTER];			//モーションデータのパス
	CModel::MODEL_DATA m_aModelData[MAX_PARTS];			//モデルデータ
	CModel * m_apModel[MAX_PARTS];							//モデルのポインタ
	CMotion * m_pMotion;									//モーションのポインタ
};
#endif