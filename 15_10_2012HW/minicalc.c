#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT(x) printf("%d\n", x);

const char *welcome_str = "Welcome to Mini Calculator!\n"\
						  "Type \"help\" to get list of supported commands";

const char *help_str = "Supported commands:\n\n"
	                   "add <arg1> <arg2>\n"
	                   "Prints arg1 + arg2\n\n"
	                   "sub <arg1> <arg2>\n"
	                   "Prints arg1 - arg2\n\n"
	                   "mult <arg1> <arg2>\n"
	                   "Prints arg1 * arg2\n\n"
					   "div <arg1> <arg2>\n"
					   "Prints arg1 / arg2\n\n"
					   "mod <arg1> <arg2>\n"
					   "Prints arg1 mod arg2\n\n"
					   "fdig <arg1>\n"
					   "Prints first digit of arg1\n\n"
					   "quit\n"
					   "Terminates this application\n\n"
					   "Warning! All arguments must be integers!";

const char *err_str = "Wrong syntax. See help";
const char *ediv_zero_str = "Error! Division by zero!";

enum tOperations 
{
	OP_ADD = 0,
	OP_SUB, 
	OP_MULT,
	OP_DIV,
	OP_MOD,
	OP_FDIG
};

int get_two_arg(char *data, int *a, int *b)
{
	if (data)
		if (sscanf(data, "%d%d", a, b) == 2)
			return 1;
	return 0;
}

void do_operation(char *args, int op)
{
	int a, b;
	if (!args)
	{
		printf("%s\n", err_str);
		return;
	}
	if (op == OP_FDIG)
		if (sscanf(args, "%d", &a) == 1)
		{
			while(a > 10)
				a /= 10;
			printf("%d\n", a);
			return;
		}
		else
			printf("%s\n", err_str);

	if (!get_two_arg(args, &a, &b))
	{
		printf("%s\n", err_str);
		return;
	}
	switch(op)
	{
	case OP_ADD:
		PRINT(a + b);
		break;
	case OP_SUB:
		PRINT(a - b);
		break;
	case OP_MULT:
		PRINT(a * b);
		break;
	case OP_DIV:
		{
			if (b == 0)
			{
				printf("%s\n", ediv_zero_str);
				return;
			}
			PRINT(a / b);
			break;
		}
	case OP_MOD:
		{
			if (b == 0)
			{
				printf("%s\n", ediv_zero_str);
				return;
			}
			PRINT(a % b);
			break;
		}
	}
}

int main()
{
	char buf[256];
	char *cmd = NULL, *args = NULL;
	printf("%s\n", welcome_str);
	while(1)
	{
		printf(">");
		fgets(buf, sizeof(buf), stdin);
		cmd = strtok(buf, " \n");
		args = strtok(NULL, "\n");
		if (!cmd)
			continue;
		if (!strcmp(cmd, "quit"))
			break;
		else if (!strcmp(cmd, "help"))
			printf("%s\n", help_str); 
		else if (!strcmp(cmd, "add"))
			do_operation(args, OP_ADD);
		else if (!strcmp(cmd, "sub"))
			do_operation(args, OP_SUB);
		else if (!strcmp(cmd, "mult"))
			do_operation(args, OP_MULT);
		else if (!strcmp(cmd, "div"))
			do_operation(args, OP_DIV);
		else if (!strcmp(cmd, "mod"))
			do_operation(args, OP_MOD);
		else if (!strcmp(cmd, "fdig"))
			do_operation(args, OP_FDIG);
		else
			printf("Command \"%s\" not found\n", cmd);
	}
	return 0;
}