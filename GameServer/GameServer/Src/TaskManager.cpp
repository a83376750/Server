#include "TaskManager.h"
#include "Server.h"
#include "Json.h"

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
	if (task)
		listTask.push_back(task);
}

//这里可以优化,因为服务器逻辑不会太多,重复创建和删除太低效,建议进行初始化,待实现
ServerTask* TaskManager::popTask()
{
	int TaskCount = GetTastCount();
	//std::cout << "当前任务个数:" << TaskCount << std::endl;
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
/* ServerTask															*/
/************************************************************************/
ServerTask::ServerTask()
{
	
}

ServerTask::~ServerTask()
{

}


void ServerTask::StartTask()
{
	std::cout << "Default Task Output!!!!" << std::endl;
}

/************************************************************************/
/* CharTask                                                             */
/************************************************************************/
CharTask::CharTask()
{
	testNum = 0;
}

CharTask::~CharTask()
{

}


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

/************************************************************************/
/* RecvSendTask                                                           */
/************************************************************************/
RecvTask::RecvTask(Server *ptrServer)
	:m_pServer(ptrServer)
{

}

RecvTask::~RecvTask()
{
}

void RecvTask::StartTask()
{
	char buffer[NETBUFFER];
	while (m_pServer)
	{
		m_pServer->RecvBuffer(buffer);
		BufferStream ss;
		if (ss.InitDocument(buffer))
		{
			int value = ERROR;
			ss.ReadInt("Page", value);
			switch (value)
			{
				case PageType::TASK:
				{
					ss.PrintJsonString();

					break;
				}
				case PageType::HEAD:
				{
					ss.PrintJsonString();
					BufferStream re;
					re.Write("Page", "2");
					break;
				}
				default:
				{
					std::cout << "错误包" << std::endl;
					break;
				}
			}
		}
		else
		{
			std::cout << "不是jsonstring" << std::endl;
			std::cout << (char*)buffer << std::endl;
		}
	}
}

/************************************************************************/
/* JsonParse                                                            */
/************************************************************************/
JsonParse::JsonParse(Server *ptrServer)
{
	m_pServer = ptrServer;
}

JsonParse::~JsonParse()
{

}

void JsonParse::StartTask()
{
	BufferStream ss;
	ss.WriteArray("arr", 3, 1, 2, 3);
	std::cout << ss.GetJsonString() << std::endl;
	m_pServer->WriteBuffer((void*)ss.GetJsonString(), 1024);
}
