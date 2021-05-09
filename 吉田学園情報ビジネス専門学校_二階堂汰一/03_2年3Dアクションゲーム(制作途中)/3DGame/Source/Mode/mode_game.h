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
	void SetbCreatePause(bool bPouse) { m_bCreatePause = bPouse; }
	bool GetbCreatePause(void) { return m_bCreatePause; }
	static CPlayer * GetPlayer(void) { return m_pPlayer; }
	static CDragon * GetDragon(void) { return m_pDragon; }
	CCamera * GetCamera(void) { return m_pCamera; }
private:
	void Input(void);
	void InitCreate(void);
	void UpdateCreate(void);
	void BaseCreateAll(void);
	void MapObjectCreateAll(void);
	void CharacterCreateAll(void);
	static CPlayer * m_pPlayer;		//プレイヤーのポインタ
	static CDragon * m_pDragon;		//ドラゴンのポインタ
	CCamera * m_pCamera;			//カメラのポインタ
	CLight * m_pLight;				//ライトのポインタ
	bool m_bCreatePause;			//ポーズを生成してるか
};
#endif
