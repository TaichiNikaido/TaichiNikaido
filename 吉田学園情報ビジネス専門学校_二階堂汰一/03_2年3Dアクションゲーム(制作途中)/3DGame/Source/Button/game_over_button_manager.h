//=============================================================================
//
// ゲームオーバーボタンマネージャー [game_over_button_manager.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _GAME_OVER_BUTTON_MANAGER_H_
#define _GAME_OVER_BUTTON_MANAGER_H_

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
	CButton * m_apButton[BUTTON_MAX];	//ボタンのポインタ
	int m_nButton;						//ボタン
	int m_nInputCount;					//入力間隔
};
#endif