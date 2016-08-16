#pragma once
#include "Constant.h"
#include <iostream>
#include <string>

class Client
{
public:
	Client();
	~Client();
	static Client *Instance();
	void SendData(void *buffer, size_t len);
	void RecvData(void *bufferm, size_t len);
	unsigned int StartClient();

public:
	static Client *m_client;
private:
#ifdef BASESOCKET
	SOCKET m_socket;
#else
	void *m_socket;
	void *m_ctx;
#endif
	//KeepAlive kAlive;
};