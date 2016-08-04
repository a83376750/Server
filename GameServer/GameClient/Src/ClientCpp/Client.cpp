#include "Client.h"
#include "Constant.h"
#include <iostream>
#include <string>
#include <assert.h>

#define  GameC11
#define  BASESOCKET


#ifdef GameC11
#include <thread>
#else
#include <process.h>
#endif



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

void Client::SendData(void *s)
{
	SOCKET *socket = (SOCKET*)s;
	cout << "SendData - Start" << endl;

	char SendBuf[NETBUFFER];
	while (1)
	{
		cin >> SendBuf;
		if (send(*socket, SendBuf, sizeof(SendBuf), 0) == SOCKET_ERROR)
		{
			PRINTFERRORINFO(SendSocket_ERR);
			continue;
		}
		printf("发送消息:%s\n", SendBuf);
	}
	cout << "SendData - End" << endl;
}

void Client::RecvData(void *s)
{
	SOCKET *socket = (SOCKET*)s;
	cout << "RecvData - Start" << endl;
	char RecvBuf[NETBUFFER];
	memset(RecvBuf, 0, NETBUFFER);
	int nSize = recv(*socket, RecvBuf, NETBUFFER, 0);
	cout << "Buffer:" << RecvBuf << endl;
	cout << "RecvData - End" << endl;
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

#ifdef GameC11
	thread t1(SendData,&Socket);
	t1.join();
	thread::id nID = t1.get_id();
	
#else
	_beginthread(SendData, 0, (void*)(&Socket));
#endif

	while (1)
	{
		cout << "主线程运行中...." << endl;
		Sleep(1000);
	}
	closesocket(Socket);
	WSACleanup();
#else
	void *ctx = zmq_ctx_new();
	assert(ctx);

	//ZMQ_STREAM 流模式socket, 试采用ZMQ_ROUTER
	void *socket = zmq_socket(ctx, ZMQ_STREAM);
	assert(socket);

	char address[24] = "tcp://localhost:8080";
	int rc = zmq_connect(socket, address);
	assert(rc == 0);

	char str[NETBUFFER];
	while (1)
	{
		rapidjsonTest();
		cin >> str;
		int nSize = zmq_send(socket, str, sizeof(str), 0);
		cout << str << endl;
		cout << "nSize:" << nSize << endl;
		memset(str, 0, NETBUFFER);
	}

#endif
	return 0;
}
