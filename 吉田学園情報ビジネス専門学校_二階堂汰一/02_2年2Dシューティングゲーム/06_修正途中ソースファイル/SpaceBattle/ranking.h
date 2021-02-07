//=============================================================================
//
// �����L���O [ranking.h]
// Author : ��K������
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "result.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_RANKING 10
#define SERVER_IP_NUM "127.0.0.1"
#define SERVER_PORT_NUM 12345
#define BUFFER_NUM 1024

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
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