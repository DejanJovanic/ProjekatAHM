#include "ThreadTests.h"

int main(int argc, char* argv[]) 
{
	if (argc != 2)
	{
		printf("Ne postoje argumenti komandne linije\n");
		return 0;
	}

	ManagerInitialization_initialize_manager(atoi(argv[1]));
	ThreadTests_initialize_test(1); 
	
	ThreadTests_initialize_test(2);
	
	//ThreadTests_initialize_test(5);
	
	//ThreadTests_initialize_test(10);
	
	//ThreadTests_initialize_test(20);
	
	//ThreadTests_initialize_test(50);
	ManagerInitialization_destroy_manager();

	printf("\nPritisnite bilo sta za izlazak iz programa...\n");
	getchar();


	return 0;
}