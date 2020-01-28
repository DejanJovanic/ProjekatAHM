#pragma once
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

BOOL InitializeWindowsSockets();
/**
*	Base_custom_select() - Osluskuje da li je moguce slanje ili primanje podataka
*
*	s			: soket za konekciju
*	operation	: operacija koja se slusa, r - read, w - write
**/
void Base_custom_select(SOCKET s, char operation);
/**
*	Base_custom_send() - Salje poruku nasumicne duzine
*
*	s			: soket za konekciju
*	niz			: niz sa sadrzajem poruke
*	broj_bajtova: duzina poruke
**/
void Base_custom_send(SOCKET s, char* niz, int brojBajtova);
/**
*	Base_custom_recieve() - Prima poruku nasumicne duzine
*
*	s	: soket za konekciju
*	niz	: adresa niza u koji cemo smestiti podatke
**/
int Base_custom_recieve(SOCKET s, char** niz);