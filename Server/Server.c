#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "../DataSerialization/DataSerializationOperations.h"
#include "../BaseOperations/BaseOperations.h"
#include "../DataCollections/Message.h"

#pragma warning (disable:4996)
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_PORT "27016"
#define CLIENTS_NO 10
DWORD WINAPI listenThreadFunction(LPVOID lpParam);

int  main(void)
{
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET acceptedSocket = INVALID_SOCKET;
	int iResult;

    if(InitializeWindowsSockets() == FALSE)
    {
		return 1;
    }
    
	ADDRINFO *resultingAddress = NULL;
	ADDRINFO hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4 address
    hints.ai_socktype = SOCK_STREAM; // Provide reliable data streaming
    hints.ai_protocol = IPPROTO_TCP; // Use TCP protocol
    hints.ai_flags = AI_PASSIVE;     // 

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &resultingAddress);
    if ( iResult != 0 )
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    listenSocket = socket(AF_INET,      // IPv4 address famly
                          SOCK_STREAM,  // stream socket
                          IPPROTO_TCP); // TCP

    if (listenSocket == INVALID_SOCKET)
    {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(resultingAddress);
        WSACleanup();
        return 1;
    }

    iResult = bind( listenSocket, resultingAddress->ai_addr, (int)resultingAddress->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(resultingAddress);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(resultingAddress);

    iResult = listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

	printf("Server initialized, waiting for clients.\n");
	DWORD id;
	HANDLE listenThread = CreateThread(NULL, 0, &listenThreadFunction, &listenSocket, 0, &id);
	
	printf("Press any key to stop server.\n\n");
	getchar();
	//getchar();
	

    iResult = shutdown(listenSocket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(acceptedSocket);
        WSACleanup();
        return 1;
    }

    closesocket(listenSocket);
    closesocket(acceptedSocket);
    WSACleanup();

    return 0;
}

DWORD WINAPI listenThreadFunction(LPVOID lpParam)
{

	char* message;
	int length = 0;
	SOCKET listenSocket = *((SOCKET*)(lpParam));
	unsigned long mode = 1;
	int iResult = ioctlsocket(listenSocket, FIONBIO, &mode);
	if (iResult != NO_ERROR)
	{
		printf("ioctlsocket za listen failed with error: %ld\n", iResult);
	}
	iResult = listen(listenSocket, SOMAXCONN);

	SOCKET clientSockets[CLIENTS_NO];

	int counter = 0;

	while (1)
	{
		if (counter != CLIENTS_NO)
		{
			Base_custom_select(listenSocket, 'r');
		}
		else
			return 0;

		struct sockaddr_in clientAddr;
		int clientAddrSize = sizeof(struct sockaddr_in);
		clientSockets[counter] = accept(listenSocket, (struct sockaddr *)&clientAddr, &clientAddrSize);

		if (clientSockets[counter] == INVALID_SOCKET)
		{
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(listenSocket);
			WSACleanup();
			return 1;
		}
		else
		{
			if (ioctlsocket(clientSockets[counter], FIONBIO, &mode) != 0)
			{
				printf("ioctlsocket failed with error.");
				continue;
			}
			printf("New client request accepted (%d). Client address: %s : %d\n", counter, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
			
			Base_custom_select(clientSockets[counter], 'r');
			Base_custom_recieve(clientSockets[counter], &message);
			printf("Primio od klijenta: %s\n", message);
			free(message);
			//counter++;
			//vracanje poruke nasumicne duzine
			length = Data_generate_message(&message, counter+10);
			Base_custom_select(clientSockets[counter], 'w');
			Base_custom_send(clientSockets[counter], message, length);
			printf("Saljem na klijenta: %s\n\n", message);
			free(message);
			counter++;
		}
	}

}