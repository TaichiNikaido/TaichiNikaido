//=============================================================================
//
// マネージャー [manager.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;
class CInputKeyboard;
class CInputJoystick;
class CScene2d;
class CSound;
class CTitle;
class CGame;
class CResult;
class CRanking;
class CFade;
class CName;
class CText;
class CTutorial;
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_NONE = -1,
		MODE_TITLE,
		MODE_TUTORIAL,
		MODE_NAME,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_END
	}MODE;
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInsitance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetMode(MODE mode);
	static MODE GetMode(void);
	static CRenderer * GetRenderer(void);
	static CInputKeyboard * GetInputKeyboard(void);
	static CInputJoystick * GetInputJoystick(void);
	static CSound * GetSound(void);
	static CFade * GetFade(void);
	static CText * GetText(void) { return m_pText; };
	static bool GetbPause(void) { return m_bPause; };
	static void SetbPause(bool bPause) { m_bPause = bPause; };
	static void StartFade(MODE mode);
	static void StopFade(void);
	CScene2d * GetScene2d(void);
private:
	static CRenderer * m_pRenderer;
	static CInputKeyboard * m_pInputKeyboard;
	static CInputJoystick * m_pInputJoystick;
	static CSound * m_pSound;
	static CTitle * m_pTitle;
	static  CTutorial * m_pTutorial;
	static CName * m_pName;
	static CGame * m_pGame;
	static CResult * m_pResult;
	static CRanking * m_pRanking;
	static CFade * m_pFade;
	static CText * m_pText;
	static bool m_bUseFade;
	static bool m_bPause;
	static MODE m_mode;
	CScene2d * m_pScene2d;
};
#endif