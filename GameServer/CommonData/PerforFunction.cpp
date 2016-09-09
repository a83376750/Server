#include "PerforFunction.h"
#include <chrono>


const std::string GetCurrentSystemTime()
{
	auto tt = std::chrono::system_clock::to_time_t
		(std::chrono::system_clock::now());
	tm *ptm = new tm();
	localtime_s(ptm, &tt);
	char date[60] = { 0 };
	sprintf_s(date, "%d-%02d-%02d      %02d:%02d:%02d",
	(int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday,
	(int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
	delete ptm;
	return std::string(date);
}

void GetTmTimer(tm *ptm)
{
	auto tt = std::chrono::system_clock::to_time_t
	(std::chrono::system_clock::now());
	localtime_s(ptm, &tt);
	ptm->tm_year += 1900;
	ptm->tm_mon += 1;
}

