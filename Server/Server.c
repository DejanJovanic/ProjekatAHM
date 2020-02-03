#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../DataSerialization/DataSerializationOperations.h"
#include "../BaseOperations/BaseOperations.h"
#include "../DataCollections/Message.h"
#include "../AdvancedHeapManager/ManagerInitialization.h"
#include "../AdvancedHeapManager/ManagerOperations.h"

#pragma warning (disable:4996)
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_PORT "27016"
#define CLIENTS_NO 10
DWORD WINAPI listen_thread_function(LPVOID lpParam);

int  main(void)
{
    SOCKET listen_socket = INVALID_SOCKET;
    SOCKET accepted_socket = INVALID_SOCKET;
	int result;

    if(Base_initialize_windows_sockets() == FALSE)
    {
		return 1;
    }
    
	ADDRINFO *resulting_address = NULL;
	ADDRINFO hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4 address
    hints.ai_socktype = SOCK_STREAM; // Provide reliable data streaming
    hints.ai_protocol = IPPROTO_TCP; // Use TCP protocol
    hints.ai_flags = AI_PASSIVE;     // 

	result = getaddrinfo(NULL, DEFAULT_PORT, &hints, &resulting_address);
    if (result != 0 )
    {
        printf("getaddrinfo failed with error: %d\n", result);
        WSACleanup();
        return 1;
    }

	listen_socket = socket(AF_INET,      // IPv4 address famly
                          SOCK_STREAM,  // stream socket
                          IPPROTO_TCP); // TCP

    if (listen_socket == INVALID_SOCKET)
    {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(resulting_address);
        WSACleanup();
        return 1;
    }

	result = bind(listen_socket, resulting_address->ai_addr, (int)resulting_address->ai_addrlen);
    if (result == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(resulting_address);
        closesocket(listen_socket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(resulting_address);

	result = listen(listen_socket, SOMAXCONN);
    if (result == SOCKET_ERROR)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(listen_socket);
        WSACleanup();
        return 1;
    }

	printf("Server initialized, waiting for clients.\n");
	DWORD id;
	HANDLE listen_thread = CreateThread(NULL, 0, &listen_thread_function, &listen_socket, 0, &id);
	
	printf("Press any key to stop server.\n\n");
	getchar();
	
	CloseHandle(listen_thread);

	result = shutdown(listen_socket, SD_SEND);
    if (result == SOCKET_ERROR)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(accepted_socket);
        WSACleanup();
        return 1;
    }

    closesocket(listen_socket);
    closesocket(accepted_socket);
    WSACleanup();

    return 0;
}

DWORD WINAPI listen_thread_function(LPVOID param)
{

	char* message;
	int length = 0;
	SOCKET listen_socket = *((SOCKET*)(param));
	unsigned long mode = 1;
	int result = ioctlsocket(listen_socket, FIONBIO, &mode);
	if (result != NO_ERROR)
	{
		printf("ioctlsocket za listen failed with error: %ld\n", result);
	}
	result = listen(listen_socket, SOMAXCONN);

	SOCKET client_sockets[CLIENTS_NO];

	int counter = 0;

	while (1)
	{
		if (counter != CLIENTS_NO)
		{
			Base_custom_select(listen_socket, 'r');
		}
		else
			return 0;

		struct sockaddr_in client_addr;
		int client_addr_size = sizeof(struct sockaddr_in);
		client_sockets[counter] = accept(listen_socket, (struct sockaddr *)&client_addr, &client_addr_size);

		if (client_sockets[counter] == INVALID_SOCKET)
		{
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(listen_socket);
			WSACleanup();
			return 1;
		}
		else
		{
			if (ioctlsocket(client_sockets[counter], FIONBIO, &mode) != 0)
			{
				printf("ioctlsocket failed with error.");
				continue;
			}
			printf("New client request accepted (%d). Client address: %s : %d\n", counter, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			
			Base_custom_select(client_sockets[counter], 'r');
			int bytes_recieved = Base_custom_recieve(client_sockets[counter], &message);
			//printf("Primio od klijenta: %s\n", message);

			ManagerInitialization_initialize_manager(5);
			clock_t start_time, end_time;
			double cpu_time_used;
			start_time = clock();

			char* message_for_advanced_malloc = advanced_malloc(bytes_recieved);
			advanced_free(message_for_advanced_malloc);

			end_time = clock();
			cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

			printf("Vreme potrebno za zauzimanje %d bajtova advanced malloc i free je : %f\n", bytes_recieved, cpu_time_used);

			free(message);


			ManagerInitialization_destroy_manager();
			//counter++;
			//vracanje poruke nasumicne duzine
			length = Data_generate_message(&message, counter + 10);
			Base_custom_select(client_sockets[counter], 'w');
			Base_custom_send(client_sockets[counter], message, length);
			//printf("Saljem na klijenta: %s\n\n", message);
			free(message);
			counter++;
		}
	}

}