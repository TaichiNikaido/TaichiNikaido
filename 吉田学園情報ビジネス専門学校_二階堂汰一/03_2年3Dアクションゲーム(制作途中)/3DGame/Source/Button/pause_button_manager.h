//=============================================================================
//
// ポーズボタンマネージャー [pause_button_manager.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _PAUSE_BUTTON_MANAGER_H_
#define _PAUSE_BUTTON_MANAGER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Base/scene.h"
#include "button.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CButton;
class CPauseBG;

//*****************************************************************************
// クラス定義
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
	CButton * m_apButton[BUTTON_MAX];	//ボタンのポインタ
	int m_nButton;						//ボタン
	int m_nInputCount;					//入力間隔
	CPauseBG * m_pPouseBG;				//ポーズ背景のポインタ
};
#endif