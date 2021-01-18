//=============================================================================
//
// 爆弾のUI [ui_bomb.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _UI_BOMB_H_
#define _UI_BOMB_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"
#include "player.h"
#include "ui_bomb_texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUIBombTexture;

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBombUI :public CScene
{
public:
	CBombUI(int nPriority = DEFAULT_PRIORITY);
	~CBombUI();
	static CBombUI * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetBomb(int nScore);
private:
	CUIBombTexture * m_apBombTexture[PLAYER_MAX_BOMB];	//UI用数字テクスチャへのポインタ
};
#endif