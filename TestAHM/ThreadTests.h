#pragma once
#include "stdio.h"
#include "windows.h"
#include "time.h"
#include "..\AdvancedHeapManager\ManagerInitialization.h"
#include "..\AdvancedHeapManager\ManagerOperations.h"

DWORD WINAPI ThreadTests_custom_malloc(LPVOID lpParam);
DWORD WINAPI ThreadTests_malloc(LPVOID lpParam);
void ThreadTests_custom_malloc_initialize(int number_of_threads);
void ThreadTests_malloc_initialize(int number_of_threads);
