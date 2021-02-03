//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
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
// コンストラクタ
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
// デストラクタ
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// テクスチャロード関数
//=============================================================================
HRESULT CRanking::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_RANKING,								// ファイルの名前
		&m_pTexture);									// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャアンロード関数
//=============================================================================
void CRanking::Unload(void)
{
	for (int nCount = 0; nCount < MAX_RANKING_TEXTURE; nCount++)
	{
		// テクスチャの破棄
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
	}
}

//=============================================================================
// 生成関数
//=============================================================================
CRanking * CRanking::Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	CRanking * pRanking;
	pRanking = new CRanking;
	pRanking->Init(pos, SizeHeight, SizeWidth);
	return pRanking;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CRanking::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	//サウンドの取得
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
// 終了関数
//=============================================================================
void CRanking::Uninit(void)
{
	CScene::Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CRanking::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	//ジョイスティックの取得
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

	// 頂点座標を設定
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);

	//もしENTERかAボタンを押したとき
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || lpDIDevice != NULL &&pInputJoystick->GetJoystickTrigger(JS_A))
	{
		//サウンドを停止する
		pSound->StopSound();
		//タイトルに移動
		CManager::StartFade(CManager::MODE_TITLE);
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CRanking::Draw(void)
{
}

void CRanking::GetRanking(RankingData * pRankingData)
{
	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
	//何らかの原因で初期化に失敗した場合
	if (nErr != 0)
	{
		/*printf("WSAStartup failed\n");*/
	}
	CTcpClient *pTcpClient = pTcpClient->Create(SERVER_IP_NUM, SERVER_PORT_NUM);
	if (pTcpClient == NULL)
	{
		//ソケット接続をクローズ
		//pTcpClient->Close();
		return;
	}
	char aSendBuf[BUFFER_NUM];
	memset(aSendBuf, 0, sizeof(aSendBuf));
	aSendBuf[0] = COMMAND_TYPE_GET_RANKING;
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
		nTime = ntohl(nTime);// エンディアン変更
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
	//何らかの原因で初期化に失敗した場合
	if (nErr != 0)
	{
		/*printf("WSAStartup failed\n");*/
	}

	CTcpClient *pTcpClient = pTcpClient->Create(SERVER_IP_NUM, SERVER_PORT_NUM);

	if (pTcpClient == NULL)
	{
		//ソケット接続をクローズ
		//pTcpClient->Close();
		return 0;
	}

	//ランキング設定リクエストを送信
	char aSendBuf[BUFFER_NUM];
	memset(aSendBuf, 0, sizeof(aSendBuf));
	aSendBuf[0] = COMMAND_TYPE_SET_RANKING;
	//クリアタイムを設定
	nScore = htonl(nScore);
	memcpy(&aSendBuf[1], &nScore, sizeof(int));
	//名前せってい
	memcpy(&aSendBuf[5], aName, MAX_NAME);
	//送信
	pTcpClient->Send(aSendBuf, 13);
	//データをサーバから受け取る
	char aRecvBuffer[BUFFER_NUM];
	memset(aRecvBuffer, 0, sizeof(aRecvBuffer));
	pTcpClient->Recv(aRecvBuffer, sizeof(aRecvBuffer));

	pTcpClient->Release();
	return nScore;
}
