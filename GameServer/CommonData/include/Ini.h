#pragma once

#define INI_PATH "./Sand.ini"
#include <string>
#include <iostream>
#include <fstream>
/*
WritePrivateProfileString, 
GetPrivateProfileString, 
GetPrivateProfileInt
*/
#ifdef WIN32
#include <windows.h>
#endif
	class CIni
	{
	public:
		CIni();
		~CIni();
		//写配置,暂时没有用
		bool WriteString(const char *sAppName, const char *sKey, const char *sValue);

		unsigned long ReadString(const char * sAppName, const char * sKey, char *sOutput, const char * sDefault = "");
		long ReadInt(const char * sAppName, const char * sKey, long nDefault = 0);
		void CheckPath();
		void SetPath(const char *sPath);
	private:
		//默认地址 ./Sand.ini
		std::string m_sPath;
		
	public:	
#ifndef WIN32
		long PackagingFunction(const char *lpAppName, const char *lpKeyName, const char *lpDefault,
			char *lpReturnedString, unsigned long nSize, const char *lpFileName);
#endif
	};

