#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "../DataSerialization/DataSerializationOperations.h"
#include "../BaseOperations/BaseOperations.h"
#include "../DataCollections/List.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 2
#define DEFAULT_PORT "27016"


int  main(void)
{
	/*
	pak* head = NULL;
	pak* tail = NULL;
	char* c[10];
	for (int i = 0; i < 10; i++) {
		c[i] = (char *)malloc(2* sizeof(char));
		c[i][0] = ('0' + i);
		c[i][1] = 0;
		Push(&head, &tail, 2, c[i]);
	}
	
	pak p = Pop(&head, &tail);
	printf(p.data);
	*/
	
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET acceptedSocket = INVALID_SOCKET;
    int iResult;
    
	pak* head = NULL;
	pak* tail = NULL;

	char* recievedData;
	int brojBajtova = 0;

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

	do
	{
		CustomSelect(listenSocket, 1);
        acceptedSocket = accept(listenSocket, NULL, NULL);

        if (acceptedSocket == INVALID_SOCKET)
        {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        do
        {
			CustomSelect(acceptedSocket, 'r');
            brojBajtova = CustomRecieve(acceptedSocket, &recievedData);

			Deserialize(&head, &tail, recievedData, brojBajtova);
			Data_print_list(head);

        } while (iResult > 0);

		Sleep(2000);
    } while (1);

    iResult = shutdown(acceptedSocket, SD_SEND);
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