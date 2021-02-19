//=============================================================================
//
// 屍 [object_corpse.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _OBJECT_CORPSE_H_
#define _OBJECT_CORPSE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"
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
class CCorpse : public CObject
{
public:
	CCorpse();
	~CCorpse();
	static HRESULT ModelLoad(void);
	static void ModelUnload(void);
	static CCorpse * Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void DataLoad(void);
	static CModel::MODEL_DATA m_ModelData;		//モデルデータ
	static D3DXMATERIAL * m_pMaterial;			//マテリアルのポインタ
};
#endif