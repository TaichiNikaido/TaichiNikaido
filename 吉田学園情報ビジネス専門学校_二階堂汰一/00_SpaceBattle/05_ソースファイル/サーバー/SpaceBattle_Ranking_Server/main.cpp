//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// 警告制御
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include <stdio.h>
#include <winsock2.h>
#include <thread>
#include <mutex>
#include "tcp_listener.h"
#include "tcp_client.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SERVER_PORT_NUM 12345		//接続先サーバの接続先ポート
#define MAX_ACCEPT_CONNECTION 5		//接続受付最大数
#define MAX_RANKING 10				//ランキングの最大数	
#define MAX_NAME 8					//名前の最大文字数
#define BUFFER_NUM 1024				//データサイズの最大量

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	char aRcevData[BUFFER_NUM];		//受信データ
	char aSendData[BUFFER_NUM];		//送信データ
}STRDATA;		//データ
typedef struct
{
	int nClearTime;			//クリアタイム
	char aName[MAX_NAME];	//名前
}PlayerData;	//プレイヤー情報

//*****************************************************************************
// 列挙型宣言
//*****************************************************************************
typedef enum
{
	COMMAND_TYPE_NONE = 0,
	COMMAND_TYPE_GET_RANKING,		// ランキング一覧を取得
	COMMAND_TYPE_SET_RANKING		// ランキングを設定
} COMMAND_TYPE;		//コマンド

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void LoadFile(void);
void SaveFile(void);
void WorkerThread(CTcpClient *pTcpClient);
int SetRanking(int nTime, char *pName);

//*****************************************************************************
// グローバル変数定義
//*****************************************************************************
PlayerData g_aRankingData[MAX_RANKING];	//ランキングデータ

//=============================================================================
// メイン処理関数
//=============================================================================
int main()
{
	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
	if (nErr != 0)
	{
		//何らかの原因で初期化に失敗した
		printf("WSAStartup failed\n");
		return 1;
	}
	//グローバル変数初期化
	memset(g_aRankingData, 0, sizeof(g_aRankingData));
	//ランキングファイル読み込み
	LoadFile();
	CTcpListener *pTcpListener = pTcpListener->Create(SERVER_PORT_NUM);

	if (pTcpListener == NULL)
	{
		//ソケット接続をクローズ
		pTcpListener->Close();
		return 1;
	}
	//ソケット接続を受け付ける（受け付けるまでプログラムはブロックされる
	while (1)
	{
		//接続受付処理関数呼び出し
		CTcpClient * pTcpClient = pTcpListener->Accept();
		//TcpクライアントのポインタがNULLの場合
		if (pTcpClient == NULL)
		{
			//再度繰り返す
			continue;
		}
		//スレッド処理関数呼び出し
		std::thread WorkerThread(WorkerThread, pTcpClient);
		//スレッドを切り離す
		WorkerThread.detach();
	}
	//ソケット接続をクローズ
	pTcpListener->Release();
	//winsock終了処理
	WSACleanup();
	rewind(stdin);
	getchar();
	return 0;
}

//=============================================================================
// ファイル読み込み処理関数
//=============================================================================
void LoadFile(void)
{
	FILE *pFile = NULL;	//ファイルのポインタ
	//もしファイルのポインタがNULLの場合
	if (pFile == NULL)
	{
		//ファイルを開く
		pFile = fopen("RankingData.txt", "r");
		//もしファイルのポインタがNULLではない場合
		if (pFile != NULL)
		{
			//読み込み完了メッセージの表示
			printf("ファイルの読み込みが完了しました。\n");
			//ランキングの最大数分回す
			for (int nCount = 0; nCount < MAX_RANKING; nCount++)
			{
				//クリアタイムの読み込み
				fscanf(pFile, "%d", &g_aRankingData[nCount].nClearTime);
				//名前の読み込み
				fscanf(pFile, "%s", &g_aRankingData[nCount].aName);
			}
			//ファイルを閉じる
			fclose(pFile);
		}
		else
		{
			//読み込み失敗メッセいーじの表示
			printf("ファイルがオープン出来ませんでした。");
		}
	}
}

