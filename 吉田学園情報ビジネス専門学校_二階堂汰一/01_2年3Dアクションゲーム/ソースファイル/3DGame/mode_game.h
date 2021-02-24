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
#include "scene.h"

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
class CStage;

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
	static CCamera * GetCamera(void) { return m_pCamera; }
	static CPlayer * GetPlayer(void) { return m_pPlayer; }
	static CDragon * GetDragon(void) { return m_pDragon; }
	static CStage * GetStage(void) { return m_pStage; }
private:
	void InitCreateAll(void);
	void UpdateCreateAll(void);
	static CCamera * m_pCamera;	//カメラのポインタ
	static CPlayer * m_pPlayer;	//プレイヤーのポインタ
	static CDragon * m_pDragon;	//ドラゴンのポインタ
	static CStage * m_pStage;	//ステージのポインタ
	CLight * m_pLight;			//ライトのポインタ
};
#endif
