#include "Server.h"
#include "ThreadPoor.h"
#include "Ini.h"
#include "Log.h"

void StartServer()
{
	Server *server = Server::Instance();
	server->StartServer();
	std::shared_ptr<ThreadPoor> poor = std::make_shared<ThreadPoor>();
	poor->pushTask(new RecvTask(server));
	poor->pushTask(new JsonParse(server));
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
		std::cout << "服务器关闭异常:" << e.what() << std::endl;
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
		std::cout << "3.测试读取文件" << std::endl;
		std::cout << "4.测试LOG" << std::endl;

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
			case 3:
			{
#define INI_COMDEF "COMDEF"
				CIni ini;
				char str[1024];
				ini.ReadString(INI_COMDEF, "com", str);
				std::cout << str << std::endl;

				ini.ReadString(INI_COMDEF, "scan", str);
				std::cout << str << std::endl;

				ini.ReadString(INI_COMDEF, "BaudRate", str);
				std::cout << str << std::endl;

				ini.ReadString(INI_COMDEF, "Parity", str);
				std::cout << str << std::endl;

				ini.ReadString(INI_COMDEF, "StopBit", str);
				std::cout << str << std::endl;

				ini.ReadString(INI_COMDEF, "ReadTimeOut", str);
				std::cout << str << std::endl;

				ini.ReadString(INI_COMDEF, "WriteTimeOut", str);
				std::cout << str << std::endl;


				ini.ReadString("PORTDEF", "01", str);
				std::cout << str << std::endl;

				ini.ReadString("PORTDEF", "03", str);
				std::cout << str << std::endl;

				ini.ReadString("PORTDEF", "05", str);
				std::cout << str << std::endl;

				ini.ReadString("PORTDEF", "68", str);
				std::cout << str << std::endl;

				ini.ReadString("LOG", "bOpen", str);
				std::cout << str << std::endl;

				ini.ReadString("DEBUG", "bOpen", str);
				std::cout << str << std::endl;

				ini.ReadString("NETDEF", "01", str);
				std::cout << str << std::endl;

				ini.ReadString("NETDEF", "68", str);
				std::cout << str << std::endl;

				int i = ini.ReadInt("DEBUG", "bOpen");
				std::cout << i << std::endl;


				i = ini.ReadInt("DEBUG", "bOpen");
				std::cout << i << std::endl;

				i = ini.ReadInt("PORTDEF", "01");
				std::cout << i << std::endl;

				i = ini.ReadInt("PORTDEF", "03");
				std::cout << i << std::endl;

				i = ini.ReadInt("PORTDEF", "06");
				std::cout << i << std::endl;

				i = ini.ReadInt("PORTDEF", "44");
				std::cout << i << std::endl;

				i = ini.ReadInt("PORTDEF", "68");
				std::cout << i << std::endl;
				break;
			}

			case 4:
			{
				CLog::Write("123");
				break;
			}
			default:
			{
				std::cout << "请输入其他值" << std::endl;
			}
		}
	}
}

int main(int argc, char * argv[])
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
