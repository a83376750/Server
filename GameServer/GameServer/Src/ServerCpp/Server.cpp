#include "Server.h"
#include <iostream>

Server::Server()
{
}

Server::~Server()
{

}


unsigned int Server::StartServer()
{
	WORD usSocketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(usSocketVersion, &wsaData))
	{
		return StartSocket_ERR;
	}


	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_Socket == INVALID_SOCKET)
	{
		return CreateSocket_ERR;
	}

	sockaddr_in inSin;
	inSin.sin_port = htons(8888);
	inSin.sin_addr.S_un.S_addr = INADDR_ANY;
	inSin.sin_family = AF_INET;

	if (bind(m_Socket, (sockaddr*)&inSin, sizeof(inSin)) == SOCKET_ERROR)
	{
		return BindSocket_ERR;
	}

	if (listen(m_Socket, 5) == SOCKET_ERROR)
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
		SOCKET RecvSocket = accept(m_Socket, (sockaddr*)&recvAddr, &AddLen);
		if (RecvSocket == INVALID_SOCKET)
		{
			return AcceptSocket_ERR;
		}
		using namespace std;
		cout << "客户端连接::" << inet_ntoa(recvAddr.sin_addr) << ":" << recvAddr.sin_port << endl;


// 		int len = recv(recvSocket, buffer, sizeof(buffer), NULL);
// 		if (len <= 0)
// 		{
// 			continue;
// 		}
// 		printf("消息：%s\n", buffer);

		_beginthread(SaveBuffer, 0, (LPVOID)RecvSocket);

	}

	closesocket(m_Socket);
	WSACleanup();
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

}