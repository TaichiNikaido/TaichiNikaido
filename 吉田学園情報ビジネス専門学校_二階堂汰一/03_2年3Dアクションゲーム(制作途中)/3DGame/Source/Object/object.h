//=============================================================================
//
// オブジェクト [object.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

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
class CModel;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CObject :public CScene3d
{
public:
	CObject();
	~CObject();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetCollisionSize(D3DXVECTOR3 CollisionSize) { m_CollisionSize = CollisionSize; }
	void SetModelData(CModel::MODEL_DATA ModelData) { m_ModelData = ModelData; }
	bool GetbCollision(void) { return m_bCollision; }
private:
	void Collision(void);
	D3DXVECTOR3 m_CollisionSize;		//衝突判定用のサイズ
	bool m_bCollision;					//衝突したか
	CModel::MODEL_DATA m_ModelData;		//モデルデータ
	CModel * m_pModel;					//モデルのポインタ
};
#endif