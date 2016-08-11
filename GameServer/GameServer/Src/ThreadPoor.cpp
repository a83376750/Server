#include "ThreadPoor.h"
#include <assert.h>

ThreadPoor::ThreadPoor()
{
	std::cout << "线程池开启" << std::endl;
	InitPoor();
}


ThreadPoor::~ThreadPoor()
{
	std::cout << "线程数:" << m_nThreadCount << std::endl;
	m_flag = ThreadFlag::END;
	NotifyAllThread();
	while (m_nThreadCount)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "主线程等待子线程结束!" << std::endl;
		std::cout << "当前还有线程数:" << m_nThreadCount << std::endl;
	}
	std::cout << "线程池关闭" << std::endl;
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
		m_vecThread.push_back(std::move(th));	//减少vector的对象复制
		m_nThreadCount++;
	}
}

//子线程入口
void ThreadPoor::TaskPolling()
{
	ServerTask *pTask = nullptr;
	while (CheckCurentlyFlag() == RUNNING)
	{
		std::cout << "线程号:" << std::this_thread::get_id()<< "---";
		pTask = popTask();
		if (pTask)
		{
			std::cout << "线程执行任务中" << std::endl;
			pTask->StartTask();
		}
		else
		{
			std::cout << "线程睡眠" << std::endl;
			std::unique_lock<std::mutex> lock(m_mutex);
			m_cv.wait(lock, [&]() { return taskMag.GetTastCount() || CheckCurentlyFlag() ? true:false; } );
// 			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
	}
	Lock();
	m_nThreadCount--;
	UnLock();
	std::cout<< "线程号:" << std::this_thread::get_id() << "---" << "该线程关闭"<< std::endl;
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

//主线程执行,不需要锁
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
