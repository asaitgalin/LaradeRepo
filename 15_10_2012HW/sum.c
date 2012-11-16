#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ulong;

const float ideal = 1.6449340668482264f;

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

float kahan_sum(const float *a, int n)
{
	int i;
	float sum = 0.0f;
	float c = 0.0f;
	float y, t;
    for (i = 0; i < n; ++i)
	{ 
		y = a[i] - c;   
		t = sum + y;      
        c = (t - sum) - y;  
        sum = t;
	}
    return sum;
}

void fill_direct(float *a, int n)
{
	int i;
	for (i = 1; i <= n; ++i)
		a[i - 1] = (float)1 / ((ulong)i * i);
}

void fill_mixed(float *a, int n)
{
	int i;
	for (i = 0; i < n; i += 2)
		a[i] = (float)1 / ((ulong)(i + 1) * (i + 1));
	for (i = 1; i < n; i += 2)
		a[i] = (float)1 / ((ulong)(i + 1) * (i + 1));
}

int main()
{
	int n;
	float *a = NULL;
	scanf("%d", &n);
	a = (float *)malloc(n * sizeof(float));
	if (!a)
		return -1;
	fill_direct(a, n);
	printf("Kahan: %.5e\n", ideal - kahan_sum(a, n));
	printf("Direct: %.5e\n", ideal - direct_sum(a, n));
	printf("Reverse: %.5e\n", ideal - reverse_sum(a, n));
	free(a);
	return 0;
}
