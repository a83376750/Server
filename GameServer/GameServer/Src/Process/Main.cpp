#include "Server.h"
#include "ThreadPoor.h"

int main()
{
	ThreadPoor *poor = new ThreadPoor();
	int StopFlag;
	std::cin >> StopFlag;
	if (StopFlag == 0)
	{
		delete poor;
		system("pause");
		return 0;
	}
	Server *StartServer = new Server();
	StartServer->StartServer();
	return 0;
}