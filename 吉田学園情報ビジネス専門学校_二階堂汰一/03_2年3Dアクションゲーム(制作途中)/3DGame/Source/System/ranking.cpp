////=============================================================================
////
//// �����L���O [ranking.cpp]
//// Author : ��K������
////
////=============================================================================
//
////*****************************************************************************
//// �w�b�_�t�@�C���̃C���N���[�h
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
//// �}�N����`
////*****************************************************************************
//
////*****************************************************************************
//// �ÓI�����o�ϐ�������
////*****************************************************************************
//
////=============================================================================
//// �R���X�g���N�^
////=============================================================================
//CRanking::CRanking()
//{
//	memset(&m_aReceiveData, NULL, sizeof(m_aReceiveData));	//��M������
//}
//
////=============================================================================
//// �f�X�g���N�^
////=============================================================================
//CRanking::~CRanking()
//{
//}
//
////=============================================================================
//// ���������֐�
////=============================================================================
//CRanking * CRanking::Create(void)
//{
//	//�����L���O�̃|�C���^
//	CRanking * pRanking = NULL;
//	//���������L���O�̃|�C���^��NULL�̏ꍇ
//	if (pRanking == NULL)
//	{
//		//�����L���O�̃������m��
//		pRanking = new CRanking;
//		//���������L���O�̃|�C���^��NULL����Ȃ��ꍇ
//		if (pRanking != NULL)
//		{
//			//�����L���O�̏����������֐��Ăяo��
//			pRanking->Init();
//		}
//	}
//	//�����L���O�̃|�C���^��Ԃ�
//	return pRanking;
//}
//
////=============================================================================
//// �����������֐�
////=============================================================================
//HRESULT CRanking::Init(void)
//{
//	//�f�[�^���M�����֐��Ăяo��
//	SendData();
//	//�f�[�^��M�����֐��Ăяo��
//	ReceiveData();
//	return S_OK;
//}
//
////=============================================================================
//// �f�[�^���M�����֐�
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
//	//�����L���O�ݒ胊�N�G�X�g�𑗐M
//	char aSendBuf[BUFFER_NUM];
//	memset(aSendBuf, 0, sizeof(aSendBuf));
//	aSendBuf[0] = COMMAND_TYPE_SEND;
//	//�v���C���[����ݒ�
//	PlayerData.nScore = htonl(PlayerData.nScore);
//	memcpy(&aSendBuf[1], &PlayerData.nScore, sizeof(int));
//	memcpy(&aSendBuf[5], PlayerData.aName, MAX_NAME);
//	//���M
//	pTcpClient->Send(aSendBuf, 13);
//	//�f�[�^���T�[�o����󂯎��
//	char aRecvBuffer[BUFFER_NUM];
//	memset(aRecvBuffer, 0, sizeof(aRecvBuffer));
//	pTcpClient->Recv(aRecvBuffer, sizeof(aRecvBuffer));
//	pTcpClient->Release();
//	return PlayerData.nScore;
//}
//
////=============================================================================
//// �f�[�^��M�����֐�
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
//	//��������T�[�o�ɑ��M
//	pTcpClient->Send(aSendBuf, sizeof(int));
//	////�f�[�^���T�[�o����󂯎��
//	char aRecvBuffer[BUFFER_NUM];
//	memset(aRecvBuffer, 0, sizeof(aRecvBuffer));
//	pTcpClient->Recv(aRecvBuffer, sizeof(aRecvBuffer));
//	int nIndex = 0;
//	//�����L���O�̍ő吔����
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