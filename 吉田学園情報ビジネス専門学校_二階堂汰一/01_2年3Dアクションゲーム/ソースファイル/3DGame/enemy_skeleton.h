//=============================================================================
//
// スケルトン [enemy_skeleton.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _ENEMY_SKELETON_H_
#define _ENEMY_SKELETON_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSkeleton : public CEnemy
{
public:
	CSkeleton();
	~CSkeleton();
	static HRESULT ModelLoad(void);
	static void ModelUnload(void);
	static CSkeleton * Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void DataLoad(void);
	static CModel::MODEL_DATA m_aModelData[MAX_PARTS];		//モデルデータ
	static D3DXMATERIAL * m_pMaterial;						//マテリアルのポインタ

};
#endif
