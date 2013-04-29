#define WIN32_LEAN_AND_MEAN

#include "Client.h"
#include "string"
#include "iostream"




int __cdecl main(int argc, char **argv) 
{

		
		    printf("enter command, please ... format command <tag_name> <tag_value>\n");
			char* s = "localhost";
			
			std::string query;
			std::getline (std::cin, query);
			std::cout<<query<<"\n";
			Client *client = new Client();
			client->initializeWinsock ();
			client->getServerInfo(s);
			client->connectServer();
			client->setSendbuf(query.c_str());
			client->sendBuffer();
			client->receiveData();
			
	
	
    return 0;

}