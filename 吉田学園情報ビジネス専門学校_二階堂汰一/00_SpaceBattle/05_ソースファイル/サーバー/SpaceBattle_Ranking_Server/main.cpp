//=============================================================================
//
// ���C������ [main.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �x������
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include <stdio.h>
#include <winsock2.h>
#include <thread>
#include <mutex>
#include "tcp_listener.h"
#include "tcp_client.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SERVER_PORT_NUM 12345		//�ڑ���T�[�o�̐ڑ���|�[�g
#define MAX_ACCEPT_CONNECTION 5		//�ڑ���t�ő吔
#define MAX_RANKING 10				//�����L���O�̍ő吔	
#define MAX_NAME 8					//���O�̍ő啶����
#define BUFFER_NUM 1024				//�f�[�^�T�C�Y�̍ő��

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	char aRcevData[BUFFER_NUM];		//��M�f�[�^
	char aSendData[BUFFER_NUM];		//���M�f�[�^
}STRDATA;		//�f�[�^
typedef struct
{
	int nClearTime;			//�N���A�^�C��
	char aName[MAX_NAME];	//���O
}PlayerData;	//�v���C���[���

//*****************************************************************************
// �񋓌^�錾
//*****************************************************************************
typedef enum
{
	COMMAND_TYPE_NONE = 0,
	COMMAND_TYPE_GET_RANKING,		// �����L���O�ꗗ���擾
	COMMAND_TYPE_SET_RANKING		// �����L���O��ݒ�
} COMMAND_TYPE;		//�R�}���h

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void LoadFile(void);
void SaveFile(void);
void WorkerThread(CTcpClient *pTcpClient);
int SetRanking(int nTime, char *pName);

//*****************************************************************************
// �O���[�o���ϐ���`
//*****************************************************************************
PlayerData g_aRankingData[MAX_RANKING];	//�����L���O�f�[�^

//=============================================================================
// ���C�������֐�
//=============================================================================
int main()
{
	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
	if (nErr != 0)
	{
		//���炩�̌����ŏ������Ɏ��s����
		printf("WSAStartup failed\n");
		return 1;
	}
	//�O���[�o���ϐ�������
	memset(g_aRankingData, 0, sizeof(g_aRankingData));
	//�����L���O�t�@�C���ǂݍ���
	LoadFile();
	CTcpListener *pTcpListener = pTcpListener->Create(SERVER_PORT_NUM);

	if (pTcpListener == NULL)
	{
		//�\�P�b�g�ڑ����N���[�Y
		pTcpListener->Close();
		return 1;
	}
	//�\�P�b�g�ڑ����󂯕t����i�󂯕t����܂Ńv���O�����̓u���b�N�����
	while (1)
	{
		//�ڑ���t�����֐��Ăяo��
		CTcpClient * pTcpClient = pTcpListener->Accept();
		//Tcp�N���C�A���g�̃|�C���^��NULL�̏ꍇ
		if (pTcpClient == NULL)
		{
			//�ēx�J��Ԃ�
			continue;
		}
		//�X���b�h�����֐��Ăяo��
		std::thread WorkerThread(WorkerThread, pTcpClient);
		//�X���b�h��؂藣��
		WorkerThread.detach();
	}
	//�\�P�b�g�ڑ����N���[�Y
	pTcpListener->Release();
	//winsock�I������
	WSACleanup();
	rewind(stdin);
	getchar();
	return 0;
}

//=============================================================================
// �t�@�C���ǂݍ��ݏ����֐�
//=============================================================================
void LoadFile(void)
{
	FILE *pFile = NULL;	//�t�@�C���̃|�C���^
	//�����t�@�C���̃|�C���^��NULL�̏ꍇ
	if (pFile == NULL)
	{
		//�t�@�C�����J��
		pFile = fopen("RankingData.txt", "r");
		//�����t�@�C���̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pFile != NULL)
		{
			//�ǂݍ��݊������b�Z�[�W�̕\��
			printf("�t�@�C���̓ǂݍ��݂��������܂����B\n");
			//�����L���O�̍ő吔����
			for (int nCount = 0; nCount < MAX_RANKING; nCount++)
			{
				//�N���A�^�C���̓ǂݍ���
				fscanf(pFile, "%d", &g_aRankingData[nCount].nClearTime);
				//���O�̓ǂݍ���
				fscanf(pFile, "%s", &g_aRankingData[nCount].aName);
			}
			//�t�@�C�������
			fclose(pFile);
		}
		else
		{
			//�ǂݍ��ݎ��s���b�Z���[���̕\��
			printf("�t�@�C�����I�[�v���o���܂���ł����B");
		}
	}
}

