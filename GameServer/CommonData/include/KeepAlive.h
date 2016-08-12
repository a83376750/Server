#pragma once
#include "Constant.h"
class KeepAlive
{
public:
	KeepAlive();
	~KeepAlive();

	
private:
#ifdef GAMECLIENT
/************************************************************************/
/* Client                                                               */
/************************************************************************/
	unsigned char	*QueryBuffer;
	float			nKeepAliveDelay;

#elif GAMESERVER
/************************************************************************/
/* Server                                                               */
/************************************************************************/
	unsigned char	*AnswerBuffer;
	float			nRecvAliveDelay;


#endif


};

