#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#include "utils.h"

int compare(const void *a, const void *b)
{
	int num1 = *(int *)a;
	int num2 = *(int *)b;
	if (num1 > num2)
		return 1;
	else if (num2 > num1)
		return -1;
	else 
		return 0;
}

int main()
{
	int n;
	int *a;
	clock_t after, before;
	scanf("%d", &n);
	while (n > 0)
	{
			a = get_int_array(n, 3);
			before = clock();
			qisort(a, n, sizeof(int), compare); 
			after = clock();
			//print_int_array(a, n);
			if (is_sorted(a, n))
				printf("Time elapsed: %.1f\n", (float)(after - before) / CLOCKS_PER_SEC);
			else
				printf("ERROR: Not sorted!\n");
			free(a);
			scanf("%d", &n);
	}
	return 0;
}