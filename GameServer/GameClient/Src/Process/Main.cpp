#include "Client.h"
#include "Constant.h"



int main(int argc, char * argv[])
{
// 	if (__cplusplus < 201103L)
// 		return -1;
	Client *StartClient = new Client();
	StartClient->StartClient();

	return 0;
}