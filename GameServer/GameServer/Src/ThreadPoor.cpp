#include "ThreadPoor.h"

ThreadPoor::ThreadPoor()
{
	taskMag = new TaskManager();
	InitPoor();
}


ThreadPoor::~ThreadPoor()
{
	int thCount = MAXTHREADCOUNT;
	for (std::thread &thr : m_vecThread)
	{
		thr.detach();
		thCount--;
	}
	std::cout << "线程数:" << thCount << std::endl;

	delete taskMag;
}

void ThreadPoor::InitPoor()
{
	for (int i = 0; i < MAXTHREADCOUNT;++i)
		m_vecThread.emplace_back(&ThreadPoor::TaskPolling, this);
}

void ThreadPoor::TaskPolling()
{
	ServerTask *pTask = nullptr;
	while (1)
	{
		pTask = taskMag->popTask();
		if (pTask)
		{
			pTask->StartTask();
		}
		else
		{
			std::cout << "睡眠一下" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(5));
		}
	}
}
