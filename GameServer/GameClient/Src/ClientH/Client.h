#pragma once
#include "Constant.h"

class Client
{
public:
	Client();
	~Client();

	static void SendData(void *s);
	static void RecvData(void *s);

	unsigned int StartClient();

private:
	//KeepAlive kAlive;
};