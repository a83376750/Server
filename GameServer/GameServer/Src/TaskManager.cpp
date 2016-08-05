#include "TaskManager.h"

/************************************************************************/
/* TaskManager                                                          */
/************************************************************************/
TaskManager::TaskManager()
{
}


TaskManager::~TaskManager()
{
	while (!listTask.empty())
	{
		auto iter = listTask.begin();
		if (iter != listTask.end())
		{
			delete *iter;
			listTask.erase(iter);
		}
	}
}

void TaskManager::pushTask(ServerTask *task)
{
	if (!task)
		listTask.push_back(task);
}

//��������Ż�,��Ϊ�������߼�����̫��,�ظ�������ɾ��̫��Ч,������г�ʼ��,��ʵ��
ServerTask* TaskManager::popTask()
{
	int TaskCount = GetTastCount();
	//std::cout << "��ǰ�������:" << TaskCount << std::endl;
	if (TaskCount <= 0)
	{
		return nullptr;
	}
	else
	{
		ServerTask* task = listTask.front();
		listTask.pop_front();
		return task;
	}
}

int TaskManager::GetTastCount() const
{
	return listTask.size();
}

/************************************************************************/
/* ServerManager                                                        */
/************************************************************************/
void ServerTask::StartTask()
{
	std::cout << "Default Task Output!!!!" << std::endl;
}


/************************************************************************/
/* CharTask                                                             */
/************************************************************************/
void CharTask::StartTask()
{
	std::cout << "BeforeNum:" << testNum << std::endl;
	setNum();
}

void CharTask::setNum()
{
	testNum = rand()%100;
	std::cout << "SetNum log:" << testNum << std::endl;
}
