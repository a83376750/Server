#include "Client.h"
#include "Json.h"

int main(int argc, char * argv[])
{
#ifdef DEBUG
	//if (__cplusplus < 201103L)
	//	return -1;
#endif

	Client *StartClient = new Client();
	StartClient->StartClient();

	return 0;
}