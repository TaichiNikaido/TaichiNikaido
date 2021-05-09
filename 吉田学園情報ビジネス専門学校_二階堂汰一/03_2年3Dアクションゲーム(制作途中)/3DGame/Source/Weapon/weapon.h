//=============================================================================
//
// 武器 [weapon.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _WEAPON_H_
#define _WEAPON_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/scene3d.h"
#include "Base/model.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CWeapon : public CScene3d
{
public:
	CWeapon(int nPriority = PRIORITY_WEAPON);
	~CWeapon();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetCollisionSize(D3DXVECTOR3 CollisionSize) { m_CollisionSize = CollisionSize; }
	void SetModelData(CModel::MODEL_DATA ModelData) { m_aModelData = ModelData; }
	void SetParentModel(CModel * pParentModel) { m_pParentModel = pParentModel; }
private:
	void Collision(void);
	D3DXVECTOR3 m_CollisionSize;		//衝突判定用サイズ
	CModel * m_pModel;					//モデルのポインタ
	CModel * m_pParentModel;			//親モデルのポインタ
	CModel::MODEL_DATA m_aModelData;		//モデルデータ
};
#endif