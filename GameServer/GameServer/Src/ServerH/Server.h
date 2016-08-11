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
};

void SaveBuffer(void *lpParameter);
