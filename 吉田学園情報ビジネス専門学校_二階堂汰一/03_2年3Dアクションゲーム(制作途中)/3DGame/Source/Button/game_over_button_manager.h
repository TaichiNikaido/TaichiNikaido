//=============================================================================
//
// �Q�[���I�[�o�[�{�^���}�l�[�W���[ [game_over_button_manager.h]
// Author : ��K������
//
//=============================================================================
#ifndef _GAME_OVER_BUTTON_MANAGER_H_
#define _GAME_OVER_BUTTON_MANAGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/scene.h"
#include "button.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CButton;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGameOverButtonManager : public CScene
{
public:
	CGameOverButtonManager(int nPriority = PRIORITY_BUTTON);
	~CGameOverButtonManager();
	static CGameOverButtonManager * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		BUTTON_NONE = -1,
		BUTTON_RETRY,
		BUTTON_BACK_TO_TITLE,
		BUTTON_MAX
	}BUTTON;
	void Input(void);
	void Select(void);
	void CancelSound(void);
	void InitCreateAll(void);
	CButton * m_apButton[BUTTON_MAX];	//�{�^���̃|�C���^
	int m_nButton;						//�{�^��
	int m_nInputCount;					//���͊Ԋu
};
#endif