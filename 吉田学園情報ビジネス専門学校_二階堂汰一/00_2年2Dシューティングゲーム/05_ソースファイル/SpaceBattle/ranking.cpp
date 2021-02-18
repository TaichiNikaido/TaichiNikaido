//=============================================================================
//
// ランキング [ranking.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// 警告制御
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include "main.h"
#include "name.h"
#include "renderer.h"
#include "manager.h"
#include "result.h"
#include "ranking.h"
#include "tcp_client.h"
#include "mode_result.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CRanking::CRanking()
{
	memset(&m_aRankingData, NULL, sizeof(m_aRankingData));
}

//=============================================================================
// デストラクタ
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CRanking * CRanking::Create(void)
{
	CRanking * pRanking;
	pRanking = new CRanking;
	pRanking->Init();
	return pRanking;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CRanking::Init(void)
{
	CResultMode * pResultMode = CManager::GetResultMode();
	CResult::PLAYER_DATA pPlayerData = pResultMode->GetResult()->GetPlayerData();
	SendRanking(pPlayerData);
	ReceiveRanking(m_aRankingData);

	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CRanking::Uninit(void)
{
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CRanking::Update(void)
{
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CRanking::Draw(void)
{
}

//=============================================================================
// データ送信処理関数
//=============================================================================
int CRanking::SendRanking(CResult::PLAYER_DATA PlayerData)
{
	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
	CTcpClient *pTcpClient = pTcpClient->Create(SERVER_IP_NUM, SERVER_PORT_NUM);
	if (pTcpClient == NULL)
	{
		return 0;
	}
	//ランキング設定リクエストを送信
	char aSendBuf[BUFFER_NUM];
	memset(aSendBuf, 0, sizeof(aSendBuf));
	aSendBuf[0] = COMMAND_TYPE_SEND_RANKING;
	//クリアタイムを設定
	PlayerData.nScore = htonl(PlayerData.nScore);
	memcpy(&aSendBuf[1], &PlayerData.nScore, sizeof(int));
	//名前設定
	memcpy(&aSendBuf[5], PlayerData.aName, MAX_NAME);
	//送信
	pTcpClient->Send(aSendBuf, 13);
	//データをサーバから受け取る
	char aRecvBuffer[BUFFER_NUM];
	memset(aRecvBuffer, 0, sizeof(aRecvBuffer));
	pTcpClient->Recv(aRecvBuffer, sizeof(aRecvBuffer));
	pTcpClient->Release();
	return PlayerData.nScore;
}

//=============================================================================
// データ受信処理関数
//=============================================================================
void CRanking::ReceiveRanking(RankingData * pRankingData)
{
	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
	//何らかの原因で初期化に失敗した場合
	if (nErr != 0)
	{
	}
	CTcpClient *pTcpClient = pTcpClient->Create(SERVER_IP_NUM, SERVER_PORT_NUM);
	if (pTcpClient == NULL)
	{
		return;
	}
	char aSendBuf[BUFFER_NUM];
	memset(aSendBuf, 0, sizeof(aSendBuf));
	aSendBuf[0] = COMMAND_TYPE_RECEIVE_RANKING;
	//文字列をサーバに送信
	pTcpClient->Send(aSendBuf, sizeof(int));
	////データをサーバから受け取る
	char aRecvBuffer[BUFFER_NUM];
	memset(aRecvBuffer, 0, sizeof(aRecvBuffer));
	pTcpClient->Recv(aRecvBuffer, sizeof(aRecvBuffer));
	int nIndex = 0;
	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		int nTime = *(int*)&aRecvBuffer[nIndex];
		nTime = ntohl(nTime);
		pRankingData[nCntRank].nScore = nTime;
		nIndex += sizeof(int);
		memcpy(pRankingData[nCntRank].aName, &aRecvBuffer[nIndex], MAX_NAME);
		nIndex += MAX_NAME;
	}
	pTcpClient->Release();
}