#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <conio.h>
#include <windows.h>
#include <winsock2.h>

#include "../DataSerialization/DataSerializationOperations.h"
#include "../BaseOperations/BaseOperations.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 2
#define DEFAULT_PORT 27016

void AddToList(pak** head, pak** tail, int num, struct Packet* next) {

	pak *p = (pak*)malloc(sizeof(pak));
	p->data = num;
	p->next = NULL;

	if (*head == NULL) {
		*head = *tail = p;
		return;
	}

	(*tail)->next = p;
	*tail = p;
}

void PrintList(pak* head) {

	while (head != NULL) {
		printf("%d\t", head->data);
		head = head->next;
	}

}

int __cdecl main(int argc, char **argv)
{
	zpak* serializedList;
	pak* head = NULL;
	pak* tail = NULL;
	// 100 000 000 / 4 = 25 000 000
	int counter = 0;
	do {
		AddToList(&head, &tail, counter, NULL);
	} while (++counter < 25000000);


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

	Serialize(head, &serializedList, counter);

	int velicinaPaketa = sizeof(*serializedList)*counter;
	CustomSelect(connectSocket, 'w');
	CustomSend(connectSocket, (char*)serializedList, &velicinaPaketa);

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