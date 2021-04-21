//=============================================================================
//
// コンティニューボタンマネージャー [continue_button_manager.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _CONTINUE_BUTTON_MANAGER_H_
#define _CONTINUE_BUTTON_MANAGER_H_

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

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CContinueButtonManager : public CScene
{
public:
	CContinueButtonManager();
	~CContinueButtonManager();
	static CContinueButtonManager * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		BUTTON_NONE = -1,
		BUTTON_CONTINUE,
		BUTTON_NOT_CONTINUE,
		BUTTON_MAX
	}BUTTON;
	void Input(void);
	void InitCreateAll(void);
	CButton * m_apButton[BUTTON_MAX];	//ボタンのポインタ
	int m_nButton;						//ボタン
	int m_nInputCount;					//入局間隔
};
#endif