#include "BaseOperations.h"

BOOL InitializeWindowsSockets()
{
	WSADATA wsaData;
	// Initialize windows sockets library for this process
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup failed with error: %d\n", WSAGetLastError());
		return FALSE;
	}
	return TRUE;
}

void CustomSelect(SOCKET s, char operation) {
	if (operation == 'r') {
		//ovo je citanje
		do {
			FD_SET set;
			TIMEVAL timeVal;
			FD_ZERO(&set);
			FD_SET(s, &set);
			timeVal.tv_sec = 1;
			timeVal.tv_usec = 0;
			int iResult = select(0 /* ignored */, &set, NULL, NULL, &timeVal);

			if (iResult > 0)
			{
				//Sleep(200);
				break;
			}

		} while (1);
	}
	else if (operation == 'w') {
		//ovo je pisanje
		do {
			FD_SET set;
			TIMEVAL timeVal;
			FD_ZERO(&set);
			FD_SET(s, &set);
			timeVal.tv_sec = 1;
			timeVal.tv_usec = 0;

			int iResult = select(0 /* ignored */, NULL, &set, NULL, &timeVal);

			if (iResult > 0)
			{
				break;
			}
		} while (1);
	}




}

void CustomSend(SOCKET s, char* niz, int* brojBajtova) {
	int iResult = 0;
	int bytesSent = 0;
	int bytesToSend = *brojBajtova;
	CustomSelect(s, 'w');
	iResult = send(s, (char*)&bytesToSend, 4, NULL);

	do {
		CustomSelect(s, 'w');
		iResult = send(s, niz + bytesSent, *brojBajtova - bytesSent, NULL);

		if (iResult == 0) {

			continue;
		}
		else if (iResult == -1) {
			printf("\nGreska!\n");
			return;
		}

		bytesSent += iResult;

	} while (bytesSent < *brojBajtova);

	printf("pposlao sam\n");
	getc(stdin);

	return;
}

void CustomRecieve(SOCKET s, char** niz, int* brojBajta) {

	int iResult = 0;
	int bytesRecieved = 0;

	char* buff = (char *)malloc(4 * sizeof(char));
	//u niz smestamo 4bajtni broj koji nam govori kolika je kolicina podataka koju treba da primimo kroz mrezu
	CustomSelect(s, 1);
	iResult = recv(s, buff, 4, NULL);

	//pocetnu adresu prihvatnog bafera kastujem na int* (4 bajta) i dereferenciram kako bih dobio kolicinu podatka
	*brojBajta = *((int*)buff);
	free(buff);
	*niz = (char*)malloc(*brojBajta);


	do {
		CustomSelect(s, 'r');
		iResult = recv(s, *niz + bytesRecieved, *brojBajta - bytesRecieved, NULL);

		if (iResult == 0) {
			continue;
		}
		else if (iResult == -1) {
			printf("\nGreska!\n");
			break;
		}

		bytesRecieved += iResult;

	} while (bytesRecieved < *brojBajta);

	return;
}