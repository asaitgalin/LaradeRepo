#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
	List list;
	list_make_empty(&list);	
	list_push_front(&list, 15);
	list_push_front(&list, 12);
	list_push_front(&list, 3);
	printf("First: %d\n", list.first->value);
	printf("Middle: %d\n", list.last->prev->value);
	printf("Last: %d\n", list.last->value);
	printf("%d\n", list_get_size(&list));
	list_clear(&list);
	return 0;	
}