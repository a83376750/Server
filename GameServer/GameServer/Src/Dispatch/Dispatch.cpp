#include "Dispatch.h"



CDispatch::CDispatch()
{
}


CDispatch::~CDispatch()
{
}


CServerDispatch::~CServerDispatch()
{

}

unsigned int CServerDispatch::Dis_Send(void *Target, void *Source)
{
	return 0;
}

unsigned int CServerDispatch::Dis_Recv(void *Target, void *Source)
{
	return 0;
}
