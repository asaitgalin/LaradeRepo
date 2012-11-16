#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_brackets(const char *s)
{
	int balance = 0;
	while (*s != '\0')
	{
		if (*s == '(')
			++balance;
		else if (*s == ')')
			--balance;
		if (balance < 0)
			return 0;
		++s;
	}
	return (balance == 0);
}

int substr(const char *s, const char *p)
{
	int i = 0, j;
	int len = strlen(p);
	while (s[i] != '\0')
	{
		j = 0;
		while(s[i + j] == p[j] && s[i + j])
			++j;
		if (j == len)
			return i;
		++i;
	}
	return -1;
}

int main()
{
	char buf[256];
	char sub[256];
	gets(buf);
	gets(sub);
	printf("%d\n", substr(buf, sub));
	return 0;
}