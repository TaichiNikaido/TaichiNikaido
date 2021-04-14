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
#define MAX_FLAME (15000)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScoreUI;
class CBombUI;
class CLifeUI;
class CPlayer;
class CEnemy;
class CEnemyDragon;
class CWarning;
class CBulletFireball;

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
	int GetFlameCount(void) {return m_nFlameCount;}
	static void SetDragon(CEnemyDragon * pDragon) { m_pDragon = pDragon; }
	static void SetWarning(CWarning * pWarning) { m_pWarning = pWarning; }
	static void SetFireBall(CBulletFireball * pBulletFireball) { m_pBulletFireBall = pBulletFireball; }
	static CScoreUI * GetScoreUI(void) { return m_pScoreUI; }
	static CBombUI * GetBombUI(void) { return m_pBombUI; }
	static CLifeUI * GetLifeUI(void) { return m_pLifeUI; }
	static CPlayer * GetPlayer(void) { return m_pPlayer; }
	static CEnemyDragon * GetDragon(void) { return m_pDragon; }
	static CWarning * GetWarning(void) { return m_pWarning; }
	static CBulletFireball * GetBulletFireBall(void) { return m_pBulletFireBall; }
private:
	void InitCreateAll(void);
	void UpdateCreateAll(void);
	static CScoreUI * m_pScoreUI;					//スコアのUIへのポインタ
	static CBombUI * m_pBombUI;						//爆弾のUIへのポインタ
	static CLifeUI * m_pLifeUI;						//体力のUIへのポインタ
	static CPlayer * m_pPlayer;						//プレイヤーへのポインタ
	static CEnemyDragon * m_pDragon;				//ドラゴンへのポインタ
	static CWarning * m_pWarning;					//危険地帯へのポインタ
	static CBulletFireball * m_pBulletFireBall;		//火球のポインタ
	int m_nFlameCount;								//フレーム数
};
#endif
