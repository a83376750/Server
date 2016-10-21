#include "Ini.h"

CIni::CIni()
	:m_sPath(INI_PATH)
{
}


CIni::~CIni()
{
}


bool CIni::WriteString(const char *sAppName, const char *sKey, const char *sValue)
{
#ifdef WIN32
	return !!WritePrivateProfileString(sAppName, sKey, sValue, m_sPath.c_str());
#else
	return true;
#endif
}

unsigned long CIni::ReadString(const char *sAppName, const char *sKey, char *sOutput, const char *sDefault)
{
#ifdef WIN32
	return GetPrivateProfileString(sAppName, sKey, sDefault, sOutput, 50, m_sPath.c_str());
#else
	return PackagingFunction(sAppName, sKey, sDefault, sOutput, 50, m_sPath.c_str());
#endif
}

long CIni::ReadInt(const char *sAppName, const char *sKey, long nDefault)
{
#ifdef WIN32
	return GetPrivateProfileInt(sAppName, sKey, nDefault, m_sPath.c_str());
#else
	char Return_Value[512];
	char sDefault[20];
	sprintf_s(sDefault, "%d", nDefault);
	PackagingFunction(sAppName, sKey, sDefault, Return_Value, sizeof(Return_Value), m_sPath.c_str());
	return atoi(Return_Value);
#endif
}

void CIni::CheckPath()
{
	if (m_sPath == "")
	{
		m_sPath = INI_PATH;
	}
}

void CIni::SetPath(const char *sPath)
{
	m_sPath = sPath;
}


#ifndef WIN32
long CIni::PackagingFunction(const char *lpAppName, const char *lpKeyName, const char *lpDefault, char *lpReturnedString, unsigned long nSize, const char *lpFileName)
{
	std::fstream fs;
	fs.open(lpFileName, std::ios::in);

	if (!fs.is_open())
	{
		std::cout << "打开文件失败:" << lpAppName << std::endl;
		return -1;
	}

	int key_len = strlen(lpKeyName);
	if (!key_len)
	{
		std::cout << "传入key值有问题" << std::endl;
		return -1;
	}
	int name_len = strlen(lpAppName);
	if (!name_len)
	{
		std::cout << "传入name值有问题" << std::endl;
		return -1;
	}

	fs.seekp(0, std::ios::beg);

	char str[512] = "";
	std::string ss;
	bool isSameApp = false;
	size_t nBeg;
	size_t nEnd;
	while (!fs.eof())
	{
		fs.getline(str, sizeof(str));
		if (str[0] == '#' || str[0] == ' ' || str == "")
			continue;

		if(!isSameApp && (str[0] == '['))
			isSameApp = false;

		//查找App
		if (!isSameApp)
		{
			ss.assign(str);
			nBeg = ss.find_first_of('[');
			if (nBeg == std::string::npos)
				continue;

			nEnd = ss.find_first_of(']');
			if (nEnd == std::string::npos)
				continue;

			std::string sub = ss.substr(nBeg + 1, nEnd - nBeg - 1);
			if (strcmp(sub.c_str(), lpAppName))
				continue;

			fs.getline(str, sizeof(str));
			isSameApp = true;
		}
		//查找Key
		ss.assign(str);
		size_t eq = ss.find_first_of('=');
		if (eq == std::string::npos)
			continue;

		nBeg = ss.find(lpKeyName);
		if (nBeg == std::string::npos || nBeg > eq)
			continue;

		for (size_t i = nBeg + strlen(lpKeyName); i < ss.size(); ++i)
		{
			if (ss[i] != ' ' || ss[i] != '=')
			{
				strcpy_s(lpReturnedString, nSize, ss.substr(i + 1, ss.size() - i).c_str());
				return strlen(lpReturnedString);
			}
		}
	}

	if (lpDefault == nullptr)
		return -1;
	return strlen(lpDefault);
}
#endif