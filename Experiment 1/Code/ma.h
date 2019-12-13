#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_MEMORY 1000

struct map{
	unsigned m_size;
	char* m_addr;
	struct map *next, *prior;
};

typedef struct map Map;

/*
** to initiate the empty memory link
** input: 
**     baseaddr: ptr to the base address of memeory
**     number: the number of maps of memory link
** output:
**     head: ptr to the first map of empty memory link
*/
void initiatemap(char** baseaddr, int *number, Map** maphead)
{
	*baseaddr = (char*)malloc(MAX_MEMORY);
	if (*baseaddr != NULL)
	{
		printf("The base address of memory is: %p\t.\n", *baseaddr);
	}
	else {
		printf("malloc failed!\n");
		exit(1);
	}
	*maphead = (Map*)malloc(sizeof(Map));
	if (*maphead == NULL)
		printf("Error");
	(*maphead)->m_addr = *baseaddr;
	(*maphead)->m_size = 1000;
	(*maphead)->next = *maphead;
	(*maphead)->prior = *maphead;
	(*number)++;
};

/*
** to initiate the memory space with 4 maps, structure is shown below
** 128(empty) || 22(occupied) || 256(empty) || 44(occupied) || \
   128(empty) || 22(ocupied) || 128(empty) || 272(occupied)
** input: 
**     baseaddr: ptr to the base address of memeory
**     number: the number of maps of memory link
** output:
**     head: ptr to the first map of empty memory link
*/
void random_insert(Map* head, int *number, char* baseaddr)
{
	// Map *new_m1 = (Map*)malloc(sizeof(Map));
	Map *new_m2 = (Map*)malloc(sizeof(Map));
	Map *new_m3 = (Map*)malloc(sizeof(Map));
	Map *new_m4 = (Map*)malloc(sizeof(Map));

	head->m_size = 128;
	head->m_addr = baseaddr;
	head->next = new_m2;
	head->prior = new_m4;

	//new_m1->m_size = 128;
	//new_m1->m_addr = baseaddr;
	//new_m1->next = new_m2;
	//new_m1->prior = new_m4;
	// head = new_m1;
	// (*number)++;

	new_m2->m_size = 256;
	new_m2->m_addr = (char*)(baseaddr + 150);
	new_m2->next = new_m3;
	new_m2->prior = head;
	(*number)++;

	new_m3->m_size = 128;
	new_m3->m_addr = (char*)(baseaddr + 450);
	new_m3->next = new_m4;
	new_m3->prior = new_m2;
	(*number)++;

	new_m4->m_size = 128;
	new_m4->m_addr = (char*)(baseaddr + 600);
	new_m4->next = head;
	new_m4->prior = new_m3;
	(*number)++;

	// return new_m1;
};

/*
** print a map in the empty memory link
** input:
**     para: ptr to the map to be printed
** output: None
*/
void printmap(Map *para)
{
	printf("------------------------------------------------------------\n");
	printf("The message about this map of link is shown as follows.\n");
	printf("The size is :\t%d.\n", para->m_size);
	printf("The beginning address is:\t%p.\n", para->m_addr);
	printf("The next map is:\t%p.\n", (para->next)->m_addr);
	printf("The prior map is:\t%p.\n", (para->prior)->m_addr);
	printf("------------------------------------------------------------\n");
};

/*
** print all maps in the empty memory link
** input:
**     head: ptr to the first map of empty memory link;
**     number: the number of maps in the empty memory link
** output: None
*/
void printmap_n(Map *head, int number)
{
	for (int i = 0; i < number; i++)
	{
		printmap(head);
		head = head->next;
	}
};

/*
** remove a map from the empty memory link
** input:
**     p: previous map of the map will be removed;
**     c: the map to be removed;
**     n: the next map of the map will be removed;
** output: None
*/
void remove_map(Map *p, Map *c, Map *n)
{
	p->next = n;
	n->prior = p;
	free(c);
};

/*
** find the map that has lowest address
** input:
**     begin: the current head of empty memory link
**     number: the number of maps in the empty memory link
** output: 
**	   ptr: the map should be the head of empty memory link
*/
Map* findthelowest(Map* begin, int number)
{
	Map* ptr = begin;
	for (int i = 0; i < number; ++i)
	{
		if (ptr->m_addr > begin->m_addr)
			ptr = begin;
		begin = begin->next;
	}
	return ptr;
};

