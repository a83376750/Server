#include "Server.h"
#include <iostream>
#include <assert.h>
#include "ThreadPoor.h"



#ifdef BASESOCKET
#include <process.h>
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")	
#else
#include "zmq.h"
#endif


Server *Server::m_server = nullptr;

Server::Server()
{
}

Server::~Server()
{
}


Server* Server::Instance()
{
	if (m_server)
		return m_server;
	else
		return new Server();
}

unsigned int Server::StartServer()
{
	std::cout << "ServerStart......." << std::endl;
#ifdef BASESOCKET
	WORD usSocketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(usSocketVersion, &wsaData))
	{
		return StartSocket_ERR;
	}


	SOCKET socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket == INVALID_SOCKET)
	{
		return CreateSocket_ERR;
	}

	sockaddr_in inSin;
	inSin.sin_port = htons(8888);
	inSin.sin_addr.S_un.S_addr = INADDR_ANY;
	inSin.sin_family = AF_INET;

	if (bind(socket, (sockaddr*)&inSin, sizeof(inSin)) == SOCKET_ERROR)
	{
		return BindSocket_ERR;
	}

	if (listen(socket, 5) == SOCKET_ERROR)
	{
		return ListenSocket_ERR;
	}

	printf("Server is Start!!!\n");

	sockaddr_in recvAddr;
	int AddLen = sizeof(recvAddr);
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	while (1)
	{
		SOCKET RecvSocket = accept(socket, (sockaddr*)&recvAddr, &AddLen);
		if (RecvSocket == INVALID_SOCKET)
		{
			return AcceptSocket_ERR;
		}
		using namespace std;
		cout << "客户端连接::" << inet_ntoa(recvAddr.sin_addr) << ":" << recvAddr.sin_port << endl;

		_beginthread(SaveBuffer, 0, (LPVOID)RecvSocket);

	}

	closesocket(socket);
	WSACleanup();
#else
	m_ctx = zmq_ctx_new();
	assert(m_ctx);

	//ZMQ_STREAM 流模式socket, 试采用ZMQ_ROUTER
	m_socket = zmq_socket(m_ctx, ZMQ_STREAM);
	assert(m_socket);

	// 	int64_t affinity = 1;
	// 	int rc = zmq_setsockopt(socket, ZMQ_IDENTITY, &affinity, sizeof(affinity));

	// 	assert(rc);


	char address[24] = "tcp://*:8080";
	int rc = zmq_bind(m_socket, address);
	assert(rc == 0);

// 	void *buffer[NETBUFFER];
// 	int bufferLen = sizeof(buffer);
// 	while (1)
// 	{
// 		cout << "Start recv....." << endl;
// 		int nBytes = zmq_recv(m_socket, buffer, bufferLen, 0);
// 		cout << (char *)buffer << endl;
// 	}


#endif

	return Succee_ERR;
}


void Server::RecvBuffer(void *buffer)
{
	int nBytes = zmq_recv(m_socket, buffer, NETBUFFER, 0);
	std::cout << "线程号:" << std::this_thread::get_id() << "---";
	std::cout << (char*)buffer << std::endl;
	std::cout << "字节数:" << nBytes << std::endl;
}

void Server::WriteBuffer(void *buffer, int len)
{
	int nBytes = zmq_send(m_socket, buffer, len, 0);
	std::cout << (char*)buffer << std::endl;
	std::cout << "字节数:" << nBytes << std::endl;
}

void SaveBuffer(void *lpParameter)
{
#ifdef BASESOCKET
	SOCKET CientSocket = (SOCKET)lpParameter;
	int Ret, Err = 0;
	char RecvBuffer[1024];

	using namespace std;
	while (true)
	{
		memset(RecvBuffer, 0, sizeof(RecvBuffer));
		Ret = recv(CientSocket, RecvBuffer, sizeof(RecvBuffer), 0);
		if (Ret == SOCKET_ERROR)
		{
			Err = WSAGetLastError();
			if (Err == WSAEWOULDBLOCK)
			{
				continue;
			}
			else if (Err == WSAETIMEDOUT)
			{
				printf("超时!!!!!");
				continue;
			}
			else
			{
				continue;
			}
		}

		cout << "接收到客户信息为:" << RecvBuffer << endl;
	}
	closesocket(CientSocket);
#else

#endif
}