#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

char ans[121][121][121];
int lenans[121][121];
int minper[121][121];


int main(){
	//freopen("input.txt","r",stdin);
	string str, bufstr, bufstr1;
	cin >> str;
	int strlen = str.length();
	char symb;

	for (int len = 2; len <= strlen; ++len)
	{
		for (int pos = 1; pos <= strlen - len+1; ++pos)
		{
			for (int per = 1; per <= len; per++)
			{
				if (len % per == 0)
				{
					bufstr.clear();
					bufstr.append(str,pos-1+per,len-per);
					bufstr.append(str,pos-1,per);
					bufstr1.clear();
					bufstr1.append(str,pos-1,len);
					if (bufstr == bufstr1) 
					{
						minper[len][pos] = per;
						break;
					}
				}
			}
		}
	}

	for (int pos = 1; pos <= strlen; ++pos)
	{
		ans[1][pos][1] = str[pos-1];
		lenans[1][pos] = 1;
	}

	for (int len = 2; len <=strlen; ++len)
	{
		for (int pos=1; pos <= strlen-len+1; ++pos)
		{
			if ( (len>3) && (minper[len][pos] < len) && !( (len==4) && (minper[len][pos] == 2)  ) )
			{
				if (len / minper[len][pos] == 100) 
				{
					cout << "100(" << str[0] << ")"; 
					return 0;
				}

				if ((len / minper[len][pos]) > 9) 
				{
					symb = (len / minper[len][pos]) / 10 + '0';
					ans[len][pos][1] = symb;
					symb = (len / minper[len][pos]) % 10 + '0';
					ans[len][pos][2] = symb;
					ans[len][pos][3] = '(';

					for (int i = 1; i <= lenans[minper[len][pos]][pos]; ++i)
						ans[len][pos][3+i] = ans[minper[len][pos]][pos][i];
					ans[len][pos][4+lenans[minper[len][pos]][pos]] = ')';
					lenans[len][pos] = 4 + lenans[minper[len][pos]][pos];
					
					/*
					for (int i=1; i<=minper[len][pos]; ++i)
						ans[len][pos][3+i]=str[pos+i-2];
					ans[len][pos][4+minper[len][pos]]=')';
					lenans[len][pos]=4+minper[len][pos];*/

				}
				else 
				{
					symb = (len/minper[len][pos]) + '0';
					ans[len][pos][1] = symb;
					ans[len][pos][2] = '(';

					for (int i = 1; i <= lenans[minper[len][pos]][pos]; ++i)
						ans[len][pos][2+i] = ans[minper[len][pos]][pos][i];
					ans[len][pos][3+lenans[minper[len][pos]][pos]] = ')';
					lenans[len][pos] = 3+lenans[minper[len][pos]][pos];

					/*
					for (int i=1; i<=minper[len][pos]; ++i)
						ans[len][pos][2+i]=str[pos+i-2];
					ans[len][pos][3+minper[len][pos]]=')';
					lenans[len][pos]=3+minper[len][pos];*/
				}
			}
			else 
			{
				int min = 1;
				for (int i = 2;i < len; ++i)
				{
					if (lenans[i][pos] + lenans[len-i][i+pos] < lenans[min][pos] + lenans[len-min][min+pos])
						min = i;
				}

				lenans[len][pos] = lenans[min][pos] + lenans[len-min][min+pos];
				for (int i = 1;i <= lenans[min][pos]; ++i)
					ans[len][pos][i] = ans[min][pos][i];
				for (int i = 1;i <= lenans[len-min][min+pos]; ++i)
					ans[len][pos][i + lenans[min][pos]] = ans[len-min][min+pos][i];
			}
		}
	}
	for (int i = 1; i <= lenans[strlen][1]; ++i)
		cout << ans[strlen][1][i];

	return 0;
}