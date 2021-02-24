//=============================================================================
//
// UIのゲージ [ui_gauge.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _UI_GAUGE_H_
#define _UI_GAUGE_H_

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
class CGauge
{
public:
	CGauge();
	~CGauge();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CGauge * Create(D3DXVECTOR3 Position,D3DXVECTOR3 Size,D3DXCOLOR Color);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
	void SetMaxValue(int nMaxValue) { m_nMaxValue = nMaxValue; }
	void SetValue(int nValue) { m_nValue = nValue; }
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファのポインタ
	D3DXVECTOR3 m_Position;						//位置
	D3DXVECTOR3 m_Size;							//サイズ
	D3DXCOLOR m_Color;							//色
	int m_nMaxValue;							//値の最大値
	int m_nValue;								//値
};
#endif