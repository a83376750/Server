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
#else

#endif
	class CIni
	{
	public:
		CIni();
		~CIni();
		void Init();
		bool WriteString(const char *sAppName, const char *sKey, const char *sValue);
		unsigned long ReadString(const char * sAppName, const char * sKey, char *sOutput, const char * sDefault = "");
		long ReadInt(const char * sAppName, const char * sKey, long nDefault = 0);
		void CheckPath();
		void SetPath(const char *sPath);
	private:
		std::string m_sPath;
	};

#ifdef WIN32

#else
	bool WritePrivateProfileString(const char *sAppName, const char *sKey, const char *sValue, const char *sDefault);

	unsigned long GetPrivateProfileString(const char *lpAppName, const char *lpKeyName, const char *lpDefault,
		char *lpReturnedString, unsigned long nSize, const char *lpFileName);

	long GetPrivateProfileInt(const char *lpAppName, const char *lpKeyName, int nDefault, const char *lpFileName);

	long PackagingFunction(const char *lpAppName, const char *lpKeyName, const char *lpDefault,
		char *lpReturnedString, unsigned long nSize, const char *lpFileName);

#endif