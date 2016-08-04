#pragma once

#define GameC11
#define MAXTHREADCOUNT 24

#ifdef GameC11
#include <thread>
#else
#include <process.h>
#endif

#include <mutex>
#include <vector>

class ThreadPoor
{
public:
	ThreadPoor();
	~ThreadPoor();

	void InitPoor();
private:
	std::vector<std::thread*> m_vecThread;
	std::mutex m_mutex;
};

