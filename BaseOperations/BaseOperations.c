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

void Base_custom_select(SOCKET s, char operation) {
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

void Base_custom_send(SOCKET s, char* niz, int broj_bajtova) {
	int iResult = 0;
	int poslato_bajtova = 0;
	
	Base_custom_select(s, 'w');
	iResult = send(s, (char*)&broj_bajtova, 4, NULL);

	do {
		Base_custom_select(s, 'w');
		iResult = send(s, niz + poslato_bajtova, broj_bajtova - poslato_bajtova, NULL);

		if (iResult == 0) {

			continue;
		}
		else if (iResult == -1) {
			printf("\nGreska!\n");
			return;
		}

		poslato_bajtova += iResult;

	} while (poslato_bajtova < broj_bajtova);

	printf("pposlao sam\n");
	getc(stdin);

	return;
}

int Base_custom_recieve(SOCKET s, char** niz) {

	int iResult = 0;
	int bytesRecieved = 0;

	char* buff = (char *)malloc(4 * sizeof(char));
	//u niz smestamo 4bajtni broj koji nam govori kolika je kolicina podataka koju treba da primimo kroz mrezu
	Base_custom_select(s, 'r');
	iResult = recv(s, buff, 4, NULL);

	//pocetnu adresu prihvatnog bafera kastujem na int* (4 bajta) i dereferenciram kako bih dobio kolicinu podatka
	int brojBajta = *((int*)buff);
	free(buff);
	*niz = (char*)malloc(brojBajta);


	do {
		Base_custom_select(s, 'r');
		iResult = recv(s, *niz + bytesRecieved, brojBajta - bytesRecieved, NULL);

		if (iResult == 0) {
			continue;
		}
		else if (iResult == -1) {
			printf("\nGreska!\n");
			break;
		}

		bytesRecieved += iResult;

	} while (bytesRecieved < brojBajta);

	return brojBajta;
}