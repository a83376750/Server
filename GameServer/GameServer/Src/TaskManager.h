#pragma once
#include <list>
#include <iostream>

/************************************************************************/
/* TaskManager                                                          */
/************************************************************************/
class ServerTask;
class TaskManager
{
public:
	TaskManager();
	~TaskManager();

	void pushTask(ServerTask *task);
	ServerTask* popTask();

	int GetTastCount()const;
private:
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
	virtual void StartTask();

	void setNum();
private:
	int testNum;
};