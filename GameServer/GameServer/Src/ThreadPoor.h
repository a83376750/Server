#pragma once

#define GameC11
#define MAXTHREADCOUNT 2

//标准库头文件
#ifdef GameC11
#include <thread>
#include <condition_variable>
#include <mutex>
#else
#include <process.h>
#endif


#include <vector>

//自定义头文件
#include "TaskManager.h"

class ThreadPoor
{
public:
	ThreadPoor();
	~ThreadPoor();

	//初始化线程池
	void InitPoor();

	//任务执行函数
	void TaskPolling();

	//加锁和解锁
	bool Lock();
	void UnLock();

	void pushTask(ServerTask *task);
	ServerTask* popTask();
private:
	std::vector<std::thread> m_vecThread;
	TaskManager *taskMag;
	std::mutex m_mutex;
public:
	std::condition_variable m_cv;

};

