#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000

typedef unsigned long long ulong;

const float ideal = 1.6449340668482264f;

void float_swap(float *a, float *b)
{
	float t = *a;
	*a = *b;
	*b = t;
}

void heapify(float *a, int n, int i)
{
	int l = 2 * i + 1, r = 2 * i + 2;
	int j;
	while(r < n)
	{
		if (a[i] <= a[l] && a[i] <= a[r])
			break;
		if (a[l] < a[r])
			j = l;
		else
			j = r;
		if (a[i] > a[j])
		{
			float_swap(&a[i], &a[j]);
			i = j;
		}
		l = 2 * i + 1;
		r = 2 * i + 2;
	}
	if (l == n - 1 && a[i] > a[l])
		float_swap(&a[i], &a[l]);
}

void build_heap(float *a, int n)
{
	int i;
	for (i = (n - 1) / 2; i >= 0; --i)
		heapify(a, n, i);
}

float heap_sum(float *a, int n)
{
	float x, y;
	int i;
	build_heap(a, n);
	for (i = n - 1; i > 0; --i)
	{	
		x = a[0];
		float_swap(&a[0], &a[i]);
		heapify(a, i, 0);
		y = a[0];
		a[0] = x + y;
		heapify(a, n, i);
	}
	return *a;
}

float direct_sum(const float *a, int n)
{
	int i;
	float sum = 0.0f;
	for (i = 0; i < n; ++i)
		sum += a[i];
	return sum;
}

float reverse_sum(const float *a, int n)
{
	int i;
	float sum = 0.0f;
	for (i = n - 1; i >= 0; i--)
		sum += a[i];
	return sum;
}

void fill_mixed(float *a, int n)
{
	int i;
	// even
	for (i = 0; i < n; i += 2)
		a[i] = (float)1 / ((ulong)(n - i) * (n - i));
	// odd
	for (i = 0; i < n; i += 2)
		a[i + 1] = (float)1 / ((ulong)(i + 1) * (i + 1));
}

int main()
{
	float *a = NULL;
	float dsum, rsum, hsum;
	a = (float *)malloc(MAX_N * sizeof(float));
	if (!a)
		return -1;
	fill_mixed(a, MAX_N);
	dsum = direct_sum(a, MAX_N);
	rsum = reverse_sum(a, MAX_N);
	hsum = heap_sum(a, MAX_N);
	printf("Direct: %.5e\n", ideal - dsum);
	printf("Reverse: %.5e\n", ideal - rsum);
	printf("Heap: %.5e\n\n", ideal - hsum);
	printf("Direct Value: %.10f\n", dsum);
	printf("Reverse Value: %.10f\n", rsum);
	printf("Heap Value: %.10f\n", hsum);
	free(a);
	return 0;
}