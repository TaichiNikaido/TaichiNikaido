//=============================================================================
//
// カメラ [camera.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }
private:
	void Input(void);
	void DataLoad();
	D3DXVECTOR3 m_PositionV;		//視点の位置
	D3DXVECTOR3 m_PositionR;		//注視点の位置
	D3DXVECTOR3 m_VectorU;			//上方向ベクトル
	D3DXVECTOR3 m_Rotation;			//回転
	D3DXMATRIX m_MtxProjection;		//プロジェクションマトリックス
	D3DXMATRIX m_MtxView;			//ビューマトリックス
	float m_fDistance;				//視点と注視点の距離
};
#endif