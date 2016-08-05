#pragma once

#define GameC11
#define MAXTHREADCOUNT 2

//标准库头文件
#ifdef GameC11
#include <thread>
#else
#include <process.h>
#endif

#include <mutex>
#include <vector>

//自定义头文件
#include "TaskManager.h"

class ThreadPoor
{
public:
	ThreadPoor();
	~ThreadPoor();

	void InitPoor();

	void TaskPolling();
private:
	std::vector<std::thread> m_vecThread;
	std::mutex m_mutex;
	TaskManager *taskMag;
};

