//=============================================================================
//
// �����L���O [ranking.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �x������
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
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
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRanking::CRanking()
{
	memset(&m_aRankingData, NULL, sizeof(m_aRankingData));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CRanking * CRanking::Create(void)
{
	CRanking * pRanking;
	pRanking = new CRanking;
	pRanking->Init();
	return pRanking;
}

//=============================================================================
// �����������֐�
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
// �I�������֐�
//=============================================================================
void CRanking::Uninit(void)
{
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CRanking::Update(void)
{
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CRanking::Draw(void)
{
}

//=============================================================================
// �f�[�^���M�����֐�
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
	//�����L���O�ݒ胊�N�G�X�g�𑗐M
	char aSendBuf[BUFFER_NUM];
	memset(aSendBuf, 0, sizeof(aSendBuf));
	aSendBuf[0] = COMMAND_TYPE_SEND_RANKING;
	//�N���A�^�C����ݒ�
	PlayerData.nScore = htonl(PlayerData.nScore);
	memcpy(&aSendBuf[1], &PlayerData.nScore, sizeof(int));
	//���O�ݒ�
	memcpy(&aSendBuf[5], PlayerData.aName, MAX_NAME);
	//���M
	pTcpClient->Send(aSendBuf, 13);
	//�f�[�^���T�[�o����󂯎��
	char aRecvBuffer[BUFFER_NUM];
	memset(aRecvBuffer, 0, sizeof(aRecvBuffer));
	pTcpClient->Recv(aRecvBuffer, sizeof(aRecvBuffer));
	pTcpClient->Release();
	return PlayerData.nScore;
}

//=============================================================================
// �f�[�^��M�����֐�
//=============================================================================
void CRanking::ReceiveRanking(RankingData * pRankingData)
{
	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
	//���炩�̌����ŏ������Ɏ��s�����ꍇ
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
	//��������T�[�o�ɑ��M
	pTcpClient->Send(aSendBuf, sizeof(int));
	////�f�[�^���T�[�o����󂯎��
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