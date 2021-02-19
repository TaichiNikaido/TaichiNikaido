//=============================================================================
//
// モデル管理処理 [model.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene3d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PARTS (20)			//最大パーツ数
#define MAX_MATERIAL (30)		//最大マテリアル数

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CModel : public CScene3d
{
public:
	typedef struct
	{
		LPD3DXBUFFER pBuffMat;						//マテリアル情報へのポインタ
		DWORD nNumMat;								//マテリアル情報の数
		LPD3DXMESH pMesh;							//メッシュ情報へのポインタ
		LPDIRECT3DTEXTURE9 pTexture[MAX_MATERIAL];	//テクスチャへのポインタ
		D3DXMATRIX mtxWorld;						//ワールド変換行列
		CModel *pParent;							//親のモデルへのポインタ
		int nIndexModelParent;						//親モデルのインデックス
	}MODEL_DATA;
	CModel();
	~CModel();
	static char * LoadModelText(const char *cText);
	static CModel* Create(MODEL_DATA modeldata);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetParentModel(CModel * pParentModel);
	void SetModel(D3DXVECTOR3 Position, D3DXVECTOR3 Rotation, D3DXVECTOR3 Size);
	void BindModel(MODEL_DATA ModelData) { m_ModelData = ModelData; }
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture,int nCount);
	MODEL_DATA GetModelData(void) { return m_ModelData; }
private:
	MODEL_DATA m_ModelData;			//モデルデータ
	D3DXVECTOR3 m_WorldPosition;	//ワールド座標
};
#endif
