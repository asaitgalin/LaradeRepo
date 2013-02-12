#include <iostream>

using namespace std;

int input[100][500];
long long result[100][500];
int from[100][500];
int answer[500000];

int main()
{
	int n, m;
	cin >> m >> n;
	for (int i=0; i<m; i++) 
		for (int j=0; j<n; j++) 
			cin >> input[i][j];

	for (int j=0; j<n; j++)
	{
		from[0][j]=-1;
		result[0][j]=input[0][j];
	}

	for (int i=1; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{
			if ( (result[i][j] == 0) || (result[i][j] > result[i-1][j] + input[i][j]) )
			{
				from[i][j] = j;
				result[i][j] = result[i-1][j] + input[i][j];
			}

			int k=j;
			while ( (k > 0) && (result[i][k-1] == 0) || (result[i][k-1] > result[i][k] + input[i][k-1]) )
			{
				from[i][k-1] = k;
				result[i][k-1] = result[i][k] + input[i][k-1];
				--k;
			}

			k = j;
			while ( (k < n-1) && (result[i][k+1] == 0) || (result[i][k+1] > result[i][k] + input[i][k+1]) )
			{
				from[i][k+1] = k;
				result[i][k+1] = result[i][k] + input[i][k+1];
				++k;
			}
		}
	}
	int min = 0;
	for (int j = 1;j < n; j++)
		if (result[m-1][j] < result[m-1][min])
			min = j;
	answer[0] = min;
	int num = 0;
	int x = m-1;
	int y = min;
	while (from[x][y] != -1)
	{
		++num;
		answer[num] = from[x][y];
		if (from[x][y] == y) 
			--x;
		else 
			if (from[x][y] < y) 
				--y;
			else if (from[x][y]>y) 
				++y;
	}

	for (int i = num; i >= 0; i--)
		cout << answer[i]+1 << ' ';

	return 0;
}