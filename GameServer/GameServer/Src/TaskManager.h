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
class RecvSendTask : public ServerTask
{
public:
	RecvSendTask(Server *ptrServer);
	virtual ~RecvSendTask();
	virtual void StartTask();

private:
	Server *m_pServer;
};
