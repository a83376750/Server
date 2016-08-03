#pragma once

class Client
{
public:
	Client();
	~Client();

	static void SendData(void *s);
	static void RecvData(void *s);

	unsigned int StartClient();

};