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
	enum ThreadFlag{ RUNNING, END };

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

	//ѹ��,��������
	void pushTask(ServerTask *task, bool AtOnceRun = true);
	ServerTask* popTask();

	//����˳���־
	const ThreadFlag& CheckCurentlyFlag();

	void NotifyAllThread();
private:
	std::vector<std::thread> m_vecThread;
	TaskManager taskMag;
	std::mutex m_mutex;

	//std::shared_ptr<TaskManager> ptrTask;

	ThreadFlag m_flag;	//��־�߳�״̬,���߳̾����Ƿ��˳�,�����̹߳ر�
	std::condition_variable m_cv;

	unsigned int m_nThreadCount;
public:

};

