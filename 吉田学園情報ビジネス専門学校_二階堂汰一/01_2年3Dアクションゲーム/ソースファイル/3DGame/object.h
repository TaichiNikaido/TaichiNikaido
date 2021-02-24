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
#include "scene.h"
#include "model.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CObject : public CScene
{
public:
	CObject();
	~CObject();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetCollisionSize(D3DXVECTOR3 CollisionSize) { m_CollisionSize = CollisionSize; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetModelData(CModel::MODEL_DATA ModelData) { m_ModelData = ModelData; }
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	D3DXVECTOR3 GetCollisionSize(void) { return m_CollisionSize; }
	int GetLife(void) { return m_nLife; }
private:
	void SubLife(void);
	void Collision(void);
	D3DXVECTOR3 m_Position;				//位置
	D3DXVECTOR3 m_Size;					//サイズ
	D3DXVECTOR3 m_CollisionSize;		//衝突判定用サイズ
	D3DXVECTOR3 m_Rotation;				//回転
	int m_nLife;						//体力
	CModel * m_pModel;					//モデルのポインタ
	CModel::MODEL_DATA m_ModelData;		//モデルデータ
};
#endif