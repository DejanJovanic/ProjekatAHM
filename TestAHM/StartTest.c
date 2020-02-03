#include "ThreadTests.h"

int main(int argc, char* argv[]) 
{
	if (argc != 2)
	{
		printf("Ne postoje argumenti komandne linije\n");
		return 0;
	}
	ManagerInitialization_initialize_manager(atoi(argv[1]));
	

	ThreadTests_custom_malloc_initialize(1);
	ThreadTests_custom_malloc_initialize(2);
	ThreadTests_custom_malloc_initialize(5);
	ThreadTests_custom_malloc_initialize(10);
	ThreadTests_custom_malloc_initialize(20);
	ThreadTests_custom_malloc_initialize(50);
	ManagerInitialization_destroy_manager();
	/*ThreadTests_malloc_initialize(1);
	ThreadTests_malloc_initialize(2);
	ThreadTests_malloc_initialize(5);
	ThreadTests_malloc_initialize(10);
	ThreadTests_malloc_initialize(20);
	ThreadTests_malloc_initialize(50);*/


	printf("\nPritisnite bilo sta za izlazak iz programa...\n");
	getchar();


	return 0;
}