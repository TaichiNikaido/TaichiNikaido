//=============================================================================
//
// �Q�[�����[�h [mode_game.h]
// Author : ��K������
//
//=============================================================================
#ifndef _MODE_GAME_H_
#define _MODE_GAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScoreUI;
class CBombUI;
class CLifeUI;
class CPlayer;
class CEnemy;
class CEnemyDragon;
class CWarning;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
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
	static void SetDragon(CEnemyDragon * pDragon) { m_pDragon = pDragon; }
	static void SetWarning(CWarning * pWarning) { m_pWarning = pWarning; }
	static CScoreUI * GetScoreUI(void) { return m_pScoreUI; }
	static CBombUI * GetBombUI(void) { return m_pBombUI; }
	static CLifeUI * GetLifeUI(void) { return m_pLifeUI; }
	static CPlayer * GetPlayer(void) { return m_pPlayer; }
	static CEnemy * GetEnemy(void) { return m_pEnemy; }
	static CEnemyDragon * GetDragon(void) { return m_pDragon; }
	static CWarning * GetWarning(void) { return m_pWarning; }
private:
	void CreateAll(void);
	static CScoreUI * m_pScoreUI;		//�X�R�A��UI�ւ̃|�C���^
	static CBombUI * m_pBombUI;			//���e��UI�ւ̃|�C���^
	static CLifeUI * m_pLifeUI;			//�̗͂�UI�ւ̃|�C���^
	static CPlayer * m_pPlayer;			//�v���C���[�ւ̃|�C���^
	static CEnemy * m_pEnemy;			//�G�ւ̃|�C���^
	static CEnemyDragon * m_pDragon;	//�h���S���ւ̃|�C���^
	static CWarning * m_pWarning;		//�댯�n�тւ̃|�C���^
	int m_nFlameCount;					//�t���[����
	bool m_bReplay;						//���v���C�̐^�U
};
#endif
