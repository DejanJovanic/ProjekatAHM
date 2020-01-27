#pragma once
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

BOOL InitializeWindowsSockets();
void CustomSelect(SOCKET s, char operation);
void CustomSend(SOCKET s, char* niz, int brojBajtova);
int CustomRecieve(SOCKET s, char** niz);