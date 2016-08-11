#include "Server.h"
#include "ThreadPoor.h"

int main()
{
	try
	{
		std::shared_ptr<ThreadPoor> poor = std::make_shared<ThreadPoor>();
		Server *server = Server::Instance();
		poor->pushTask(new RecvSendTask(server));

		delete server;
	}
	catch (std::exception& e)
	{
		std::cout << "�������쳣:" << e.what() << std::endl;
	}

	
	return 0;
}

#ifdef DEBUG
void DebugFun()
{
	std::shared_ptr<ThreadPoor> poor = std::make_shared<ThreadPoor>();
	int StopFlag;
	while (1)
	{
		std::cin.clear();
		std::cin.sync();
		std::cin >> StopFlag;
		if (StopFlag == 0)
		{
			break;
		}
		else if (StopFlag == 1)
		{
			poor->pushTask(new CharTask());
		}
		else if (StopFlag == 2)
		{
			ServerTask *pTask = poor->popTask();
			if (pTask == nullptr)
				continue;
			pTask->StartTask();
			delete pTask;
		}
		else if (StopFlag == 3)
		{
			poor->NotifyAllThread();
		}
		else if (StopFlag == 5)
		{
			std::cout << "����߳���:" << std::thread::hardware_concurrency() << std::endl;
		}
	}
}
#endif // DEBUG