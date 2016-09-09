#pragma once

#define FILE_NAME ".\\log\\"

#include <fstream>

class CLog
{
public:
	CLog();
	~CLog();
	static void Init();
	static void Write(const char *str);
	static void WriteUc(void *str, int len);
private:
	static bool IsOpenLog();
	static std::ofstream os;
};

