#pragma once
#include "Constant.h"

class Client
{
public:
	Client();
	~Client();
#ifdef BASESOCKET
	void SendData(void *s);
	void RecvData(void *s);
#endif
	unsigned int StartClient();

private:
	//KeepAlive kAlive;
};