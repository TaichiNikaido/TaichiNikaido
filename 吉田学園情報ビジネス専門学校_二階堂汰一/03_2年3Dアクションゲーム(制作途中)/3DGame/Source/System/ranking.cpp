////=============================================================================
////
//// ランキング [ranking.cpp]
//// Author : 二階堂汰一
////
////=============================================================================
//
////*****************************************************************************
//// ヘッダファイルのインクルード
////*****************************************************************************
//#include <stdio.h>
//#include <stdlib.h>
//#include <WinSock2.h>
//#include "main.h"
//#include "name.h"
//#include "renderer.h"
//#include "manager.h"
//#include "ranking.h"
//#include "tcp_client.h"
//
////*****************************************************************************
//// マクロ定義
////*****************************************************************************
//
////*****************************************************************************
//// 静的メンバ変数初期化
////*****************************************************************************
//
////=============================================================================
//// コンストラクタ
////=============================================================================
//CRanking::CRanking()
//{
//	memset(&m_aReceiveData, NULL, sizeof(m_aReceiveData));	//受信する情報
//}
//
////=============================================================================
//// デストラクタ
////=============================================================================
//CRanking::~CRanking()
//{
//}
//
////=============================================================================
//// 生成処理関数
////=============================================================================
//CRanking * CRanking::Create(void)
//{
//	//ランキングのポインタ
//	CRanking * pRanking = NULL;
//	//もしランキングのポインタがNULLの場合
//	if (pRanking == NULL)
//	{
//		//ランキングのメモリ確保
//		pRanking = new CRanking;
//		//もしランキングのポインタがNULLじゃない場合
//		if (pRanking != NULL)
//		{
//			//ランキングの初期化処理関数呼び出し
//			pRanking->Init();
//		}
//	}
//	//ランキングのポインタを返す
//	return pRanking;
//}
//
////=============================================================================
//// 初期化処理関数
////=============================================================================
//HRESULT CRanking::Init(void)
//{
//	//データ送信処理関数呼び出し
//	SendData();
//	//データ受信処理関数呼び出し
//	ReceiveData();
//	return S_OK;
//}
//
////=============================================================================
//// データ送信処理関数
////=============================================================================
//void CRanking::SendData(void)
//{
//	WSADATA wsaData;
//	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
//	CTcpClient *pTcpClient = pTcpClient->Create(SERVER_IP_NUM, SERVER_PORT_NUM);
//	if (pTcpClient == NULL)
//	{
//		return 0;
//	}
//	//ランキング設定リクエストを送信
//	char aSendBuf[BUFFER_NUM];
//	memset(aSendBuf, 0, sizeof(aSendBuf));
//	aSendBuf[0] = COMMAND_TYPE_SEND;
//	//プレイヤー情報を設定
//	PlayerData.nScore = htonl(PlayerData.nScore);
//	memcpy(&aSendBuf[1], &PlayerData.nScore, sizeof(int));
//	memcpy(&aSendBuf[5], PlayerData.aName, MAX_NAME);
//	//送信
//	pTcpClient->Send(aSendBuf, 13);
//	//データをサーバから受け取る
//	char aRecvBuffer[BUFFER_NUM];
//	memset(aRecvBuffer, 0, sizeof(aRecvBuffer));
//	pTcpClient->Recv(aRecvBuffer, sizeof(aRecvBuffer));
//	pTcpClient->Release();
//	return PlayerData.nScore;
//}
//
////=============================================================================
//// データ受信処理関数
////=============================================================================
//void CRanking::ReceiveData(void)
//{
//	WSADATA wsaData;
//	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
//	CTcpClient *pTcpClient = pTcpClient->Create(SERVER_IP_NUM, SERVER_PORT_NUM);
//	if (pTcpClient == NULL)
//	{
//		return;
//	}
//	char aSendBuf[BUFFER_NUM];
//	memset(aSendBuf, 0, sizeof(aSendBuf));
//	aSendBuf[0] = COMMAND_TYPE_RECEIVE;
//	//文字列をサーバに送信
//	pTcpClient->Send(aSendBuf, sizeof(int));
//	////データをサーバから受け取る
//	char aRecvBuffer[BUFFER_NUM];
//	memset(aRecvBuffer, 0, sizeof(aRecvBuffer));
//	pTcpClient->Recv(aRecvBuffer, sizeof(aRecvBuffer));
//	int nIndex = 0;
//	//ランキングの最大数分回す
//	for (int nCount = 0; nCount < MAX_RANKING; nCount++)
//	{
//		int nTime = *(int*)&aRecvBuffer[nIndex];
//		nTime = ntohl(nTime);
//		pRankingData[nCount].nScore = nTime;
//		nIndex += sizeof(int);
//		memcpy(pRankingData[nCount].aName, &aRecvBuffer[nIndex], MAX_NAME);
//		nIndex += MAX_NAME;
//	}
//	pTcpClient->Release();
//}