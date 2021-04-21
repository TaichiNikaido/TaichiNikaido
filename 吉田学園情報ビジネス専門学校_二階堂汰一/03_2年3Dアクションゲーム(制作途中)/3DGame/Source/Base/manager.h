//=============================================================================
//
// �}�l�[�W���[ [manager.h]
// Author : ��K������
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;
class CSound;
class CKeyboard;
class CJoystick;
class CMouse;
class CTutorialMode;
class CGameMode;
class CResultMode;
class CRankingMode;
class CFade;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_NONE = -1,
		MODE_TITLE,
		MODE_NAME,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_MAX
	}MODE;
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void StartFade(MODE mode);
	static void StopFade(void);
	static void SetMode(MODE Mode);
	static MODE GetMode(void) { return m_Mode; }
	static CRenderer * GetRenderer(void) { return m_pRenderer; }
	static CSound * GetSound(void) { return m_pSound; }
	static CKeyboard * GetKeyboard(void) { return m_pKeyboard; }
	static CJoystick * GetJoystick(void) { return m_pJoystick; }
	static CMouse * GetMouse(void) { return m_pMouse; }
	static CTutorialMode * GetTutorialMode(void) { return m_pTutorialMode; }
	static CGameMode * GetGameMode(void) { return m_pGameMode; }
	static CResultMode * GetResultMode(void) { return m_pResultMode; }
	static CRankingMode * GetRankingMode(void) { return m_pRankingMode; }
	static CFade * GetFade(void) { return m_pFade; }
private:
	void LoadAll(void);
	void UnloadAll(void);
	void DeleteAll(void);
	static CRenderer * m_pRenderer;				//�����_���[�̃|�C���^
	static CSound * m_pSound;					//�T�E���h�̃|�C���^
	static CKeyboard * m_pKeyboard;				//�L�[�{�[�h�̃|�C���^
	static CJoystick * m_pJoystick;				//�W���C�X�e�B�b�N�̃|�C���^
	static CMouse * m_pMouse;					//�}�E�X�̃|�C���^
	static CTutorialMode * m_pTutorialMode;		//�`���[�g���A�����[�h�̃|�C���^
	static CGameMode * m_pGameMode;				//�Q�[�����[�h�̃|�C���^
	static CResultMode * m_pResultMode;			//���U���g���[�h�̃|�C���^
	static CRankingMode * m_pRankingMode;		//�����L���O���[�h�̃|�C���^
	static CFade * m_pFade;						//�t�F�[�h�̃|�C���^
	static MODE m_Mode;							//���[�h
	static bool m_bUseFade;						//�t�F�[�h�̎g�p���
};
#endif