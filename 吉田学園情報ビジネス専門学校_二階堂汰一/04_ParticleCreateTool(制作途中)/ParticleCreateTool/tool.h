//=============================================================================
//
// ツール [tool.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _TOOL_H_
#define _TOOL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTool
{
public:
	CTool();
	~CTool();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }
	D3DXVECTOR3 GetSize(void) { return m_Size; }
	D3DXVECTOR3 GetMove(void) { return m_Move; }
	D3DXCOLOR GetColor(void) { return m_Color; }
	int GetLife(void) { return m_nLife; }
	float GetScale(void) { return m_fScale; }
	float GetAngle(void) { return m_fAngle; }
	bool GetbScale(void) { return m_bScale; }
	bool GetbLife(void) { return m_bLife; }
private:
	void TextSave(void);
	void TextLoad(void);
	D3DXVECTOR3 m_Position;				//位置
	D3DXVECTOR3 m_Rotation;				//向き
	D3DXVECTOR3 m_Size;					//サイズ
	D3DXVECTOR3 m_Move;					//移動量
	D3DXCOLOR m_Color;					//色
	int m_nLife;						//体力
	int m_nCreateInterval;				//生成間隔
	int m_nCreateTime;					//生成時間
	float m_fScale;						//拡縮
	float m_fAngle;						//角度
	char m_aSaveTextName[MAX_TEXT];		//セーブするテキストの名前
	char m_aLoadTextName[MAX_TEXT];		//ロードするテキストの名前
	bool m_bWindow;						//ウィンドウを使用しているか
	bool m_bScale;						//拡縮を使用するか
	bool m_bLife;						//体力を使用するか
};
#endif
