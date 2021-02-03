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
class CScoreUI;
class CBombUI;
class CLifeUI;
class CPlayer;
class CEnemy;
class CBullet;

//*****************************************************************************
// 構造体定義
//*****************************************************************************

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
	void SetbReplay(bool bReplay);
	int GetFlameCount(void) {return m_nFlameCount;}
	bool GetbReplay(void) { return m_bReplay; }
	static CScoreUI * GetScoreUI(void) { return m_pScoreUI; }
	static CBombUI * GetBombUI(void) { return m_pBombUI; }
	static CLifeUI * GetLifeUI(void) { return m_pLifeUI; }
	static CPlayer * GetPlayer(void) { return m_pPlayer; }
	static CEnemy * GetEnemy(void) { return m_pEnemy; }
private:
	void CreateAll(void);
	static CScoreUI * m_pScoreUI;	//スコアのUIへのポインタ
	static CBombUI * m_pBombUI;		//爆弾のUIへのポインタ
	static CLifeUI * m_pLifeUI;		//体力のUIへのポインタ
	static CPlayer * m_pPlayer;		//プレイヤーへのポインタ
	static CEnemy * m_pEnemy;		//敵へのポインタ
	int m_nFlameCount;				//フレーム数
	bool m_bReplay;					//リプレイの真偽
};
#endif
