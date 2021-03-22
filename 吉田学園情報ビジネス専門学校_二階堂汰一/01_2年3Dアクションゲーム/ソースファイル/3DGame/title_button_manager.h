//=============================================================================
//
// タイトルボタンマネージャー [title_button_manager.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _START_BUTTON_MANAGER_H_
#define _START_BUTTON_MANAGER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"
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
class CTitleButtonManager : public CScene
{
public:
	CTitleButtonManager();
	~CTitleButtonManager();
	static CTitleButtonManager * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	typedef enum
	{
		BUTTON_NONE = -1,
		BUTTON_START,
		BUTTON_TUTORIAL,
		BUTTON_RANKING,
		BUTTON_EXIT,
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