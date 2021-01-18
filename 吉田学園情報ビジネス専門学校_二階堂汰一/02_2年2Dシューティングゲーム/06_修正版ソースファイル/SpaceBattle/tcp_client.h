//=============================================================================
//
// クライアント [tcp_client.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTcpClient
{
public:
	CTcpClient();
	~CTcpClient();
	static CTcpClient * Create(const char* pHostName, int nPortNum);
	void Release(void);
	bool Init(const char *pHostName, int nPortNum);
	int Send(char *pSendData, int nSendDataSize);
	int Recv(char *pRecvBuf, int nRecvBufSize);
	void Close();
private:
	SOCKET m_sock;
};
#endif