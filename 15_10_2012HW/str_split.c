#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my_vec.h"

const char test_str[] = "String  split works  fine!";
const char test_delim[] = "  ";

char** split(const char *str, const char *delim)
{
	int cursor = 0, i, dindex;
	int substr_c = 0;
	char **res = NULL;
	my_vec *v = NULL;
	int dlen = strlen(delim);
	v = v_create_2();
	if (!v) return NULL;
	while(str[cursor] != '\0')
	{
		while(str[cursor] != delim[0] && str[cursor] != '\0')
			cursor++;
		if (str[cursor] == '\0') 
		{
			v_pushback(v, cursor - 1);
			break;
		}
		dindex = 0;
		while(str[cursor] == delim[dindex])
		{
			++cursor;
			++dindex; 
		}
		if (dindex == dlen)
			v_pushback(v, cursor - dindex - 1);
	}
	res = (char **)malloc((v_size(v) + 1) * sizeof(char *));
	for (i = 0; i < v_size(v); ++i)
	{
		int len = (i == 0) ? v_at(v, i) + 1 : v_at(v, i) - v_at(v, i - 1) - dlen;
		res[i] = (char *)malloc((len + 1) * sizeof(char));
		strncpy(res[i], &str[v_at(v, i) - len + 1], len);
		res[i][len] = '\0';
	}
	res[v_size(v)] = NULL;
	v_free(v);
	return res;
}

void delete_string_array(char **str)
{
	int i = 0;
	while(str[i] != NULL)
		free(str[i++]);
	free(str);
}

int main()
{
	char **substr = NULL;
	int i = 0;
	substr = split(test_str, test_delim);
	while (substr[i] != NULL)
		printf("%s\n", substr[i++]); 
	delete_string_array(substr);
	return 0;
}