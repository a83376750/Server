#include "ThreadPoor.h"

ThreadPoor::ThreadPoor()
{
	InitPoor();
}


ThreadPoor::~ThreadPoor()
{
	std::cout << "�߳���:" << m_nThreadCount << std::endl;
	delete taskMag;
}

void ThreadPoor::InitPoor()
{
	taskMag = new TaskManager();
	m_nThreadCount = 0;
	for (int i = 0; i < MAXTHREADCOUNT; ++i)
	{
		m_vecThread.emplace_back(&ThreadPoor::TaskPolling, this);
		m_nThreadCount++;
	}
	m_flag = ThreadFlag::RUNNING;
}

void ThreadPoor::TaskPolling()
{
	ServerTask *pTask = nullptr;
	while (1)
	{
		std::cout << "��ǰ�̺߳�:" << std::this_thread::get_id() << std::endl;
		pTask = popTask();
		if (pTask)
		{
			pTask->StartTask();
		}
		else
		{
			std::cout << "˯��һ��" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(5));
		}
	}
	
}

bool ThreadPoor::Lock()
{
	return m_mutex.try_lock();
}

void ThreadPoor::UnLock()
{
	m_mutex.unlock();
}

void ThreadPoor::pushTask(ServerTask *task)
{
	Lock();
	taskMag->pushTask(task);
	UnLock();
}

ServerTask* ThreadPoor::popTask()
{
	Lock();
	ServerTask *pTask = taskMag->popTask();
	UnLock();
	return pTask;
}
