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
class CEnemy : public CCharacter
{
public:
	CEnemy();
	~CEnemy();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetCollisionSize(D3DXVECTOR3 CollisionSize) { m_CollisionSize = CollisionSize; }
	void SetMove(D3DXVECTOR3 Move) { m_Move = Move; }
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetAttack(int nAttack) { m_nAttack = nAttack; }
	void SetScriptPass(const char * ScriptPass) { m_apScriptPass[0] = ScriptPass; }
	D3DXVECTOR3 GetCollisionSize(void) { return m_CollisionSize; }
	int GetLife(void) { return m_nLife; }
	int GetAttack(void) { return m_nAttack; }
private:
	void Hit(void);
	void SubLife(void);
	void DataLoad(void);
	D3DXVECTOR3 m_CollisionSize;							//衝突判定用サイズ
	D3DXVECTOR3 m_Move;										//移動量
	int m_nLife;											//体力
	int m_nAttack;											//攻撃力
	const char * m_apScriptPass[MAX_PASS_LETTER];			//スクリプトのパス
};
#endif