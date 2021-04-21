//=============================================================================
//
// タイトルロゴの処理 [title_logo.h]
// Author : 佐藤颯紀
//
//=============================================================================
#ifndef  _TITLELOGO_H_
#define  _TITLELOGO_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "Base/scene2d.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define TITLELOGO_TYPE			(2)			// ロゴの種類の最大数
#define TITLE_PLESS_POS_X		(900.0f)	// PLESSのX座標
#define TITLE_PLESS_POS_Y		(900.0f)	// PLESSのY座標
#define TITLE_PLESS_SIZE_X		(700.0f)	// PLESSのXサイズ
#define TITLE_PLESS_SIZE_Y		(90.0f)		// PLESSのYサイズ
#define TITLE_PLESS_COLLAR		(30)		// PLESSの表示間隔
#define TITLE_PLESS_ERASE		(60)		// PLESSの消してる間隔

//=============================================================================
//クラス宣言
//=============================================================================
class CTitlelogo :public CScene2d
{
public:
	typedef enum
	{
		LOGOTYPE_NONE = -1,
		LOGOTIPE_TITLE,			// タイトル
		LOGOTIPE_PRESS,			// プレス文字
		LOGOTYPE_MAX
	}LOGOTYPE;

	CTitlelogo();
	~CTitlelogo();

	static CTitlelogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE type);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, LOGOTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Flashing(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TITLELOGO_TYPE];

	D3DXVECTOR3	m_pos;		// ポリゴンの位置
	D3DXVECTOR3 m_move;		// ポリゴンの移動量
	D3DXVECTOR3 m_size;		// ポリゴンのサイズ
	D3DXCOLOR   m_col;		// カラー
	LOGOTYPE	m_type;		// ポリゴンのタイプ
	int m_nCounter;			// カウンター
	int m_nPattern;			// 使用しているかどうか
};

#endif // ! _TITLELOGO_H_
