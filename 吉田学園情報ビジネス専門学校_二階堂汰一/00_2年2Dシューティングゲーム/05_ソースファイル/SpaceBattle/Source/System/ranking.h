//=============================================================================
//
// ランキング [ranking.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "result.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_RANKING 10
#define SERVER_IP_NUM "127.0.0.1"
#define SERVER_PORT_NUM 12345
#define BUFFER_NUM 1024

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CRanking
{
public:
	typedef struct
	{
		int nScore;
		char aName[8];
	} RankingData;
	typedef enum
	{
		COMMAND_TYPE_NONE = 0,
		COMMAND_TYPE_RECEIVE_RANKING,
		COMMAND_TYPE_SEND_RANKING
	} COMMAND_TYPE;
	CRanking();
	~CRanking();
	static CRanking * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	int SendRanking(CResult::PLAYER_DATA PlayerData);
	void ReceiveRanking(RankingData * pRankingData);
	RankingData * GetRankingData(void) { return m_aRankingData; }
private:
	RankingData m_aRankingData[MAX_RANKING];
};
#endif