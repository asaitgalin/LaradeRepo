#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"
#include "sort.h"

void insertion_sort(int *a, int n)
{
	int i, j;
	for (i = 1; i < n; ++i)
		for (j = i; j > 0 && a[j - 1] > a[j]; --j)
			SWAP(a[j - 1], a[j]); 
}

int get_pivot(int n)
{
	int x, i;
	unsigned char *p = (unsigned char *)&x;
	srand(time(0));
	for (i = 0; i < sizeof(int); ++i)
		p[i] = rand() % 256;
	if (x < 0)
		x = -x;
	return (x % n);
}

void quick_sort(int *a, int n)
{
	int l, r, p;
loop:
	if (n <= 1) 
		return;
	if (n < 7)
	{
		insertion_sort(a, n);
		return;
	}
	l = 0; r = n - 1;
	p = a[get_pivot(n)];
	while (l <= r) 
	{
		while(a[l] < p)
			++l;
		while(a[r] > p)
			--r;
		if (l <= r) 
		{
			if (l < r) 
				SWAP(a[l], a[r]);
			++l;
			--r;
		}
	}
	if ((r + 1) < (n - l))
	{ 
		quick_sort(a, r + 1);
		a += l;
		n -= l;  
	}
	else
	{
		quick_sort(a + l, n - l);
		n = r + 1;
	}
	goto loop; 
}

void merge(int *a, int len_a, int *b, int len_b, int *c)
{
	int i = 0, j = 0, k = 0;
	while (i < len_a && j < len_b)
		c[k++] = a[i] < b[j] ? a[i++] : b[j++]; 
	while (i < len_a)
	{
		c[k++] = a[i];
		++i;
	}
	while (j < len_b)
	{
		c[k++] = b[j];
		++j;
	}
}

void do_merge_sort(int *a, int n, int *c)
{
	int m = n / 2;
	if (n > 1)
	{
		do_merge_sort(c, m, a);
		do_merge_sort(c + m, n - m, a + m);
		merge(c, m, c + m, n - m, a);
	}
}

void merge_sort(int *a, int n)
{
	int *c = (int *)malloc(n * sizeof(int));
	if (!c)
		return;
	memcpy(c, a, n * sizeof(int));
	do_merge_sort(a, n, c);
	free(c);
}

// Heap sort
int is_max_heap(const int *a, int n)
{	
	int i;
	for (i = 1; i < n; ++i)
		if (a[(i - 1) / 2] < a[i])
			return 0;
	return 1;	
}

void max_sift_up(int *a, int i)
{
	int k = (i - 1) / 2;
	while(a[i] > a[k])
	{
		SWAP(a[i], a[k]);
		i = k;
		k = (i - 1) / 2;
	}
}

void max_sift_down(int *a, int n, int i)
{
	int l = 2 * i + 1, r = 2 * i + 2;
	int j;
	while(r < n)
	{
		if (a[i] >= a[l] && a[i] >= a[r])
			break;
		if (a[l] > a[r])
			j = l;
		else
			j = r;
		if (a[i] < a[j])
		{
			SWAP(a[i], a[j]);
			i = j;
		}
		l = 2 * i + 1;
		r = 2 * i + 2;
	}
	if (l == n - 1 && a[i] < a[l])
		SWAP(a[i], a[l]);
}

void heapify_max(int *a, int n)
{
	int i;
	for (i = 0; i < n; ++i)
		max_sift_up(a, i);
}

void heap_sort(int *a, int n)
{
	int i;
	heapify_max(a, n);
	for (i = n - 1; i > 0; --i)
	{
		SWAP(a[0], a[i]);
		max_sift_down(a, i, 0);
	}
}

// Heap sum
void float_swap(float *a, float *b)
{
	float t = *a;
	*a = *b;
	*b = t;
}

void min_sift_up(float *a, int i)
{
	int k = (i - 1) / 2;
	while(a[i] < a[k])
	{
		float_swap(&a[i], &a[k]);
		i = k;
		k = (i - 1) / 2;
	}
}

void heapify_min(float *a, int n)
{
	int i;
	for (i = 0; i < n; ++i)
		min_sift_up(a, i);
}

float heap_sum(float *a, int n)
{
	float sum = 0.0f;
	int i = 0;
	int l = 2 * i + 1, r = 2 * i + 2;
	heapify_min(a, n);
	sum += a[0];
	while (r < n)
	{
		sum += (a[l] < a[r]) ? a[l] : a[r];
		sum += (a[l] < a[r]) ? a[r] : a[l];
		++i;
		l = 2 * i + 1;
		r = 2 * i + 2;
	}
	if (l == n - 1)
		sum += a[l];
	return sum;
}



