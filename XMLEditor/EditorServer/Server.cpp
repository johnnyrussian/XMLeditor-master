#include "Server.h"
#include <iostream>


Server::Server(void)
{
	result = NULL;
	recvbuflen = DEFAULT_BUFLEN;
	ListenSocket = INVALID_SOCKET;
    ClientSocket = INVALID_SOCKET;
}


Server::~Server(void)
{
	closesocket(ClientSocket);
    WSACleanup();
}

void Server::initializeWinsock()
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
    
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
}

void Server::resolveServerInfo()
{
	try
	{
		if ( getaddrinfo(NULL, DEFAULT_PORT, &hints, &result) != 0 ) 
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

void Server::setupListenerSocked()
{ 
	try
	{
		ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (ListenSocket == INVALID_SOCKET) 
		{
			freeaddrinfo(result);
			throw("socket failed with error: %ld\n");
		}

		//////////////////////////////////////////////////////////////////////////////
		// Setup the TCP listening socket
		if (bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
		{
			freeaddrinfo(result);
			closesocket(ListenSocket);
			throw ("bind failed with error: %d\n");
		}

		freeaddrinfo(result);

		if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) 
		{
			closesocket(ListenSocket);
			throw ("listen failed with error: %d\n");
			
		}
	}

	catch(char *str)
	{
		std::cerr<<str<<":"<<WSAGetLastError()<<std::endl;
		WSACleanup();
	}
}

void Server::acceptClientSocked()
{
	try
	{
		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) 
		{
			throw("accept failed with error: %d\n");
		}

		closesocket(ListenSocket);
	}
	catch(char *str)
	{
		std::cerr<<str<<":"<<WSAGetLastError()<<std::endl;
		closesocket(ListenSocket);
		WSACleanup();
	}

}

void Server::receiveData()
{
	int iResult;
	try
	{
	 do {
		 iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);

        if (iResult > 0) 
		{
            printf("Bytes received: %d\n", iResult);
			Editor editor = Editor(recvbuf);
           // Echo the buffer back to the sender
            if ((iSendResult = send( ClientSocket, recvbuf, iResult, 0 )) == SOCKET_ERROR) 
			{
                throw("send failed with error: %d\n");
			}
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else 
		{
            throw("recv failed with error: %d\n");
        }

    } while (iResult > 0);
	}
	 catch(char *str)
	{
		std::cerr<<str<<":"<<WSAGetLastError()<<std::endl;
	    closesocket(ClientSocket);
        WSACleanup();
	
	}

}

void Server::shutdownConnection()
{
	try
	{
		if (shutdown(ClientSocket, SD_SEND) == SOCKET_ERROR)
		{
			throw("shutdown failed with error: %d\n");
		}
	}
	 catch(char *str)
	{
		std::cerr<<str<<":"<<WSAGetLastError()<<std::endl;
	    closesocket(ClientSocket);
        WSACleanup();
	
	}
}
 