//=============================================================================
// ファイル保存処理関数
//=============================================================================
void SaveFile(void)
{
	FILE *pFile = NULL;	//ファイルのポインタ
	//ファイルのポインタがNULLの場合
	if (pFile == NULL)
	{
		//ファイルを開く
		pFile = fopen("RankingData.txt", "w");
		//もしファイルのポインタがNULLではない場合
		if (pFile != NULL)
		{
			//ランキングの最大数分回す
			for (int nCount = 0; nCount < MAX_RANKING; nCount++)
			{
				//クリアタイムの書き込み
				fprintf(pFile, "%d\n", g_aRankingData[nCount].nClearTime);
				//名前の書き込み
				fprintf(pFile, "%s\n", g_aRankingData[nCount].aName);
				fprintf(pFile, "\n");
				printf("[%d]人目のプレイヤーの情報を保存しました。\n",nCount + 1);
			}
			//ファイルを閉じる
			fclose(pFile);
		}
		else
		{
			//読み込み失敗メッセージの表示
			printf("ファイルがオープン出来ませんでした。");
		}
	}
}

//=============================================================================
// スレッド処理関数
//=============================================================================
void WorkerThread(CTcpClient * pTcpClient)
{
	//受信内容の取得
	char aRecvBuffer[BUFFER_NUM];
	char aSendBuf[BUFFER_NUM];
	int nNumRecv = pTcpClient->Recv(aRecvBuffer, sizeof(aRecvBuffer));
	if (nNumRecv <= 0)
	{
		//ソケット接続をクローズ
		pTcpClient->Close();
	}
	COMMAND_TYPE command = (COMMAND_TYPE)aRecvBuffer[0];
	int nIndex = 0;
	int nData = 1;
	int nRank = 1;
	int nTime = 0;
	switch (command)
	{
	case COMMAND_TYPE_GET_RANKING:
		//ランキングの最大数分回す
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			//エンディアン変換
			nData = (int)htonl(g_aRankingData[nCount].nClearTime);
			memcpy(&aSendBuf[nIndex], &nData, sizeof(int));
			nIndex += sizeof(int);
			g_aRankingData[nCount].aName[MAX_NAME - 1] = '\0';
			memcpy(&aSendBuf[nIndex], g_aRankingData[nCount].aName, MAX_NAME);
			nIndex += MAX_NAME;
		}
		//送信処理関数呼び出し
		pTcpClient->Send(aSendBuf, sizeof(aSendBuf));
		printf("送信完了\n");
		break;
	case COMMAND_TYPE_SET_RANKING:
		//クリアタイムを取得
		nTime = ntohl(*(int*)&aRecvBuffer[1]);
		//名前取得
		char aName[MAX_NAME];
		memcpy(aName, &aRecvBuffer[5], MAX_NAME);
		aName[MAX_NAME - 1] = '\0';
		//ランキング更新
		nRank = SetRanking(nTime, aName);
		//ランキング順位送信
		aSendBuf[0] = (char)nRank;
		pTcpClient->Send(aSendBuf, sizeof(aSendBuf));
		//ファイル保存処理関数呼び出し
		SaveFile();
		break;
	default:
		break;
	}
	
	//ソケット接続をクローズ
	pTcpClient->Release();
}

//=============================================================================
// ランキング設定処理関数
//=============================================================================
int SetRanking(int nTime, char * pName)
{
	int nCount = 0;
	//ランキングの最大数分回す
	for (nCount; nCount < MAX_RANKING; nCount++)
	{
		//ランキング情報が入っているか確認する
		if (g_aRankingData[nCount].nClearTime == 0 || nTime > g_aRankingData[nCount].nClearTime)
		{
			//以降のランキングデータを後ろに移動
			for (int nCntMove = MAX_RANKING - 1; nCntMove > nCount; nCntMove--)
			{
				g_aRankingData[nCntMove].nClearTime = g_aRankingData[nCntMove - 1].nClearTime;
				strcpy(g_aRankingData[nCntMove].aName, g_aRankingData[nCntMove - 1].aName);
			}
			g_aRankingData[nCount].nClearTime = nTime;
			strcpy(g_aRankingData[nCount].aName, pName);
			break;
		}
	}
	return nCount + 1;
}
