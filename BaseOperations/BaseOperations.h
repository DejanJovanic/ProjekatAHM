#pragma once
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

BOOL InitializeWindowsSockets();
void CustomSelect(SOCKET s, char operation);
void CustomRecieve(SOCKET s, char** niz, int* brojBajta);