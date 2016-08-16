#include "Client.h"
#define  GameC11

#ifdef GameC11
#include <thread>
#else
#include <process.h>
#endif


int main(int argc, char * argv[])
{
#if DEBUG
	if (__cplusplus < 201103L)
		return -1;
#endif

	Client *client = Client::Instance();
	client->StartClient();
	char buffer[1024];
	std::thread th(&Client::RecvData, client, buffer, 1024);
	th.detach();
	 while (1)
	 {
		 char buffer[1024];
		 std::cin >> buffer;
		 client->SendData(buffer, 1024);
		 std::cout << "客户端已启动" << std::endl;
	 }
	return 0;
}