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
#include "Base/scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CLight;
class CCamera;
class CPlayer;
class CDragon;

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
	static CPlayer * m_pPlayer;		//�v���C���[�̃|�C���^
	static CDragon * m_pDragon;		//�h���S���̃|�C���^
	CCamera * m_pCamera;			//�J�����̃|�C���^
	CLight * m_pLight;				//���C�g�̃|�C���^
	bool m_bCreatePause;			//�|�[�Y�𐶐����Ă邩
};
#endif
