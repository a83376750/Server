#include "Client.h"
#include "Constant.h"
#include <iostream>
#include <assert.h>

#ifdef BASESOCKET
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include "zmq.h"
#endif
#define HOSTADDRESS "127.0.0.1"
#define HOSTPORT 8080

using namespace std;

Client::Client()
{

}

Client::~Client()
{

}

unsigned int Client::StartClient()
{
#ifdef BASESOCKET
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
#else
	void *ctx = zmq_ctx_new();
	assert(ctx);

	void *socket = zmq_socket(ctx, ZMQ_STREAM);
	assert(socket);

	char address[24] = "tcp://127.0.0.1:8080";
	int rc = zmq_connect(socket, address);
	assert(rc == 0);

	unsigned char str[NETBUFFER];
	while (1)
	{
		cin >> str;
		int nSize = zmq_send(socket, str, sizeof(str), 0);
		cout << str << endl;
		cout << "nSize:" << nSize << endl;

	}

#endif
	return 0;
}
