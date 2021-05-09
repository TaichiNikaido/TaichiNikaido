//=============================================================================
//
// キャラクター [character.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/scene3d.h"
#include "Base/model.h"
#include "Base/motion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CShadow;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCharacter : public CScene3d
{
public:
	CCharacter(int nPriority = PRIORITY_CHARACTER);
	~CCharacter();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetModelScriptPass(const char * pModelScriptPass) { m_apModelScriptPass[0] = pModelScriptPass; }
	void SetModelData(CModel::MODEL_DATA ModelData[MAX_PARTS]);
	void SetCollisionSize(D3DXVECTOR3 CollisionSize) { m_CollisionSize = CollisionSize; }
	CModel * GetModel(int nParts) { return m_apModel[nParts]; }
	CMotion * GetpMotion(void) { return m_pMotion; }
	D3DXVECTOR3 GetCollisionSize(void) { return m_CollisionSize; }
	D3DXVECTOR3 GetPositionOld(void) { return m_PositionOld; }
private:
	void ShadowCreate(void);
	const char * m_apModelScriptPass[MAX_PASS_LETTER];		//モデルのスクリプトパス
	CModel::MODEL_DATA m_aModelData[MAX_PARTS];				//モデルデータ
	D3DXVECTOR3 m_PositionOld;								//過去の位置
	D3DXVECTOR3 m_CollisionSize;							//衝突判定用のサイズ
	CModel * m_apModel[MAX_PARTS];							//モデルのポインタ
	CMotion * m_pMotion;									//モーションのポインタ
	//CShadow * m_pShadow;									//影のポインタ
};
#endif
