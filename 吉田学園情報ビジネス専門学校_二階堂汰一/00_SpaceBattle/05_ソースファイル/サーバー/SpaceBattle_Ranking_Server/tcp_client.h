//=============================================================================
//
// �N���C�A���g���� [tcp_client.h]
// Author : ��K������
//
//=============================================================================
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

//*****************************************************************************
// �N���X��`
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
