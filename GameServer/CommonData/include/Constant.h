#pragma once

enum ERRID
{
	Succee_ERR = 1000,
	StartSocket_ERR,		//1001
	CreateSocket_ERR,		//1002
	BindSocket_ERR,			//1003
	ListenSocket_ERR,		//1004
	AcceptSocket_ERR,		//1005
	ConnectSocket_ERR,		//1006
	RecvSocket_ERR,			//1007
	SendSocket_ERR,			//1008
};

#define PRINTFERRORINFO(ID) printf("Error ID:%d\n",ID)

enum CONECTTYPE
{
	TCP,
	UDP,
	OTHER
};

#define NETBUFFER 1024

struct SBaseNature
{
	long	HP;
	long	MP;
	int		STR;
};

enum EDispatchType
{
	PlayerNature,		//玩家属性
	Goods,				//商品
};