#include <stdio.h>
#include <stdlib.h>

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
	float sum = 0.0f;
	int i;
	build_heap(a, n);
	for (i = n - 1; i >= 0; --i)
	{	
		sum += a[0];
		float_swap(&a[0], &a[i]);
		heapify(a, i, 0);
	}
	return sum;
}

int main()
{
	float a[] = {5.4f, 43.1f, 3.6f, 8.7f};
	printf("%f\n", heap_sum(a, sizeof(a) / sizeof(a[0])));
	return 0;
}
