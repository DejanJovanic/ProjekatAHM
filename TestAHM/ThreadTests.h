#pragma once
#include "stdio.h"
#include "windows.h"
#include "time.h"
#include "..\Manager\ManagerInitialization.h"
#include "..\Manager\ManagerOperations.h"

DWORD WINAPI ThreadTests_custom_malloc(LPVOID lpParam);
DWORD WINAPI ThreadTests_malloc(LPVOID lpParam);
void ThreadTests_custom_malloc_initialize(int number_of_threads, int number_of_heaps);
void ThreadTests_malloc_initialize(int number_of_threads);
