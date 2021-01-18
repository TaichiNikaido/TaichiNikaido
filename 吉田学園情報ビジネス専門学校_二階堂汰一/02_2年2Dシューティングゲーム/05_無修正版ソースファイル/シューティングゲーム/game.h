//=============================================================================
//
// �Q�[�� [game.h]
// Author : ��K������
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "wormhole.h"
#include "enemy.h"
#include "dragon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
//class CScene2d;
class CBg;
class CEnemy;
class Wormhole;
class CScore;
class COwnUI;
class CBombUI;
class CDragon;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame(int nPriority = 0);
	~CGame();
	static CGame * Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	HRESULT Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer * GetPlayer(void);
	CEnemy * GetEnemy(void);
	CWormhole * GetWormhole(void);
	CScene2d * GetScene2d(void);
	static CScore * GetScore(void) { return m_pScore; };
	static COwnUI * GetOwnUI(void) { return m_pOwnUI; };
	static CBombUI * GetBombUI(void) { return m_pBombUI; };
	static CDragon * GetDragon(void) {return m_pDragon;};
	static int GetbInputSaveCount(void){ return m_nInputSaveCount; };
	static int GetbInputLoadCount(void) { return m_nInputLoadCount; };
private:
	static CScore * m_pScore;
	static COwnUI * m_pOwnUI;
	static CBombUI * m_pBombUI;
	static CPlayer * m_pPlayer;
	static CDragon * m_pDragon;
	static int m_nInputSaveCount;
	static int m_nInputLoadCount;
	CScene2d * m_pScene2d;
	CEnemy * m_pEnemy;
	CWormhole * m_pWormhole;
	D3DXVECTOR3 m_Location[MAX_LOCATION];
	int m_nCount;
};
#endif