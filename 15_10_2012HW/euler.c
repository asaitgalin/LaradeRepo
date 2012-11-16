#include <stdio.h>
#include <stdlib.h>

int euler_func(int n) 
{
	int i;
	int res = n;
	for (i = 2; i*i <= n; ++i)
		if (n % i == 0) 
		{
			while (n % i == 0)
				n /= i;
			res -= res / i;
		}
	if (n > 1)
		res -= res / n;
	return res;
}

int main()
{
	printf("%d\n", euler_func(95));
}