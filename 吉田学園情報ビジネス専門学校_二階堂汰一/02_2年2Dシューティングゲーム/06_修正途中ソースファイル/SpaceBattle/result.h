//=============================================================================
//
// リザルト [result.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CResult
{
public:
	typedef struct
	{
		char aName[8];
		int nDeath;
		int nContinue;
		int nBomb;
		int nScore;
	}PLAYER_DATA;
	CResult();
	~CResult();
	static CResult * Create();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DataLoad(void);
	PLAYER_DATA GetPlayerData(void) { return m_PlayerData; }
private:
	PLAYER_DATA m_PlayerData;
};
#endif