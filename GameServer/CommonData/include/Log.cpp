#include "Log.h"
#include "Ini.h"
#include "PerforFunction.h"
#include <iostream>
#include <thread>

//跨平台宏
#ifdef WIN32
#include <direct.h>
#include <io.h>
#define MKDIR(x) _mkdir(x)
#elif _LINUX
#include <stdarg.h>
#include <sys/stat.h>
#define MKDIR(x) mkdir(x, S_IRWXU)
#endif

#ifdef WIN32
#include <windows.h>
#else
#endif

std::ofstream CLog::os;
CLog::CLog()
{
	Init();
}

CLog::~CLog()
{
	if(IsOpenLog())
		os.close();
}

void CLog::Init()
{
	if (!IsOpenLog())
		return;
	tm sys;
	GetTmTimer(&sys);
	char fileName[50];
	sprintf_s(fileName, "%s%4d-%02d-%02d.txt", FILE_NAME, sys.tm_year, sys.tm_mon, sys.tm_mday);
	os.open(fileName, std::ios::out|std::ios::app);
	if (!os.is_open())
	{
		if (!MKDIR(".\\log"))
		{
			Init();
			return;
		}
		std::cout << "CLog file can not open!!" << std::endl;
	}
}


void CLog::Write(const char *str)
{
	Init();
	if (!os.is_open())
	{
		return ;
	}
	tm sys;
	GetTmTimer(&sys);
	os << "\n" << "[" << sys.tm_year << "/" << sys.tm_mon << "/" << sys.tm_mday
		<< " " << sys.tm_hour << ":" << sys.tm_min << ":" << sys.tm_sec << "]"
		<< " - " << "{线程ID:" << std::this_thread::get_id() << "}" << str << std::endl;
	os.close();
}


void CLog::Write(const char *str, size_t len)
{
	char *sLog = new char[len + 1];
	memcpy(sLog, str, len);
	sLog[strlen(sLog)] = '\0';
	CLog::Write(sLog);
}

void CLog::WriteUc(void *str, int len)
{
	Init();
	if (!os.is_open())
	{
		return;
	}
	unsigned char *ucStr = (unsigned char*)str;
	tm sys;
	GetTmTimer(&sys);
	os << "\n" << "[" << sys.tm_year << "/" << sys.tm_mon << "/" << sys.tm_mday
		<< " " << sys.tm_hour << ":" << sys.tm_min << ":" << sys.tm_sec << "]" << "{线程ID:" << std::this_thread::get_id() << "}"
		<< "输出buffer:";

	char cStr[6];
	for (int i = 0; i < len; ++i)
	{
		if (i % 10 == 0)
			os << std::endl;
		sprintf_s(cStr, "%02x ", ucStr[i]);
		os << cStr;
	}
	os << std::endl;
	os.close();
}

bool CLog::IsOpenLog()
{
	CIni ini;
	int flag = ini.ReadInt("LOG", "bOpen");
	return !!flag;
}
