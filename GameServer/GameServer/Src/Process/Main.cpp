#include "Server.h"
#include "ThreadPoor.h"

void StartServer()
{
	Server *server = Server::Instance();
	server->StartServer();
	std::shared_ptr<ThreadPoor> poor = std::make_shared<ThreadPoor>();
	poor->pushTask(new RecvSendTask(server));
	while (1)
	{
		std::cout << "服务器线程已启动" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void CloseServer()
{
	try
	{
		Server *server = Server::Instance();
		delete server;
	}
	catch (std::exception& e)
	{
	}
}

void DisplayMenu()
{
	bool bStart = true;
	while (bStart)
	{
		std::cout << "*****************************************************" << std::endl;
		std::cout << "*****************************************************" << std::endl;
		std::cout << "*****************************************************" << std::endl;

		std::cout << "1.启动服务器" << std::endl;
		std::cout << "2.关闭服务器" << std::endl;

		std::cout << "*****************************************************" << std::endl;
		std::cout << "*****************************************************" << std::endl;
		std::cout << "*****************************************************" << std::endl;
		int key;
		std::cin >> key;

		switch (key)
		{
			case 1:
			{
				StartServer();
				break;
			}
			case 2:
			{
				CloseServer();
				bStart = false;
				break;
			}
			default:
			{
				std::cout << "请输入其他值" << std::endl;
			}
		}
	}
}

int main()
{
	DisplayMenu();
	
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
			std::cout << "最大线程数:" << std::thread::hardware_concurrency() << std::endl;
		}
	}
}
#endif // DEBUG