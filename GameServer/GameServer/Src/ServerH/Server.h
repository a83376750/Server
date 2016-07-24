#pragma once

#include "Constant.h"


class Server
{
public:
	Server();
	~Server();
	unsigned int StartServer();
	void RecvBuffer(void *buffer);
	void WriteBuffer(void *buffer, int len);

public:
	CONECTTYPE	NetType;
};

void SaveBuffer(void *lpParameter);
