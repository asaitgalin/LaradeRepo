#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#include "utils.h"

int main()
{
	/*float a[] = {4.2f, 1.0f, 23.2f, 1.4f, 7.4f, 9.6f};
	float sum = heap_sum(a, sizeof(a) / sizeof(a[0]));
	printf("%f\n", sum);*/
	int n;
	int *a;
	clock_t after, before;
	scanf("%d", &n);
	while (n > 0)
	{
			a = get_int_array(n, 3);
			before = clock();
			quick_sort(a, n);
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