#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <cstdio>
#include <string>



// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class Client
{

private:
	WSADATA wsaData;
	SOCKET ConnectSocket;
	struct addrinfo *result,
                    *ptr,
                    hints;
	char *server_adress;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen;
	

public:
	
	char* getSendbuf();
	char *sendbuf;
	void setSendbuf(const char *_sendbuf);
	void initializeWinsock ();
	void getServerInfo(char *server_adress);
	void connectServer();
	void sendBuffer();
	void receiveData();

	Client(void);
	~Client(void);
};

