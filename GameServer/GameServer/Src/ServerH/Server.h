#pragma once

#include <WinSock2.h>
#include "Constant.h"
#include <process.h>

#pragma comment (lib,"ws2_32.lib")

class Server
{
public:
	Server();
	~Server();
	unsigned int StartServer();
	void RecvBuffer(void *buffer);
	void WriteBuffer(void *buffer, int len);

public:
	SOCKET m_Socket;
};

void SaveBuffer(void *lpParameter);