/*
** allocate the memory according to the empty memory link
** input:
**     size: the size of the memory to be allocated;
**     number: the total number of maps in the empty memory link;
**     search: ptr to the ptr to the Map that searching begins
** output: None
*/
void lmalloc(unsigned size, int * number, Map **search)
{
	int flag = 0;
	Map *head = *search;
	// Map *target = (Map *)malloc(sizeof(Map));
	do
	{
		if ((*search)->m_size > size)
		{
			flag = 1;
			(*search)->m_size -= size;
			(*search)->m_addr = (char*)((*search)->m_addr + size);
			(*search) = (*search)->next;
			// target->prior = (*e_map)->prior;
			// target->next = NULL;
			break;
		}
		else
		{
			if ((*search)->m_size == size)
			{
				flag = 1;
				(*number)--;
				if (*number)
				{
					Map* tmp = (*search)->next;
					remove_map((*search)->prior, (*search), (*search)->next);
					(*search) = tmp;
				}
				break;
			}
			else
				continue;
		}
	} while ((*search) = (*search)->next, (*search)->next != head);

	if (flag)
	{
		if (!(*number))
		{
			printf("*********************************************\n");
			printf("All memory has been alloced.\n");
			printf("*********************************************\n");
			(*search) = NULL;
		}
		else {
			head = findthelowest(*search, *number);
			printmap_n(head, *number);
		}
	}
	else
	{
		(*search) = head;
		printf("*********************************************\n");
		printf("Can't find enough memory space to alloc.\n");
		printf("*********************************************\n");
	}
	printf("The alloc address next searching is: %p.\n", (*search)->m_addr);
};

/*
** insert a new map to the empty memory link between `lower` and `upper`
** input:
**     anew: the new map to be inserted
**     lower: the previous map of the new map
**     upper: the next map of the new map
** output: None
*/
void insertmap(Map* anew, Map* lower, Map* upper)
{
	lower->next = anew;
	anew->prior = lower;
	anew->next = upper;
	upper->prior = anew;
};

// input maybe not the beginning address of a map
/*
** free an allocated memory according to the command
** input:
**     size: the size of memory needed to free;
**     addr: beginning address of map;
**     head: ptr to the ptr to the first map of empty memory link;
**     number: the number of maps in the empyt memory link;
**     baseaddr: the beginning address of whole memory space;
** output: result of free
**     1: success;
**     0: fail;
 */
int lfree(unsigned size, char * addr, Map** head, int *number, const char* baseaddr)
{		
	char * freebegin = addr;
	char * freeend = (char *)(addr + size);
	Map * ptr = *head;
	// upper :the next empty map
	Map* upper = NULL;
	// lower : the previous empty map
	Map* lower = NULL;
	if (freeend > (baseaddr + MAX_MEMORY))
		return 0;
	if (freebegin < (baseaddr))
		return 0;
	if ((*head) != NULL)
	{
		do
		{
			if ((ptr->m_addr + ptr->m_size) <= freebegin)
			{
				lower = ptr;
			}
			if ((ptr->m_addr >= freeend) && upper == NULL)
			{
				upper = ptr;
			}
		} while (ptr = ptr->next, ptr != (*head));
		if (upper == NULL && lower == NULL)
			return 0;
	}
	else
	{
		Map * new_map = (Map*)malloc(sizeof(Map));
		new_map->m_addr = freebegin;
		new_map->m_size = size;
		new_map->next = new_map;
		new_map->prior = new_map;
		*head = new_map;
		return 1;
	}

	// test the size is correct or not
	if (lower != NULL || upper != NULL)
	{
		if ( lower != NULL && ( ((lower->next)->m_addr < freebegin) && (lower->m_addr + lower->m_size) > freebegin ) )
			return 0;
		if (lower == NULL && (((*head)->m_addr < freebegin) && ((*head)->m_addr + (*head)->m_size > freebegin)))
			return 0;
		if ((upper != NULL) && ( ((upper->prior)->m_addr < freeend) && ((upper->prior)->m_addr + ((upper->prior)->m_size) > freeend) ) )
			return 0;
		if ((upper == NULL) && ((((*head)->prior)->m_addr < freeend) && (((*head)->prior)->m_addr + ((*head)->prior)->m_size > freeend)))
			return 0;
	}

	if ( (lower != NULL) && ((lower->m_addr + lower->m_size) == freebegin) )
	{
		/* empty || free || empty */
		if ( (upper != NULL) && ((upper->next)->m_addr == freeend) )
		{
			lower->m_size += size;
			(*number)--;
			if ((*number) > 1)
				remove_map(lower, upper, upper->next);
			else
			{
				printf("*********************************************\n");
				printf("The size of memory is 1000 now.\n");
				printf("*********************************************\n");
			}
		}
		/* empty || free || allocation || empty(or end) */
		else
		{
			lower->m_size += size;
		}
	}
	/* empty (or begin) || allocation || free || ... */
	else
	{
		/* empty (or begin) || allocation || free || empty */
		if ( (upper != NULL) && (upper->m_addr == freeend) )
		{
			upper->m_addr = freebegin;
			upper->m_size += size;
		}
		/* empty (or begin) || allocation || free || allocation || empty(or end) */
		else
		{
			Map * new_map = (Map*)malloc(sizeof(Map));
			new_map->m_addr = freebegin;
			new_map->m_size = size;

			/* empty (or begin) || allocation || free || allocation || empty */
			if (upper != NULL)
			{
				insertmap(new_map, upper->prior, upper);
				(*number)++;
			}
			/* empty (or begin) || allocation || free || allocation (end) */
			else
			{
				if (lower != NULL)
				{
					insertmap(new_map, lower, lower->next);
					(*number)++;
				}
			}
		}
	}
	// changeheader(head, *number);
	(*head) = findthelowest(*head, *number);
	return 1;
};

