//=============================================================================
//
// 爆弾のUI処理 [ownui.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _BOMBUI_H_
#define _BOMBUI_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "bombtexture.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BOMBUI_SIZE_WIDTH 30		//自機のUIの幅のサイズ
#define BOMBUI_SIZE_HEIGHT 30		//自機のUIの高さのサイズ

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBombUI :public CScene
{
public:
	CBombUI(int nPriority = 5);
	~CBombUI();
	static CBombUI * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetBombUI(int nBomb);
	void AddBombUI(int nValue);
	void SubBombUI(int nValue);
private:
	CBombTexture *m_apBombUI[PLAYER_MAX_BOMB];	//ボムのテクスチャへのポインタ
	int m_nBombUI;	//爆弾のUI
};
#endif