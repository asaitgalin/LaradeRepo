#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "utils.h"

void read_int_array(int *a, int n)
{
	int i;
	for (i = 0; i < n; ++i)
		scanf("%d", &a[i]);
}

void print_int_array(const int *a, int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%d ", a[i]);
	printf("\n");
}

void fill_random(int *a, int n)
{
	int x, i, j;
	unsigned char *p = (unsigned char *)&x;
	srand(time(NULL));
	for (i = 0; i < n; ++i)
	{	
		for (j = 0; j < sizeof(x); ++j)
			p[j] = rand() % 256;
		a[i] = x;
	}
}

int is_sorted(const int *a, int n)
{
	int i;
	for (i = 0; i < n - 1; ++i)
		if (a[i] > a[i + 1])
			return 0;
	return 1;
}

// mode = 1: 0, 1, 2, 3, ..., n - 1
// mode = 2: n - 1, n - 2, n - 3, ..., 0
// mode = 3: random
// mode = 4: reads array from input

int *get_int_array(int n, int mode)
{
	int i;
	int *a = (int *)calloc(n, sizeof(int));
	if (!a)
		return NULL;
	switch(mode)
	{
	case 1:
		for (i = 0; i < n; ++i)
			a[i] = i;
		break;
	case 2:
		for (i = n - 1; i >= 0; --i)
			a[n - i - 1] = i;
		break;
	case 3:
		fill_random(a, n);
		break;
	case 4:
		read_int_array(a, n);
		break;
	}
	return a;
}
