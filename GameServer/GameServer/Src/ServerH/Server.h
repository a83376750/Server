#pragma once

#include "Constant.h"
#include <map>

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
	SOCKET *m_socket;
#else
	void *m_ctx;
	void *m_socket;
#endif

public:
	std::map<char*, short> m_ClientHeadPackage;
};