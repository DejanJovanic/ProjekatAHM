#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "conio.h"


#include "../DataSerialization/DataSerializationOperations.h"
#include "../BaseOperations/BaseOperations.h"
#include "../DataCollections/Message.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define SERVER_IP_ADDRESS "127.0.0.1"
#define SERVER_PORT 27016
#define CLIENTS_NO 10
//HANDLE hSemaphores[CLIENTS_NO];
DWORD WINAPI clientThread(LPVOID lpParam);
CRITICAL_SECTION cs;

int main()
{

	if (InitializeWindowsSockets() == FALSE)
	{
		return 1;
	}


	/*for (int i = 0; i < CLIENTS_NO; i++)
	{
		
			hSemaphores[i] = CreateSemaphore(0, 0, 1, NULL);
	}*/
	InitializeCriticalSection(&cs);
	DWORD ids[CLIENTS_NO];
	HANDLE threads[CLIENTS_NO];


	for (int i = 0; i < CLIENTS_NO; i++)
	{
		threads[i] = CreateThread(NULL, 0, &clientThread, (LPVOID)i, 0, &ids[i]);
		//WaitForSingleObject(hSemaphores[i], INFINITE);
	}


	getchar();
	/*for (int i = 0; i < CLIENTS_NO; i++)
	{
		CloseHandle(hSemaphores[i]);
	}*/
	for (int i = 0; i < CLIENTS_NO; i++)
	{
		CloseHandle(threads[i]);
	}
	DeleteCriticalSection(&cs);

	
	// Deinitialize WSA library
	WSACleanup();
	
	return 0;


}

DWORD WINAPI clientThread(LPVOID lpParam)
{
	EnterCriticalSection(&cs);
	
	int n = (int)lpParam;
	if (InitializeWindowsSockets() == FALSE)
	{
		return 1;
	}
	

	printf("\nClient NO: %d\n", n);
	
	
	SOCKET connectSocket = INVALID_SOCKET;
	int iResult;
	char* message;
	int length = 0;

	connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (connectSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	struct sockaddr_in serverAddress;
	

	serverAddress.sin_family = AF_INET;								// IPv4 protocol
	serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);	// ip address of server
	serverAddress.sin_port = htons(SERVER_PORT);

	if (connect(connectSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
	{
		printf("Unable to connect to server.\n");
		closesocket(connectSocket);
		WSACleanup();
	}

	unsigned long int nonBlockingMode = 1;
	iResult = ioctlsocket(connectSocket, FIONBIO, &nonBlockingMode);

	

	length = Data_generate_message(&message, n+20);
	Base_custom_select(connectSocket, 'w');
	Base_custom_send(connectSocket, message, length);
	printf("Saljem na server: %s\n", message);
	free(message);
	
	Base_custom_select(connectSocket, 'r');
	length = Base_custom_recieve(connectSocket, &message);
	
	printf("Primio od servera: %s\n", message);
	
	free(message);
	//LeaveCriticalSection(&cs);
	iResult = shutdown(connectSocket, SD_BOTH);

	// Check if connection is succesfully shut down.
	if (iResult == SOCKET_ERROR)
	{
		printf("Shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(connectSocket);
		WSACleanup();
		return 1;
	}

	closesocket(connectSocket);
	LeaveCriticalSection(&cs);
	//ReleaseSemaphore(hSemaphores[(n + 1) % CLIENTS_NO-1], 1, NULL);
	return 0;
}