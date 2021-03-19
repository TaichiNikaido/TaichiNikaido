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
class CVillage;

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
	static CVillage * GetVillage(void) { return m_pVillage; }
private:
	void InitCreateAll(void);
	void UpdateCreateAll(void);
	static CCamera * m_pCamera;		//カメラのポインタ
	static CPlayer * m_pPlayer;		//プレイヤーのポインタ
	static CDragon * m_pDragon;		//ドラゴンのポインタ
	static CVillage * m_pVillage;	//村のポインタ
	CLight * m_pLight;				//ライトのポインタ
};
#endif
