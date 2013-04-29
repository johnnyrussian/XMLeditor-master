
#include "Server.h"
int __cdecl main(void) 
{
    Server server = Server();
	server.initializeWinsock();
	server.resolveServerInfo();
	server.setupListenerSocked();
	server.acceptClientSocked();
	server.receiveData();
	server.shutdownConnection();
	system("pause");

    return 0;
}