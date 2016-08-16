#include "Client.h"
#include <assert.h>



#ifdef BASESOCKET
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include "zmq.h"
#endif


Client* Client::m_client = nullptr;
Client::Client()
{

}

Client::~Client()
{

}

Client* Client::Instance()
{
	if (m_client)
		return m_client;
	else
		return new Client();
}

void Client::SendData(void *buffer, size_t len)
{
	int nSize;
	std::cout << "SendData - Start" << std::endl;
#ifdef BASESOCKET
	if (nSize = send(m_socket, buffer, len, 0) == len)
#else
	if(nSize = zmq_send(m_socket,buffer, len,0) == len)
#endif
	{
		std::cout << "发送消息:" << (char*)buffer << std::endl;
	}
	std::cout << "读取数据大小:" << nSize << std::endl;
	std::cout << "SendData - End" << std::endl;
}

void Client::RecvData(void *buffer, size_t len)
{
	std::cout << "RecvData - Start" << std::endl;
#ifdef BASESOCKET
	int nSize = recv(m_socket, buffer, len, 0);
#else
	int nSize = zmq_recv(m_socket, buffer, len, 0);
#endif
	std::cout << "Buffer:" << (char*)buffer << std::endl;
	std::cout << "RecvData - End" << std::endl;
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

	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET)
	{
		return CreateSocket_ERR;
	}

	sockaddr_in inSin;

	inSin.sin_family = AF_INET;
	inSin.sin_addr.s_addr = inet_addr(HOSTADDRESS);
	inSin.sin_port = htons(HOSTPORT);
	memset(inSin.sin_zero, 0x00, 8);

	if (connect(m_socket, (sockaddr*)&inSin, sizeof(inSin)))
	{
		return ConnectSocket_ERR;
	}

#ifdef GameC11
	thread t1(SendData, &m_socket);
	t1.join();
	thread::id nID = t1.get_id();

#else
	_beginthread(SendData, 0, (void*)(&m_socket));
#endif

	while (1)
	{
		cout << "主线程运行中...." << endl;
		Sleep(1000);
	}
	closesocket(m_socket);
	WSACleanup();
#else
	m_ctx = zmq_ctx_new();
	assert(m_ctx);
	m_socket = zmq_socket(m_ctx, ZMQ_DEALER);
	assert(m_socket);
	int rc;
// 	int64_t affinity = 1;
// 	rc = zmq_setsockopt(socket, ZMQ_AFFINITY, &affinity, sizeof(int64_t));
// 	assert(rc == 0);
	char address[24] = ZMQADDRESS;
	rc = zmq_connect(m_socket, address);
	assert(rc == 0);
#endif
	return 0;
}
