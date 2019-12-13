#include "ma.h"

Map * next_search = NULL;

int main(){
	int number = 0;
	char ch = '\0';
	char* baseaddr = NULL;  // (char*)malloc(MAX_MEMORY);
	Map* maphead = NULL;
	int flagcontinue = 1;
	
	initiatemap(&baseaddr, &number, &maphead);
	// random_insert(maphead, &number, baseaddr);

	next_search = maphead;

	printf("==============\n");
	printf("Initial state.\n");
	printf("==============\n");
	printmap_n(maphead, number);

	while (1)
	{
		if (!flagcontinue)
			break;
		control_input(&number, &next_search, &maphead, &flagcontinue, baseaddr);
	}

	free(baseaddr);
	freeallmap(maphead, number);
	baseaddr = NULL;
	system("pause");
	return 0;
}
