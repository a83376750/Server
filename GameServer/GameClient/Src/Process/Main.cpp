#include "Client.h"
#define  GameC11

#ifdef GameC11
#include <thread>
#else
#include <process.h>
#endif


int main(int argc, char * argv[])
{
#ifdef DEBUG
	//if (__cplusplus < 201103L)
	//	return -1;
#endif

	Client *client = Client::Instance();
	client->StartClient();
	char buffer[1024];
	std::thread th(&Client::RecvData, client, buffer, 1024);
	th.detach();
	 while (1)
	 {
		 char buffer[1024];
		 char flag;
		 std::cin >> flag;
		 switch (flag)
		 {
			 case '1':
			 {
				 strcpy_s(buffer, 1024, "{ \"Page\" : 1, \"project\" : \"RapidJSON\", \"stars\" : 11, \"a\" : { \"b\" : [null] } }");
				 break;
			 }
			 case '2':
			 {
				 std::cin >> buffer;
				 
				 break;
			 }
			 default:
			 {

			 }
		 }
		 client->SendData(buffer, sizeof(buffer));
		 std::cout << "�ͻ���������" << std::endl;
	 }
	return 0;
}