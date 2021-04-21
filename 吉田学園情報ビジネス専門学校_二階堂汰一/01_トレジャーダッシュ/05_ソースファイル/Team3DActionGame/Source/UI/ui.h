//=============================================================================
//
// ui処理 [ui.h]
// Author : 佐藤颯紀
//
//=============================================================================

#ifndef _UI_H_
#define _UI_H_

#include "Base/scene2d.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define UI_TYPE			(3)		// UIの種類

// ダイヤ
#define DAIYA_POS_X		(1805.0f)	// ダイヤのX座標
#define DAIYA_POS_Y		(250.0f)	// ダイヤのY座標
#define DAIYA_SIZE		(90.0f)		// ダイヤのサイズ

// お肉
#define MEAT_POS_X		(1805.0f)	// お肉のX座標
#define MEAT_POS_Y		(350.0f)	// お肉のY座標
#define MEAT_SIZE		(120.0f)		// お肉のサイズ
#define MEAT_FLASH		(1)			// お肉が点滅をはじめる個数

// WARNING
#define WARNING_POS_X	(640.0f)	// WARNINGのX座標
#define WARNING_POS_Y	(350.0f)	// WARNINGのY座標
#define WARNING_SIZE	(100.0f)	// WARNINGのサイズ
#define WARNING_COL_IN	(5)			// 色の出てる時間
#define WARNING_COL_OUT	(10)		// 色の消える時間
#define WARNING_ERASE	(120)		// 出現時間

//=============================================================================
//クラス宣言
//=============================================================================
class CUi :public CScene2d
{
public:
	typedef enum
	{
		UITYPE_NONE = -1,
		UITYPE_DAIYA,		// ダイヤモンドUI
		UITYPE_MEAT,		// 肉のUI
		UITYPE_WARNING,		// 警報のUI
		UITYPE_MAX
	}UITYPE;

	CUi(int nPriority = OBJTYPE_DEFAULT);
	~CUi();

	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, UITYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Flashing(void);
	void MeatFlash(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[UITYPE_MAX];
	D3DXVECTOR3	m_pos;		// ポリゴンの位置
	D3DXVECTOR3 m_move;		// ポリゴンの移動量
	D3DXVECTOR3 m_size;		// ポリゴンのサイズ
	D3DXCOLOR   m_col;		// カラー
	UITYPE		m_type;		// ポリゴンのタイプ
	int m_nColCounter;		// カラーのカウンター
	int m_nEraseCounter;	// 消滅のカウンター
	int m_nMeatColCounter;	// 肉のカラーカウンター
	int m_nMeat;			// 肉の数
};

#endif // !_UI_H_