//=============================================================================
//
// �|�[�Y�{�^���}�l�[�W���[ [pose_button_manager.h]
// Author : ��K������
//
//=============================================================================
#ifndef _POSE_BUTTON_MANAGER_H_
#define _POSE_BUTTON_MANAGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/scene.h"
#include "button/button.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CButton;
class CBackgroundPause;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPoseButtonManager : public CScene
{
public:
	CPoseButtonManager(int nPriority = PRIORITY_BUTTON);
	~CPoseButtonManager();
	static CPoseButtonManager * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		BUTTON_NONE = -1,
		BUTTON_QUIT_GAME,
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
	CBackgroundPause * m_pPauseBG;		//�|�[�Y�w�i�̃|�C���^
};
#endif