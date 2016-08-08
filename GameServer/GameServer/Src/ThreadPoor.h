#pragma once

#define GameC11
#define MAXTHREADCOUNT 2

//��׼��ͷ�ļ�
#ifdef GameC11
#include <thread>
#include <condition_variable>
#include <mutex>
#else
#include <process.h>
#endif


#include <vector>

//�Զ���ͷ�ļ�
#include "TaskManager.h"

class ThreadPoor
{
public:
	ThreadPoor();
	~ThreadPoor();

	//��ʼ���̳߳�
	void InitPoor();

	//����ִ�к���
	void TaskPolling();

	//�����ͽ���
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

