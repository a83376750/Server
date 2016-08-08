#include "Server.h"
#include "ThreadPoor.h"

int main()
{
	ThreadPoor *poor = new ThreadPoor();
	int StopFlag;
	while (1)
	{
		std::cin.clear();
		std::cin.sync();
		std::cin >> StopFlag;
		if (StopFlag == 0)
		{
			delete poor;
			system("pause");
			return 0;
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
			poor->m_cv.notify_one();
		}
		else if (StopFlag == 4)
		{
			poor->m_cv.notify_all();
		}
		else if (StopFlag == 5)
		{
			std::cout << "最大线程数:" << std::thread::hardware_concurrency() << std::endl;
		}
	}

	Server *StartServer = new Server();
	StartServer->StartServer();
	return 0;
}