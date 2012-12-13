#include <iostream>
#include <string>


long long a[105][32];

int main(){
	int n;
	std::cin >> n; // Ввод
	std::string st;
	std::cin >> st; // Ввод
	int slen=st.length();
	if (slen==1) 
	{
		std::cout << 1 << std::endl; 
		return 0; 
	}; // Если подстрока состоит из одного символа, то не содержит ее только нулевая строка. Выводим ответ и выходим

	int petr = 1; //Делаем маску. А - 0, B - 1
	for(int i = 0; i <= slen-1; ++i)
	{
		petr = petr << 1;
		if (st[i] == 'B') 
			++petr;
	}
	
	for(int i = 1; i < 10; ++i) //searching values for 1 to 9
	{
		for(int s = 0; s < 1 << i; ++s)
			for(int mask = (1 << (slen-1)); mask < (1 << slen); ++mask)
			{
				int q = 1;
				for(int j=0; j < (i >> 1); ++j)
				{
					int mask1 = 1 << j;
					int mask2 = 1 << (i-j-1);
					if ( ((s & mask1)*(s & mask2) == 0) && ((s & mask1) != (s & mask2)) ) 
						q = 0;
				}
				if(i < slen-1) 
					q = 0;
				if((s >> (i-slen+1)) + (1 << (slen-1)) != mask) 
					q = 0;
				
				for (int j = 0; j < (i-slen+1); ++j)
					if ( ( ( (s >> j) & ((1 << slen)-1) ) + (1 << slen) ) == petr) 
						q = 0;
				
				a[i][mask] += q;
			}
	}

	for (int i = 10; i <= n; ++i) //dinamical algorithmization if n>9;
		for (int mask = (1 << (slen-1)); mask < (1 << slen); ++mask){
			int revmask = 0;
			for (int j = 1; j < slen; ++j){ 
				revmask = revmask << 1;
				if ( (mask >> j) << j != (mask >> (j-1)) << (j-1) ) 
					++revmask;
			}
			if  ( (mask << 1 != petr) && (((1 << slen) + revmask) != petr) ) 
				a[i][mask] += a[i-2][ ( ( mask & ( (1 << (slen-2)) -1 ) ) << 1) + (1 << (slen-1)) ];
			
			if  ( ( (mask << 1) +1 != petr) && (((1 << slen) + (1 << (slen-1)) + revmask) != petr) ) 
				a[i][mask] += a[i-2][ ( ( mask & ( (1<<(slen-2)) -1 ) ) << 1) + (1 << (slen-1)) + 1];
		}
	
	long long answer = 0; //generating answer
	for (int mask = (1 << (slen-1)); mask < (1 << slen); ++mask)
		answer += a[n][mask];

	std::cout << answer << std::endl; //output
	return 0;
	}