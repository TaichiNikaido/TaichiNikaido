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
class CSound;
class CKeyboard;
class CJoystick;
class CTitleMode;
class CResultMode;
class CRankingMode;
class CGameMode;
class CFade;
class CText;

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
		MODE_TITLE,		//タイトルモード
		MODE_NAME,		//名前入力モード
		MODE_TUTORIAL,	//チュートリアルモード
		MODE_GAME,		//ゲームモード
		MODE_RESULT,	//リザルトモード
		MODE_RANKING,	//ランキングモード
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
	static CGameMode * GetGameMode(void) { return m_pGameMode; }
	static CResultMode * GetResultMode(void) { return m_pResultMode; }
	static CRankingMode * GetRankingMode(void) { return m_pRankingMode; }
	static CFade * GetFade(void) { return m_pFade; }
	static CText * GetText(void) { return m_pText; }
private:
	void LoadAll(void);
	void UnloadAll(void);
	void DeleteAll(void);
	static CRenderer * m_pRenderer;				//レンダラーのポインタ
	static CSound * m_pSound;					//サウンドのポインタ
	static CKeyboard * m_pKeyboard;				//キーボードのポインタ
	static CJoystick * m_pJoystick;				//ジョイスティックのポインタ
	static CGameMode * m_pGameMode;				//ゲームモードのポインタ
	static CResultMode * m_pResultMode;			//リザルトモードのポインタ
	static CRankingMode * m_pRankingMode;		//ランキングモードのポインタ
	static CFade * m_pFade;						//フェードのポインタ
	static CText * m_pText;						//テクストのポインタ
	static MODE m_Mode;							//モードのポインタ
	static bool m_bUseFade;						//フェードの使用状態
};
#endif