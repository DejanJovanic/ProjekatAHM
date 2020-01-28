#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>

#include "../DataSerialization/DataSerializationOperations.h"
#include "../BaseOperations/BaseOperations.h"
#include "../DataCollections/Message.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 2
#define DEFAULT_PORT 27016




int __cdecl main(int argc, char **argv)
{
	zpak* serializedList;
	pak* head = NULL;
	pak* tail = NULL;

	char* message;
	int length = 0;
	
	


	SOCKET connectSocket = INVALID_SOCKET;
	int iResult;

	if (argc != 2)
	{
		printf("usage: %s server-name\n", argv[0]);
		return 1;
	}

	if (InitializeWindowsSockets() == FALSE)
	{
		return 1;
	}

	connectSocket = socket(AF_INET,
		SOCK_STREAM,
		IPPROTO_TCP);

	if (connectSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	SOCKADDR_IN serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(argv[1]);
	serverAddress.sin_port = htons(DEFAULT_PORT);

	if (connect(connectSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
	{
		printf("Unable to connect to server.\n");
		closesocket(connectSocket);
		WSACleanup();
	}

	unsigned long int nonBlockingMode = 1;
	iResult = ioctlsocket(connectSocket, FIONBIO, &nonBlockingMode);


	length = Data_generate_message(&message);

	Base_custom_select(connectSocket, 'w');
	Base_custom_send(connectSocket, message, length);

	free(message);
	do {

		Base_custom_select(connectSocket, 'r');
		length = Base_custom_recieve(connectSocket, &message);
		printf("%s\n", message);
	} while (length < 1);



	//Serialize(head, &serializedList, counter * 7);

	//int velicinaPaketa = sizeof(*serializedList)*counter;
	//
	//CustomSend(connectSocket, (char*)serializedList, velicinaPaketa);

	if (iResult == SOCKET_ERROR)
	{
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(connectSocket);
		WSACleanup();
		return 1;
	}

	printf("Bytes Sent: %ld\n", iResult);

	closesocket(connectSocket);
	WSACleanup();

	return 0;
}