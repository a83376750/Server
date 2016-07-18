#pragma once

enum ERRID
{
	StartSocket_ERR = 1000,
	CreateSocket_ERR,				//1001
	BindSocket_ERR,					//1002
	ListenSocket_ERR,				//1003
	AcceptSocket_ERR,				//1004
	ConnectSocket_ERR,				//1005
	RecvSocket_ERR,					//1006
	SendSocket_ERR,					//1007
};

#define PRINTFERRORINFO(ID) printf("Error ID:%d\n",ID)