/*
** free the Map variables in the empty memory link
** input:
**     head: the first map of the empty memory link
**     number: the total number of maps in the empty memory link
** output: None
*/
void freeallmap(Map *head, int number)
{
	Map* ptr = head;
	for (int i = 0; i < number; i++)
	{
		ptr = head->next;
		free(head);
		printf("Having free the %d th map.\n", i + 1);
		head = ptr;
	}
};

/*
** switch the execute function accroding to the parameters input by the user
** input:
**     number: the total number of maps in the empty memory link
**     search: the ptr to the Map that searching begins
**     head: the ptr to the first map of empty memory link
**     tocontinue: flag to record the quit operation
**     baseaddr: the beginning address of whole memory space 
** output: None
*/
void control_input(int* number, Map** search, Map** head, int* tocontinue, const char* baseaddr)
{
	printf("**************************************************************\n");
	printf("Please input the character to execute the memory allocation.\n");
	printf("Input 'Q' / 'q' to quit.\n");
	printf("'M' / 'm' for executing malloc\t 'F' / 'f' for executing free.\n");
	printf("**************************************************************\n");
	char ch = '\0';
	char para = '\0';
	scanf("%c", &para);
	while ((ch = getchar()) != EOF && ch != '\n')
		;
	int size = 0, offset = 0;
	char* ptr = NULL;
	switch (para)
	{
	case 'm' :case 'M':
		printf("---------------------------------------\n");
		printf("Please input the size to be allocated.\n");
		printf("NOTE: the size should be a integar.\n");
		printf("---------------------------------------\n");
		scanf("%d", &size);
		while ((ch = getchar()) != EOF && ch != '\n')
			;
		if (size <= 0)
		{	
			// *tocontinue = 0;
			printf("==============================\n");
			printf("The size should be positive.\n");
			printf("==============================\n");
			return;
		}
		lmalloc(size, number, search);
		// printf("Now the search begins from: %p\n", search->m_addr);
		break;
	case 'f' : case 'F':
		printf("------------------------------------------------------------------------------\n");
		printf("Please specify the address of memory to be freed.\n");
		// printf("NOTE: the address should be in HEX.\n");
		printf("NOTE: input the relative address(aka offset, which ranges in [0, 1000]) is OK.\n");
		printf("------------------------------------------------------------------------------\n");
		scanf("%d", &offset);
		while ((ch = getchar()) != EOF && ch != '\n')
			;
		if (offset < 0)
		{
			printf("==============================\n");
			printf("The offset should be positive.\n");
			printf("==============================\n");
			// *tocontinue = 0;
			return;
		}
		ptr = (char*)(baseaddr + offset);
		// scanf("%p", &ptr);
		printf("---------------------------------------\n");
		printf("Please input the size of freed memory.\n");
		printf("NOTE: the size should be a integar.\n");
		printf("---------------------------------------\n");
		scanf("%d", &size);
		while ((ch = getchar()) != EOF && ch != '\n')
			;
		if (size <= 0 )
		{
			printf("==============================\n");
			printf("The size should be positive.\n");
			printf("==============================\n");
			//  *tocontinue = 0;
			return;
		}
		if(lfree(size, ptr, head, number, baseaddr))
		{
			printf("==============\n");
			printf("Free succeeded!\n");
			printf("==============\n");
			printmap_n(*head, *number);
		}
		else
		{
			printf("=====================================\n");
			printf("Free failed!\nPlease re-enter the size and address!\n");
			printf("=====================================\n");
		}
		break;
	case 'q': case 'Q':
		//while ((ch = getchar()) != EOF && ch != '\n')
		//	;
		*tocontinue = 0;
		break;
	default:
		printf("==================================\n");
		printf("Please enter the correct key word!\n");
		printf("==================================\n");
	};
};
