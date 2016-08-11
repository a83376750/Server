#pragma once

#include "Constant.h"


class Server
{
public:
	Server();
	~Server();
	static Server* Instance();
	unsigned int StartServer();
	void RecvBuffer(void *buffer);
	void WriteBuffer(void *buffer, int len);

public:
	static Server *m_server;
	CONECTTYPE	NetType;
public:
#ifdef BASESOCKET
#else
	void *m_ctx;
	void *m_socket;
#endif
};

void SaveBuffer(void *lpParameter);
