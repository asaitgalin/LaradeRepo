#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
	List list;
	list_make_empty(&list);
	list_push_back(&list, 15);
	list_push_back(&list, 12);
	printf("%d\n", list_get_size(&list));
	list_clear(&list);
	return 0;
}