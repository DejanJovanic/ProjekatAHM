#include "Thread5Test.h"
int b = 0;
CRITICAL_SECTION mutex;

void StartTest5()
{

	clock_t start_time, end_time;
	double cpu_time_used;
	ManagerInitialization_initialize_manager(5); //5 je broj hipova
	InitializeCriticalSection(&mutex);
	DWORD ids[5];
	HANDLE threads[5];
	start_time = clock();
	for (int i = 0; i < 5; i++) {

		threads[i] = CreateThread(NULL, 0, &Test5, NULL, 0, &ids[i]);
	}

	int temp = 0;

	while (1)
	{
		EnterCriticalSection(&mutex);
		temp = b;

		LeaveCriticalSection(&mutex);
		if (temp == 5)
			break;
	}
	
	end_time = clock();
	b = 0;
	temp = 0;
	cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\n Time for allocate and free with 5 threads  in seconds %f\n", cpu_time_used);
	for (int i = 0; i < 5; i++) {

		CloseHandle(threads[i]);
	}
	ManagerInitialization_destroy_manager();
	DeleteCriticalSection(&mutex);
	/*start_time = clock();
	for (int i = 0; i < 5; i++) {

		threads[i] = CreateThread(NULL, 0, &Test5Malloc, NULL, 0, &ids[i]);
	}

	while (1)
	{
		EnterCriticalSection(&mutex);
		temp = b;

		LeaveCriticalSection(&mutex);
		if (temp == 5)
			break;
	}
	end_time = clock();

	cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\n Time for allocate and free with 5 threads with MALLOC in seconds %f\n", cpu_time_used);*/
}
DWORD WINAPI Test5(LPVOID lpParam) {


	void* items[10000];

	
	for (int i = 0; i < 10000; i++) {
		
		items[i] = thread_malloc(80000);
	}

	for (int i = 0; i < 10000; i++) {
		if (items[i] != NULL)
			thread_free(items[i]);
	}

	EnterCriticalSection(&mutex);
	b++;
	LeaveCriticalSection(&mutex);
	return 0;

}

/*DWORD WINAPI Test5Malloc(LPVOID lpParam)
{
	void* items[10000];


	for (int i = 0; i < 10000; i++) {
		items[i] = malloc(80000);
	}

	for (int i = 0; i < 10000; i++) {
		free(items[i]);
	}

	EnterCriticalSection(&mutex);
	b++;
	LeaveCriticalSection(&mutex);
	return 0;
}*/