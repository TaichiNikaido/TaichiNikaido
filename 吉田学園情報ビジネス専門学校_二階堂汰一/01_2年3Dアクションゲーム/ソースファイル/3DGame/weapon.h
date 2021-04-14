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
class CWeapon : public CScene
{
public:
	CWeapon();
	~CWeapon();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetCollisionSize(D3DXVECTOR3 CollisionSize) { m_CollisionSize = CollisionSize; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetModelData(CModel::MODEL_DATA ModelData) { m_aModelData = ModelData; }
	void SetParentModel(CModel * pParentModel) { m_pParentModel = pParentModel; }
private:
	void Collision(void);
	D3DXVECTOR3 m_Position;				//位置
	D3DXVECTOR3 m_Size;					//サイズ
	D3DXVECTOR3 m_CollisionSize;		//衝突判定用サイズ
	D3DXVECTOR3 m_Rotation;				//回転
	CModel * m_pModel;					//モデルのポインタ
	CModel * m_pParentModel;			//親モデルのポインタ
	CModel::MODEL_DATA m_aModelData;		//モデルデータ
};
#endif