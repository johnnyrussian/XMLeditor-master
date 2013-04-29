#pragma once
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <cstdio>
#include "Editor.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class Server
{
private:
	WSADATA wsaData;
	struct addrinfo *result;
    struct addrinfo hints;
	SOCKET ListenSocket;
    SOCKET ClientSocket;
    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen;
public:
	Server(void);
	~Server(void);

	void initializeWinsock ();
	void resolveServerInfo();
	void setupListenerSocked();
	void acceptClientSocked();
	void receiveData();
	void shutdownConnection();
};