//=============================================================================
// �t�@�C���ۑ������֐�
//=============================================================================
void SaveFile(void)
{
	FILE *pFile = NULL;	//�t�@�C���̃|�C���^
	//�t�@�C���̃|�C���^��NULL�̏ꍇ
	if (pFile == NULL)
	{
		//�t�@�C�����J��
		pFile = fopen("RankingData.txt", "w");
		//�����t�@�C���̃|�C���^��NULL�ł͂Ȃ��ꍇ
		if (pFile != NULL)
		{
			//�����L���O�̍ő吔����
			for (int nCount = 0; nCount < MAX_RANKING; nCount++)
			{
				//�N���A�^�C���̏�������
				fprintf(pFile, "%d\n", g_aRankingData[nCount].nClearTime);
				//���O�̏�������
				fprintf(pFile, "%s\n", g_aRankingData[nCount].aName);
				fprintf(pFile, "\n");
				printf("[%d]�l�ڂ̃v���C���[�̏���ۑ����܂����B\n",nCount + 1);
			}
			//�t�@�C�������
			fclose(pFile);
		}
		else
		{
			//�ǂݍ��ݎ��s���b�Z�[�W�̕\��
			printf("�t�@�C�����I�[�v���o���܂���ł����B");
		}
	}
}

//=============================================================================
// �X���b�h�����֐�
//=============================================================================
void WorkerThread(CTcpClient * pTcpClient)
{
	//��M���e�̎擾
	char aRecvBuffer[BUFFER_NUM];
	char aSendBuf[BUFFER_NUM];
	int nNumRecv = pTcpClient->Recv(aRecvBuffer, sizeof(aRecvBuffer));
	if (nNumRecv <= 0)
	{
		//�\�P�b�g�ڑ����N���[�Y
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
		//�����L���O�̍ő吔����
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			//�G���f�B�A���ϊ�
			nData = (int)htonl(g_aRankingData[nCount].nClearTime);
			memcpy(&aSendBuf[nIndex], &nData, sizeof(int));
			nIndex += sizeof(int);
			g_aRankingData[nCount].aName[MAX_NAME - 1] = '\0';
			memcpy(&aSendBuf[nIndex], g_aRankingData[nCount].aName, MAX_NAME);
			nIndex += MAX_NAME;
		}
		//���M�����֐��Ăяo��
		pTcpClient->Send(aSendBuf, sizeof(aSendBuf));
		printf("���M����\n");
		break;
	case COMMAND_TYPE_SET_RANKING:
		//�N���A�^�C�����擾
		nTime = ntohl(*(int*)&aRecvBuffer[1]);
		//���O�擾
		char aName[MAX_NAME];
		memcpy(aName, &aRecvBuffer[5], MAX_NAME);
		aName[MAX_NAME - 1] = '\0';
		//�����L���O�X�V
		nRank = SetRanking(nTime, aName);
		//�����L���O���ʑ��M
		aSendBuf[0] = (char)nRank;
		pTcpClient->Send(aSendBuf, sizeof(aSendBuf));
		//�t�@�C���ۑ������֐��Ăяo��
		SaveFile();
		break;
	default:
		break;
	}
	
	//�\�P�b�g�ڑ����N���[�Y
	pTcpClient->Release();
}

//=============================================================================
// �����L���O�ݒ菈���֐�
//=============================================================================
int SetRanking(int nTime, char * pName)
{
	int nCount = 0;
	//�����L���O�̍ő吔����
	for (nCount; nCount < MAX_RANKING; nCount++)
	{
		//�����L���O��񂪓����Ă��邩�m�F����
		if (g_aRankingData[nCount].nClearTime == 0 || nTime > g_aRankingData[nCount].nClearTime)
		{
			//�ȍ~�̃����L���O�f�[�^�����Ɉړ�
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
