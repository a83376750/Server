#include "Client.h"
#include "Constant.h"
#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#define HOSTADDRESS "127.0.0.1"
#define HOSTPORT 8888

Client::Client()
{

}

Client::~Client()
{

}

unsigned int Client::StartClient()
{
	WSADATA wsaData;
	using namespace std;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		return StartSocket_ERR;
	}

	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET)
	{
		return CreateSocket_ERR;
	}

	sockaddr_in inSin;

	inSin.sin_family = AF_INET;
	inSin.sin_addr.s_addr = inet_addr(HOSTADDRESS);
	inSin.sin_port = htons(HOSTPORT);
	memset(inSin.sin_zero, 0x00, 8);

	if (connect(Socket, (sockaddr*)&inSin, sizeof(inSin)))
	{
		return ConnectSocket_ERR;
	}

	char SendBuf[1024];
	while (1)
	{
		cin >> SendBuf;
		if (send(Socket, SendBuf, sizeof(SendBuf), 0) == SOCKET_ERROR)
		{
			PRINTFERRORINFO( SendSocket_ERR );
			continue;
		}
		printf("·¢ËÍÏûÏ¢:%s\n", SendBuf);
	}
	closesocket(Socket);
	WSACleanup();
	return 0;
}
