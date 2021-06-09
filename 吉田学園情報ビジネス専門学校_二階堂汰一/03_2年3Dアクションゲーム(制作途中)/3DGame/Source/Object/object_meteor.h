//=============================================================================
//
// メテオ [object_meteor.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _OBJECT_METEOR_H_
#define _OBJECT_METEOR_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRoundShadow;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMeteor :public CObject
{
public:
	CMeteor();
	~CMeteor();
	static HRESULT ModelLoad(void);
	static void ModelUnload(void);
	static CMeteor * Create(D3DXVECTOR3 Position);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static CModel::MODEL_DATA m_MeteorModelData;	//モデル情報
	static D3DXMATERIAL * m_pMaterial;				//マテリアルのポインタ
	D3DXVECTOR3 m_Move;								//移動量
	D3DXVECTOR3 m_MeteorShadowSize;					//メテオの影のサイズ
	D3DXCOLOR m_MeteorShadowColor;					//メテオの影の色
	float m_fMeteorMaxHeight;						//隕石の最大高さ
	float m_fMeteorHeight;							//隕石の現在の高さ
	CRoundShadow * m_pRoundShadow;					//丸影のポインタ
};
#endif