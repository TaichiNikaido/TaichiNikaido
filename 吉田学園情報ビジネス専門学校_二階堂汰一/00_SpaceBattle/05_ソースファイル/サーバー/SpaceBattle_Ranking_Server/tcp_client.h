//=============================================================================
//
// クライアント処理 [tcp_client.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTcpClient
{
public:
	CTcpClient();
	~CTcpClient();
	static CTcpClient * Create(SOCKET sock);
	bool Init(SOCKET sock);
	int Send(char *pSendData, int nSendDataSize);
	int Recv(char *pRecvBuf, int nRecvBufSize);
	void Release(void);
	void Close();
private:
	SOCKET m_sock;
};
#endif
