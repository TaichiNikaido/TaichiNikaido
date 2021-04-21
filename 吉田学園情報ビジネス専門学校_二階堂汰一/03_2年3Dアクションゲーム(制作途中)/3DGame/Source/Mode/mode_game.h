//=============================================================================
//
// ゲームモード [mode_game.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MODE_GAME_H_
#define _MODE_GAME_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CLight;
class CCamera;
class CPlayer;
class CDragon;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGameMode : CScene
{
public:
	CGameMode();
	~CGameMode();
	static CGameMode * Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetbPouse(bool bPouse) { m_bPouse = bPouse; }
	CCamera * GetCamera(void) { return m_pCamera; }
	CPlayer * GetPlayer(void) { return m_pPlayer; }
	CDragon * GetDragon(void) { return m_pDragon; }
private:
	void Input(void);
	void InitCreate(void);
	void UpdateCreate(void);
	void BaseCreateAll(void);
	void MapObjectCreateAll(void);
	void CharacterCreateAll(void);
	void UICreateAll(void);
	CCamera * m_pCamera;		//カメラのポインタ
	CPlayer * m_pPlayer;		//プレイヤーのポインタ
	CDragon * m_pDragon;		//ドラゴンのポインタ
	CLight * m_pLight;			//ライトのポインタ
	bool m_bPouse;				//ポーズを使用してるか
};
#endif
