#pragma once
#include <list>
#include <iostream>

/************************************************************************/
/* TaskManager                                                          */
/************************************************************************/
class ServerTask;
class Server;

class TaskManager
{
public:
	TaskManager();
	~TaskManager();
public:


	void pushTask(ServerTask *task);
	ServerTask* popTask();

	int GetTastCount()const;
private:
	//先进先出
	std::list<ServerTask*> listTask;
};


/************************************************************************/
/* ServerTask                                                           */
/************************************************************************/
class ServerTask
{
public:
	ServerTask();
	virtual ~ServerTask();

	virtual void StartTask() = 0;

	enum PageType
	{
		TASK,
		HEAD,
	};
};

/************************************************************************/
/* CharTask                                                             */
/************************************************************************/
class CharTask : public ServerTask
{
public:
	CharTask();
	virtual ~CharTask();
	virtual void StartTask() override;
	void setNum();
private:
	int testNum;
};

/************************************************************************/
/* RecvSendTask                                                           */
/************************************************************************/
class RecvTask : public ServerTask
{
public:
	RecvTask(Server *ptrServer);
	virtual ~RecvTask();
	virtual void StartTask();

private:
	Server *m_pServer;
};
