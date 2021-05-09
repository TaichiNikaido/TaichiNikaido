//=============================================================================
//
// �|�[�Y�{�^���}�l�[�W���[ [pause_button_manager.h]
// Author : ��K������
//
//=============================================================================
#ifndef _PAUSE_BUTTON_MANAGER_H_
#define _PAUSE_BUTTON_MANAGER_H_

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
class CPauseBG;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPauseButtonManager : public CScene
{
public:
	CPauseButtonManager(int nPriority = PRIORITY_BUTTON);
	~CPauseButtonManager();
	static CPauseButtonManager * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		BUTTON_NONE = -1,
		BUTTON_QUIT_GAME,
		BUTTON_CONTROLLER_GUIDE,
		BUTTON_BACK_TO_TITLE,
		BUTTON_EXIT,
		BUTTON_MAX
	}BUTTON;
	void Input(void);
	void Select(void);
	void InitCreateAll(void);
	CButton * m_apButton[BUTTON_MAX];	//�{�^���̃|�C���^
	int m_nButton;						//�{�^��
	int m_nInputCount;					//���͊Ԋu
	CPauseBG * m_pPouseBG;				//�|�[�Y�w�i�̃|�C���^
};
#endif