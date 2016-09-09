#include "Log.h"
#include <iostream>
#include "Ini.h"

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
#ifdef WIN32

	if (!IsOpenLog())
		return;
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	char fileName[50];
	sprintf_s(fileName, "%s%4d %02d %02d", FILE_NAME, sys.wYear, sys.wMonth, sys.wDay);
	os.open(fileName, std::ios::out|std::ios::app);
	if (!os.is_open())
	{
		if (CreateDirectory(".\\log", NULL))
		{
			Init();
			return;
		}
		std::cout << "CLog file can not open!!" << std::endl;
	}

#else
#endif
}


void CLog::Write(const char *str)
{
#ifdef WIN32
	Init();
	if (!os.is_open())
	{
		return ;
	}
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	os << "\n" << "[" << sys.wYear << "/" << sys.wMonth << "/" << sys.wDay
		<< " " << sys.wHour << ":" << sys.wMinute << ":" << sys.wSecond << "]"
		<< " - " << str << std::endl;
	os.close();

#else
#endif
}


void CLog::WriteUc(void *str, int len)
{
#ifdef WIN32
	Init();
	if (!os.is_open())
	{
		return;
	}
	unsigned char *ucStr = (unsigned char*)str;
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	os << "\n" << "[" << sys.wYear << "/" << sys.wMonth << "/" << sys.wDay
		<< " " << sys.wHour << ":" << sys.wMinute << ":" << sys.wSecond << "]";
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

#else
#endif
}

bool CLog::IsOpenLog()
{
#ifdef WIN32
	CIni ini;
	LONG flag = ini.ReadInt("LOG", "bOpen");
	return !!flag;
#else
	return true;
#endif
}
