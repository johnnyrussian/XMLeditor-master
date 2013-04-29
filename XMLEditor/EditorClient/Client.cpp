#include "Client.h"
#include <iostream>

Client::Client(void)
{
	result = NULL;
	ptr = NULL;
	ConnectSocket = INVALID_SOCKET;
	recvbuflen = DEFAULT_BUFLEN;
}


Client::~Client(void)
{

	closesocket(ConnectSocket);
    WSACleanup();
}

char *Client::getSendbuf()
{
	return sendbuf;
}

void Client::setSendbuf(const char *_sendbuf)
{
	memcpy(&sendbuf, &_sendbuf, std::strlen(_sendbuf));
	
}

void Client::initializeWinsock()
{
	try
	{
		if ((WSAStartup(MAKEWORD(2,2), &wsaData)!=0))
		{
			throw ("WSAStartup failed with error: %d\n");
		}
    }  
	catch (char *str)
	{
		std::cerr<<str<<":"<<WSAGetLastError()<<std::endl;
		
	}
    
	ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
}

void Client::getServerInfo(char *server_adress)
{
	try
	{
		if ( getaddrinfo(server_adress, DEFAULT_PORT, &hints, &result) != 0 ) 
		{
			throw ("getaddrinfo failed with error: %d\n");
		}
        
	}
	catch (char *str)
	{
		std::cerr<<str<<":"<<WSAGetLastError()<<std::endl; ///which error?
		WSACleanup();
		
	}
}

void Client::connectServer()
{
	try
		{
			// Attempt to connect to an address until one succeeds
			for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) 
			{
				// Create a SOCKET for connecting to server
				ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
				ptr->ai_protocol);
				if (ConnectSocket == INVALID_SOCKET) 
				{
					throw ("socket failed with error: %ld\n");
					
				}

				if (connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen) == SOCKET_ERROR) 
				{
					closesocket(ConnectSocket);
					ConnectSocket = INVALID_SOCKET;
					continue;
				}
			break;
		}
	
		freeaddrinfo(result);

		if (ConnectSocket == INVALID_SOCKET)
		{
			throw ("Unable to connect to server!\n");
		}

		}
    catch(char *str)
	{
		std::cerr<<str<<":"<<WSAGetLastError()<<std::endl;
		WSACleanup();
	}
}

void Client::sendBuffer()
{
	try
	{
		int iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );
		if (iResult == SOCKET_ERROR) 
		{
			throw ("send failed with error: %d\n");
		}
		
		printf("Bytes Sent: %ld\n", iResult);

		// shutdown the connection since no more data will be sent
		 
		if (shutdown(ConnectSocket, SD_SEND) == SOCKET_ERROR)
		{
	    throw("shutdown failed with error: %d\n", WSAGetLastError());
		}
	}
    catch(char *str)
	{
		std::cerr<<str<<":"<<WSAGetLastError()<<std::endl;
		closesocket(ConnectSocket);
		WSACleanup();
	}

}

void Client::receiveData()
{
	int iResult = 0;
	    do {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 )
            printf("Bytes received: %d\n", iResult);
        else if ( iResult == 0 )
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while( iResult > 0 );
	system("pause");
}