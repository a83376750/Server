#include "Server.h"
#include <iostream>



#ifdef BASESOCKET
#include <process.h>
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")	
#else

#endif

Server::Server()
{
}

Server::~Server()
{

}


unsigned int Server::StartServer()
{
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

#endif
	return 0;
}


void Server::RecvBuffer(void *buffer)
{
	printf("recv\n");
}

void Server::WriteBuffer(void *buffer, int len)
{

}

void SaveBuffer(void *lpParameter)
{
#ifdef BASESOCKET
	SOCKET CientSocket = (SOCKET)lpParameter;
	int Ret,Err = 0;
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