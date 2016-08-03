#pragma once
class CDispatch
{
private:
	CDispatch();

public:
	virtual ~CDispatch();
	virtual unsigned int Dis_Send(void *Target, void *Source) = 0;
	virtual unsigned int Dis_Recv(void *Target, void *Source) = 0;
};

class CServerDispatch : public CDispatch
{
public:
	virtual ~CServerDispatch();
	virtual unsigned int Dis_Send(void *Target, void *Source);
	virtual unsigned int Dis_Recv(void *Target, void *Source);

};

