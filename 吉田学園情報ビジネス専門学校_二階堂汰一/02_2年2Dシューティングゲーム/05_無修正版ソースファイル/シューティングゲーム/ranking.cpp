//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <WinSock2.h>
#include "main.h"
#include "ranking.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "tcp_client.h"
#include "result.h"
#include "sound.h"

LPDIRECT3DTEXTURE9 CRanking::m_pTexture = NULL;
CRanking::RankingData CRanking::m_aRankingData[MAX_RANKING] = {};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRanking::CRanking(int nPriority) : CScene(nPriority)
{
	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		m_apScene[nCount] = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	memset(m_col, 0, sizeof(m_col));
	m_fTextureX = 0.0f;
	m_fTextureY = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// �e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CRanking::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKING,								// �t�@�C���̖��O
		&m_pTexture);									// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h�֐�
//=============================================================================
void CRanking::Unload(void)
{
	for (int nCount = 0; nCount < MAX_RANKING_TEXTURE; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
	}
}

//=============================================================================
// �����֐�
//=============================================================================
CRanking * CRanking::Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	CRanking * pRanking;
	pRanking = new CRanking;
	pRanking->Init(pos, SizeHeight, SizeWidth);
	return pRanking;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CRanking::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_RANKING);
	m_pos = pos;
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	m_fWidth = SizeWidth;
	m_fHeight = SizeHeight;
	for (int nCount = 0; nCount < MAX_RANKING_TEXTURE; nCount++)
	{
		m_apScene[nCount] = new CScene2d;
		m_apScene[nCount]->Init(pos, SizeHeight, SizeWidth);
		m_apScene[nCount]->SetVertexPosition(m_vpos);
		m_apScene[nCount]->BindTexture(m_pTexture);

		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		m_apScene[nCount]->SetColor(m_col);
	}
	CResult::PLAYER_DATA pPlayerData = CResult::GetPlayerData();
	SetRanking(pPlayerData.nScore, pPlayerData.aName);
	GetRanking(m_aRankingData);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CRanking::Uninit(void)
{
	CScene::Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CRanking::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	//�W���C�X�e�B�b�N�̎擾
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
	DIJOYSTATE js;

	if (lpDIDevice != NULL)
	{
		lpDIDevice->Poll();
		lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	for (int nCount = 0; nCount < MAX_RANKING_TEXTURE; nCount++)
	{
		m_apScene[nCount]->Update();
		m_apScene[nCount]->SetVertexPosition(m_vpos);
		m_apScene[nCount]->SetTex(0.0f, 0.0f, 1.0f,1.0f);
	}
	m_apScene[0]->SetTex(0.0f, 0.0f, 1.0f, 1.0f);

	// ���_���W��ݒ�
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);

	//����ENTER��A�{�^�����������Ƃ�
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A))
	{
		//�T�E���h���~����
		pSound->StopSound();
		//�^�C�g���Ɉړ�
		CManager::StartFade(CManager::MODE_TITLE);
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void CRanking::Draw(void)
{
}

void CRanking::GetRanking(RankingData * pRankingData)
{
	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
	//���炩�̌����ŏ������Ɏ��s�����ꍇ
	if (nErr != 0)
	{
		/*printf("WSAStartup failed\n");*/
	}
	CTcpClient *pTcpClient = pTcpClient->Create(SERVER_IP_NUM, SERVER_PORT_NUM);
	if (pTcpClient == NULL)
	{
		//�\�P�b�g�ڑ����N���[�Y
		//pTcpClient->Close();
		return;
	}
	char aSendBuf[BUFFER_NUM];
	memset(aSendBuf, 0, sizeof(aSendBuf));
	aSendBuf[0] = COMMAND_TYPE_GET_RANKING;
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
		nTime = ntohl(nTime);// �G���f�B�A���ύX
		pRankingData[nCntRank].nScore = nTime;
		nIndex += sizeof(int);
		memcpy(pRankingData[nCntRank].aName, &aRecvBuffer[nIndex], MAX_NAME);
		nIndex += MAX_NAME;
	}
	pTcpClient->Release();
}

int CRanking::SetRanking(int nScore, char aName[MAX_NAME])
{
	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
	//���炩�̌����ŏ������Ɏ��s�����ꍇ
	if (nErr != 0)
	{
		/*printf("WSAStartup failed\n");*/
	}

	CTcpClient *pTcpClient = pTcpClient->Create(SERVER_IP_NUM, SERVER_PORT_NUM);

	if (pTcpClient == NULL)
	{
		//�\�P�b�g�ڑ����N���[�Y
		//pTcpClient->Close();
		return 0;
	}

	//�����L���O�ݒ胊�N�G�X�g�𑗐M
	char aSendBuf[BUFFER_NUM];
	memset(aSendBuf, 0, sizeof(aSendBuf));
	aSendBuf[0] = COMMAND_TYPE_SET_RANKING;
	//�N���A�^�C����ݒ�
	nScore = htonl(nScore);
	memcpy(&aSendBuf[1], &nScore, sizeof(int));
	//���O�����Ă�
	memcpy(&aSendBuf[5], aName, MAX_NAME);
	//���M
	pTcpClient->Send(aSendBuf, 13);
	//�f�[�^���T�[�o����󂯎��
	char aRecvBuffer[BUFFER_NUM];
	memset(aRecvBuffer, 0, sizeof(aRecvBuffer));
	pTcpClient->Recv(aRecvBuffer, sizeof(aRecvBuffer));

	pTcpClient->Release();
	return nScore;
}
