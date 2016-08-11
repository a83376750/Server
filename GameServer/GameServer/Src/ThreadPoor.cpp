#include "ThreadPoor.h"
#include <assert.h>

ThreadPoor::ThreadPoor()
{
	std::cout << "�̳߳ؿ���" << std::endl;
	InitPoor();
}


ThreadPoor::~ThreadPoor()
{
	std::cout << "�߳���:" << m_nThreadCount << std::endl;
	m_flag = ThreadFlag::END;
	NotifyAllThread();
	while (m_nThreadCount)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "���̵߳ȴ����߳̽���!" << std::endl;
		std::cout << "��ǰ�����߳���:" << m_nThreadCount << std::endl;
	}
	std::cout << "�̳߳عر�" << std::endl;
}

void ThreadPoor::InitPoor()
{
#ifdef DEBUG
	assert(std::thread::hardware_concurrency() < MAXTHREADCOUNT);
#endif // DEBUG

	m_flag = ThreadFlag::RUNNING;
	m_nThreadCount = 0;
	for (int i = 0; i < MAXTHREADCOUNT; ++i)
	{
		std::thread th(&ThreadPoor::TaskPolling, this);
		th.detach();
		m_vecThread.push_back(std::move(th));	//����vector�Ķ�����
		m_nThreadCount++;
	}
}

//���߳����
void ThreadPoor::TaskPolling()
{
	ServerTask *pTask = nullptr;
	while (CheckCurentlyFlag() == RUNNING)
	{
		std::cout << "�̺߳�:" << std::this_thread::get_id()<< "---";
		pTask = popTask();
		if (pTask)
		{
			std::cout << "�߳�ִ��������" << std::endl;
			pTask->StartTask();
		}
		else
		{
			std::cout << "�߳�˯��" << std::endl;
			std::unique_lock<std::mutex> lock(m_mutex);
			m_cv.wait(lock, [&]() { return taskMag.GetTastCount() || CheckCurentlyFlag() ? true:false; } );
// 			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
	}
	Lock();
	m_nThreadCount--;
	UnLock();
	std::cout<< "�̺߳�:" << std::this_thread::get_id() << "---" << "���̹߳ر�"<< std::endl;
	return;
}

bool ThreadPoor::Lock()
{
	while (!m_mutex.try_lock());
	return true;
}

void ThreadPoor::UnLock()
{
	m_mutex.unlock();
}

//���߳�ִ��,����Ҫ��
void ThreadPoor::pushTask(ServerTask *task, bool AtOnceRun)
{
	taskMag.pushTask(task);
	if(taskMag.GetTastCount() && AtOnceRun)
		NotifyAllThread();
}

ServerTask* ThreadPoor::popTask()
{
	Lock();
	ServerTask *pTask = taskMag.popTask();
	UnLock();
	return pTask;
}

const ThreadPoor::ThreadFlag& ThreadPoor::CheckCurentlyFlag()
{
	return m_flag;
}

void ThreadPoor::NotifyAllThread()
{
	m_cv.notify_all();
}
